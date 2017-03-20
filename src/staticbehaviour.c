// Active Object Source
#include "qpc.h"
#include "staticbehaviour.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} StaticBehaviour;

static StaticBehaviour l_staticbehaviour;

QActive * const AO_StaticBehaviour = &l_staticbehaviour.super;

// States
static QState StaticBehaviour_initial(StaticBehaviour * const me, QEvt const * const e);
static QState StaticBehaviour_active(StaticBehaviour * const me, QEvt const * const e);

void StaticBehaviour_ctor(void) {
    StaticBehaviour * const me = &l_staticbehaviour;
    QActive_ctor(&me->super, Q_STATE_CAST(&StaticBehaviour_initial));
}

QState StaticBehaviour_initial(StaticBehaviour * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_staticbehaviour);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&StaticBehaviour_initial);
    QS_FUN_DICTIONARY(&StaticBehaviour_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[StaticBehaviour] Initialized\n");
    
    return Q_TRAN(&StaticBehaviour_active);
}

QState StaticBehaviour_active(StaticBehaviour * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            status = Q_HANDLED();
        }
        default: {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status;
}
        
