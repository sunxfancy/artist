/* 
* @Author: sxf
* @Date:   2015-05-30 12:30:13
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 20:33:38
*/

#include "packages/packagemanager.h"
#include "packages/package.h"
#include <list>
#include <map>
#include <iostream>
#include <glibmm.h>

using namespace std;

class PackageManager_private
{
public:
	PackageManager_private();
	~PackageManager_private();
	
	void searchPackages(Glib::ustring& path);
	void loadPackage(Glib::ustring& path);

	map<string, Package*> packages;

	list<Glib::ustring> path_list;
	Glib::ustring default_name;
};

PackageManager::PackageManager() {
	priv = new PackageManager_private();
}

PackageManager::~PackageManager() {
	delete priv;
}

void PackageManager::Search() {
	for (auto root : priv->path_list) {
		priv->searchPackages(root);
	}
}

void PackageManager::addSearchPath(const char* path) {
	priv->path_list.push_back(path);
}

void PackageManager::removeAllPath() {
	priv->path_list.clear();
}

void PackageManager::LoadPackage(const char* path) {
	Glib::ustring tempath(path);
	priv->loadPackage(tempath);
}

PackageManager_private::PackageManager_private() {
	default_name = "package.meta";
}

PackageManager_private::~PackageManager_private() {
	
}

void PackageManager_private::searchPackages(Glib::ustring& path) {
	Glib::ustring file_name = path;
	file_name.append("/").append(default_name);
	if (Glib::file_test(file_name, Glib::FILE_TEST_EXISTS)) {
		loadPackage(file_name);
		return;
	}

	Glib::Dir dirs(path);
	for (auto dir : dirs) {
		Glib::ustring fullpath = path;
		fullpath.append("/").append(dir);
		if (Glib::file_test(fullpath, Glib::FILE_TEST_IS_DIR)) {
			searchPackages(fullpath);
		}
	}
}

void PackageManager_private::loadPackage(Glib::ustring& path) {
	cout << "Loading: " << path.c_str() << endl;
	Package* package = new Package(path.c_str());
	if ( packages.find(package->getName()) != packages.end() ) { // 发现包已经载入
		delete package; return;
	}
	package->Load();
	packages.insert( make_pair(package->getName(), package) );
}
