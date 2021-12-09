#include "JSONConverter.h"

// Helpers
bool hasLeafChild(Node* node) {
    return node -> numberOfChilds() == 1 && !node -> getChild(0)->hasChildren();
}
bool hasArray(Node* node) {
    if(node -> numberOfChilds() > 1) 
        if(node -> getChild(0) -> getName() == node -> getChild(1) -> getName()) return true;
    
    return false;
}
bool escapedChars(const char& c) {
    if (c == '\n' || c == '\r' || c == ' ') return true;
    else return false;
}
void escapeString(const string& sentence, stringstream& ss) {
    int start = 0, end = sentence.size() - 1;
    while(escapedChars(sentence[start])) start++;
    while(escapedChars(sentence[end])) end--;
    for (int i = start; i <= end; ++i) {
        ss << sentence[i]; 
    } 
}


JSONConverter::JSONConverter(XMLTree& t): tree(t) {
    convert();
}

void JSONConverter::convert() {
    Node* root = tree.getRoot();
    stringstream str;
    convert(root, "", str);
    jsonStr = str.str();
}

void JSONConverter::convert(Node* node, string indent, stringstream& ss) {

    if (hasArray(node)) ss << "[\n" << indent + TABS;
    else if (!hasLeafChild(node)) ss << "{\n";

    for(int i = 0; i < node ->numberOfChilds(); ++i) {

        if(!node -> getChild(i) -> hasChildren()) {
            ss << "\"", escapeString(node -> getChild(i) -> getName(), ss), ss << "\"";
        }else {

            if(!hasArray(node)) 
                ss << indent + TABS << "\"" << node -> getChild(i) -> getName() << "\": ";
            convert(node -> getChild(i), indent + TABS, ss);

        }
        if(i < node -> numberOfChilds() - 1) ss << ",\n";
        if(hasArray(node)) ss << indent + TABS;

    }

    if(hasArray(node)) ss << "\n" << indent << "]";
    else if (!hasLeafChild(node)) ss << "\n" << indent << "}";

}

string JSONConverter::JSONString() {
    return jsonStr;
}

