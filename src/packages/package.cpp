/* 
* @Author: sxf
* @Date:   2015-05-30 13:25:26
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 20:33:21
*/

#include "packages/package.h"
#include "tools/brush.h"
#include "utils/fileloader.h"
#include "cJSON.h"
#include <map>
#include <string>

using namespace std;

class Package_private
{
public:
	void parser_json();
	char* load_file();  
	void parser_name(cJSON* root);
	void parser_lua_main(cJSON* root);
	void parser_tools(cJSON* root);
	void parser_actions(cJSON* root);

	string name;
	string lua_main; // lua文件名
	
	string env_path; // 包环境路径
	string json_path; // 最先被初始化，json文件的路径

	map<string, Tool*> tool_set;
	map<string, Brush*> brush_set;

	int xg;
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
	if (!priv->lua_main.empty()) {
		string lua_file_path = priv->env_path + priv->lua_main;
		signal_run_lua_file.emit(lua_file_path.c_str());
	}
}

void Package::UnLoad() {

}

const char* Package::getName() const {
	return priv->name.c_str();
}


void Package_private::parser_json() {
	char* data = FileLoader::load(json_path.c_str());
	if (data == NULL) return;

	xg        = json_path.find_last_of('/');
	env_path  = json_path.substr(0, xg+1);
	
	cJSON* cj = cJSON_Parse(data);
	if (!cj) { printf("error json format\n"); return; }

	parser_name(cj);
	parser_lua_main(cj);
	parser_tools(cj);
	parser_actions(cj);

	cJSON_Delete(cj);
	delete data;
}

void Package_private::parser_name(cJSON* root) {
	cJSON *name_j = cJSON_GetObjectItem(root, "name");
	if (name_j) {
		name = name_j->valuestring;
	} else {
		int xgq = json_path.find_last_of('/', xg);
		name = json_path.substr(xgq+1, xg+1);
	}
}

void Package_private::parser_lua_main(cJSON* root) {
	cJSON *lua_j = cJSON_GetObjectItem(root, "lua_main");
	if (lua_j) {
		lua_main = lua_j->valuestring;
	}
}

void Package_private::parser_tools(cJSON* root) {
	cJSON *tools = cJSON_GetObjectItem(root, "tools");
	if ( tools && tools->type == cJSON_Array ) 
		for ( cJSON* p = tools->child; p != NULL; p = p->next ) 
			if ( p->type == cJSON_String ) 
				tool_set[ p->valuestring ] = NULL;
}

void Package_private::parser_actions(cJSON* root) {
	cJSON *tools = cJSON_GetObjectItem(root, "actions");
	if ( tools && tools->type == cJSON_Object ) 
		for ( cJSON* p = tools->child; p != NULL; p = p->next ) 
			if ( p->type == cJSON_String ) 
				Package::signal_action_register.emit(p->string, p->valuestring);
}


sigc::signal<void, const char*> 				Package::signal_run_lua_file;
sigc::signal<void, const char*, const char*> 	Package::signal_action_register;