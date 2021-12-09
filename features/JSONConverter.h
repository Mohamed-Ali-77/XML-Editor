#ifndef _JSONCONV_
#define _JSONCONV_

#define TABS "    "

#include "XMLTree.h"
#include "sstream"
#include "string"

// Converts XML to JSON
class JSONConverter
{
private:
    XMLTree& tree;
    string jsonStr;
    // Converts XMLTree to JSON 
    void convert(Node* node, string indent, stringstream& ss);
    void convert();

public:
    // Takes XMLTree
    JSONConverter(XMLTree& tree);
    // Returns JSON as string
    string JSONString();
};


#endif