// Active Object Source
#include "qpc.h"
#include "user.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} User;

static User l_user;

QActive * const AO_User = &l_user.super;

// States
static QState User_initial(User * const me, QEvt const * const e);
static QState User_active(User * const me, QEvt const * const e);

void User_ctor(void) {
    User * const me = &l_user;
    QActive_ctor(&me->super, Q_STATE_CAST(&User_initial));
}

QState User_initial(User * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_user);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&User_initial);
    QS_FUN_DICTIONARY(&User_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[User] Initialized\n");

    return Q_TRAN(&User_active);
}

QState User_active(User * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
        	QActive_subscribe(&me->super, LOGIN);
            status = Q_HANDLED();
            break;
        }
        case LOGIN: {
        	printf("received login request\n");
        	LoginEvt* evt = Q_EVT_CAST(LoginEvt);
        	// TODO: Actually verify user
        	UserEvt* pe = Q_NEW(UserEvt, USER_VALID);
        	pe->user_id = 1U;
        	pe->n_characters = 0;
        	pe->password = evt->password;
        	pe->username = evt->username;
        	pe->username_size = 0;
        	pe->password_size = 0;
        	QF_PUBLISH((QEvent *)pe, me);

        	status = Q_HANDLED(); // TODO: Transition to a "user logged in" state.
        	break;
        }
        default: {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status;
}
        
