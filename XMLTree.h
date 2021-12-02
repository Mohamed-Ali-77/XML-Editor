#ifndef _XMLTree_
#define _XMLTree_

#include<vector>
#include<string>
#include<stack>
#include<iostream>

using namespace std;

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

class XMLTree
{

private:
    Node* root;
    string body;
    int currentOpeningTag = -1;
    int currentClosingTag;
public:
    XMLTree(const string& xmlContent);

    int getNextOpening() {
        currentOpeningTag++;

        return currentOpeningTag = body.find_first_of("<", currentOpeningTag);
    }

    int getClosing() {
        return currentClosingTag = body.find_first_of(">", currentOpeningTag);
    }

    bool isClosingTag() {
        return body[currentOpeningTag + 1] == '/';
    }


    ~XMLTree();

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
            // cout << "Popped: " << depth.top() -> getName() << " " << depth.top() -> numberOfChilds() << endl;

            // If Node doesn't have children then it is a leaf node
            if (!depth.top() -> hasChildren()) {
                string textData = body.substr(prevClosingTag + 1, currentOpeningTag - prevClosingTag - 1);
                Node* textNode = new Node(textData);
                depth.top() -> addChild(textNode);
                // cout << textData << endl;
            }
            depth.pop();
            continue;
        };

        // cout << currentOpeningTag << endl;
        // cout << currentClosingTag << endl;

        string currentTagName = body.substr(currentOpeningTag + 1, getClosing() - currentOpeningTag - 1);
        Node* currentTag = new Node(currentTagName);
        depth.top() -> addChild(currentTag);
        depth.push(currentTag);
        // cout << "Pushed: "<< depth.top() -> getName()  << endl;

        prevClosingTag = currentClosingTag;
    }
    
}



XMLTree::~XMLTree()
{
}


#endif