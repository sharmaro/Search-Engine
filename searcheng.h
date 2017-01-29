#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

using namespace std;

class SearchEng {
 public:

  SearchEng();

  ~SearchEng();

  void add_parse_from_index_file(std::string index_file, 
				 Parser* parser);

  void add_parse_page(std::string filename, 
		      Parser* parser);

  /**** Add other desired member functions here *****/

  void printAll();

  MySet<WebPage*> getSetWebPage(string query);

  WebPage* getWebPage(string target);

 private:
  /**** Add other desired data members here *****/

 	map<string, MySet<WebPage*> > myMap;
  MySet<WebPage*> webpages;
};

#endif
