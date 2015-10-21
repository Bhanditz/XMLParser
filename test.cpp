#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <string>
#include <pwd.h>

using namespace std;


int main(int argc, char** argv) {

	ifstream in;
	char targetDir[128];
	string buffer;

	strcpy(targetDir, getpwuid(getuid())->pw_dir);
	strcat(targetDir, "/.mdtmApp.xml");
	in.open(targetDir);
	
	while(getline(in, buffer)) {
		cout << buffer << endl;	
	}

	








	return 0;
}
