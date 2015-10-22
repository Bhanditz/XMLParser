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
#include <unordered_map>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "XMLNode.h"

class XMLParser
{

public:

/*	
	use the number of indent to determine the level of certain tag, 
	then because in the last level, the tag and the value may in the same
	line, or the value may in the next line.
	use "<" to judge a node begin and "</" means its end.
*/
	
	string getFilePath()
	{
		return file_path;
	}

	XMLNode* getWrapperNode()
	{
		return header;
	}	





	XMLParser(string filepath) 
	{
		file_path = filepath;
	}

   ~XMLParser() {}


private:

	// store the file path
	string file_path
	// the first node of the outest level
	XMLNode *header;


	string parseNodeName(string s) 
	{
		int left = 0, right = 0;
		for(int i=0; i<s.length(); i++) {
			if(right != 0) break;
			if(s.at(i) == '<') left = i;
			if(s.at(i) == '>') right = i;
		}
		
		return s.substr(left+1, right);
	}

	/* judge the level of tab according to the indents
	   if it does not contain the tag, it regards as value, and return -1
	*/	
	int countLevel(string s) 
	{
		int cnt = 0, i = 0;
		for(i=0; i<s.length(); i++) {
			if(s.at(i) == '\t') cnt++;
			else break;
		}		

		if(s.at(i) != '<') return -1; // regard as value
		return cnt;
	}

	// a line is valid when it is a tag or value or mix
	bool isValidLine(string s) 
	{
		if(s.find("<?") !=  string::npos) return false;
		if(s.find("<!") !=  string::npos) return false;
		if(s.empty() || isEmptyLine(s)) return false;
				
		return true;		
	}

	// fill with spaces
	bool isEmptyLine(string s) 
	{
		for(int i=0; i<s.length(); i++) {
			if(s.at(i) != ' ') return false;
		}
		return true;
	}



};


#endif
