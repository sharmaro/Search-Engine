#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>

using namespace std;

// avoid circular reference
class WebPage;

template <class T>
class MySet : public set<T>
{
public:
  MySet();
  MySet set_intersection(const MySet& other);
  MySet set_union(const MySet& other);
};

template <class T>
MySet<T>::MySet() : set<T>() {


}

template <class T>
MySet<T> MySet<T>::set_intersection(const MySet& other) {

	MySet newString;

	class MySet<T>::iterator it1;
	class MySet<T>::iterator it2;

	// Only adding words that appear in both sets
	for(it1 = other.begin(); it1 != other.end(); ++it1){
		for(it2 = this->begin(); it2 != this->end(); ++it2){
			if(*it1 == *it2){
				newString.insert(*it1);
			}
		}
	}

	return newString;
}

template <class T>
MySet<T> MySet<T>::set_union(const MySet& other) {

	MySet newString;

	class MySet<T>::iterator it1;
	class MySet<T>::iterator it2;

	// Adding all words that appear in "other" set
	for(it1 = other.begin(); it1 != other.end(); ++it1){
		newString.insert(*it1);
	}

	// Adding all words that appear in "this" set
	for(it2 = this->begin(); it2 != this->end(); ++it2){
		newString.insert(*it2);
	}

	return newString;
}


#endif
