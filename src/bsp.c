/* Essence Board Support Package, POSIX */
#include "qpc.h"
#include "bsp.h"
#include "qassert.h"

#include "signals.h"

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

// TODO: This is the worst possible database
typedef struct {
	enum_t key;
	enum_t type;
	size_t value_size;
	void* value;
} Datum;
static size_t data_size;
static Datum data[512];

/*..........................................................................*/
void QF_onStartup(void) {     /* startup callback */
    struct termios tio;       /* modified terminal attributes */

    tcgetattr(0, &l_tsav);    /* save the current terminal attributes */void* const BSP_data_get(enum_t key) {

    }
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

    FD_ZERO(&con);
    FD_SET(0, &con);
    /* check if a console input is available, returns immediately */
    if (0 != select(1, &con, 0, 0, &timeout)) { /* any descriptor set? */
        char ch;
        read(0, &ch, 1);

        KeyPressedEvt* pe = Q_NEW(KeyPressedEvt, KEY_PRESSED);
        pe->key = ch;
        QF_PUBLISH((QEvent *)pe, 0);
    }
}
/*..........................................................................*/
void BSP_init() {
    printf("Essence\nQP version: %s\n"
           "Press ESC to quit...\n",
           QP_VERSION_STR);
}

void BSP_init_ui(void) {
	// TODO
}

void BSP_deactivate_ui(void) {
	// TODO
}

// Update the UI to show a particular screen
void BSP_show_screen(enum_t screen) {
	// TODO
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

// Forward-declare internals
Datum* get_data_obj_by_key(enum_t key);

void BSP_data_init(void) {
	// TODO: This should connect to or open the actual database
}

void BSP_data_deactivate(void) {
	// TODO: This should disconnect or close the actual database
}

int BSP_data_get_int(enum_t key) {
	Datum* datum = get_data_obj_by_key(key);
	Q_ASSERT(datum > 0 && datum->type == DATA_TYPE_INT);
	return (int)datum->value;
}
void BSP_data_set_int(enum_t key, int value) {
	Datum* datum = get_data_obj_by_key(key);
	if (datum == 0) {
		data[data_size].key = key;
		data[data_size].type = DATA_TYPE_INT;
		data[data_size].value_size = sizeof(int);
		data[data_size].value = (void*)value;
		datum = &data[data_size];
		data_size++;
	}
	data[data_size].value_size = sizeof(int);
	data[data_size].value = (void*)value;
}

int BSP_data_get_string(enum_t key, char* string_data) {
	Datum* datum = get_data_obj_by_key(key);
	Q_ASSERT(datum > 0 && datum->type == DATA_TYPE_STRING);
	string_data = (char*)datum->value;
	return (int)datum->value_size;
}

void BSP_data_set_string(enum_t key, size_t string_data_size, char* string_data) {
	Datum* datum = get_data_obj_by_key(key);
	if (datum == 0) {
		data[data_size].key = key;
		data[data_size].type = DATA_TYPE_STRING;
		datum = &data[data_size];
		data_size++;
	}
	data[data_size].value_size = string_data_size;
	data[data_size].value = (void*)string_data;
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

Datum* get_data_obj_by_key(enum_t key) {
	for (int i = 0; i < 512; i++) {
		if (data[i].key == key) {
			return &data[i];
		}
	}
	return (Datum*)0;
}
