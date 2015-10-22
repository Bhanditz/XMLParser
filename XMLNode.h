#ifndef _XMLNODE_H
#define _XMLNODE_H

#include <iostream>
#include <unordered_map>
#include <string.h>
#include <string>

#include "Aux.h"

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

	void addAttribute(string key, string value) 
	{
		if(!map) sys_err("[ERROR]: cannot add attribute to the node[" + node_name +"] ...");
		map->insert({key, value});
	}

	string getAttribute(string key)
	{
		if(map->find(key) != map->end()) return map->at(key);
		else sys_err("[ERROR]: attribute[" + key +  "] does not exist in node[" + node_name + "]...");
	}

	// return the whole map for interation in the call
	map<string, string>*  getAttributeSet() 
	{
		if(!map) sys_err("[ERROR]: node[" + node_name + "] doesn't contain MAP...");
		return map;
	}

	XMLNode(string name, int level, bool last) 
	{
		node_name = name;
		node_level = level;
		if(last) {
			map = new unordered_map<string, string>();
		} else {
			map = 0;
		}
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
