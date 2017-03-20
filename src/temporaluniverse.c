// Active Object Source
#include "qpc.h"
#include "temporaluniverse.h"
#include "signals.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;

    QTimeEvt hourEvt;
    QTimeEvt dayEvt;
    QTimeEvt weekEvt;
    QTimeEvt monthEvt;
    QTimeEvt yearEvt;
} TemporalUniverse;

static TemporalUniverse l_temporaluniverse;

QActive * const AO_TemporalUniverse = &l_temporaluniverse.super;

// States
static QState TemporalUniverse_initial(TemporalUniverse * const me, QEvt const * const e);
static QState TemporalUniverse_active(TemporalUniverse * const me, QEvt const * const e);

void TemporalUniverse_ctor(void) {
    TemporalUniverse * const me = &l_temporaluniverse;
    QActive_ctor(&me->super, Q_STATE_CAST(&TemporalUniverse_initial));
    QTimeEvt_ctorX(&me->hourEvt, &me->super, HOUR_ELAPSED, 0U);
    QTimeEvt_ctorX(&me->dayEvt, &me->super, DAY_ELAPSED, 0U);
    QTimeEvt_ctorX(&me->weekEvt, &me->super, WEEK_ELAPSED, 0U);
    QTimeEvt_ctorX(&me->monthEvt, &me->super, MONTH_ELAPSED, 0U);
    QTimeEvt_ctorX(&me->yearEvt, &me->super, YEAR_ELAPSED, 0U);
}

QState TemporalUniverse_initial(TemporalUniverse * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_temporaluniverse);
    QS_OBJ_DICTIONARY(&l_temporaluniverse.hourEvt);
    QS_OBJ_DICTIONARY(&l_temporaluniverse.dayEvt);
    QS_OBJ_DICTIONARY(&l_temporaluniverse.weekEvt);
    QS_OBJ_DICTIONARY(&l_temporaluniverse.monthEvt);
    QS_OBJ_DICTIONARY(&l_temporaluniverse.yearEvt);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&TemporalUniverse_initial);
    QS_FUN_DICTIONARY(&TemporalUniverse_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    QS_SIG_DICTIONARY(HOUR_ELAPSED, (void *)0);
    QS_SIG_DICTIONARY(DAY_ELAPSED, (void *)0);
    QS_SIG_DICTIONARY(WEEK_ELAPSED, (void *)0);
    QS_SIG_DICTIONARY(MONTH_ELAPSED, (void *)0);
    QS_SIG_DICTIONARY(YEAR_ELAPSED, (void *)0);
    
    printf("[TemporalUniverse] Initialized\n");
    
    return Q_TRAN(&TemporalUniverse_active);
}

QState TemporalUniverse_active(TemporalUniverse * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	QTimeEvt_armX(&me->hourEvt, BSP_TICKS_PER_SEC, BSP_TICKS_PER_SEC);
			QTimeEvt_armX(&me->dayEvt, DAY_TICKS, DAY_TICKS);
			QTimeEvt_armX(&me->weekEvt, WEEK_TICKS, WEEK_TICKS);
			QTimeEvt_armX(&me->monthEvt, MONTH_TICKS, MONTH_TICKS);
			QTimeEvt_armX(&me->yearEvt, YEAR_TICKS, YEAR_TICKS);
            status = Q_HANDLED();
            break;
        }
        case HOUR_ELAPSED: {
        	QEvent* pe = Q_NEW(QEvent, HOUR_ELAPSED);
			QF_PUBLISH((QEvent *)pe, me);
        	status = Q_HANDLED();
        	break;
        }
        case DAY_ELAPSED: {
        	QEvent* pe = Q_NEW(QEvent, DAY_ELAPSED);
			QF_PUBLISH((QEvent *)pe, me);
        	status = Q_HANDLED();
        	break;
        }
        case WEEK_ELAPSED: {
        	QEvent* pe = Q_NEW(QEvent, WEEK_ELAPSED);
			QF_PUBLISH((QEvent *)pe, me);
        	status = Q_HANDLED();
        	break;
        }
        case MONTH_ELAPSED: {
        	QEvent* pe = Q_NEW(QEvent, MONTH_ELAPSED);
			QF_PUBLISH((QEvent *)pe, me);
        	status = Q_HANDLED();
        	break;
        }
        case YEAR_ELAPSED: {
        	QEvent* pe = Q_NEW(QEvent, YEAR_ELAPSED);
			QF_PUBLISH((QEvent *)pe, me);
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
        
