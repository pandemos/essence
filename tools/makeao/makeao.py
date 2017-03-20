#!/usr/bin/python
# Generate the header and source files for a Quantum Framework active object

import sys

def write_ao_header(path, name):
    name_lower = name.lower()
    with open(path+'/'+name_lower+'.h', 'w') as fi:
        fi.write("""// Active Object Header
#ifndef {name_lower}_h
#define {name_lower}_h

#include "signals.h"

void {name}_ctor(void);
extern QActive * const AO_{name};

#endif /* {name_lower}_h */
        """.format(name=name, 
                   name_lower=name_lower, 
                   path=path))


def write_ao_source(path, name):
    name_lower = name.lower()
    with open(path+'/'+name_lower+'.c', 'w') as fi:
        fi.write("""// Active Object Source
#include "qpc.h"
#include "{name_lower}.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {{
    QActive super;
}} {name};

static {name} l_{name_lower};

QActive * const AO_{name} = &l_{name_lower}.super;

// States
static QState {name}_initial({name} * const me, QEvt const * const e);
static QState {name}_active({name} * const me, QEvt const * const e);

void {name}_ctor(void) {{
    {name} * const me = &l_{name_lower};
    QActive_ctor(&me->super, Q_STATE_CAST(&{name}_initial));
}}

QState {name}_initial({name} * const me, QEvt const * const e) {{
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_{name_lower});
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&{name}_initial);
    QS_FUN_DICTIONARY(&{name}_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[{name}] Initialized\\n");
    
    return Q_TRAN(&{name}_active);
}}

QState {name}_active({name} * const me, QEvt const * const e) {{
    QState status;
    switch (e->sig) {{
        case Q_ENTRY_SIG: {{
            status = Q_HANDLED();
            break;
        }}
        default: {{
            status = Q_SUPER(&QHsm_top);
            break;
        }}
    }}
    return status;
}}
        """.format(name=name,
                   name_lower=name_lower,
                   path=path))

def print_ao_init(name):
    print ("""#include "{name_lower}.h"

static QEvt const *l_{name_lower}QSto[10];

{name}_ctor();
QACTIVE_START(AO_{name},
              1U, /* This must be a unique QP priority ID */
              l_{name_lower}QSto,
              Q_DIM(l_{name_lower}QSto),
              (void *)0,
              0U,
              (QEvt*)0);
    """.format(name=name, name_lower=name.lower()))

def main(args):
    if len(args) < 4:
        print ("Usage: makeao.py header_path source_path actor_name\nActor name should be Pascal case if desired.")
        exit(1)
    header_path = args[1]
    source_path = args[2]
    actor_name = args[3]
    
    write_ao_header(header_path, actor_name)
    write_ao_source(source_path, actor_name)
    print_ao_init(actor_name)
      

if __name__ == '__main__':
    main(sys.argv)