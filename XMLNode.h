/*
	A node is a structure that contains an instance of a certain level object.
	It has a pointer points to the next level node it wraps into,
	also it has another pointer points to peer level node.
	Finally, if the tag contains value, it won't be regarded as a node and their pair of <tag, value>
	will be store in the node into a hashmap container.
*/

#ifndef _XMLNODE_H
#define _XMLNODE_H

class XMLNode 
{

public:












	XMLNode() {}
   ~XMLNode() {}



private:

	// point to the first tag of next level 
	XMLNode *next_level;
	
	// point to the peer tag of same level
	XMLNode *next_node;

	








};



#endif
