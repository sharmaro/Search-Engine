#include "pageparser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void Parser::parse(string filename, MySet<string>& allWords, MySet<string>& allLinks){

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
		if(open_paren(chars)){

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
			allLinks.insert(wordToAdd);

			// clears string for new words
			wordToAdd.clear();

			paren_count--;
		}

		// checking for close bracket
		if(open_bracket(chars)){

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

bool Parser::open_paren(char check){

	if(check == '('){

		return true;
	}

	return false;
}

bool Parser::open_bracket(char check){

	if(check == '['){

		return true;
	}

	return false;
}