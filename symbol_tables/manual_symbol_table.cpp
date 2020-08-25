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
	string attribute;
	string scope;
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
 
 i 		to insert symbol
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
		cout<< setw(15) << "HASH" << setw(15) << "TYPE" << setw(15) << "IDENTIFIER" << setw(15) <<  "SCOPE" << setw(15) << "ATTRIBUTES" << endl;
		cout << setw(15) << hash << setw(15) << table[hash].name << setw(15) << table[hash].type << setw(15) << table[hash].scope <<  setw(15) << table[hash].attribute << endl;
	}
	else if(table[hash].exists && table[hash].name != symbol){
		int index = full_search(symbol);
		if(index!=-1){
			cout << "Symbol doesn't exist." << endl;
		}
		else if(index >= 0){
			cout << "Symbol found @ "<< index <<endl;
			cout<< setw(15) << "HASH" << setw(15) << "TYPE" << setw(15) << "IDENTIFIER" << setw(15) <<  "SCOPE" << setw(15) << "ATTRIBUTES" << endl;
			cout << setw(15) << index << setw(15) << table[index].name << setw(15) << table[index].type << setw(15) << table[index].scope <<  setw(15) << table[index].attribute << endl;
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
		cout<< setw(15) << "HASH" << setw(15) << "TYPE" << setw(15) << "IDENTIFIER" << setw(15) <<  "SCOPE" << setw(15) << "ATTRIBUTES" << endl;
		for(int i=0; i <= MAX_SIZE; i++){
			if(table[i].exists){
				cout << setw(15) << i << setw(15) << table[i].name << setw(15) << table[i].type << setw(15) << table[i].scope <<  setw(15) << table[i].attribute << endl;	
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

void collision_insert(string symbol, string type, string att, string scope){
	for(int i=0;i<MAX_SIZE;i++){
		if(!table[i].exists){
			//Empty slot found
			table[i].name = symbol;
			table[i].attribute = att;
			table[i].type = type;
			table[i].scope = scope;
			table[i].exists = true;
			cout << "*****Collision Insert @ Index i" << endl;
			Sleep(600);
		}
	}	
}

void insert(string symbol, string type, string att, string scope){
		int hash = compute_hash(symbol);
		
		cout << "*Generated hash: " << hash << endl;
		
		if(!table[hash].exists){
			cout << "**Symbol does not exist..." << endl;
			
			//Element@Hash doesn't exist
			table[hash].name = symbol;
			table[hash].attribute = att;
			table[hash].type = type;
			table[hash].scope = scope;
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
				collision_insert(symbol, type, att, scope);
			}
		}
		Sleep(3000);
}

void insert_menu(){
	string cmd;
	
	cout << "Enter the symbol in format (? optional): \n<datatype> <identifier> <scope> <?attribute>\n";

	getline(cin >> ws, cmd);
	
	vector<string> tokens = scan(cmd);
	
	insert(tokens[1], tokens[0], tokens[3], tokens[2]);
	
	main();
};

int main(){
	self:
	system("cls");
	char choice;
	string code;
	
	print_options();
	
	//User options
	cin >> choice;
	switch(choice){
		case 'i': insert_menu();
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

