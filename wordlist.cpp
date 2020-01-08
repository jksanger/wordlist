/* WordList source file
*
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias m_list in any way that would result
*	in undefined behavior. 
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif

// Do not include any other libraries
#include"wordlist.h"
#include<iostream>
#include<cstring>


using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;



/* Function: Wordlist Constructor
*
*	Constructs an empty Wordlist that is allocated enough space to store 
*	max_words many words.  If max_words is less than 1, set m_list to nullptr
*	and the other member variables should be made consistent with this state.  
*/
WordList::WordList(const int max_words) {
	if (max_words < 1) {
		m_list = nullptr;
		m_count = 0;
		m_max = 0;
	}
	else {
		m_list = new char*[max_words];
		for (int i = 0; i < max_words; i++) {
			m_list[i] = new char[20];
		}
		m_count = 0;
		m_max = max_words;
	}
}


/* Function: Wordlist Copy Constructor
*
*	Constructs a Wordlist that is a copy of an existing WordList
*/
WordList::WordList(const WordList &other) {
	if (other.m_max == 0) {
		m_list = nullptr;
		m_count = 0;
		m_max = 0;
	}
	else {
		m_list = new char*[other.m_max];
		for (unsigned int i = 0; i < other.m_max; i++) {
			m_list[i] = new char[20];
		}
		for (unsigned int i = 0; i < other.m_count; i++) {
			strcpy(m_list[i], other.m_list[i]);
		}
		m_count = other.m_count;
		m_max = other.m_max;
	}
}


/* Function: Wordlist Destructor
*
*	Cleans up WordList's dynamically allocated memory.
*/
WordList::~WordList() {
	for (unsigned int i = 0; i < m_max; i++) {
		delete m_list[i];
	}
	delete m_list;

}

/* Function: printList
*
*	Prints all the words in WordList in a single line with spaces between each
*	word, then followed by a newline after the last word. Returns the number 
*	of words printed.  If m_list is nullptr there is nothing to print, return -1. 
*/
int	WordList::print() const {
	if (m_list == nullptr) {
		return -1;
	}
	for (unsigned int i = 0; i < m_count; i++) {
		cout << m_list[i] << " ";
	}
	cout << endl;
	return m_count;

}



/* Function: getAt
*
*	Returns the word at the index position in the WordList.
*	return nullptr if the index is out of bounds.
*/
char* WordList::get(const int index) const {

	if (index >= m_count || index < 0) {
		return nullptr;
	}
	return m_list[index];

}


/* Function: getCount
*
*	Returns the number of words currently stored in WordList.
*/
int	WordList::count() const {

	return m_count;

}


/* Function: addWord
*
*	Adds the word into WordList (words have no spaces).  If WordList does not have
*	enough space to add word, addWord will resize with just enough space to allow for 
*	the addition of word. If addWord needed to resize then return 1, otherwise if there 
*	already enough space to add word without resizing, return 0. If word is empty  
*	do nothing return -1. If m_list was nullptr, everything above still holds true except
*	return -2.  
*/
int	WordList::add(const char word[]) {

	if (strlen(word) == 0) {
		return -1;
	}
	if (m_list == nullptr) {
		m_list = new char*[1];
		m_list[0] = new char[20];
		strcpy(m_list[0], word);
		m_count = 1;
		m_max = 1;
		return -2;
	}
	if (m_count < m_max) {
		strcpy(m_list[m_count], word);
		m_count++;
		return 0;
	}
	char **newList = new char*[m_max + 1];
	for (unsigned int i = 0; i < m_max; i++) {
		newList[i] = new char[20];
		strcpy(newList[i], m_list[i]);
		delete m_list[i];
	}
	newList[m_count] = new char[20];
	strcpy(newList[m_count], word);
	delete m_list;
	m_list = newList;
	m_max++;
	m_count++;
	return 1;

}


/* Funtion: removeWord
*
*	If m_list is nullptr, returns -1.  Otherwise, searches for every
*	occurrence of word[], and removes that word of the list, returns
*	the number of words removed.
*/
int	WordList::remove(const char word[]) {

	if (m_list == nullptr) {
		return -1;
	}
	int occurances = 0;
	for (unsigned int i = 0, j = 0; i < m_count; i++) {
		if (strcmp(word, m_list[i]) != 0) {
			strcpy(m_list[j], m_list[i]);
			j++;
		}
		else {
			occurances++;
		}
	}
	m_count -= occurances;
	return occurances;
}


/* Funtion: appendList
*
*
*	Appends the contents of other to the WordList.  If WordList does 
*	not have enough space appendList should dynamically allocate enough space
*	to append the contents of other to WordList, returns number of words 
*	appended.  If other is nullptr or empty appendList does nothing and 
*	returns -1. If this WordList::m_list is nullptr everything above still 
*	holds but returns -2.
*
*	Note the pointer parameter type as opposed to reference type.
*/
int	WordList::append(const WordList* other) {
	if (other->count() == 0) {
		return -1;
	}
	if (m_list == nullptr) {
		m_list = new char*[other->count()];
		for (int i = 0; i < other->count(); i++) {
			m_list[i] = new char[20];
			strcpy(m_list[i], other->m_list[i]);
		}
		m_count = m_max = other->count();
		return -2;
	}
	if (m_max - m_count >= other->m_count) {
		for (int i = 0; i < other->count(); i++) {
			strcpy(m_list[i + m_count], other->m_list[i]);
		}
		m_count += other->count();
		return other->count();
	}
	char **newList = new char*[m_count + other->count()];
	for (unsigned int i = 0; i < m_count; i++) {
		newList[i] = new char[20];
		strcpy(newList[i], m_list[i]);
		delete m_list[i];
	}
	delete m_list;
	for (int i = 0; i < other->count(); i++) {
		newList[i + m_count] = new char[20];
		strcpy(newList[i + m_count], other->m_list[i]);
	}
	m_list = newList;
	m_max = m_count = m_count + other->count();
	return other->count();

}


/* Funtion: findWord
*
*	Finds the first occurrence of the word in the WordList
*	returns the position of that word in the list.  Otherwise, 
*	if the word is not in the WordList or if m_list is nullptr
*	return -1. 
*/
int WordList::find(const char word[]) const {

	for (unsigned int i = 0; i < m_count; i++) {
		if (strcmp(m_list[i], word) == 0) {
			return i;
		}
	}
	return -1;

}


/* Funtion: sortList
*
*	If m_list is nullptr return -1.  If there is only one word
*	in the list return 1.  Otherwise, sortList sorts the
*	words in WordList in ascending order.  Returns 0 on
*	success.
*/
int	WordList::sort() {

	if (m_list == nullptr) {
		return -1;
	}
	if (m_count == 1) {
		return 1;
	}
	char *temp = new char[20];
	for (unsigned int i = 0; i < m_count - 1; i++) {
		for (unsigned int j = 0; j < m_count - i - 1; j++) {
			if (strcmp(m_list[j], m_list[j + 1]) > 0) {
				strcpy(temp, m_list[j]);
				strcpy(m_list[j], m_list[j + 1]);
				strcpy(m_list[j + 1], temp);
			}
		}
	}
	return 0;

}


/* Funtion: Assignment Operator
*
*	Overload the assignment operator for WordList.  Makes a deep 
*	copy from other to this WordList.  
*/
WordList& WordList::operator=(const WordList &other) {

	for (unsigned int i = 0; i < m_max; i++) {
		delete m_list[i];
	}
	delete m_list;
	m_list = new char*[other.m_max];
	for (unsigned int i = 0; i < other.m_max; i++) {
		m_list[i] = new char[20];
	}
	for (unsigned int i = 0; i < other.m_count; i++) {
		strcpy(m_list[i], other.m_list[i]);
	}
	m_count = other.m_count;
	m_max = other.m_max;
	return *this;
}