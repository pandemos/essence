// Active Object Source
#include "qpc.h"
#include "physicaluniverse.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} PhysicalUniverse;

static PhysicalUniverse l_physicaluniverse;

QActive * const AO_PhysicalUniverse = &l_physicaluniverse.super;

// States
static QState PhysicalUniverse_initial(PhysicalUniverse * const me, QEvt const * const e);
static QState PhysicalUniverse_active(PhysicalUniverse * const me, QEvt const * const e);

void PhysicalUniverse_ctor(void) {
    PhysicalUniverse * const me = &l_physicaluniverse;
    QActive_ctor(&me->super, Q_STATE_CAST(&PhysicalUniverse_initial));
}

QState PhysicalUniverse_initial(PhysicalUniverse * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_physicaluniverse);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&PhysicalUniverse_initial);
    QS_FUN_DICTIONARY(&PhysicalUniverse_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[PhysicalUniverse] Initialized\n");
    
    return Q_TRAN(&PhysicalUniverse_active);
}

QState PhysicalUniverse_active(PhysicalUniverse * const me, QEvt const * const e) {
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
        
