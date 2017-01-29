#include "webpage.h"
#include <iostream>
#include <string>
#include <fstream>
#include "pageparser.h"

using namespace std;

WebPage::WebPage(){}

WebPage::WebPage(string filename){

  	file_name = filename;
    pageRank = 0.0;
}

WebPage::~WebPage(){}

  /**
   * Sets the filename/URL of this webpage
   */
void WebPage::filename(string fname){


  	file_name = fname;

}

  /**
   * Returns the filename/URL of this webpage
   */
string WebPage::filename() const{

  	return file_name;
}

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
void WebPage::all_words(const MySet<string>& words){

  	stringSet.clear();
  	stringSet.set_union(words);
}

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
MySet<string> WebPage::all_words() const{

  	return stringSet;
}

  /**
   * Adds a webpage that links to this page
   */
void WebPage::add_incoming_link(WebPage* wp){

  	pages_in.insert(wp);
}

  /**
   * Returns all webpages that link to this page
   */
MySet<WebPage*> WebPage::incoming_links() const{

  	return pages_in;
}

  /**
   * Adds a webpage that this page links to
   */
void WebPage::add_outgoing_link(WebPage* wp){

  	pages_out.insert(wp);
}

  /**
   * Returns all webpages this page links to
   */
MySet<WebPage*> WebPage::outgoing_links() const{

  	return pages_out;
}

  /**
   * Displays the webpage text to the screen 
   */
ostream& operator<< (ostream & os, const WebPage& page){

  	string file = "";
  	file = page.filename();

  	ifstream infile;
  	infile.open(file.c_str());

  	char chars;


  	// Looping through file until it reaches
  	// the end/fails
  	while(!infile.fail()){

  		infile.get(chars);

  		if(infile.fail()){

  			break;
  		}

  		// Doesn't read the links
  		if(chars == '('){

  			infile.get(chars);

  			// Keeps updating the character that is being read in
  			while(chars != ')'){

  				infile.get(chars);
  			}

  		} else {

  			os << chars;
  		} 
  	}

  	infile.close();

  	return os;
}

void WebPage::setPageValue(double rank){

  pageRank = rank;
}

double WebPage::getPageValue(){

  return pageRank;
}