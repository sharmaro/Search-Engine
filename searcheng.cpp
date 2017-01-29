#include "searcheng.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

SearchEng::SearchEng(){}

SearchEng::~SearchEng(){}

void SearchEng::add_parse_page(std::string filename, Parser* parser){

  		// Creating empty set for outgoing links
  		MySet<string> links_out;

  		// Creating tempSet for passing it into
  		// the parse function
  		MySet<string> tempSet;

  		// Instantiating a new webPage with the given
  		// filename
  		WebPage *myWebPage = getWebPage(filename);

  		// Giving tempSet the set of all words
  		tempSet = myWebPage->all_words();

  		// Parsing file to get all the words and links in the
  		// right sets
  		parser->parse(myWebPage->filename(), tempSet, links_out);

  		// Declaring iterator for looping through all
  		// the words
  		set<string>::iterator it;

  		// Looping through stringSet/tempSet for all the words
  		for(it = tempSet.begin(); it != tempSet.end(); ++it){

  			// Declaring a new web page set to put into
  			// the map's value
  			MySet<WebPage*> tempWebPage;

  			// Iterator for map
  			map<string, MySet<WebPage*> >::iterator map_find;
  			// Getting the iterator/location for the given string
  			map_find = myMap.find(*it);

  			// If string is in the map already
  			if(map_find != myMap.end()){

  				// Declare a temp set of web pages
  				MySet<WebPage*> temp;

  				// Getting the value of the given string (map's value)
				  temp = map_find->second;
				  // Inserting additional webpages into existing set
				  temp.insert(myWebPage);

				  // Updating map to include the mutltiple webpages
				  // where the given word appears
				  myMap[*it] = temp;
  			
  			} else {

  				// If word is not in the map
  				// insert webpage into the set of webpages
				  tempWebPage.insert(myWebPage);
				  // Simply make a new pair in the map variable
  				myMap.insert(make_pair(*it, tempWebPage));  				
			 }
  		}

      MySet<string>::iterator links;
      for(links = links_out.begin(); links != links_out.end(); ++links){

        WebPage *tempPage = getWebPage(*links);
        tempPage->add_incoming_link(myWebPage);
        myWebPage->add_outgoing_link(tempPage);
      }
}
  
void SearchEng::add_parse_from_index_file(std::string index_file, Parser* parser){

  		ifstream infile;
  		// Opening file from index file
  		infile.open(index_file.c_str());

  		string file = "";

  		// Looping through file names in index file
  		while(!infile.fail()){

			   if(infile.fail()){

				    break;
			   }  		

			   // Getting each file name
			   getline(infile,file);

			   if(file.length() > 0){
				 // Calling Parse_page on each file
				  add_parse_page(file, parser);
			   }
  		}
}

  	// Helper function that prints out all the words in ever data file
void SearchEng::printAll(){

  		map<string, MySet<WebPage*> >::iterator it;

  		for(it = myMap.begin(); it != myMap.end(); ++it){

  			cout << it->first << endl;
  		}
}

  	// Helper function that returns the web page set from the map
  	// if the word exists in it
MySet<WebPage*> SearchEng::getSetWebPage(string query){

  		MySet<WebPage*> empty;

      map<string, MySet<WebPage*> >::iterator it;
      it = myMap.find(query);

      if(it != myMap.end()){

        return it->second;
      }

      return empty;
}

WebPage* SearchEng::getWebPage(string target){

      MySet<WebPage*>::iterator it;
      for(it = webpages.begin(); it != webpages.end(); ++it){

        if((*it)->filename() == target){

          return *it;
        }
      }

      WebPage* tempWebPage = new WebPage(target);
      webpages.insert(tempWebPage);
      return tempWebPage;
}