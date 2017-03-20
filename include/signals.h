#ifndef signals_h
#define signals_h

enum BlinkySignals {
    DUMMY_SIG = Q_USER_SIG,

	HOUR_ELAPSED,
	DAY_ELAPSED,
	WEEK_ELAPSED,
	MONTH_ELAPSED,
	YEAR_ELAPSED,

	KEY_PRESSED,

    MAX_PUB_SIG,          /* the last published signal */

    TIMEOUT_SIG,

    MAX_SIG               /* the last signal */
};

typedef struct KeyPressedTag {
	QEvt super;

	char key;
} KeyPressedEvt;

#endif /* signals_h */
