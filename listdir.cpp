#include <cstdio>
#include <dirent.h>
#include <iostream>

using namespace std;

void listdir (const string& path)
{
	DIR *pdir = opendir(path.c_str());
	if (pdir == 0) {
		cerr << "Directory could not be opened: " << path << endl;
		return;
	}
	struct dirent *pent = 0;
	while ((pent = readdir(pdir))) {
		if (pent == 0) {
			cerr << "A directory entry could not be read" << endl;
		} else {
			printf("%s\n", pent->d_name);
		}
	}
	closedir(pdir);
}

