#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	string fileOut;
	string fileIn;

	try{
		
		ifstream file("dump.txt");
		ofstream fileTwo("dump-copy.txt");
		
		if(!file || !fileTwo){
			throw 404;
		}
		
		while(getline(file, fileIn)){
			fileOut+=fileIn;
			fileOut+="\n";
		}
		
		fileTwo << fileOut;
		
		cout<<"Copied successfully.";
		
		file.close();
		fileTwo.close();
	}
	
	catch(int code){
		cout<<"Error reading the file";
	}
	
	return 0;	
}
