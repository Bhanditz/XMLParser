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

	string getNodeName() 
	{
		return node_name;
	}

	int getNodeLevel() 
	{
		return node_level;
	}

	XMLNode* getNextLevel() 
	{
		return next_level;
	}

	XMLNode* getNextNode()
	{
		return next_node;
	}

	void setNextLevel(XMLNode* node)
	{
		next_level = node;
	}

	void setNextNode(XMLNode* node)
	{
		next_node = node;
	}

	void addAttribute(const string &key, const string &value) 
	{
		if(!map) throwError("<runtime error>: fail to add attribute to the node[" + node_name +"] ...");
		map->insert({key, value});
	}

	string getAttribute(const string &key)
	{
		if(map->find(key) == map->end()) throwError("<runtime error>: attribute[" + key +  "] doesn't exist in node[" + node_name + "]...");
		return map->at(key);
	}

	// return the whole map for interation in the call
	unordered_map<string, string>*  getAttributeSet() 
	{
		if(!map) throwError("<runtime error>: node[" + node_name + "] doesn't contain MAP...");
		return map;
	}

	XMLNode(const string &name, int level, bool last=false) 
	{
		node_name = name;
		node_level = level;
		if(last) {
			map = new unordered_map<string, string>();
		} else {
			map = 0;
		}
		next_level = 0;
		next_node = 0;
	}

   ~XMLNode() 
	{
		if(map) {
			delete(map);
			map = 0;
		}
	}



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
