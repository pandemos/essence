// Active Object Source
#include "qpc.h"
#include "priorityqueuebehaviour.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} PriorityQueueBehaviour;

static PriorityQueueBehaviour l_priorityqueuebehaviour;

QActive * const AO_PriorityQueueBehaviour = &l_priorityqueuebehaviour.super;

// States
static QState PriorityQueueBehaviour_initial(PriorityQueueBehaviour * const me, QEvt const * const e);
static QState PriorityQueueBehaviour_active(PriorityQueueBehaviour * const me, QEvt const * const e);

void PriorityQueueBehaviour_ctor(void) {
    PriorityQueueBehaviour * const me = &l_priorityqueuebehaviour;
    QActive_ctor(&me->super, Q_STATE_CAST(&PriorityQueueBehaviour_initial));
}

QState PriorityQueueBehaviour_initial(PriorityQueueBehaviour * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_priorityqueuebehaviour);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&PriorityQueueBehaviour_initial);
    QS_FUN_DICTIONARY(&PriorityQueueBehaviour_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[PriorityQueueBehaviour] Initialized\n");
    
    return Q_TRAN(&PriorityQueueBehaviour_active);
}

QState PriorityQueueBehaviour_active(PriorityQueueBehaviour * const me, QEvt const * const e) {
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
        
