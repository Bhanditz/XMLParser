#include <iostream>
#include <unordered_map>
#include <string.h>
#include <string>

#include "XMLNode.h"

using namespace std;


string XMLNode::getNodeName() 
{
	return node_name;
}

int XMLNode::getNodeLevel() 
{
	return node_level;
}

XMLNode* XMLNode::getNextLevel() 
{
	return next_level;
}

XMLNode* XMLNode::getNextNode()
{
	return next_node;
}

void XMLNode::setNextLevel(XMLNode* node)
{
	next_level = node;
}

void XMLNode::setNextNode(XMLNode* node)
{
	next_node = node;
}

void XMLNode::addAttribute(const string &key, const string &value) 
{
	if(!map) throwError("<runtime error>: fail to add attribute to the node[" + node_name +"] ...");
	map->insert({key, value});
}

string XMLNode::getAttribute(const string &key)
{
	if(map->find(key) == map->end()) throwError("<runtime error>: attribute[" + key +  "] doesn't exist in node[" + node_name + "]...");
	return map->at(key);
}

// return the whole map for interation in the call
unordered_map<string, string>* XMLNode::getAttributeSet() 
{
	if(!map) throwError("<runtime error>: node[" + node_name + "] doesn't contain MAP...");
	return map;
}

XMLNode::XMLNode(const string &name, int level, bool last) 
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

XMLNode::~XMLNode() 
{
	if(map) {
		delete(map);
		map = 0;
	}
}

