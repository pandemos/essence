/* Essence Board Support Package, POSIX */
#include "qpc.h"
#include "bsp.h"

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

/*..........................................................................*/
void Q_onAssert(char const *module, int loc) {
    (void)module;
    (void)loc;
    QS_ASSERTION(module, loc, (uint32_t)10000U); /* report assertion to QS */
    fprintf(stderr, "Assertion failed in %s, location %d", module, loc);
    exit(-1);
}
