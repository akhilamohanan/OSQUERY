#include <stdio.h>
#include <string.h>
#include <osquery/core.h>
//#include <osquery/extensions.h>
#include <osquery/flags.h>
#include <osquery/logger.h>
#include <osquery/system.h>
#include "osquery/core/process.h"
#include "osquery/core/utils.h"
#include "osquery/core/watcher.h"
#include "osquery/devtools/devtools.h"
#include "osquery/filesystem/fileops.h"
#include "osquery/sql/sqlite_util.h"
//#include "osquery/sql/sqlite_util.cpp"
#include <iostream>
//#include <boost/algorithm/string/predicate.hpp>
#include <osquery/database.h>
#include "osquery/sql/virtual_table.h"
using namespace osquery;
using namespace std;

string myjsonPrint(const QueryData& q) {
  string jsonString = "";
  jsonString += "[";
  //printf("[\n");
  for (size_t i = 0; i < q.size(); ++i) {
    std::string row_string;

    if (serializeRowJSON(q[i], row_string).ok()) {
      row_string.pop_back();
      jsonString += row_string.c_str();
      //printf("  %s", row_string.c_str());
      if (i < q.size() - 1) {
        jsonString += ",";
        //printf(",\n");
      }
    }
  }
  jsonString += "]";
  //printf("\n]\n");
  return jsonString;
}

int main(int argc, char *argv[]) {
      if(argc != 2) {
          cout << "Usage: queryi <table_name>\n";
          return 1;
      }
      osquery::Initializer runner(argc, argv, osquery::ToolType::SHELL);
      //runner.start();
      osquery::DatabasePlugin::setAllowOpen(true);
      osquery::RegistryFactory::get().setActive("database", "ephemeral");
      const std::string query = "select * from "+ string(argv[1]);
      cout << query;
      auto dbc = osquery::SQLiteDBManager::get();
      osquery::QueryData results;
      auto status = osquery::queryInternal(query, results, dbc->db());
      string response;
      response = myjsonPrint(results);
      cout << response;
      //runner.requestShutdown();
     return 0;
}
