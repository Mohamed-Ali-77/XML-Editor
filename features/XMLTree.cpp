#include "XMLTree.h"

XMLTree::XMLTree(const string& xmlContent)
{
    root = new Node();
    body = xmlContent;
    currentClosingTag = 0;
    stack<Node* > depth;
    depth.push(root);
    int prevClosingTag = 0;
    while (getNextOpening() != string::npos) {
        getClosing();

        if (isClosingTag()) {

            // If Node doesn't have children then it is a leaf node
            if (!depth.top() -> hasChildren()) {
                string textData = body.substr(prevClosingTag + 1, currentOpeningTag - prevClosingTag - 1);
                Node* textNode = new Node(textData);
                depth.top() -> addChild(textNode);
            }
            depth.pop();
            continue;
        };

        // Gets name of the tag
        string currentTagName = body.substr(currentOpeningTag + 1, getClosing() - currentOpeningTag - 1);
        int firstSpace = currentTagName.find_first_of(" ");
        if (firstSpace != string::npos) currentTagName.erase(firstSpace);

        Node* currentTag = new Node(currentTagName);
        depth.top() -> addChild(currentTag);
        depth.push(currentTag);

        prevClosingTag = currentClosingTag;
    }
}


string XMLTree::inorderXML() {
    stringstream str;
    for(int i = 0; i < root -> numberOfChilds(); ++i) {
        inorderXML(root -> getChild(i), str);
    }
    return str.str();

}

void XMLTree::inorderXML(Node* tag, stringstream& str) {
    if(!tag -> hasChildren()) {
        str << tag -> getName();
        return;
    }

    str << "<" << tag -> getName() << ">"; 

    for(int i = 0; i < tag -> numberOfChilds(); ++i) {
        inorderXML(tag -> getChild(i), str);
    }

    str << "</" << tag -> getName() << ">";
}

void XMLTree::deleteTree(Node* node) {
    for (int i = 0; i < node -> numberOfChilds(); ++i) {
        deleteTree(node -> getChild(i));
    }
    delete  node;
}

XMLTree::~XMLTree()
{
    deleteTree(root);
}

