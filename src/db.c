#include "db.h"

#include "qpc.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

void db_deactivate(sqlite3* db_ptr) {
	sqlite3_close(db_ptr);
}

void db_init(const char* filepath, sqlite3** db_ptr) {
	int rc = sqlite3_open_v2(filepath, db_ptr, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
	if (rc) {
		printf("Failed to open db\n");
		db_deactivate(db_ptr);
	}
	Q_ASSERT(rc == 0);
}

void db_error(int rc) {
	if (rc) {
		printf("SQL error: %d\n", rc);
	}
	Q_ASSERT(rc == 0);
}

int callback(void* arg, int argc, char** argv, char** colName) {
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\t", colName[i], argv[i] ? : "NULL");
	}
	printf("\n");
	return 0;
}

void db_query(sqlite3* db_ptr, char* query) {
	char* errmsg = 0;
	db_error(sqlite3_exec(db_ptr, query, callback, 0, &errmsg));

	if (errmsg) {
		sqlite3_free(errmsg);
	}
}
