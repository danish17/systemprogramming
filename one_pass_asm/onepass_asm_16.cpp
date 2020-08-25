#include <iostream>
#include <unordered_map>
#include "windows.h"
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#include <ctime>
#define MAX_SIZE 128

using namespace std;

hash <string> hasher;

int TOTAL;

int main();

struct isa{
	string mnem;
	string bin;
	bool exists = false;
};

isa isa_array[MAX_SIZE];

string assembled;

int compute_hash(string name){
	int hash = hasher(name);
	hash%=MAX_SIZE;
	
	if(hash < 0){
		hash*=-1;
	}
	
	return hash;
}

void gen_isa(){
	ifstream isa("config/isa.cnf");
	try{
		string line;
		if(!isa){
			throw 404;
		}
		else{
			while(getline(isa, line)){
				string buffer, mnem, bin;
				for(int i = 0; i<line.length(); i++){
					if(line[i]==' '){
						mnem = buffer;
						buffer.erase();
					}
					else{
						buffer+=line[i];
					}
					bin = buffer;
				}
				int ind = compute_hash(mnem);
				isa_array[ind].bin = bin;
				isa_array[ind].mnem = mnem;
				isa_array[ind].exists = true;
			}
		}
	}	
	catch(int code){
		cerr << "NO ISA FILE FOUND" << endl;
		main();
	}
}

void print_options(){
	cout << R"(	 
	
https://github.com/danish17                                  
 ________  ________   ________  _______   _____ ______   ________  ___       _______   ________     
|\   __  \|\   ____\ |\   ____\|\  ___ \ |\   _ \  _   \|\   __  \|\  \     |\  ___ \ |\   __  \    
\ \  \|\  \ \  \___|_\ \  \___|\ \   __/|\ \  \\\__\ \  \ \  \|\ /\ \  \    \ \   __/|\ \  \|\  \   
 \ \   __  \ \_____  \\ \_____  \ \  \_|/_\ \  \\|__| \  \ \   __  \ \  \    \ \  \_|/_\ \   _  _\  
  \ \  \ \  \|____|\  \\|____|\  \ \  \_|\ \ \  \    \ \  \ \  \|\  \ \  \____\ \  \_|\ \ \  \\  \| 
   \ \__\ \__\____\_\  \ ____\_\  \ \_______\ \__\    \ \__\ \_______\ \_______\ \_______\ \__\\ _\ 
    \|__|\|__|\_________\\_________\|_______|\|__|     \|__|\|_______|\|_______|\|_______|\|__|\|__|
             \|_________\|_________|                                                                
                                                                                                    
Basic One-Pass 16-bit ASM.                                                                                                                                                                                                                                                                                                          
	)" << "\n";
	
	cout << R"(
Commands
----
 
 a 		to assemble program from a file
 q 		to exit
)" << "\n>> ";
}

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

bool is_in_isa(string token){
	int ind = compute_hash(token);
	if(isa_array[ind].exists==true){
		return true;
	}
	else{
		return false;
	}
}

bool is_operand(string token){
	if(token[token.size() - 1] == 'h' || token[token.size() - 1] == 'H'){
		return true;
	}
	else{
		return false;
	}
}

bool is_label(string token){
	if(token[token.size() - 1] == ':'){
		return true;
	}
	else{
		return false;
	}
}

string HexToBin(string hex) { 
  	string bin;
  	
    long int i = 0; 
  
    while (hex[i]) { 
  
        switch (hex[i]) { 
        case '0': 
            bin += "0000"; 
            break; 
        case '1': 
            bin +="0001"; 
            break; 
        case '2': 
            bin += "0010"; 
            break; 
        case '3': 
            bin += "0011"; 
            break; 
        case '4': 
            bin += "0100"; 
            break; 
        case '5': 
            bin += "0101"; 
            break; 
        case '6': 
            bin += "0110"; 
            break; 
        case '7': 
            bin += "0111"; 
            break; 
        case '8': 
        	bin += "1000"; 
            break; 
        case '9': 
            bin += "1001"; 
            break; 
        case 'A': 
        case 'a': 
            bin += "1010"; 
            break; 
        case 'B': 
        case 'b': 
            bin += "1011"; 
            break; 
        case 'C': 
        case 'c': 
            bin += "1100"; 
            break; 
        case 'D': 
        case 'd': 
            bin += "1101"; 
            break; 
        case 'E': 
        case 'e': 
            bin += "1110"; 
            break; 
        case 'F': 
        case 'f': 
            bin += "1111"; 
            break; 
        default: 
            continue;
        } 
        i++; 
    }
	return bin; 
} 

bool translate(vector<string> tokens){
	bool line_is_label = false;
	for(int i = 0;i < tokens.size(); i++){
		cout << "PROCESSING:" << tokens[i] << endl;
		if(tokens[i] != ""){
			tokens[i].erase(remove_if(tokens[i].begin(), tokens[i].end(), ::isspace), tokens[i].end());
			if(is_in_isa(tokens[i])){
				cout << tokens[i] << " :: ISA ADDED" << endl;
				int ind = compute_hash(tokens[i]);
				assembled += isa_array[ind].bin;
				assembled += ' ';
			}
			else if(is_operand(tokens[i])){
				cout << tokens[i] << " :: OPERAND ADDED" << endl;
				tokens[i].erase(tokens[i].end()-1);
				assembled += HexToBin(tokens[i]);
				assembled += ' ';
			}
			else if(is_label(tokens[i])){
				line_is_label = true;
			}
		}
	}
	if(!line_is_label){
		assembled += '\n';
	}
}

void tokenize(string line){
	vector<string> tokens;
	string token;
	
	for(int i=0; line[i]!='\0'; i++){
		if(line[i]!=' ' || line[i]!=','){
			token += line[i];
		}
		
		if(((line[i]==' ' || line[i]==',' )&&token != "")||line[i+1]=='\0'){
			if(token[token.length()-1]==','){
				token.erase(token.end()-1);
			}
			tokens.push_back(token);
			token = "";
		}
		if(line[i+1]=='\0'){
			translate(tokens);
			tokens.clear();
		}			
	}
}

long int unix_timestamp(){
    time_t t = std::time(0);
    long int now = static_cast<long int> (t);
    return now;
}

void save(){
	string file_name = "out_";
	stringstream unix_ts;
	string ts;
	
	long int now = unix_timestamp();
	unix_ts << now;
	unix_ts >> ts;
	file_name += ts;
	file_name += ".bin";
	cout << "\n\n***GENERATED FILE: " << file_name << endl;
	ofstream file(file_name);
	file << assembled;
	file.close();	
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
	save();
}

void load_menu(){
	string path;
	cout << ">> Enter the file path: (demo: example/demo.txt) \n>> ";
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
		
		gen_isa();
		parse_lines(code);	
	}
	catch(int code){
		cout << "***ERROR READING FILE***" << endl;
		Sleep(500);
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
		case 'a': load_menu();
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
