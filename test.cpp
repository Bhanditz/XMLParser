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

	ifstream in;
	char targetDir[128];
	string buffer;

	strcpy(targetDir, getpwuid(getuid())->pw_dir);
	strcat(targetDir, "/.mdtmApp.xml");
	in.open(targetDir);


/*
	while(getline(in, buffer)) {
		cout << buffer << endl;	
	}
*/
	
	XMLNode node("device", 1, true);

	node.addAttribute("ip", "192.168.142.20");

	cout << node.getAttribute("ip") << endl;

	node.getAttribute("id");

	in.close();
	return 0;
}


