// Active Object Source
#include "qpc.h"
#include "input.h"
#include "bsp.h"

#include "signals.h"

//Q_DEFINE_THIS_FILE

#define INPUT_BUFFER_SIZE 512

typedef struct {
    QActive super;
} Input;

static Input l_input;

QActive * const AO_Input = &l_input.super;

// States
static QState Input_initial(Input * const me, QEvt const * const e);
static QState Input_active(Input * const me, QEvt const * const e);

void Input_ctor(void) {
    Input * const me = &l_input;
    QActive_ctor(&me->super, Q_STATE_CAST(&Input_initial));
}

QState Input_initial(Input * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_input);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&Input_initial);
    QS_FUN_DICTIONARY(&Input_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[Input] Initialized\n");
    
    return Q_TRAN(&Input_active);
}

QState Input_active(Input * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	QActive_subscribe(&me->super, QUIT);
            status = Q_HANDLED();
            break;
        }
        case QUIT: {
        	BSP_deactivate_ui();
        	BSP_data_deactivate();
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
        
