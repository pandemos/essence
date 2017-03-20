#ifndef signals_h
#define signals_h

#include "qpc.h"

enum Signals {
    DUMMY_SIG = Q_USER_SIG,

	HOUR_ELAPSED,
	DAY_ELAPSED,
	WEEK_ELAPSED,
	MONTH_ELAPSED,
	YEAR_ELAPSED,

	KEY_PRESSED,

	LOGIN,
	VERIFY_USER,
	USER_VALID,
	USER_INVALID,

	CREATE_CHARACTER,
	CHARACTER_CREATED,
	CHARACTER_CREATION_FAILED,
	ENTER_GAME,
	EXIT_GAME,

    MAX_PUB_SIG,          /* the last published signal */

    TIMEOUT_SIG,

    MAX_SIG               /* the last signal */
};

typedef struct KeyPressedTag {
	QEvt super;

	char key;
} KeyPressedEvt;

typedef struct LoginTag {
	QEvt super;

	int username_size;
	char* username;

	int password_size;
	char* password;
} LoginEvt;

typedef struct UserTag {
	QEvt super;

	int username_size;
	char* username;

	int password_size;
	char* password;

	int n_characters;
} UserEvt;

#endif /* signals_h */
