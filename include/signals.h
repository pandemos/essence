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

	CREATE_VESSEL,
	CREATE_VESSEL_SUCCESSFUL,
	CREATE_VESSEL_FAILED,
	DESTROY_VESSEL,
	DESTROY_VESSEL_SUCCESSFUL,
	DESTROY_VESSEL_FAILED,
	MOVE_VESSEL,

    MAX_PUB_SIG,          /* the last published signal */
    MAX_SIG               /* the last signal */
};

enum UiSignals {
	UI_LOGIN = 100,
	UI_CHARACTER_CREATE,
	UI_CHARACTER_SELECT,
	UI_IN_GAME
};

typedef struct KeyPressedTag {
	QEvt super;

	char key;
} KeyPressedEvt;

typedef struct LoginTag {
	QEvt super;

	size_t username_size;
	char* username;

	size_t password_size;
	char* password;
} LoginEvt;

typedef struct UserTag {
	QEvt super;

	unsigned int user_id;

	size_t username_size;
	char* username;

	size_t password_size;
	char* password;

	size_t n_characters;
} UserEvt;

typedef struct CreateVesselTag {

	unsigned int vessel_id;
	unsigned int x;
	unsigned int y;
	unsigned int z;

} CreateVesselEvt;

typedef struct DestroyVesselTag {

	unsigned int vessel_id;

} DestroyVesselEvt;

typedef struct VesselHandleTag {

	void* vessel_handle;

} VesselHandleEvt;

typedef struct MoveVesselTag {

	void* vessel_handle;
	unsigned int x;
	unsigned int y;
	unsigned int z;

} MoveVesselEvt;

#endif /* signals_h */
