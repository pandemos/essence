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
static QState Screen_login(Screen * const me, QEvt const * const e);
static QState Screen_character_create(Screen * const me, QEvt const * const e);
static QState Screen_character_select(Screen * const me, QEvt const * const e);
static QState Screen_in_game(Screen * const me, QEvt const * const e);

void Screen_ctor(void) {
    Screen * const me = &l_screen;
    QActive_ctor(&me->super, Q_STATE_CAST(&Screen_initial));
}

QState Screen_initial(Screen * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_screen);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&Screen_initial);
    QS_FUN_DICTIONARY(&Screen_login);
    QS_FUN_DICTIONARY(&Screen_character_create);
    QS_FUN_DICTIONARY(&Screen_character_select);
    QS_FUN_DICTIONARY(&Screen_in_game);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[Screen] Initialized\n");
    
    return Q_TRAN(&Screen_login);
}

QState Screen_login(Screen * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	printf("[Screen] Login\n");
        	BSP_show_screen(UI_LOGIN);
            status = Q_HANDLED();
            break;
        }
        case LOGIN: {
            UserEvt* pe = Q_NEW(UserEvt, VERIFY_USER);
            pe->username_size = 4;
            pe->username = "cat\0";
            pe->password_size = 4;
            pe->password = "cat\0";
            pe->n_characters = 0;
            QF_PUBLISH((QEvent *)pe, 0);
        	status = Q_HANDLED();
        	break;
        }
        case USER_VALID: {
        	UserEvt* pe = Q_EVT_CAST(UserEvt);
        	if (pe->n_characters == 0) {
        		status = Q_TRAN(&Screen_character_create);
        	}
        	else {
        		status = Q_TRAN(&Screen_character_select);
        	}
        	break;
        }
        case USER_INVALID: {
        	UserEvt* pe = Q_EVT_CAST(UserEvt);
        	(void)pe;
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

QState Screen_character_create(Screen * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	printf("[Screen] Character Creation\n");
        	BSP_show_screen(UI_CHARACTER_CREATE);
            status = Q_HANDLED();
            break;
        }
        case CHARACTER_CREATED: {
        	status = Q_TRAN(&Screen_character_select);
        	break;
        }
        case CHARACTER_CREATION_FAILED: {
        	UserEvt* pe = Q_EVT_CAST(UserEvt);
        	(void)pe;
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
QState Screen_character_select(Screen * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	printf("[Screen] Character Selection\n");
        	BSP_show_screen(UI_CHARACTER_SELECT);
            status = Q_HANDLED();
            break;
        }
        case ENTER_GAME: {
        	status = Q_TRAN(&Screen_in_game);
        	break;
        }
        default: {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status;
}
QState Screen_in_game(Screen * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	printf("[Screen] In Game\n");
        	BSP_show_screen(UI_IN_GAME);
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
