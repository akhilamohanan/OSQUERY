#include <ctime>
#include <gflags/gflags.h>
#include <osquery/system.h>
#include <osquery/events.h>

#include <boost/algorithm/string/trim.hpp>
#include <osquery/sql.h>
#include <osquery/core.h>
#include <osquery/flags.h>
#include <osquery/system.h>
#include <osquery/tables.h>
using namespace std;
namespace osquery {

DECLARE_bool(utc);

namespace tables {







QueryData genDemousers(QueryContext& context) {

  auto uname = SQL("select username, directory from users;"); 
  if (uname.rows().size() > 0) {
    
      for (unsigned long int i=0; i<uname.rows().size(); i++ ){
      Row r;
      r["username"] = uname.rows()[i].at("username");
      r["directory"] = uname.rows()[i].at("directory");
      results.push_back(r);
      }
   } 


  return results;


}

}

}
