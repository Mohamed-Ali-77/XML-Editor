#ifndef __XMLTree__
#define __XMLTree__

#include<vector>
#include<string>
#include<stack>
#include<sstream>
using namespace std;


// Node for XML tag containing a vector its children nodes
// Children represents the inner tags encapsulated by tag that the node represents
// Name is the tag name and if the node doesn't have children then represents the text data of the tag
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

    void deleteTree(Node* node);
};




#endif