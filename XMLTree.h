#ifndef _XMLTree_
#define _XMLTree_

#include<vector>
#include<string>
#include<stack>
#include<sstream>
using namespace std;


// Node for XML tag containing a vector its children nodes
// Children represents the inner tags encapsulated by tag that the node represents
// Name is the tag name and if the node doesn't have children then represents the text gata of the tag
class Node
{
private:

    vector<Node* > children;
    string name;

public:
    Node(string tagName = "") {
        name = tagName;
    }

    bool hasChildren() {
        return numberOfChilds() != 0;
    }

    int numberOfChilds() {
        return children.size();
    }

    Node* getChild(int child) {
        return children[child];
    }
    void addChild (Node * newChild) {
        children.push_back(newChild);
    }

    string getName() {
        return name;
    }

};

// Constructing a tree from XML
class XMLTree
{

private:
    Node* root;
    string body;
    int currentOpeningTag = -1;
    int currentClosingTag;

public:

    XMLTree(const string& xmlContent);

    // Returns string with XML inorder
    string inorderXML();
    

    Node* getRoot() {
        return root;
    }

    ~XMLTree();

private:
    // Gets position for the next "<"
    int getNextOpening() {
        currentOpeningTag++;
        return currentOpeningTag = body.find_first_of("<", currentOpeningTag);
    }
    // Gets position for the ">" which comes after the currentOpeningTag 
    int getClosing() {
        return currentClosingTag = body.find_first_of(">", currentOpeningTag);
    }
    // Checks if the tag that starts at currentOpeningTag is a closing Tag or not
    bool isClosingTag() {
        return body[currentOpeningTag + 1] == '/';
    }

    void inorderXML(Node* tag, stringstream& str);

};

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

XMLTree::~XMLTree()
{
}


#endif