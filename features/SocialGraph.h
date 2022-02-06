#ifndef __SOCIALGRAPH__
#define __SOCIALGRAPH__

#include "XMLTree.h"
#include <vector>
#include <string>



// Represent a user in a social network
class SocialNode {
public:
    std::string name;
    std::vector<int> followers;
    int id;
    //Each entry in posts is of size 2, where index 0 is topic and index 1 in body
    vector<vector<std::string>> posts;
};

// Represent graph of social network
class SocialGraph
{
public:
    std::vector<SocialNode* > usersSocialNodes;
    SocialGraph(XMLTree& tree);
    ~SocialGraph();
};

#endif