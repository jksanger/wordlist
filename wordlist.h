/* WordList header file
*
*	This file contains the class definition for the WordList.  
*
*	Do not make any changes to this file.
*
*	Do not submit this file
*
*	Topics: Multilevel Arrays, Pointers, Dynamic Allocation, Classes
*
*/
#ifndef WORDLIST_H
#define WORDLIST_H


/* Globally defined constants
*/
const int MAX_WORD_SIZE = 20;


/* Word List ADT
*
*/
class WordList {

public:
	WordList(const int max_words);
	WordList(const WordList &other);
	~WordList();

	int		print() const; 

	char*	get(const int index) const;

	int		count() const;

	int		add(const char word[]);

	int		remove(const char word[]); 

	int		append(const WordList* other);

	int		find(const char word[]) const;
	
	int		sort();

	WordList& operator=(const WordList &other);

#ifndef MAKE_MEMBERS_PUBLIC 
// If this macro is defined prior to including this header file
// it will ignore the private access specifier, and the member
// variables will be follow the above public specifier.
private:
#endif

	unsigned int m_count;		// Number of words currently in list
	unsigned int m_max;	// The total size of the list.
	char**		 m_list;		// The list storing the words

};

#endif