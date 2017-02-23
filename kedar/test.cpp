// Copyright 2004-present Facebook. All Rights Reserved.

#include <ctime>
#include <osquery/tables.h>
#include <osquery/sql.h>

#include "osquery/sql/sqlite_util.h"

namespace osquery {
namespace tables {

QueryData genTest(QueryContext &context) {
  Row r;
  QueryData results;
  auto dbc = osquery::SQLiteDBManager::get();

  time_t _time = time(0);
  struct tm* now = localtime(&_time);

  r["hour"] = INTEGER(now->tm_hour);
  r["minutes"] = INTEGER(now->tm_min);
  r["seconds"] = INTEGER(now->tm_sec);

  results.push_back(r);
  auto status = osquery::queryInternal("select * from routes;", results, dbc->db());
  dbc->clearAffectedTables();
  return results;
}
}
}
