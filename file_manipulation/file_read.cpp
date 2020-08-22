#include <iostream>
#include <fstream>

using namespace std;

int wordsCount(string buffer){
	int wordCount;
	
	for(int i = 0; buffer[i] != '\0'; i++){
		if(buffer[i] == ' '){
			wordCount++;
		}
	}
	return ++wordCount;
}


int main(int argc, char **argv){
	string fileInp;
	int lines=0,words=0,chars=0;

	try{
		
		ifstream file("dump.txt");

		if(!file){
			throw 404;
		}
		
		while (getline (file, fileInp)) {
  			cout << fileInp;
  			cout << "\n";
  			lines++;
  			chars+=fileInp.length();
  			words+=wordsCount(fileInp);
		}
		
		file.close();
	}
	
	catch(int code){
		cout<<"Error reading the file";
	}
	
	
	cout << "\n-----------------------";
	cout << "\n\nCharacters: " << chars <<"\nLines: " << lines <<"\nWords: " << words;
	
	return 0;	
}
