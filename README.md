Osquery tests

create library
-----------------
cd create_lib
cmake .
make
(This will create <library>.a in the same folder)
use the command "ar -t <library>.a" to list all object files in <library>.a


Compile and run client program
------------------------------
cd client
cmake .
make
./client

(prints content of routes table in json format)

