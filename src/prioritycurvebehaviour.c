// Active Object Source
#include "qpc.h"
#include "prioritycurvebehaviour.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} PriorityCurveBehaviour;

static PriorityCurveBehaviour l_prioritycurvebehaviour;

QActive * const AO_PriorityCurveBehaviour = &l_prioritycurvebehaviour.super;

// States
static QState PriorityCurveBehaviour_initial(PriorityCurveBehaviour * const me, QEvt const * const e);
static QState PriorityCurveBehaviour_active(PriorityCurveBehaviour * const me, QEvt const * const e);

void PriorityCurveBehaviour_ctor(void) {
    PriorityCurveBehaviour * const me = &l_prioritycurvebehaviour;
    QActive_ctor(&me->super, Q_STATE_CAST(&PriorityCurveBehaviour_initial));
}

QState PriorityCurveBehaviour_initial(PriorityCurveBehaviour * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_prioritycurvebehaviour);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&PriorityCurveBehaviour_initial);
    QS_FUN_DICTIONARY(&PriorityCurveBehaviour_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[PriorityCurveBehaviour] Initialized\n");
    
    return Q_TRAN(&PriorityCurveBehaviour_active);
}

QState PriorityCurveBehaviour_active(PriorityCurveBehaviour * const me, QEvt const * const e) {
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
        
