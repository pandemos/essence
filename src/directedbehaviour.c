// Active Object Source
#include "qpc.h"
#include "directedbehaviour.h"
#include "bsp.h"

#include "signals.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} DirectedBehaviour;

static DirectedBehaviour l_directedbehaviour;

QActive * const AO_DirectedBehaviour = &l_directedbehaviour.super;

// States
static QState DirectedBehaviour_initial(DirectedBehaviour * const me, QEvt const * const e);
static QState DirectedBehaviour_active(DirectedBehaviour * const me, QEvt const * const e);

void DirectedBehaviour_ctor(void) {
    DirectedBehaviour * const me = &l_directedbehaviour;
    QActive_ctor(&me->super, Q_STATE_CAST(&DirectedBehaviour_initial));
}

QState DirectedBehaviour_initial(DirectedBehaviour * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_directedbehaviour);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&DirectedBehaviour_initial);
    QS_FUN_DICTIONARY(&DirectedBehaviour_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[DirectedBehaviour] Initialized\n");
    
    return Q_TRAN(&DirectedBehaviour_active);
}

QState DirectedBehaviour_active(DirectedBehaviour * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            status = Q_HANDLED();
            break;
        }
        default: {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status;
}
        
