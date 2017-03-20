// Active Object Source
#include "qpc.h"
#include "temporaluniverse.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} TemporalUniverse;

static TemporalUniverse l_temporaluniverse;

QActive * const AO_TemporalUniverse = &l_temporaluniverse.super;

// States
static QState TemporalUniverse_initial(TemporalUniverse * const me, QEvt const * const e);
static QState TemporalUniverse_active(TemporalUniverse * const me, QEvt const * const e);

void TemporalUniverse_ctor(void) {
    TemporalUniverse * const me = &l_temporaluniverse;
    QActive_ctor(&me->super, Q_STATE_CAST(&TemporalUniverse_initial));
}

QState TemporalUniverse_initial(TemporalUniverse * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_temporaluniverse);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&TemporalUniverse_initial);
    QS_FUN_DICTIONARY(&TemporalUniverse_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[TemporalUniverse] Initialized\n");
    
    return Q_TRAN(&TemporalUniverse_active);
}

QState TemporalUniverse_active(TemporalUniverse * const me, QEvt const * const e) {
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
        
