#include "SocialGraph.h"

#include <iostream>

using namespace std;
// Constructs graph from XMLTree
SocialGraph::SocialGraph(XMLTree& tree) {

    if(!tree.getRoot() -> hasChildren()) return;

    Node* usersNode = tree.getRoot() -> getChild(0);
    int maximumId = usersNode->numberOfChilds();
    usersSocialNodes = vector<SocialNode* >(maximumId + 1);

    // Iterate over the users in tree and for each user create a SocialNode with all fields populated and add it to the graph 
    for(int userIndx = 0; userIndx < usersNode -> numberOfChilds(); ++userIndx) {

        Node* user = usersNode -> getChild(userIndx);
        SocialNode* userSocialNode = new SocialNode();

        // Iterate over fields in user node in the tree
        for(int fieldIndx = 0; fieldIndx < user -> numberOfChilds(); ++fieldIndx) {

            std::string field = user -> getChild(fieldIndx) -> getName();
            Node* fieldNode = user -> getChild(fieldIndx);
            if(field == "id") {
                
                userSocialNode -> id = stoi(fieldNode -> getChild(0) -> getName());

            } else if(field == "name") {

                userSocialNode -> name = fieldNode -> getChild(0) -> getName();

            } else if(field == "posts") {

                vector<vector<std::string>> posts(fieldNode -> numberOfChilds(), std::vector<std::string>(1));
                // Get posts topic and body 
                for(int postIndx = 0; postIndx < fieldNode -> numberOfChilds(); ++postIndx) {
                    Node* postNode = fieldNode -> getChild(postIndx);
                    for(int postFieldIndx = 0; postFieldIndx < postNode -> numberOfChilds(); ++postFieldIndx) {
                        Node* postFieldNode = postNode -> getChild(postFieldIndx);
                        if(postFieldNode -> getName() == "topics") {
                            // Get topic of post
                            for(int topicIndx = 0; topicIndx < postFieldNode -> numberOfChilds(); ++topicIndx) {
                                posts[postIndx].push_back(postFieldNode -> getChild(topicIndx) -> getChild(0) -> getName());
                            }
                        } else if (postFieldNode -> getName() == "body") {
                            posts[postIndx][0] = postFieldNode -> getChild(postFieldIndx) -> getName();
                        }
                    }
                }
                userSocialNode -> posts = posts;
            } else if(field == "followers") {
                // Get user followers list
                for(int followerIndx = 0; followerIndx < fieldNode -> numberOfChilds(); ++followerIndx) {
                    int followerId = stoi(fieldNode -> getChild(followerIndx) -> getChild(0) -> getChild(0) -> getName());
                    userSocialNode -> followers.push_back(followerId);
                }
            }
        }
        usersSocialNodes[userSocialNode -> id] = userSocialNode;
    }
}

// Deleting created SocialNodes
SocialGraph::~SocialGraph() {
    for(int i = 1; i < usersSocialNodes.size(); ++i) {
        delete usersSocialNodes[i];
    }
}