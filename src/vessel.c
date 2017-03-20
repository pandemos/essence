// Active Object Source
#include "qpc.h"
#include "vessel.h"
#include "signals.h"
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
        	printf("Subscribing\n");
        	QActive_subscribe(&me->super, HOUR_ELAPSED);
        	QActive_subscribe(&me->super, DAY_ELAPSED);
        	QActive_subscribe(&me->super, WEEK_ELAPSED);
        	QActive_subscribe(&me->super, MONTH_ELAPSED);
        	QActive_subscribe(&me->super, YEAR_ELAPSED);
        	printf("Subscribed\n");
            status = Q_HANDLED();
            break;
        }
        case HOUR_ELAPSED: {
			printf("[Vessel] An hour has elapsed\n");
			status = Q_HANDLED();
			break;
		}
        case DAY_ELAPSED: {
        	printf("[Vessel] A day has elapsed\n");
        	status = Q_HANDLED();
        	break;
        }
        case WEEK_ELAPSED: {
        	printf("[Vessel] A week has elapsed\n");
        	status = Q_HANDLED();
        	break;
        }
        case MONTH_ELAPSED: {
        	printf("[Vessel] A month has elapsed\n");
        	status = Q_HANDLED();
        	break;
        }
        case YEAR_ELAPSED: {
        	printf("[Vessel] A year has elapsed\n");
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
        
