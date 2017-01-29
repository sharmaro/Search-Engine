#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "searcheng.h"
#include "webpage.h"
#include "msort.h"

using namespace std;

class FrontEnd : public QWidget
{
	Q_OBJECT
public:
	FrontEnd(string);
	~FrontEnd();
	vector<string> parse_user_input(string var);
	void display_results(MySet<WebPage*> mySet);
	vector<WebPage*> getLinks(MySet<WebPage*> tempSet);
	void populateInOutList();
	void sortInOutLinks();

private slots:
	void search();
	bool buttonChecked(QRadioButton*);
	void quit();
	void update();
	void openWindow(int);
	void reSortLinks();
	void inLinkClicked(int);
	void outLinkClicked(int);
	void closeWindow();

private:
	// Layout
	QVBoxLayout* overallLayout;

	// Result label
	QLabel* resultLabel;
	QLabel* errorMessage;
	QLabel* searchLabel;

	// Push Buttons
	QPushButton* searchButton;
	QPushButton* quitButton;

	QRadioButton* filenameButton;
	QRadioButton* incomingButton;
	QRadioButton* outgoingButton;

	// Radio Buttons
	QRadioButton* singleButton;
	QRadioButton* OrButton;
	QRadioButton* AndButton;

	QHBoxLayout* searchOptionsLayout;

	// Search Box
	QLineEdit* searchInfo;

	// Horizontal Layout
	QHBoxLayout* horzLayout;
	QHBoxLayout* horzLayout2;

	// Button groups
	QButtonGroup* searchGroup;

	// Results 
	QListWidget* results;
	QVBoxLayout* resultsLayout;

	SearchEng searches;
  	Parser *parser;

  	// New Window
  	QHBoxLayout* otherLayout;
  	QWidget* otherWin;

  	// New Window Results
  	QHBoxLayout* newWinResultsLayout;

  	QTextEdit* newWinResults;
  	QListWidget* incResults;
  	QListWidget* outResults;

  	QRadioButton* newFileNameButton;
	QRadioButton* newIncomeButton;
	QRadioButton* newOutgoingButton;

	QLabel* linkFilter;
	QLabel* searchFilter;

	QVBoxLayout* filtersLayout;

  	vector<WebPage*> webpagesVector;
  	vector<WebPage*> incomingLinks;
  	vector<WebPage*> outgoingLinks;

  	MySet<string> setOfStrings;

  	QLabel* nameOfWindow;

  	QPushButton* closeButton;

  	QRadioButton* pageRankButton;
};