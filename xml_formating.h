#ifndef XML_FORMATING_H
#define XML_FORMATING_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

class XML_Formating
{
public:
    void indentation(vector<string> &space, int &Lineindex, int NumOfSpaces);    //store the indentaions of each line
    XML_Formating(vector<string> &OutputSpaces, vector<string> &XML_Formated , unsigned int SizeOfXML);
};

#endif // XML_FORMATING_H
