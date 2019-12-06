#define _GNU_SOURCE

#define SQLITE_INLINE_MEMCPY 1
#define SQLITE_THREADSAFE 0
#define SQLITE_OMIT_LOAD_EXTENSION 1

#include <unistd.h>
#include <sys/mman.h>

#include "sqlite3.c"

#include "../lib/stdfuncs.inc.c"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  if (argc > 0) {
    // so that all relevant code would be instrumented
    write(2, argv[0], strlen(argv[0]));
    write(2, "\n", 1);
  }
  return 0;
}

// TODO test mixing of tags
int main(void)
{
  sqlite3 *db;
  char *zErrMsg = 0;

  sqlite3_open("test.db", &db);
  sqlite3_exec(db, "select name from test", callback, 0, &zErrMsg);

  char query[128];
  int qlen = read(0, query, sizeof(query));
  query[qlen] = '\0';
  sqlite3_exec(db, query, callback, 0, &zErrMsg);

  sqlite3_close(db);
  return 0;
}
