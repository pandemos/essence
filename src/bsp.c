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
    struct timeval timeout = { 0, 0 }; /* timeout for select() */
    fd_set con;               /* FD set representing the console */

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

void* data_ptr;

void BSP_data_init(void) {
	// One for each data type
	db_init("./data.sqlite", &data_ptr);
}

void BSP_data_deactivate(void) {
	db_deactivate(data_ptr);
}

void BSP_data_query(const char* query) {
	db_query(data_ptr, query);
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

