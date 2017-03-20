// Active Object Source
#include "qpc.h"
#include "controlledbehaviour.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} ControlledBehaviour;

static ControlledBehaviour l_controlledbehaviour;

QActive * const AO_ControlledBehaviour = &l_controlledbehaviour.super;

// States
static QState ControlledBehaviour_initial(ControlledBehaviour * const me, QEvt const * const e);
static QState ControlledBehaviour_active(ControlledBehaviour * const me, QEvt const * const e);

void ControlledBehaviour_ctor(void) {
    ControlledBehaviour * const me = &l_controlledbehaviour;
    QActive_ctor(&me->super, Q_STATE_CAST(&ControlledBehaviour_initial));
}

QState ControlledBehaviour_initial(ControlledBehaviour * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_controlledbehaviour);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&ControlledBehaviour_initial);
    QS_FUN_DICTIONARY(&ControlledBehaviour_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[ControlledBehaviour] Initialized\n");
    
    return Q_TRAN(&ControlledBehaviour_active);
}

QState ControlledBehaviour_active(ControlledBehaviour * const me, QEvt const * const e) {
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
        
