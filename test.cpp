#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <string>
#include <pwd.h>

#include "XMLParser.h"

using namespace std;


int main(int argc, char** argv) {

	try{
		if(argc < 2) {
			throwError("input format: ./a.out <file_path>");
		}

		XMLParser parser(argv[1]);
		parser.parseXMLFile();
		XMLNode *header = parser.getWrapperNode();
		XMLNode *ptr = header;

		while(ptr->getNextLevel()) ptr = ptr->getNextLevel();

		while(ptr) {
			cout << ptr->getNodeName() + ": " << endl;
			unordered_map<string, string> *map = ptr->getAttributeSet();
			for(auto i = map->begin(); i != map->end(); i++) {
				cout << "\t" + i->first + ": " + i->second << endl;	
			}

			ptr = ptr->getNextNode();
		}

	} catch(const runtime_error &e) {
		cout << e.what() << endl;
	}

	exit(0);
}


