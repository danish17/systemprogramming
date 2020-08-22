#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	string fileOut;
	string line;

	try{
		
		ofstream file("dump.txt");

		if(!file){
			throw 404;
		}
		
		cout << "Ctrl+Z to exit \n0: ";
		
		int lineNum = 0;
		
		while(getline(cin, line)){
			if (line == "^Z"){
				break;
			}
			lineNum++;
			
			cout << lineNum << ": ";
			fileOut += line;
			fileOut += "\n";
		}
		
		cin >> fileOut;
		
		file << fileOut;
		
		file.close();
	}
	
	catch(int code){
		cout<<"Error reading the file";
	}
	
	return 0;	
}
