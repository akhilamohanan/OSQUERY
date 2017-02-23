#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <io.h>
#endif

#include <iostream>

#include <boost/algorithm/string/predicate.hpp>

#include <osquery/core.h>
#include <osquery/database.h>
#include <osquery/extensions.h>
#include <osquery/flags.h>
#include <osquery/logger.h>
#include <osquery/system.h>

#include "osquery/core/process.h"
#include "osquery/core/utils.h"
#include "osquery/core/watcher.h"
#include "osquery/devtools/devtools.h"
#include "osquery/filesystem/fileops.h"
#include "osquery/sql/sqlite_util.h"


using namespace osquery;
using namespace std;

string jsonReturn(const QueryData& q) {
  string json="[";
  for (size_t i = 0; i < q.size(); ++i) {
    std::string row_string;

    if (serializeRowJSON(q[i], row_string).ok()) {
      row_string.pop_back();
      json += row_string;
      if (i < q.size() - 1) {
       json += ",";
      }
    }
  }
  json += "]";
  return json;
}


string call_table(int argc, char* argv[]) {
      std::string query;
       osquery::Initializer runner(argc, argv, osquery::ToolType::SHELL);
       osquery::DatabasePlugin::setAllowOpen(true);
       osquery::RegistryFactory::get().setActive("database", "ephemeral");
      auto dbc = osquery::SQLiteDBManager::get();
      osquery::QueryData results;
      query = "select * from routes;";
      auto status = osquery::queryInternal(query, results, dbc->db()); 
      string output = jsonReturn(results);
      return output;     
}

