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
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>

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
	
	string getFilePath()
	{
		return file_path;
	}

	XMLNode* getWrapperNode()
	{
		return header;
	}	

	void parseXMLFile() 
	{
		ifstream in;
		string buffer; // use to read line
		stack<XMLNode> stack;
		XMLNode *ptr = 0, *last_node = 0;		
		int info_level = INT_MIN, this_level = 0;

		in.open(file_path);
		
		/* use a variable to record the last tag's level, if this node is the same
		   as the last one, so this one is added to the next_node, if it is the 
		   higher level, it is added to the next_level.
		   In order to judge whether is the last level that contains the info, here
		   is to traverse one time to determine the highest level, it does not need 
		   to traverse the whole file, just find out the first tag with value level
		*/

		if((info_level = findValueLevel()) < 0) {
			sys_err("[ERROR]: cannot find any useful info of XML file...");
		}
		while(getline(in, buffer)) {
			if(!isValidLine(buffer)) continue;
			if(!header) {
				header = new XMLNode(parseNodeName(buffer), countLevel(buffer));	
				stack.push(*header);
				continue;
			}
			
			// add the key-value pair to the node of stack top
			ptr = &stack.top();
			this_level = countLevel(buffer);
			if(this_level == info_level) {
				string key = parseNodeName(buffer);
				string value = parseNodeValue(buffer);
				ptr->addAttribute(key, value);	

			} else {
				/* if start tag, connect the pointer and push the node into stack
				   if end tag, pop the stack
				*/
				string node_name = parseNodeName(buffer);
				XMLNode *new_node = 0;
				if(ptr->getNodeName() == node_name) {
					stack.pop();
					last_node = ptr;
				} else {
					if(this_level == info_level-1) {
						new_node = new XMLNode(node_name, this_level, true);	
					} else {
						new_node = new XMLNode(node_name, this_level);		
					}
					if(last_node && last_node->getNodeLevel() == this_level) {
						last_node->setNextNode(new_node);
					} else {
						ptr->setNextLevel(new_node);
					}
					stack.push(*new_node);
				} 
			}
		}				
	
		in.close();
	}	



	XMLParser(string filepath) 
	{
		file_path = filepath;
		header = 0;
	}

   ~XMLParser() 
	{
		if(header) clearNodeLink(header);
	}


private:

	// store the file path
	string file_path;
	// the first node of the outest level
	XMLNode *header;

	// if return -1, means fail to find out the value level
	int findValueLevel() 
	{
		ifstream in;
		string buffer;
		int last_level = INT_MIN, this_level = 0;

		in.open(file_path);

		while(getline(in, buffer)) {
			if(!isValidLine(buffer)) continue;
			this_level = countLevel(buffer);
			if(this_level == -1) continue; // the value takes a whole line

			if(this_level <= last_level) return last_level;
			else last_level = this_level;	
		}

		in.close();
		return -1;
	}

	string parseNodeName(string &s) 
	{
		int left = 0, right = 0;
		string res;

		for(size_t i=0; i<s.length(); i++) {
			if(right != 0) break;
			if(s.at(i) == '<') {
				if(s.at(i+1) == '/') left = i+1;
				else left = i;
			}
			if(s.at(i) == '>') right = i;
		}
				
		res = s.substr(left+1, right-left-1);
		toLower(res);
		return res;
	}

	string parseNodeValue(string &s) 
	{
		int i = 0, len = s.length();
		string res;

		while(s.at(i) == '\t' || s.at(i) == ' ') i++;	
		if(s.at(i) == '<') {
			int left = 0, right = 0;
			i++;
			while(i < len) {
				if(right != 0) break;
				if(s.at(i) == '>') left = i;
				else if(s.at(i) == '<') right = i;	
				i++;
			}	
			res = s.substr(left+1, right-left-1);
		} else {
			res = s.substr(i, len-i);
		}		

		return res;
	}

	void toLower(string &s) 
	{
     	transform(all(s), s.begin(), ::tolower);	
	}
	
	/* judge the level of tab according to the indents
	   if it does not contain the tag, it regards as value, and return -1
	*/	
	int countLevel(string &s) 
	{
		int cnt = 0; 
		size_t i = 0;
		for(i=0; i<s.length(); i++) {
			if(s.at(i) == '\t') cnt++;
			else break;
		}		
		while(s.at(i) == ' ') i++;
		if(s.at(i) != '<') return -1; // regard as value
		return cnt;
	}

	// a line is valid when it is a tag or value or mix
	bool isValidLine(string &s) 
	{
		if(s.find("<?") !=  string::npos) return false;
		if(s.find("<!") !=  string::npos) return false;
		if(s.empty() || isEmptyLine(s)) return false;
				
		return true;		
	}

	// fill with spaces
	bool isEmptyLine(string &s) 
	{
		for(size_t i=0; i<s.length(); i++) {
			if(s.at(i) != ' ') return false;
		}
		return true;
	}

	void clearNodeLink(XMLNode* header) 
	{
		if(!header) return;
		clearNodeLink(header->getNextLevel());
		clearNodeLink(header->getNextNode());		
		delete(header);		
	}


};


#endif
