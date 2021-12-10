#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

class XML_Parser
{
public:
    string read_file(void);
    XML_Parser(string file_data,vector<string> &XML_Vector, unsigned int &XML_Size);

};

#endif // XML_PARSER_H
