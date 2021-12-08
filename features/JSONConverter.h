#ifndef _JSONCONV_
#define _JSONCONV_

#define TABS "    "

#include "XMLTree.h"
#include "sstream"
#include "string"

class JSONConverter
{
private:
    XMLTree& tree;
    string jsonStr;
    void convert(Node* node, string indent, stringstream& ss);
    void convert();

public:
    JSONConverter(XMLTree& tree);

    string JSONString();
};


JSONConverter::JSONConverter(XMLTree& t): tree(t) {
    convert();
}

void JSONConverter::convert() {
    Node* root = tree.getRoot();
    stringstream str;
    str << "{\n";
    convert(root -> getChild(0), TABS, str);
    str << "\n}";
    jsonStr = str.str();
}
bool hasLeafChild(Node* node) {
    return node -> numberOfChilds() == 1 && !node -> getChild(0)->hasChildren();
}
void JSONConverter::convert(Node* node, string indent, stringstream& ss) {

    ss << indent << "\"" <<  node -> getName() << "\": ";
    if (!hasLeafChild(node)) ss << "{\n";

    for(int i = 0; i < node ->numberOfChilds(); ++i) {

        if(!node -> getChild(i) -> hasChildren()) {
            ss << "\"" << node -> getChild(i) -> getName() << "\"";
        }
        else convert(node -> getChild(i), indent + TABS, ss);
        if(i < node -> numberOfChilds() - 1) ss << ",\n";

    }

    if (!hasLeafChild(node)) ss << "\n" << indent << "}";

}

string JSONConverter::JSONString() {
    return jsonStr;
}

#endif