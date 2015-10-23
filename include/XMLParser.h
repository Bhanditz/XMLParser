/*
	A node is a structure that contains an instance of a certain level object.
	It has a pointer points to the next level node it wraps into,
	also it has another pointer points to peer level node.
	Finally, if the tag contains value, it won't be regarded as a node and their pair of <tag, value>
	will be store in the node into a hashmap container.
*/


#ifndef _XMLPARSER_H
#define _XMLPARSER_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>

#include "Exception.h"
#include "XMLNode.h"

#define all(c) (c).begin(), (c).end()

using namespace std;

class XMLParser
{

public:

/*	
	use the number of indent to determine the level of certain tag, 
	then because in the last level, the tag and the value may in the same
	line, or the value may in the next line.
	use "<" to judge a node begin and "</" means its end.
*/
	
	string getFilePath();

	XMLNode* getWrapperNode();

	void parseXMLFile(); 

	XMLParser(const string filepath); 

   ~XMLParser(); 

private:

	// store the file path
	string file_path;
	// the first node of the outest level
	XMLNode *header;

	// if return -1, means fail to find out the value level
	int findValueLevel(); 

	string parseNodeName(const string &s); 

	string parseNodeValue(const string &s); 

	// delete the space on the two ends of string
	string trim(const string &s); 

	void toLower(string &s); 
	
	/* judge the level of tab according to the indents
	   if it does not contain the tag, it regards as value, and return -1
	*/	
	int countLevel(const string &s); 

	// a line is valid when it is a tag or value or mix
	bool isValidLine(const string &s); 

	// fill with spaces
	bool isEmptyLine(const string &s); 

	void clearNodeLink(XMLNode* header); 




};


#endif
