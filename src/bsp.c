/* Essence Board Support Package, POSIX */
#include "qpc.h"
#include "bsp.h"
#include "qassert.h"

#include "signals.h"

#include "ui.h"
#include "db.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>      /* for memcpy() and memset() */
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

Q_DEFINE_THIS_FILE

#ifdef Q_SPY
    #error The Blinky example does not support the SPY build configuration
#endif /* Q_SPY */

/* Local objects -----------------------------------------------------------*/
static struct termios l_tsav; /* structure with saved terminal attributes */

static enum_t current_window;

/*..........................................................................*/
void QF_onStartup(void) {     /* startup callback */
    struct termios tio;       /* modified terminal attributes */

    tcgetattr(0, &l_tsav);    /* save the current terminal attributes */
    tcgetattr(0, &tio);       /* obtain the current terminal attributes */
    tio.c_lflag &= ~(ICANON | ECHO); /* disable the canonical mode & echo */
    tcsetattr(0, TCSANOW, &tio);  /* set the new attributes */

    QF_setTickRate(BSP_TICKS_PER_SEC); /* set the desired tick rate */
}
/*..........................................................................*/
void QF_onCleanup(void) {     /* cleanup callback */
    printf("\nBye! Bye!\n");
    tcsetattr(0, TCSANOW, &l_tsav);/* restore the saved terminal attributes */
}
/*..........................................................................*/
void QF_onClockTick(void) {

    QF_TICK_X(0U, (void *)0); /* process all QF time events at rate 0 */

    ui_tick(current_window);
}
/*..........................................................................*/
void BSP_init() {
    printf("Essence\nQP version: %s\n"
           "Press ESC to quit...\n",
           QP_VERSION_STR);

    BSP_init_ui();

    BSP_data_init();

    ModelUser user;
    user.user_id = 1;
    memcpy(user.username, "allison", sizeof("allison"));
    user.username_size = 7;
    memcpy(user.password, "changeme", sizeof("changeme"));
    user.password_size = 8;
    BSP_data_create_user(&user);

    user.user_id = 2;
	memcpy(user.username, "guest", sizeof("guest"));
	user.username_size = 5;
	memcpy(user.password, "guestpass", sizeof("guestpass"));
	user.password_size = 9;
	BSP_data_create_user(&user);

	BSP_data_refresh_users();

    ModelUser u2;
    ModelUser u3;

    BSP_data_get_user(1, &u2);
    printf("%d: %s\n", u2.user_id, u2.username);
    BSP_data_get_user(2, &u3);
    printf("%d: %s\n", u3.user_id, u3.username);
}

void BSP_init_ui(void) {
	ui();
}

void BSP_deactivate_ui(void) {
	ui_cleanup();
}

// Update the UI to show a particular screen
void BSP_show_screen(enum_t screen) {
	current_window = screen;
}

void BSP_set_character_data(UiCharacterData data) {
	// TODO
}

void BSP_set_user_data(UiUserData data) {
	// TODO
}

void BSP_set_in_game_data(UiInGameData data) {
	// TODO
}

void BSP_data_init(void) {
	// TODO: protobuf
}

void BSP_data_deactivate(void) {

}

void BSP_data_create_user(ModelUser* user) {
}

void BSP_data_refresh_users() {

}

void BSP_data_get_user(unsigned int user_id, ModelUser* user) {

}

void BSP_data_update_user(ModelUser* user) {

}

void BSP_data_delete_user(unsigned int user_id) {

}

void BSP_data_search_users(const char* col_to_search, const char* value) {

}

void BSP_data_user_exists(unsigned int user_id) {

}

void BSP_data_create_vessel(ModelVessel* vessel) {

}

void BSP_data_get_vessel(unsigned int vessel_id) {

}

void BSP_data_update_vessel(ModelVessel* vessel) {

}

void BSP_data_delete_vessel(unsigned int vessel_id) {

}

void BSP_data_search_vessels(const char* col_to_search, const char* value) {

}

void BSP_data_vessel_exists(unsigned int vessel_id) {

}

void BSP_data_set_user_vessel(unsigned int user_id, unsigned int vessel_id) {

}

void BSP_data_count_user_vessels(unsigned int user_id) {

}

void BSP_data_get_user_vessels(unsigned int user_id) {

}

void BSP_data_unset_user_vessel(unsigned int user_id, unsigned int vessel_id) {

}


/*..........................................................................*/
void Q_onAssert(char const *module, int loc) {
    (void)module;
    (void)loc;
    QS_ASSERTION(module, loc, (uint32_t)10000U); /* report assertion to QS */
    fprintf(stderr, "Assertion failed in %s, location %d", module, loc);
    exit(-1);
}

// Internals

