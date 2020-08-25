#include <iostream>
#include <unordered_map>
#include "windows.h"
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#define MAX_SIZE 128

using namespace std;

hash <string> hasher;

int TOTAL;

int main();

struct symbol{
	string name;
	string type;
	string val;
	bool exists = false;
};

symbol table[MAX_SIZE];

int compute_hash(string name){
	int hash = hasher(name);
	hash%=MAX_SIZE;
	
	if(hash < 0){
		hash*=-1;
	}
	
	return hash;
}

void print_options(){
	cout << R"(
https://github.com/danish17	                                 
                         /\ \            /\_ \     /\ \__         /\ \     /\_ \            
  ____  __  __    ___ ___\ \ \____    ___\//\ \    \ \ ,_\    __  \ \ \____\//\ \      __   
 /',__\/\ \/\ \ /' __` __`\ \ '__`\  / __`\\ \ \    \ \ \/  /'__`\ \ \ '__`\ \ \ \   /'__`\ 
/\__, `\ \ \_\ \/\ \/\ \/\ \ \ \L\ \/\ \L\ \\_\ \_   \ \ \_/\ \L\.\_\ \ \L\ \ \_\ \_/\  __/ 
\/\____/\/`____ \ \_\ \_\ \_\ \_,__/\ \____//\____\   \ \__\ \__/.\_\\ \_,__/ /\____\ \____\
 \/___/  `/___/> \/_/\/_/\/_/\/___/  \/___/ \/____/    \/__/\/__/\/_/ \/___/  \/____/\/____/
            /\___/                                                                          
            \/__/                                                                                
                                                
	)" << "\n";
	
	cout << R"(
Commands
----
 
 f 		to load program from a file
 l 		to lookup
 s 		to show symboltable
 q 		to exit
)" << "\n>> ";
}

int full_search(string symbol){
	int exists = -1;
	
	for(int i=0; i<MAX_SIZE; i++){
		if(table[i].name == symbol){
			cout << "****Symbol exists @ index " << i;
			exists = i;
			break;
		}
	}
	
	return exists;
}

int lookup(string symbol){
	int hash = compute_hash(symbol);
	if(!table[hash].exists){
		cout << "Symbol '" << symbol << "' not found..." << endl;
	}
	else if(table[hash].exists && table[hash].name == symbol){
		cout << "Symbol found @ "<< hash <<endl;
		cout<< setw(15) << "HASH" << setw(15) << "SYMBOL" << setw(15) << "TYPE" << setw(15) << endl;
		cout << setw(15) << hash << setw(15) << table[hash].name << setw(15) << table[hash].type << endl;
	}
	else if(table[hash].exists && table[hash].name != symbol){
		int index = full_search(symbol);
		if(index!=-1){
			cout << "Symbol doesn't exist." << endl;
		}
		else if(index >= 0){
			cout << "Symbol found @ "<< index <<endl;
			cout<< setw(15) << "HASH" << setw(15) << "SMBOl" << setw(15) << "TYPE" << endl;
			cout << setw(15) << index << setw(15) << table[index].name << setw(15) << table[index].type << endl;
		}
	}
	system("pause");
	main();
}

void show_table(){
	if(TOTAL == 0){
		cout << "No symbols inserted yet...";
	}
	else{
		cout<< setw(15) << "HASH" << setw(15) << "SYMBOL" << setw(15) << "IDENTIFIER" << setw(15) << "VALUE" << endl;
		for(int i=0; i <= MAX_SIZE; i++){
			if(table[i].exists){
				cout << setw(15) << i << setw(15) << table[i].name << setw(15) << table[i].type << setw(15) << table[i].val << endl;	
			}
		}	
	}
	system("pause");
	main();
};

vector<string> scan(string str){
	vector<string> tokens;
	string token_buffer;
	int token_len = 0;
	
	for(int i=0;i<str.length();i++){
		if(str[i] == ' '){
			tokens.push_back(token_buffer);
			token_len++;
			token_buffer = "";
		}
		else{
			token_buffer += str[i];
		}
	}
	if(token_buffer==""){
		tokens.push_back("none");
	}
	else{
		tokens.push_back(token_buffer);
	}	
	
	return tokens;
}

void collision_insert(string symbol, string type, string val){
	for(int i=0;i<MAX_SIZE;i++){
		if(!table[i].exists){
			//Empty slot found
			table[i].name = symbol;
			table[i].type = type;
			table[i].val = val;
			table[i].exists = true;
			cout << "*****Collision Insert @ Index i" << endl;
			Sleep(600);
		}
	}	
}

void insert(string symbol, string type, string val){
		int hash = compute_hash(symbol);
		
		cout << "*Generated hash: " << hash << endl;
		
		if(!table[hash].exists){
			cout << "**Symbol does not exist..." << endl;
			
			//Element@Hash doesn't exist
			table[hash].name = symbol;
			table[hash].type = type;
			table[hash].val = val;
			table[hash].exists = true;
			
			cout << "***Added Symbol" << endl;
			TOTAL++;
		}	
		
		else{
			cout << "**Hash found, symbol may exist..." << endl;
			Sleep(300);
			cout << "***Searching for symbol..." << endl;
			Sleep(300);
			int found = full_search(symbol);
			if(found == -1){
				collision_insert(symbol, type, val);
			}
		}
		Sleep(700);
}

bool is_valid(vector<string> tokens){
	if(tokens.size()==3){
		string dir = tokens[1];
		string var = tokens[0];
		string val = tokens[2];
		
		transform(dir.begin(), dir.end(), dir.begin(), ::toupper);
		
		vector<string> dirs = {"DB","START","EQU","WORD","DW","DD","DQ","DT","RESB","RESW","RESD","RESQ","REST"};
	
		bool var_is_valid = false;
		bool dir_is_valid = false;
		
		auto it = find(dirs.begin(), dirs.end(), dir);
		if (it != dirs.end()) {
		    dir_is_valid = true;
		}
		else{
			cout << "***ERROR: " << dir << " is not a valid directive..." << endl;
		}
		
		if((int(var[0])>=97 && var[0]<=122) || (int(var[0])>=65 && var[0]<=90)){
			var_is_valid = true;
		}
		else{
			cout << "***ERROR: " << var << " is not a valid variable name..." << endl;
		}
		
		return (dir_is_valid && var_is_valid);
	}
	else{
		return false;
	}
}

void tokenize(string line){
	vector<string> tokens;
	string token;
	
	for(int i=0; line[i]!='\0'; i++){
		if(line[i]!=' '){
			token += line[i];
		}
		
		if((line[i]==' '&&token != "")||line[i+1]=='\0'){
			tokens.push_back(token);
			token = "";
		}
		if(line[i+1]=='\0'){
			if(is_valid(tokens)){
				insert(tokens[0], tokens[1], tokens[2]);
			}
			tokens.clear();
		}			
	}
}

void parse_lines(string code){
	vector<string> lines;
	string line;
	int no_lines = 0;
	
	for(int i=0; i<code.length(); i++){
		line += code[i];
		if(code[i] == '\n'){
			line += '\0';
			lines.push_back(line);
			line = "";
			no_lines++;	
		}
	}
	
	for(int i=0;i<no_lines;i++){
		tokenize(lines[i]);
	}
}

void load_menu(){
	string path;
	cout << ">> Enter the file path: \n>> ";
	cin >> path;
	string code;
	string line;
	
	try{
		ifstream file(path);
	
		if(!file){
			throw 404;
		}
		else{
			while(getline(file, line)){
				code += line;
				code += "\n";
			}
		}
		
		file.close();
		
		parse_lines(code);	
	}
	catch(int code){
		cout << "***ERROR READING FILE***" << endl;
		Sleep(1500);
		load_menu();
	}
	system("pause");
	main();
}

int main(){
	self:
	system("cls");
	char choice;
	string code;
	
	print_options();
	
	//User options
	cin >> choice;
	switch(choice){
		case 'f': load_menu();
		break;
		case 'l':  {
			string search;
			cout << "Symbol to search for?" << endl;	
			cin >> search;
			lookup(search);
		};
		break;
		case 's': show_table();
		break;
		case 'q': exit(0);
		break;
		default:{
			cout<<"INVALID OPTION!\n";
			cout<<"\n\n>> ";
			goto self;
		}		
	}

}

