/*
	Name: Parenthesis Check 
	Copyright: Danish Shakeel
	Author: Danish Shakeel (github.com/danish17)
	Date: 19-08-20 00:52
	Description: Exp. 1.2; System Programming
*/


#include<iostream>
#include "windows.h"
#include <bits/stdc++.h> 
#include <fstream>

#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

using namespace std;

struct paranthesis{
	int col;
	int row;
	char par;
};

void showstack(stack <paranthesis> s) 
{ 
    while (!s.empty()) 
    { 
        cout << "Col" << s.top().col << "Row" << s.top().row << "Par" << s.top().par; 
        cout << '\n'; 
        s.pop(); 
    } 
    
} 

void gotoxy(int x, int y)
{
    COORD c = { x, y };  
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void colorize(char text,bool revert,int code){
	HANDLE  hConsole;
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, code);
	
	cout<<text;
	if(revert==true){
		SetConsoleTextAttribute(hConsole, 15);
	}
}

string openFile(){
	system("cls");
	
	string fileInp;
	string doc;
	
	try{
		string path;
		cout<<"Enter the file path: ";
		cin>>path;	
		char * path_parsed = new char [path.length()+1];
		strcpy (path_parsed, path.c_str());
		
		cout<<"Opening "<<path_parsed<<"...";
		system("cls");
		ifstream file(path_parsed);

		if(!file){
			throw 404;
		}
		
		while (getline(file, fileInp)) {
  			doc+=fileInp;
  			doc+="\n";
		}
		
		file.close();
	}
	catch(int code){
		cout<<"Error reading the file";
		Sleep(1000);
		openFile();
	}
	
	return doc;
}

string writeText(){
	system("cls");
	string line;
	string doc;
	
	cout << "Ctrl+Z to exit \n";
		while(getline(cin, line)){
			if (line == "^Z"){
				break;
			}
			else{
				doc+=line;
				doc+="\n";
			}
		}
		
		system("cls");
	
	return doc;
}

bool isClose(char par){
	char close[] = {'}',']',')'};
	if(strchr(close,par)>0){
		return true;
	}
	else return false;
}

bool isOpen(char par){
	char open[] = {'{','[', '('};
	if(strchr(open,par)>0){
		return true;
	}
	else return false;
}

char findOpposite(char p){
	char opp;
	
	switch(p){
		case '{': opp='}';
		break;
		case '[': opp=']';
		break;
		case '(': opp=')';
	}
	
	return opp;
}

void highlight(stack <paranthesis> s)
{
	while(!s.empty()){
		int row=s.top().row;
		int col=s.top().col;
		char top = s.top().par;
	
//		cout<<"Row: "<<row<<"\tCol: "<<col<<"\n";
		gotoxy(col,row);	
		colorize(top, true, 4);
		s.pop();
	}	
}

int main(){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	stack <paranthesis> paran;
	stack <paranthesis> imb;
	
	string text;
	char par[]={'{','}','(',')','[',']'};
	
	//User prompt
	prompt:
	int resp;
	
	cout<<"1. Open a file\n2. Write text\n>> ";
	cin>>resp;
	switch(resp){
	case 1: text=openFile();
	break;
	case 2: text=writeText();
	break;
	default: {
		cout<<"Invalid Choice.";
		Sleep(1000);
		system("cls");
		goto prompt;
	}
	}
	int row=0,col=0;
	bool balanced = true;
	
	for(int i=0;i<text.length();i++){
		if(strchr(par,text[i])>0&&isOpen(text[i])){
			paranthesis p;
			p.col=col;
			p.row=row;
			p.par=text[i];
			
			paran.push(p);
		}
		
		else if(strchr(par,text[i])>0&&isClose(text[i])){
			char top = paran.top().par;
			
			if(text[i]==findOpposite(top)){
				paran.pop();
			}
			else{
				balanced = false;
				imb.push(paran.top());
				paran.pop();
			}
		}
		if(text[i]=='\n'){
			row++;
			col=0;
		}
		else{
			col++;
		}
	}
	
	//Clean console and show text
	system("cls");
	cout<<text;
	
	if(!balanced|!paran.empty()){
	recheck:
		if(!paran.empty()){
			colorize(findOpposite(paran.top().par),true,31);
			paran.pop();
			cout<<"\n***Imbalanced text. Missed a closing parenthesis... Missing paranthesis will be shown in blue...";
			goto recheck;	
		}
		else{
			cout<<"\n***Imbalanced text. Imbalanced paranthesis will be marked red...";
			highlight(imb);		
		}
	}
	else{
		cout<<"---------------------------\nBalanced.";
	}
	getchar();
	getchar();
	return 0;
} 

