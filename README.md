Osquery tests

create library
-----------------
cd create_lib
cmake .
make

(This will create <library>.a in the same folder)


Compile and run client program
------------------------------
cd client
cmake .
make
./client

(prints content of routes table in json format)
