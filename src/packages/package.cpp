/* 
* @Author: sxf
* @Date:   2015-05-30 13:25:26
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-30 20:27:50
*/

#include "package.h"
#include <string>
#include <fstream>
#include "app.h"
#include "cJSON.h"

class Package_private
{
public:
	Package_private();
	~Package_private();
	
	void parser_json();
	char* load_file();  // 使用完后注意释放内存
	
	std::string name;
	std::string lua_main;
	
	std::string env_path;
	std::string json_path; // 最先被初始化
};

Package::Package(const char* json_path) {
	priv = new Package_private();
	priv->json_path = json_path;
	priv->parser_json();
}

Package::~Package() {
	delete priv;
}

void Package::Load() {
	LuaContainer* lua = App::getLuaContainer();
	std::string lua_file_path = priv->env_path + priv->lua_main;
	printf("%s\n",lua_file_path.c_str());
	lua->RunLuafile(lua_file_path.c_str());
}

void Package::UnLoad() {

}

const char* Package::getName() const {
	return priv->name.c_str();
}

Package_private::Package_private() {
	
}

Package_private::~Package_private() {
	
}

void Package_private::parser_json() {
	char* data = load_file();
	if (data == NULL) return;

	int xg = json_path.find_last_of('/');
	std::string env_path = json_path.substr(0, xg+1);
	printf(env_path.c_str());
	
	cJSON* cj = cJSON_Parse(data);
	if (!cj) { printf("error json format\n"); return; }

	cJSON *name_j = cJSON_GetObjectItem(cj, "name");
	if (name_j) {
		name = name_j->valuestring;
	} else {
		int xgq = json_path.find_last_of('/', xg);
		name = json_path.substr(xgq+1, xg+1);
	}

	cJSON *lua_j = cJSON_GetObjectItem(cj, "lua_main");
	if (lua_j) {
		lua_main = env_path;
		lua_main.append(lua_j->valuestring);
	}
	cJSON_Delete(cj);
	delete data;
}

char* Package_private::load_file() {
	std::fstream file;
	file.open(json_path);//打开文件
    if(!file.is_open()) {
        printf("can not open json file!\n");
        return NULL;
    }
    file.seekg(0,std::ios::end);
    int flen = file.tellg();
    file.seekg(0,std::ios::beg);
    char* data = new char[flen+1];
    file.read(data,flen);
    file.close();
    data[flen] = 0;
    printf(data);
    return data;
}
