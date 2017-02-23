#include <stdio.h>
#include <string.h>
#include <iostream>
#include "test.h"
using namespace std;

int main(int argc, char* argv[])
{
   string s= call_table(argc, argv);
   cout<<s;   
   return 0;
}
