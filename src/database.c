// Active Object Source
#include "qpc.h"
#include "database.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

typedef struct {
    QActive super;
} Database;

static Database l_database;

QActive * const AO_Database = &l_database.super;

// States
static QState Database_initial(Database * const me, QEvt const * const e);
static QState Database_active(Database * const me, QEvt const * const e);

void Database_ctor(void) {
    Database * const me = &l_database;
    QActive_ctor(&me->super, Q_STATE_CAST(&Database_initial));
}

QState Database_initial(Database * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    
    QS_OBJ_DICTIONARY(&l_database);
    
    QS_FUN_DICTIONARY(&Qsm_top);
    QS_FUN_DICTIONARY(&Database_initial);
    QS_FUN_DICTIONARY(&Database_active);
    
    QS_SIG_DICTIONARY(DUMMY_SIG, (void *)0);
    
    printf("[Database] Initialized\n");
    
    return Q_TRAN(&Database_active);
}

QState Database_active(Database * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            status = Q_HANDLED();
            BSP_data_set_int(DATA_UNKNOWN, 42);
            int setting = -1;
            setting = BSP_data_get_int(DATA_UNKNOWN);
            printf("[DATABASE] Roundtrip success for setting: %d\n", setting);
            break;
        }
        default: {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status;
}
        
