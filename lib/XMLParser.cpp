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
#include "XMLParser.h"


using namespace std;

	
string XMLParser::getFilePath()
{
	return file_path;
}

XMLNode* XMLParser::getWrapperNode()
{
	return header;
}	

void XMLParser::parseXMLFile() 
{
	ifstream in;
	string buffer; // use to read line
	stack<XMLNode*> stack;
	XMLNode *ptr = 0, *last_node = 0;		
	int info_level = INT_MIN, this_level = 0, cnt = 0;

	in.open(file_path);
		
	/* use a variable to record the last tag's level, if this node is the same
	   as the last one, so this one is added to the next_node, if it is the 
	   higher level, it is added to the next_level.
	   In order to judge whether is the last level that contains the info, here
	   is to traverse one time to determine the highest level, it does not need 
	   to traverse the whole file, just find out the first tag with value level
	*/

	if((info_level = findValueLevel()) < 0) {
		throwError("<XML file error>: unavailable object value of XML file");
	}
	while(getline(in, buffer)) {
		if(!isValidLine(buffer)) continue;
	
		cnt++;

		if(!header) {
			header = new XMLNode(parseNodeName(buffer), countLevel(buffer));	
			stack.push(header);
			continue;
		}
			
		// add the key-value pair to the node of stack top
		ptr = stack.top();
		this_level = countLevel(buffer);
		if(this_level == info_level) {
			string key = parseNodeName(buffer);
			string value = parseNodeValue(buffer);
			if(value.empty()) getline(in, value);
			ptr->addAttribute(key, trim(value));	

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
				stack.push(new_node);
			} 
		}
	}				
	
	in.close();
	if(!stack.empty()) {
		throwError("<XML file error>: tags mismatch");
	}
}	


XMLParser::XMLParser(const string filepath) 
{
	file_path = filepath;
	header = 0;
}

XMLParser::~XMLParser() 
{
	if(header) clearNodeLink(header);
}


// if return -1, means fail to find out the value level
int XMLParser::findValueLevel() 
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

string XMLParser::parseNodeName(const string &s) 
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

string XMLParser::parseNodeValue(const string &s) 
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
	} 

	return res;
}

// delete the space on the two ends of string
string XMLParser::trim(const string &s) 
{
	int left = 0, right = s.length()-1;
	while(s.at(left) == '\t' || s.at(left) == ' ') left++;
	while(s.at(right) == '\t' || s.at(right) == ' ') right--;
	return s.substr(left, right-left+1);
}

void XMLParser::toLower(string &s) 
{
    transform(all(s), s.begin(), ::tolower);	
}
	
/* judge the level of tab according to the indents
   if it does not contain the tag, it regards as value, and return -1
*/	
int XMLParser::countLevel(const string &s) 
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
bool XMLParser::isValidLine(const string &s) 
{
	if(s.find("<?") !=  string::npos) return false;
	if(s.find("<!") !=  string::npos) return false;
	if(s.empty() || isEmptyLine(s)) return false;
				
	return true;		
}

// fill with spaces
bool XMLParser::isEmptyLine(const string &s) 
{
	for(size_t i=0; i<s.length(); i++) {
		if(s.at(i) != ' ') return false;
	}
	return true;
}

void XMLParser::clearNodeLink(XMLNode* header) 
{
	if(!header) return;
	clearNodeLink(header->getNextLevel());
	clearNodeLink(header->getNextNode());		
	delete(header);		
}


