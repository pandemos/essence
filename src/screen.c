// Active Object Source
#include "qpc.h"
#include "screen.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} Screen;

static Screen l_screen;

QActive * const AO_Screen = &l_screen.super;

// States
static QState Screen_initial(Screen * const me, QEvt const * const e);
static QState Screen_active(Screen * const me, QEvt const * const e);

void Screen_ctor(void) {
    Screen * const me = &l_screen;
    QActive_ctor(&me->super, Q_STATE_CAST(&Screen_initial));
}

QState Screen_initial(Screen * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_screen);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&Screen_initial);
    QS_FUN_DICTIONARY(&Screen_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[Screen] Initialized\n");
    
    return Q_TRAN(&Screen_active);
}

QState Screen_active(Screen * const me, QEvt const * const e) {
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
        
