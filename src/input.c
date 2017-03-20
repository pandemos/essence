// Active Object Source
#include "qpc.h"
#include "input.h"
#include "bsp.h"

#include "signals.h"

//Q_DEFINE_THIS_FILE

#define INPUT_BUFFER_SIZE 512

typedef struct {
    QActive super;

    int input_buffer_index;
    char input_buffer[INPUT_BUFFER_SIZE];
} Input;

static Input l_input;

QActive * const AO_Input = &l_input.super;

// States
static QState Input_initial(Input * const me, QEvt const * const e);
static QState Input_active(Input * const me, QEvt const * const e);

void Input_ctor(void) {
    Input * const me = &l_input;

    // Initialize input buffer
    for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
    	me->input_buffer[i] = 0;
    }

    me->input_buffer_index = 0;

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
        	QActive_subscribe(&me->super, KEY_PRESSED);
            status = Q_HANDLED();
            break;
        }
        case KEY_PRESSED: {
        	KeyPressedEvt* evt = Q_EVT_CAST(KeyPressedEvt);
        	char key = evt->key;

        	if (key == '\33') {
        		QF_stop();
        	}
        	else if (key == '\n') {
        		// Enter, we should process what's been entered as a TODO
        		me->input_buffer[me->input_buffer_index] = '\0';
        		me->input_buffer_index++;
        		printf("%s\n", me->input_buffer);
        	    for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
        	    	me->input_buffer[i] = 0;
        	    }
        	    me->input_buffer_index = 0;
        	}
        	else {
        		me->input_buffer[me->input_buffer_index] = key;
        		me->input_buffer_index++;
        	}

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
        