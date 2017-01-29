#include "front_end.h"
#include <sstream>

using namespace std;

FrontEnd::FrontEnd(string argv)
{

	// Parser declarations
	parser = new Parser();

  	searches.add_parse_from_index_file(argv, parser);

	// Overall layout
	overallLayout = new QVBoxLayout();

	// Grid Layout
	horzLayout = new QHBoxLayout();

	// Lyout for user results
	resultsLayout = new QVBoxLayout();

	// Layout for filters
	filtersLayout = new QVBoxLayout();

	// Layout for search filters
	searchOptionsLayout = new QHBoxLayout();

	// New Window Results
	newWinResults = new QTextEdit();
	newWinResults->setReadOnly(true);
	newWinResultsLayout = new QHBoxLayout();

	// Incoming and Outgoing Results Layout/Widgets
	incResults = new QListWidget();
	connect(incResults, SIGNAL(currentRowChanged(int)), this, SLOT(inLinkClicked(int)));

	outResults = new QListWidget();
	connect(outResults, SIGNAL(currentRowChanged(int)), this, SLOT(outLinkClicked(int)));

	linkFilter = new QLabel();
	searchFilter = new QLabel("Search Options:");

	closeButton = new QPushButton("Close");
	connect(closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));

	// Adding the text boxes to new window
	newWinResultsLayout->addWidget(newWinResults);
	newWinResultsLayout->addWidget(incResults);
	newWinResultsLayout->addWidget(outResults);

	// Search filter buttons for new window
	newFileNameButton = new QRadioButton("Filename");
	newFileNameButton->setCheckable(true);
	newFileNameButton->setChecked(true);
	connect(newFileNameButton, SIGNAL(clicked()), this, SLOT(reSortLinks()));

	newIncomeButton = new QRadioButton("Incoming Links");
	newIncomeButton->setCheckable(true);
	connect(newIncomeButton, SIGNAL(clicked()), this, SLOT(reSortLinks()));

	newOutgoingButton = new QRadioButton("Outgoing Links");
	newOutgoingButton->setCheckable(true);
	connect(newOutgoingButton, SIGNAL(clicked()), this, SLOT(reSortLinks()));

	// Other Window
	otherLayout = new QHBoxLayout();
	otherWin = new QWidget();

	// Adding the widgets to the new window
	filtersLayout->addWidget(linkFilter);
	filtersLayout->addWidget(newFileNameButton);
	filtersLayout->addWidget(newIncomeButton);
	filtersLayout->addWidget(newOutgoingButton);
	filtersLayout->addWidget(closeButton);

	otherLayout->addLayout(filtersLayout);

	// Adding results layout to the new window layout
	otherLayout->addLayout(newWinResultsLayout);
	otherWin->setLayout(otherLayout);

	// Results widget
	results = new QListWidget();
	connect(results, SIGNAL(currentRowChanged(int)), this, SLOT(openWindow(int)));
	resultsLayout->addWidget(results);

	// Result label
	resultLabel = new QLabel();
	overallLayout->addWidget(resultLabel);

	// Error messages
	errorMessage = new QLabel();
	overallLayout->addWidget(errorMessage);

	// Search Label
	searchLabel = new QLabel();
	overallLayout->addWidget(searchLabel);
	searchLabel->setText("Search Filters:");

	// Button Group
	searchGroup = new QButtonGroup();

	// Searching option buttons for main window
	filenameButton = new QRadioButton("Filename");
	filenameButton->setCheckable(true);
	filenameButton->setChecked(true);
	horzLayout->addWidget(filenameButton);
	connect(filenameButton, SIGNAL(clicked()), this, SLOT(update()));

	incomingButton = new QRadioButton("Incoming Links");
	incomingButton->setCheckable(true);
	horzLayout->addWidget(incomingButton);
	connect(incomingButton, SIGNAL(clicked()), this, SLOT(update()));

	outgoingButton = new QRadioButton("Outgoing Links");
	outgoingButton->setCheckable(true);
	horzLayout->addWidget(outgoingButton);
	connect(outgoingButton, SIGNAL(clicked()), this, SLOT(update()));

	pageRankButton = new QRadioButton("Pagerank");
	pageRankButton->setCheckable(true);
	horzLayout->addWidget(pageRankButton);
	connect(pageRankButton, SIGNAL(clicked()), this, SLOT(update()));

	// Separating these buttons from the AND, OR, SINGLE buttons
	searchGroup->addButton(filenameButton);
	searchGroup->addButton(incomingButton);
	searchGroup->addButton(outgoingButton);
	searchGroup->addButton(pageRankButton);

	overallLayout->addLayout(horzLayout);

	// Search Button
	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	overallLayout->addWidget(searchButton);

	overallLayout->addWidget(searchFilter);

	// Single Search Button
	singleButton = new QRadioButton("SINGLE");
	singleButton->setCheckable(true);
	singleButton->setChecked(true);

	// AND Button
	AndButton = new QRadioButton("AND");
	AndButton->setCheckable(true);

	// OR Button
	OrButton = new QRadioButton("OR");
	OrButton->setCheckable(true);

	searchOptionsLayout->addWidget(singleButton);
	searchOptionsLayout->addWidget(AndButton);
	searchOptionsLayout->addWidget(OrButton);

	overallLayout->addLayout(searchOptionsLayout);

	// Search Box
	searchInfo = new QLineEdit();
	overallLayout->addWidget(searchInfo);
	connect(searchInfo, SIGNAL(returnPressed()), this, SLOT(search()));

	// Quit Button
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
	
	// Results Page
	overallLayout->addLayout(resultsLayout);

	// Quit Button
	overallLayout->addWidget(quitButton);

	// Set overall layout
	setLayout(overallLayout);
}

FrontEnd::~FrontEnd()
{
	
}

void FrontEnd::search()
{	
	webpagesVector.clear();
	results->clear();
	otherWin->hide();

	// Vector that stores each word the user types
	// individually
	vector<string> user_input;

	// Getting the string the user typed
	string input = searchInfo->text().toStdString();

	// Using the parse function to get each individual word of the user
	user_input = parse_user_input(input);
	unsigned int size_of_user_input = user_input.size();
		
	// Checking to see whether the AND, OR, SINGLE button
	// has been toggled
	if(buttonChecked(OrButton) && user_input.size() > 1){

	  // Gets the webpage for the first word
      MySet<WebPage*> setWebPage = searches.getSetWebPage(user_input[1]);
      MySet<WebPage*> next;

      // Loops through all the user words
      for(unsigned int i = 2; i < size_of_user_input; i ++){

        // Gets the next webpage
        next = searches.getSetWebPage(user_input[i]);

        // Gets the union of all the webpages
        setWebPage = setWebPage.set_union(next);
      }

      // Displays the hits and the content of each of the webpages
      display_results(setWebPage); 


	} else if(buttonChecked(OrButton) && user_input.size() <= 1){

		errorMessage->setText("Need more words in the query! \n");
		return;

	} else if(buttonChecked(AndButton) && user_input.size() > 1){

	  // Gets the webpage for the first word
      MySet<WebPage*> setWebPage = searches.getSetWebPage(user_input[1]);
      MySet<WebPage*> next;


      // Loops through all the words given by the user
      for(unsigned int i = 2; i < size_of_user_input; i ++){

        // Gets the next webpage to compare
        next = searches.getSetWebPage(user_input[i]);

        // Gets the intersection of each webpage that corresponds
        // with each word
        setWebPage = setWebPage.set_intersection(next);
      }

      // Displays hits and each of the content for each of the webpages
      display_results(setWebPage);


	} else if(buttonChecked(AndButton) && user_input.size() <= 1){

		errorMessage->setText("Need more words in the query! \n");
		return;

	} else if(buttonChecked(singleButton) && user_input.size() == 1){

	  // Gets the webpage that corresponds to this word
      MySet<WebPage*> setWebPage = searches.getSetWebPage(user_input[0]);

      // Displays the hits for this word and
      // the content of its webpages
      display_results(setWebPage);

	} else if(buttonChecked(singleButton) && user_input.size() < 1){

		errorMessage->setText("You need to add a word in the query! \n");
		return;

	} else if(buttonChecked(singleButton) && user_input.size() > 1){

		errorMessage->setText("Only one word can be in the query! \n");
		return;
	}

	// Text displays at top if user doesn't type anything
	// or if the user typed in something
	if(searchInfo->text().isEmpty()){

		resultLabel->setText("You did not search for anything :( \n");
	}

	// Clearing
	errorMessage->setText("");
	resultLabel->setText("");
}

void FrontEnd::display_results(MySet<WebPage*> mySet){

	// Checks to see which button is pressed/checked
	if(filenameButton->isChecked()){

		vector<WebPage*> tempVec;
		AlphaStrComp alpha;	

		set<WebPage*>::iterator it;

		// Expanding the search results
		MySet<WebPage*> tempIncomingLinksSet;
		MySet<WebPage*> tempOutgoingLinksSet;
		MySet<WebPage*> linkUnionSet;
		
		for(it = mySet.begin(); it != mySet.end(); ++it){

			// Getting incoming and outgoing links for each webpage
			// and storing it into temporary vectors
			tempIncomingLinksSet = (*it)->incoming_links();
			tempOutgoingLinksSet = (*it)->outgoing_links();

			tempVec.push_back(*it);
			webpagesVector.push_back(*it);
		}

		// Performing a set union so we get all the links associated to the search result
		// (Expanding our search results)
		linkUnionSet = tempIncomingLinksSet.set_union(tempOutgoingLinksSet);
		set<WebPage*>::iterator linkIt;

		// Adding each new webpage to tempVec so our output results will be larger
		for(linkIt = linkUnionSet.begin(); linkIt != linkUnionSet.end(); ++linkIt){

			tempVec.push_back(*linkIt);
			webpagesVector.push_back(*linkIt);
		}
		
		double sizeOfVec = tempVec.size();

		// Page rank algorithm
		map<WebPage*, double> oldPageRank;
  		map<WebPage*, double> currPageRank;

  		// Setting initial page rank of each webpage to 1/n
		for(unsigned int i = 0; i < tempVec.size(); i++){

			tempVec[i]->setPageValue(1/sizeOfVec);
			oldPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
			currPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
		}

		// change 20 to a variable for config files
		for(int i = 0; i < 20; i++){
			for(unsigned int j = 0; j < tempVec.size(); j++){

				double summation = 0.0;

				MySet<WebPage*> in_Links = tempVec[j]->incoming_links();
				set<WebPage*>::iterator in_links_it;

				for(in_links_it = in_Links.begin(); in_links_it != in_Links.end(); ++in_links_it){

					double num_out_links = 0.0;
					num_out_links = (double)(*in_links_it)->outgoing_links().size();

					map<WebPage*, double>::iterator map_it;
					map_it = oldPageRank.find(*in_links_it);

					double currRank = 0;
					currRank = map_it->second;

					summation += currRank/num_out_links;

					// Change .15 to a variable
				}

				currPageRank[tempVec[i]] = (.85 * summation) + .15/(tempVec.size());
			}

			oldPageRank = currPageRank;
		}

		for(unsigned int i = 0; i < tempVec.size(); i++){

			map<WebPage*, double>::iterator tempIt = currPageRank.find(tempVec[i]);

			if(tempIt != currPageRank.end()){

				tempVec[i]->setPageValue(tempIt->second);
			}
		}

		// Sorts the webpages
		helperMerge(tempVec, alpha);
		helperMerge(webpagesVector, alpha);

		// Displays the filename/size/links to screen
		for(unsigned int i = 0; i < tempVec.size(); i++){

			stringstream ss;

			ss << "Filename is: " << tempVec[i]->filename() << " Incoming links size: "
			   << tempVec[i]->incoming_links().size();
			ss << " Outgoing links size: " << tempVec[i]->outgoing_links().size()
			   << " Pagerank: " << tempVec[i]->getPageValue();

			QString screenText;
			screenText = QString::fromStdString(ss.str());
			results->addItem(screenText);
 
		}

	} else if(incomingButton->isChecked()){

		vector<WebPage*> tempVec;
		IncomingLinkComp income;

		set<WebPage*>::iterator it;

		// Expanding the search results
		MySet<WebPage*> tempIncomingLinksSet;
		MySet<WebPage*> tempOutgoingLinksSet;
		MySet<WebPage*> linkUnionSet;
		
		for(it = mySet.begin(); it != mySet.end(); ++it){

			// Getting incoming and outgoing links for each webpage
			// and storing it into temporary vectors
			tempIncomingLinksSet = (*it)->incoming_links();
			tempOutgoingLinksSet = (*it)->outgoing_links();

			tempVec.push_back(*it);
			webpagesVector.push_back(*it);
		}	

		// Performing a set union so we get all the links associated to the search result
		linkUnionSet = tempIncomingLinksSet.set_union(tempOutgoingLinksSet);
		set<WebPage*>::iterator linkIt;
		// Adding each new webpage to tempVec so our output results will be larger
		for(linkIt = linkUnionSet.begin(); linkIt != linkUnionSet.end(); ++linkIt){

			tempVec.push_back(*linkIt);
			webpagesVector.push_back(*linkIt);
		}

		double sizeOfVec = tempVec.size();

		// Page rank algorithm
		map<WebPage*, double> oldPageRank;
  		map<WebPage*, double> currPageRank;

  		// Setting initial page rank of each webpage to 1/n
		for(unsigned int i = 0; i < tempVec.size(); i++){

			tempVec[i]->setPageValue(1/sizeOfVec);
			oldPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
			currPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
		}

		// change 20 to a variable for config files
		for(int i = 0; i < 20; i++){
			for(unsigned int j = 0; j < tempVec.size(); j++){

				double summation = 0.0;

				MySet<WebPage*> in_Links = tempVec[j]->incoming_links();
				set<WebPage*>::iterator in_links_it;

				for(in_links_it = in_Links.begin(); in_links_it != in_Links.end(); ++in_links_it){

					double num_out_links = 0.0;
					num_out_links = (double)(*in_links_it)->outgoing_links().size();

					map<WebPage*, double>::iterator map_it;
					map_it = oldPageRank.find(*in_links_it);

					double currRank = 0;
					currRank = map_it->second;

					summation += currRank/num_out_links;

					// Change .15 to a variable
				}

				currPageRank[tempVec[i]] = (.85 * summation) + .15/(tempVec.size());
			}

			oldPageRank = currPageRank;
		}

		for(unsigned int i = 0; i < tempVec.size(); i++){

			map<WebPage*, double>::iterator tempIt = currPageRank.find(tempVec[i]);

			if(tempIt != currPageRank.end()){

				tempVec[i]->setPageValue(tempIt->second);
			}
		}

		// Sorts the webpages
		helperMerge(tempVec, income);
		helperMerge(webpagesVector, income);

		for(unsigned int i = 0; i < tempVec.size(); i++){

			stringstream ss;

			ss << "Filename is: " << tempVec[i]->filename() << " Incoming links size: "
			   << tempVec[i]->incoming_links().size();
			ss << " Outgoing links size: " << tempVec[i]->outgoing_links().size()
			   << " Pagerank: " << tempVec[i]->getPageValue();

			QString screenText;
			screenText = QString::fromStdString(ss.str());
			results->addItem(screenText);
 
		}

	} else if(outgoingButton->isChecked()){

		vector<WebPage*> tempVec;
		OutgoingLinkComp outgoing;

		set<WebPage*>::iterator it;

		// Expanding the search results
		MySet<WebPage*> tempIncomingLinksSet;
		MySet<WebPage*> tempOutgoingLinksSet;
		MySet<WebPage*> linkUnionSet;
		
		for(it = mySet.begin(); it != mySet.end(); ++it){

			// Getting incoming and outgoing links for each webpage
			// and storing it into temporary vectors
			tempIncomingLinksSet = (*it)->incoming_links();
			tempOutgoingLinksSet = (*it)->outgoing_links();

			tempVec.push_back(*it);
			webpagesVector.push_back(*it);
		}	

		// Performing a set union so we get all the links associated to the search result
		linkUnionSet = tempIncomingLinksSet.set_union(tempOutgoingLinksSet);
		set<WebPage*>::iterator linkIt;
		// Adding each new webpage to tempVec so our output results will be larger
		for(linkIt = linkUnionSet.begin(); linkIt != linkUnionSet.end(); ++linkIt){

			tempVec.push_back(*linkIt);
			webpagesVector.push_back(*linkIt);
		}

		double sizeOfVec = tempVec.size();

		// Page rank algorithm
		map<WebPage*, double> oldPageRank;
  		map<WebPage*, double> currPageRank;

  		// Setting initial page rank of each webpage to 1/n
		for(unsigned int i = 0; i < tempVec.size(); i++){

			tempVec[i]->setPageValue(1/sizeOfVec);
			oldPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
			currPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
		}

		// change 20 to a variable for config files
		for(int i = 0; i < 20; i++){
			for(unsigned int j = 0; j < tempVec.size(); j++){

				double summation = 0.0;

				MySet<WebPage*> in_Links = tempVec[j]->incoming_links();
				set<WebPage*>::iterator in_links_it;

				for(in_links_it = in_Links.begin(); in_links_it != in_Links.end(); ++in_links_it){

					double num_out_links = 0.0;
					num_out_links = (double)(*in_links_it)->outgoing_links().size();

					map<WebPage*, double>::iterator map_it;
					map_it = oldPageRank.find(*in_links_it);

					double currRank = 0;
					currRank = map_it->second;

					summation += currRank/num_out_links;

					// Change .15 to a variable
				}

				currPageRank[tempVec[i]] = (.85 * summation) + .15/(tempVec.size());
			}

			oldPageRank = currPageRank;
		}

		for(unsigned int i = 0; i < tempVec.size(); i++){

			map<WebPage*, double>::iterator tempIt = currPageRank.find(tempVec[i]);

			if(tempIt != currPageRank.end()){

				tempVec[i]->setPageValue(tempIt->second);
			}
		}

		// Sorts the webpages
		helperMerge(tempVec, outgoing);
		helperMerge(webpagesVector, outgoing);

		for(unsigned int i = 0; i < tempVec.size(); i++){

			stringstream ss;

			ss << "Filename is: " << tempVec[i]->filename() << " Incoming links size: " 
			   << tempVec[i]->incoming_links().size();
			ss << " Outgoing links size: " << tempVec[i]->outgoing_links().size()
			   << " Pagerank: " << tempVec[i]->getPageValue();

			QString screenText;
			screenText = QString::fromStdString(ss.str());
			results->addItem(screenText);
		}

	} else if(pageRankButton->isChecked()){

		vector<WebPage*> tempVec;
		PageRankComp pageRankComp;

		set<WebPage*>::iterator it;

		// Expanding the search results
		MySet<WebPage*> tempIncomingLinksSet;
		MySet<WebPage*> tempOutgoingLinksSet;
		MySet<WebPage*> linkUnionSet;
		
		for(it = mySet.begin(); it != mySet.end(); ++it){

			// Getting incoming and outgoing links for each webpage
			// and storing it into temporary vectors
			tempIncomingLinksSet = (*it)->incoming_links();
			tempOutgoingLinksSet = (*it)->outgoing_links();

			tempVec.push_back(*it);
			webpagesVector.push_back(*it);
		}	

		// Performing a set union so we get all the links associated to the search result
		linkUnionSet = tempIncomingLinksSet.set_union(tempOutgoingLinksSet);
		set<WebPage*>::iterator linkIt;
		// Adding each new webpage to tempVec so our output results will be larger
		for(linkIt = linkUnionSet.begin(); linkIt != linkUnionSet.end(); ++linkIt){

			tempVec.push_back(*linkIt);
			webpagesVector.push_back(*linkIt);
		}

		double sizeOfVec = tempVec.size();

		// Page rank algorithm
		map<WebPage*, double> oldPageRank;
  		map<WebPage*, double> currPageRank;

  		// Setting initial page rank of each webpage to 1/n
		for(unsigned int i = 0; i < tempVec.size(); i++){

			tempVec[i]->setPageValue(1/sizeOfVec);
			oldPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
			currPageRank.insert(make_pair(tempVec[i], 1/sizeOfVec));
		}

		// change 20 to a variable for config files
		for(int i = 0; i < 20; i++){
			for(unsigned int j = 0; j < tempVec.size(); j++){

				double summation = 0.0;

				MySet<WebPage*> in_Links = tempVec[j]->incoming_links();
				set<WebPage*>::iterator in_links_it;

				for(in_links_it = in_Links.begin(); in_links_it != in_Links.end(); ++in_links_it){

					double num_out_links = 0.0;
					num_out_links = (double)(*in_links_it)->outgoing_links().size();

					map<WebPage*, double>::iterator map_it;
					map_it = oldPageRank.find(*in_links_it);

					double currRank = 0;
					currRank = map_it->second;

					summation += currRank/num_out_links;

					// Change .15 to a variable
				}

				currPageRank[tempVec[i]] = (.85 * summation) + .15/(tempVec.size());
			}

			oldPageRank = currPageRank;
		}

		for(unsigned int i = 0; i < tempVec.size(); i++){

			map<WebPage*, double>::iterator tempIt = currPageRank.find(tempVec[i]);

			if(tempIt != currPageRank.end()){

				tempVec[i]->setPageValue(tempIt->second);
			}
		}

		// Sorts the webpages
		helperMerge(tempVec, pageRankComp);
		helperMerge(webpagesVector, pageRankComp);

		for(unsigned int i = 0; i < tempVec.size(); i++){

			stringstream ss;

			ss << "Filename is: " << tempVec[i]->filename() << " Incoming links size: " 
			   << tempVec[i]->incoming_links().size();
			ss << " Outgoing links size: " << tempVec[i]->outgoing_links().size() 
			   << " Pagerank: " << tempVec[i]->getPageValue();

			QString screenText;
			screenText = QString::fromStdString(ss.str());
			results->addItem(screenText);
		}
	}
}

// Helper function for checking which button has been toggled
bool FrontEnd::buttonChecked(QRadioButton* testButton){

	if(testButton->isChecked()){

		return true;
	}

	return false;
}

// Helper function that parses the user input and stores
// all the words individually in a vector
vector<string> FrontEnd::parse_user_input(string var){

  vector<string> splitWords;

  string word;

  for(unsigned int i = 0; i < var.length(); i++){

    if(var[i] == ' ' && word.size() > 0){

      // Doesn't store AND and OR as lowercase letters
      if(word != "AND" && word != "OR"){

        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // Adds "word" to splitWords vector
        splitWords.push_back(word);
        word.clear();

        // Iterates i so a space isn't added into the vector
        i++;

      } else {

        // Pushes back other words normally
        splitWords.push_back(word);
        word.clear();

        i++;
      }
    }

    // Keeps adding the characters into "word" string
    word += var[i];

    // Adds the last word to the vector
    if(i == var.length()-1 && word.length() > 0){

      // Transform to lower case
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      splitWords.push_back(word);
    }
  }

  return splitWords;
}

// Quits
void FrontEnd::quit(){

	QApplication::exit();
}

void FrontEnd::update(){

	// Updates the window when the user types in
	// a new search query
	if(results->count() > 0){

		search();
	}
}

// Helps to open up the new window
void FrontEnd::openWindow(int var){

	if(var < 0){

		results->clear();
		newWinResults->clear();
		incResults->clear();
		outResults->clear();

		otherWin->hide();
		return;
	}

	// Putting the name of the files in the new window
	string temp = "Search Filters: " + webpagesVector[var]->filename();
	QString qtemp = QString::fromStdString(temp);
	linkFilter->setText(qtemp);

	newWinResults->clear();
	incResults->clear();
	outResults->clear();

	// Displaying to screen
	stringstream ss;
	QString stringTemp;
	ss << *(webpagesVector[var]);
	stringTemp = QString::fromStdString(ss.str());
	newWinResults->append(stringTemp);

	// Getting the incoming links
	MySet<WebPage*> inLinksSet;
	inLinksSet = webpagesVector[var]->incoming_links();
	incomingLinks = getLinks(inLinksSet);

	// Getting the outgoing links
	MySet<WebPage*> outLinksSet;
	outLinksSet = webpagesVector[var]->outgoing_links();
	outgoingLinks = getLinks(outLinksSet);

	// Sorting incoming and outgoing links
	sortInOutLinks();
	// Refreshes the links
	populateInOutList();

	otherWin->show();
}

void FrontEnd::closeWindow(){

	otherWin->hide();
}

// Gets the links for each webpage
vector<WebPage*> FrontEnd::getLinks(MySet<WebPage*> tempSet){

	MySet<WebPage*>::iterator it;

	vector<WebPage*> temp_vec;

	for(it = tempSet.begin(); it != tempSet.end(); ++it){

		temp_vec.push_back((*it));
	}

	return temp_vec;
}

// Writes out the incoming and outgoing links for
// the link that the user chooses
void FrontEnd::populateInOutList(){

	for(unsigned int i = 0; i < incomingLinks.size(); i++){

		QString temp;
		stringstream word;
		word << "filename: " << incomingLinks[i]->filename();
		word << " incoming: " << incomingLinks[i]->incoming_links().size();
		word << " outgoing: " << incomingLinks[i]->outgoing_links().size();
		temp = QString::fromStdString(word.str());
		incResults->addItem(temp);
	}

	for(unsigned int j = 0; j < outgoingLinks.size(); j++){

		QString temp;
		stringstream word;
		word << "filename: " << outgoingLinks[j]->filename();
		word << " incoming: " << outgoingLinks[j]->incoming_links().size();
		word << " outgoing: " << outgoingLinks[j]->outgoing_links().size();
		temp = QString::fromStdString(word.str());
		outResults->addItem(temp);
	}
}

// Sorting the links based on the criteria the user chose
void FrontEnd::sortInOutLinks(){

	AlphaStrComp alpha;
	IncomingLinkComp income;
	OutgoingLinkComp outgoing;

	if(newFileNameButton->isChecked()){
		helperMerge(incomingLinks, alpha);
		helperMerge(outgoingLinks, alpha);
	
	} else if(newIncomeButton->isChecked()){

		helperMerge(incomingLinks, income);
		helperMerge(outgoingLinks, income);
	
	} else if(newOutgoingButton->isChecked()){

		helperMerge(incomingLinks, outgoing);
		helperMerge(outgoingLinks, outgoing);	
	}
}

// Resorts the links when the user changes the sorting
// criteria
void FrontEnd::reSortLinks(){
	incResults->clear();
	outResults->clear();

	sortInOutLinks();
	populateInOutList();
}

// Updates the information on the screen when the user
// clicks on an incoming links
void FrontEnd::inLinkClicked(int tar){

	if(tar < 0){

		return;
	}

	WebPage* tempPage = incomingLinks[tar];
	incomingLinks.clear();
	outgoingLinks.clear();
	incomingLinks = getLinks(tempPage->incoming_links());
	outgoingLinks = getLinks(tempPage->outgoing_links());

	reSortLinks();
	incResults->setCurrentRow(-1);
	outResults->setCurrentRow(-1);

	newWinResults->clear();
	stringstream ss;
	QString stringTemp;
	ss << *tempPage;
	stringTemp = QString::fromStdString(ss.str());
	newWinResults->append(stringTemp);

	string temp = "Search Filters: " + tempPage->filename();
	QString qtemp = QString::fromStdString(temp);
	linkFilter->setText(qtemp);

}

// Updates the information on the screen when the user
// clicks on an outgoing links
void FrontEnd::outLinkClicked(int tar){

	if(tar < 0){

		return;
	}

	WebPage* tempPage = outgoingLinks[tar];
	incomingLinks.clear();
	outgoingLinks.clear();
	incomingLinks = getLinks(tempPage->incoming_links());
	outgoingLinks = getLinks(tempPage->outgoing_links());

	reSortLinks();

	newWinResults->clear();
	stringstream ss;
	QString stringTemp;
	ss << *tempPage;
	stringTemp = QString::fromStdString(ss.str());
	newWinResults->append(stringTemp);

	string temp = "Search Filters: " + tempPage->filename();
	QString qtemp = QString::fromStdString(temp);
	linkFilter->setText(qtemp);
}