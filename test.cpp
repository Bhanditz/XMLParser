#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <string>
#include <pwd.h>

#include "XMLNode.h"
#include "XMLParser.h"

using namespace std;


int main(int argc, char** argv) {

	char targetDir[128];
	string buffer;

	strcpy(targetDir, getpwuid(getuid())->pw_dir);
	strcat(targetDir, "/.mdtmApp.xml");

	XMLParser parser(targetDir);
	parser.parseXMLFile();


	return 0;
}


