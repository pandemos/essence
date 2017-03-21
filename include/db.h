#ifndef db_h
#define db_h

#include <sqlite3.h>

void db_init(const char* filepath, sqlite3** db_ptr);
void db_deactivate(sqlite3* db_ptr);
void db_query(sqlite3* db_ptr, char* query);

#endif
