#include <ctime>
#include <vector>
#include <map>
#include <sqlite3.h> 
#include <osquery/database.h>
#include "osquery/filesystem/fileops.h"
#include <boost/algorithm/string/trim.hpp>
#include "osquery/devtools/devtools.h"
#include <osquery/core.h>
#include <osquery/sql.h>
#include <osquery/flags.h>
#include <osquery/system.h>
#include <osquery/tables.h>
#include "osquery/sql/sqlite_util.h"
#include "osquery/sql/virtual_table.h"
using namespace std;
namespace osquery {



namespace tables {


    map<unsigned long int,string> GetStdoutFromCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    unsigned long int i=0;
    std::map<unsigned long int,string> output;
    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream)){
    if (fgets(buffer, max_buffer, stream) != NULL){
    output.insert(std::pair<unsigned long int,string>(i,buffer));
    i++;
    }
    }
    pclose(stream);
    }
    //for (auto it=output.begin(); it!=output.end(); ++it)
    //std::cout << it->first << " => " << it->second << '\n';
    return output;
    }





QueryData genTestLs(QueryContext& context) {
  QueryData results, results1;
    auto ls = GetStdoutFromCommand("ls");
  for (auto it=ls.begin(); it!=ls.end(); ++it){
    Row r;
    r["file"]= (it->second).erase((it->second).size() - 1);;
    results1.push_back(r);
  }
  

  return results1;


}

}

}
