#ifndef _XMLNODE_H
#define _XMLNODE_H

#include <iostream>
#include <unordered_map>
#include <string.h>
#include <string>

#include "Exception.h"

using namespace std;

class XMLNode 
{

public:

	string getNodeName();

	int getNodeLevel();

	XMLNode* getNextLevel(); 

	XMLNode* getNextNode();

	void setNextLevel(XMLNode* node);

	void setNextNode(XMLNode* node);

	void addAttribute(const string &key, const string &value); 

	string getAttribute(const string &key);

	// return the whole map for interation in the call
	unordered_map<string, string>*  getAttributeSet(); 

	XMLNode(const string &name, int level, bool last=false); 

   ~XMLNode(); 


private:

	// the name of this node 
	string node_name;
	// the level of this node
	int node_level;

	// point to the first tag of next level 
	XMLNode *next_level;
	// point to the peer tag of same level
	XMLNode *next_node;
	// the hashmap to record the pair of <tag, value>
	unordered_map<string, string> *map;	

};



#endif
