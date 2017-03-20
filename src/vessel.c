// Active Object Source
#include "qpc.h"
#include "vessel.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} Vessel;

static Vessel l_vessel;

QActive * const AO_Vessel = &l_vessel.super;

// States
static QState Vessel_initial(Vessel * const me, QEvt const * const e);
static QState Vessel_active(Vessel * const me, QEvt const * const e);

void Vessel_ctor(void) {
    Vessel * const me = &l_vessel;
    QActive_ctor(&me->super, Q_STATE_CAST(&Vessel_initial));
}

QState Vessel_initial(Vessel * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_vessel);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&Vessel_initial);
    QS_FUN_DICTIONARY(&Vessel_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[Vessel] Initialized\n");
    
    return Q_TRAN(&Vessel_active);
}

QState Vessel_active(Vessel * const me, QEvt const * const e) {
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
        
