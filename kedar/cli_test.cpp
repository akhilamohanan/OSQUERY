 #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
#include <map>

    using namespace std;

    string GetStdoutFromCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    string str_op = "";
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream)){
            if (fgets(buffer, max_buffer, stream) != NULL){
                str_op += buffer;
            }
        }
        pclose(stream);
    }
    return str_op;
    }

string client(string table){
    string query = ("osqueryi 'select * from %s' --json", table);
    string output = GetStdoutFromCommand(query);

    cout << output << "\n###################";
    return output;
}

int main (int argc, char* argv[]){
    client(argv[0]);
    return 0;
}
