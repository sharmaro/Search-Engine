#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include "myset.h"
#include "pageparser.h"

using namespace std;

class WebPage
{
 public:
  WebPage();

  WebPage(std::string filename);

  ~WebPage();

  /**
   * Sets the filename/URL of this webpage
   */
  void filename(std::string fname);

  /**
   * Returns the filename/URL of this webpage
   */
  std::string filename() const;

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
  void all_words(const MySet<string>& words);

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  MySet<string> all_words() const;

  /**
   * Adds a webpage that links to this page
   */
  void add_incoming_link(WebPage* wp);

  /**
   * Returns all webpages that link to this page
   */
  MySet<WebPage*> incoming_links() const;

  /**
   * Adds a webpage that this page links to
   */
  void add_outgoing_link(WebPage* wp);

  /**
   * Returns all webpages this page links to
   */
  MySet<WebPage*> outgoing_links() const;

  /**
   * Displays the webpage text to the screen 
   */
  friend std::ostream & operator<< (std::ostream & os, const WebPage & page);

  /**** Add other desired member functions here *****/

  void setPageValue(double rank);
  double getPageValue();

 private:
  /**** Add other desired data members here *****/

  MySet<string> stringSet;

  MySet<WebPage*> pages_in;
  MySet<WebPage*> pages_out;

  string file_name;

  double pageRank;
  
};

struct AlphaStrComp{

  bool operator()(const WebPage* lhs, const WebPage* rhs){

    return lhs->filename() <= rhs->filename();
  }

};

struct IncomingLinkComp{

  bool operator()(const WebPage*lhs, const WebPage* rhs){

    return lhs->incoming_links().size() <= rhs->incoming_links().size();
  }

};

struct OutgoingLinkComp{
  bool operator()(const WebPage* lhs, const WebPage* rhs){

    return lhs->outgoing_links().size() <= rhs->outgoing_links().size();
  }
};

struct PageRankComp{
  bool operator()(WebPage* lhs, WebPage* rhs){

    return lhs->getPageValue() >= rhs->getPageValue();
  }

};
#endif
