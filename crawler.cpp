#include <iostream>
#include "myset.h"
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>

using namespace std;

void parse(string, MySet<string>&, vector<string>&);
void parserHelper(string, ofstream&, MySet<string>&);

int main(){


	vector<string> seedFiles;
	MySet<string> discovered;

	ifstream infile;
	infile.open("data/index.txt");

	ofstream ofile;
	ofile.open("data/output.txt");

	string target;

	while(getline(infile, target)){

		seedFiles.push_back(target);
	}

	for(unsigned int i = 0; i < seedFiles.size(); i++){

		if(discovered.count(seedFiles[i]) == 0){

			discovered.insert(seedFiles[i]);
			ofile << seedFiles[i] << endl;
			parserHelper(seedFiles[i], ofile, discovered);
		}
	}

	infile.close();
	ofile.close();

	return 0;
}

void parserHelper(string target, ofstream &ofile, MySet<string>& discovered){

	vector<string> outLinks;
	MySet<string> allWords;

	parse(target, allWords, outLinks);

	for(unsigned int i = 0; i < outLinks.size(); i++){

		if(discovered.count(outLinks[i]) == 0){

			ofile << outLinks[i] << endl;
			discovered.insert(outLinks[i]);
			parserHelper(outLinks[i], ofile, discovered);
		}
	}
}

void parse(string filename, MySet<string>& allWords, vector<string>& allLinks){

	// using ifstream to open a file
	ifstream infile;
	infile.open(filename.c_str());

	// chars variable for reading in by characters
	char chars;
	// total string that will hold all the valid characters
	string wordToAdd;

	// counting parentheses and brackets for formatting issues
	int paren_count = 0;
	int brack_count = 0;

	// looping through the file
	while(!infile.fail()){

		// getting each character
		infile.get(chars);

		// checking to see if it fails
		if(infile.fail()){
			break;
		}

		// looping through each character when an opening
		// paranthese is found
		if(chars == '('){

			paren_count++;
			// getting next character
			infile.get(chars);

			// looping through each character when an opening
			// paranthese is found.
			// stops when closing paranthese is found
			while(chars != ')'){

				wordToAdd += chars;
				infile.get(chars);
			}

			// Adding link to allLinks set
			allLinks.push_back(wordToAdd);

			// clears string for new words
			wordToAdd.clear();

			paren_count--;
		}

		// checking for close bracket
		if(chars == '['){

			brack_count++;
			infile.get(chars);

			// looping through each character when an opening bracket is found.
			// stops when closing bracket is found
			while(chars != ']'){

				// adds it if it's not a special character
				if(isalpha(chars)){

					wordToAdd += chars;
				}

				// adds word to allWords set and clears the word
				// for new string
				if(!isalpha(chars)){

					transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
					allWords.insert(wordToAdd);
					wordToAdd.clear();
				}

				infile.get(chars);

				// insert word into allWords set
				// if there is another word after the special character
				if(chars == ']' && wordToAdd.length() > 0){

					transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
					allWords.insert(wordToAdd);
				}
			}
			
			wordToAdd.clear();

			brack_count--;
		}

		// keeps adding characters into string as long as they are not
		// special characters
		if(isalpha(chars)){

			wordToAdd += chars;
		}

		// clears current string when special character is found.
		// adds string to allWords set
		if(!isalpha(chars) && paren_count == 0 && brack_count == 0 && wordToAdd.length() > 0){

			transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
			allWords.insert(wordToAdd);

			wordToAdd.clear();
		}
	}

	infile.close();
}
