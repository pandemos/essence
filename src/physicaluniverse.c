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
        	QActive_subscribe(&me->super, ENTER_GAME);
        	QActive_subscribe(&me->super, EXIT_GAME);
        	QActive_subscribe(&me->super, CREATE_VESSEL);
        	QActive_subscribe(&me->super, DESTROY_VESSEL);
        	QActive_subscribe(&me->super, MOVE_VESSEL);
            status = Q_HANDLED();
            break;
        }
        case ENTER_GAME: {
        	CreateVesselEvt* evt = Q_EVT_CAST(CreateVesselEvt);
        	(void)evt;
        	status = Q_HANDLED();
        	break;
        }
        case EXIT_GAME: {
        	status = Q_HANDLED();
        	break;
        }
        case CREATE_VESSEL: {
        	CreateVesselEvt* evt = Q_EVT_CAST(CreateVesselEvt);
			(void)evt;
        	status = Q_HANDLED();
        	break;
        }
        case DESTROY_VESSEL: {
        	DestroyVesselEvt* evt = Q_EVT_CAST(DestroyVesselEvt);
        	(void)evt;
			status = Q_HANDLED();
			break;
		}
        case MOVE_VESSEL: {
        	MoveVesselEvt* evt = Q_EVT_CAST(MoveVesselEvt);
        	(void)evt;
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
        
