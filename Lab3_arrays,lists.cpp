#include <iostream>
#include <vector>
//#include <algorithm>

using namespace std;

struct link
{
	char key;
	link * next;
	link * previous;
};

class DoublyLinkedList
{
private:
	link * head;
	link * tail;
public:
	DoublyLinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	
	~DoublyLinkedList() { this->deleteList(); }

	void addLinkInEnd(char symbol);
	void addLinkAfterLink(link * linkToAdd, char symbol);
	void addLinkBeforeLink(link * linkToAdd, char symbol);
	void addLinkInBeginning(char symbol);
	void deleteLink(char symbol);
	void deleteLink(link * deleteLink);
	void deleteFirstLink();
	void deleteLastLink();
	void deleteList();
	void showList();

	bool checkEmpty();
	
	link * getHead() const { return this->head; }
	link * getTail() const { return this->tail; }
	link * search(char searchSymbol);
	
};

bool DoublyLinkedList::checkEmpty(){ return (this->head == NULL); }

void DoublyLinkedList::showList()
{
	link * temp = this->head;
	if (this->head != NULL)
		while (temp != NULL)
		{
			cout << temp->key;
			temp = temp->next;
		}
	else cout << "The list is empty!";
	cout << endl;

	delete temp;
}

link * DoublyLinkedList::search(char searchSymbol)
{

	if (this->checkEmpty())
	{
		cout << "The list is empty!" << endl;
		return NULL;
	}

	link * temp = this->head;
	while (temp != NULL && temp->key != searchSymbol)
		temp = temp->next;
	return temp;
}

void DoublyLinkedList::addLinkInBeginning(char symbol)
{
	link * newlink = new link;
	newlink->key = symbol;

	newlink->next = this->head;
	if (this->head != NULL)
		this->head->previous = newlink;
	this->head = newlink;
	newlink->previous = NULL;	

	if (this->tail == NULL)
		tail = newlink;
}

void DoublyLinkedList::addLinkInEnd(char symbol)
{
	link * newlink = new link;
	newlink->key = symbol;

	newlink->previous = this->tail;
	if (this->tail != NULL)
		this->tail->next = newlink;
	this->tail = newlink;
	newlink->next = NULL;

	if (this->head == NULL)
		head = newlink;
}

void DoublyLinkedList::addLinkAfterLink(link * linkToAdd, char symbol)
{
	link * newlink = new link;
	newlink->key = symbol;

	if (linkToAdd->previous != NULL)
		linkToAdd->previous->next = newlink;
	newlink->next = linkToAdd;
	newlink->previous = linkToAdd->previous;
	linkToAdd->previous = newlink;
}

void DoublyLinkedList::addLinkBeforeLink(link * linkToAdd, char symbol)
{
	link * newlink = new link;
	newlink->key = symbol;

	if (linkToAdd->next != NULL)
		linkToAdd->next->previous = newlink;
	newlink->next = linkToAdd->next;
	newlink->previous = linkToAdd;
	linkToAdd->next = newlink;
}

void DoublyLinkedList::deleteLink(char symbol)
{

	if (this->checkEmpty())
	{
		cout << "The list is empty!" << endl;
		return;
	}

	link * temp = search(symbol);
	if (temp != NULL)
	{
		if (temp->previous != NULL)
			temp->previous->next = temp->next;
		else this->head = temp->next;
		if (temp->next != NULL)
			temp->next->previous = temp->previous;
		else this->tail = temp->previous;
	}
	else cout << "This list doesn't have element \"" << symbol << "\"!" << endl;
	delete temp;
}

void DoublyLinkedList::deleteLink(link * deleteLink)
{
	if (deleteLink != NULL)
	{
		if (deleteLink->previous != NULL)
			deleteLink->previous->next = deleteLink->next;
		else this->head = deleteLink->next;
		if (deleteLink->next != NULL)
			deleteLink->next->previous = deleteLink->previous;
	}
	else cout << "This list doesn't have this link!" << endl;
}

void DoublyLinkedList::deleteFirstLink()
{
	if (this->checkEmpty())
	{
		cout << "The list is empty!" << endl;
		return;
	}

	if (this->tail == this->head)	//if list has one link
		tail = NULL;

	link * temp = this->head;
	this->head = this->head->next;
	if (this->head != NULL)
		this->head->previous = NULL;

	delete temp;
}

void DoublyLinkedList::deleteLastLink()
{
	if (this->checkEmpty())
	{
		cout << "The list is empty!" << endl;
		return;
	}

	if (this->tail == this->head)head = NULL;

	link * temp = this->tail;
	this->tail = this->tail->previous;
	if (this->tail != NULL)
		this->tail->next = NULL;

	delete temp;
}

void DoublyLinkedList::deleteList(){
	while (this->getHead() != NULL)
		this->deleteFirstLink();
}

void enterText(DoublyLinkedList * list) //fillList(DoublyLinkedList * list)
{
	while (cin.peek() != '\n') 
		list->addLinkInEnd(cin.get());
	if (cin.peek() == '\n')
		list->addLinkInEnd(cin.get());
}

void checkText(DoublyLinkedList * list)
{
	bool checkEmpty = true, checkLetters = true, checkPoint = true;

	do
	{
		if (list->getHead()->key == '\n')
		{
			checkEmpty = false;
			cout << "You didn't enter anything!" << endl
				 << "Try again: ";
			list->deleteFirstLink(); // delete new line ('\n') symbol if only it was entered
			enterText(list);
			continue;
		}
		list->deleteLastLink(); // for deleting new line ('\n') symbol
		checkEmpty = true;

		
		link * tempHead = list->getHead();
		link * tempTail = list->getTail();

		if (tempTail->key != '.')
		{
			cout << "Text doesn't have point in the end!" << endl
				 << "Enter text again: ";
			checkPoint = false;
			list->deleteList();
			enterText(list);
			continue;
		}
		checkPoint = true;

		checkLetters = true;
		while (tempHead->next != NULL)
		{
			if (!('a' <= tempHead->key && tempHead->key <= 'z' || tempHead->key == ' '))
			{
				checkLetters = false;
				cout << "Text has symbol which isn't small letter and isn't a space!" << endl
					 << "Enter text again: ";
				list->deleteList();
				enterText(list);
				break;
			}
			tempHead = tempHead->next;
		}
		if (checkLetters == false)
			continue;
		checkLetters = true;
	} while (!checkLetters || !checkEmpty || !checkPoint);
}

//Надрукувати всі слова, у яких непарна кількість літер. Перед друком видалити 
//першу та останню літеру кожного слова. 
void processList1(DoublyLinkedList * list) 
// alternative name: toProcessList(DoublyLinkedList * list){};
{
	int letterCounter = 0;
	link * temp = list->getHead(), *firstLetter, *lastLetter;
	while (temp->next != NULL)
	{
		if ('a' <= temp->key && temp->key <= 'z')
			letterCounter++;
		if (temp->key == ' ')
			letterCounter = 0;
		if (letterCounter == 1)
			firstLetter = temp;
		if (!('a' <= temp->next->key && temp->next->key <= 'z'))
		{
			lastLetter = temp;
			//delete words what consist of pair number of letters
			if (letterCounter % 2 == 0 && letterCounter != 0)
			{
				while (firstLetter != lastLetter)
				{
					firstLetter = firstLetter->next;
					list->deleteLink(firstLetter->previous);
				}
				list->deleteLink(firstLetter);
			}
			//delete first and last letter
			if (letterCounter % 2 == 1)
			{
				list->deleteLink(firstLetter);
				if (firstLetter != lastLetter)
					list->deleteLink(lastLetter);
			}
		}
		temp = temp->next;
	}
	// delete all spaces before first word
	temp = list->getHead();
	while (temp->key == ' ')
	{
		list->deleteFirstLink();
		temp = list->getHead();
	}
	//delete all space before before point
	temp = list->getTail();
	while (temp->previous->key == ' ')
		list->deleteLink(temp->previous);
}

//Надрукувати всі слова, які відрізняються від першого слова і співпадають з початковим відрізком алфавіту (a, ab, abc тощо).
//Видалити першу літеру в цих словах. До кожного слова дописати крапку.
void processList2(DoublyLinkedList * list)
{
	link * temp = list->getHead(), *temp2, *firstLetter, *lastLetter, *firstLetterFirstWord, *lastLetterFirstWord;
	bool equal, beginning;
	char letter;

	//save pointers for first word
	while (!('a' <= temp->key && temp->key <= 'z'))
		temp = temp->next;
	firstLetterFirstWord = temp;
	while ('a' <= temp->key && temp->key <= 'z')
		temp = temp->next;
	lastLetterFirstWord = temp->previous;
	//save pointers for first word

	temp2 = firstLetterFirstWord;
	while (temp->next != NULL)
	{
		//save pointers for next word
		while (!('a' <= temp->key && temp->key <= 'z'))
			temp = temp->next;
		firstLetter = temp;
		while ('a' <= temp->key && temp->key <= 'z')
			temp = temp->next;
		lastLetter = temp->previous;
		//save pointers for next word
		
		//delete words that are not begining from first leters of alphabet, like: a, ab, abc, etc.
		temp = firstLetter;
		letter = 'a';
		beginning = true;
		while (temp != lastLetter->next)
		{
			if (temp->key != letter)
			{
				beginning = false;
				break;
			}
			temp = temp->next;
			letter++;
		}
		if (!beginning)
		{
			temp = firstLetter;
			while (temp != lastLetter)
			{				// (temp->previous != last)
				temp = temp->next;
				list->deleteLink(temp->previous);
			}
			temp = temp->next;					//
			list->deleteLink (temp->previous);	//
			//continue;
		}
		else 
		{
			temp = lastLetter->next;
			list->deleteLink(firstLetter);
		}
		//delete words that are not begining from first leters of alphabet, like: a, ab, abc, etc.
	//list->showList();
		//compare words with first
		equal = true;
		temp2 = firstLetterFirstWord;
		temp = firstLetter;
		while (!(temp == lastLetter && temp2 == lastLetterFirstWord))
		{
			if (temp->key != temp2->key)
			{
				equal = false;
				break;
			}
			temp = temp->next;
			temp2 = temp2->next;
		}
		if (temp != lastLetter || temp2 != lastLetterFirstWord)
			equal = false;
		//compare word with first
		
		//delete words equal with first
		if (equal)
		{
			temp = firstLetter;
			while (temp != lastLetter)
			{				// (temp->previous != last)
				temp = temp->next;
				list->deleteLink(temp->previous);
			}
			temp = temp->next;					//
			list->deleteLink (temp->previous);	//
		}
		else 
		{
			temp = lastLetter->next;	
			list->addLinkBeforeLink(lastLetter, '.');
		}
		
		list->showList(); // shows how programm changes list

	}

	//delete first word
	while (firstLetterFirstWord != lastLetterFirstWord)
	{
		firstLetterFirstWord = firstLetterFirstWord->next;
		list->deleteLink(firstLetterFirstWord->previous);
	}
	list->deleteLink(lastLetterFirstWord);
	//delete first word

	// delete all spaces before first word
	temp = list->getHead();
	while (temp->key == ' ')
	{
		list->deleteFirstLink();
		temp = list->getHead();
	}
	//delete all space before before point
	temp = list->getTail();
	while (temp->previous->key == ' ')
		list->deleteLink(temp->previous);
}

//Надрукувати всі слова, які починаються на літеру, відмінну від літери, з якої починається перше слово тексту.
//Перед друком видалити зі слів всі літери ’a’ та ’o’.
void processList3(DoublyLinkedList * list)
{
	link * temp = list->getHead(), *firstLetter, *lastLetter, *firstLetterFirstWord, *lastLetterFirstWord;

	//save pointers for first word
	while (!('a' <= temp->key && temp->key <= 'z'))
		temp = temp->next;
	firstLetterFirstWord = temp;
	while ('a' <= temp->key && temp->key <= 'z')
		temp = temp->next;
	lastLetterFirstWord = temp->previous;
	//save pointers for first word 
	
	while (temp->next != NULL)
	{
		//save pointers for next word
		while (!('a' <= temp->key && temp->key <= 'z'))
			temp = temp->next;
		firstLetter = temp;
		while ('a' <= temp->key && temp->key <= 'z')
			temp = temp->next;
		lastLetter = temp->previous;
		//save pointers for next word
		
		//delete words which begin with letter which is different from the letter which starts first word
		if (firstLetterFirstWord->key == firstLetter->key)
		{
			temp = firstLetter;
			while (temp != lastLetter)
			{				// (temp->previous != last)
				temp = temp->next;
				list->deleteLink(temp->previous);
			}
			temp = temp->next;					//
			list->deleteLink (temp->previous);	//
		}
		else temp = lastLetter->next;
	}

	//delete first word
	while (firstLetterFirstWord != lastLetterFirstWord)
	{
		firstLetterFirstWord = firstLetterFirstWord->next;
		list->deleteLink(firstLetterFirstWord->previous);
	}
	list->deleteLink(lastLetterFirstWord);
	//delete first word

	//delete all letters "a", "o"
	while (list->search('a') != NULL) 
		list->deleteLink(list->search('a'));
	while (list->search('o') != NULL) 
		list->deleteLink(list->search('o'));
	//delete all letters "a", "o"

	// delete all spaces before first word
	temp = list->getHead();
	while (temp->key == ' ')
	{
		list->deleteFirstLink();
		temp = list->getHead();
	}
	//delete all space before before point
	temp = list->getTail();
	while (temp->previous->key == ' ')
		list->deleteLink(temp->previous);
}

//Надрукувати всі слова, які відрізняються від першого слова. Перед друком подвоїти першу літеру, якщо в слові 
//парна кількість літер, та видалити останню літеру, якщо в слові непарна кількість літер. Якщо слів менше, ніж два, видати повідомлення.
void processList4(DoublyLinkedList * list)
{
	link * temp = list->getHead(), *temp2, *firstLetter, *lastLetter, *firstLetterFirstWord, *lastLetterFirstWord;
	bool equal;
	int letterCounter;

	//save pointers for first word
	while (!('a' <= temp->key && temp->key <= 'z'))
		temp = temp->next;
	firstLetterFirstWord = temp;
	while ('a' <= temp->key && temp->key <= 'z')
		temp = temp->next;
	lastLetterFirstWord = temp->previous;
	//save pointers for first word

	temp2 = firstLetterFirstWord;
	while (temp->next != NULL)
	{
		letterCounter = 0;
		//save pointers for next word
		while (!('a' <= temp->key && temp->key <= 'z'))
			temp = temp->next;
		firstLetter = temp;
		while ('a' <= temp->key && temp->key <= 'z')
		{
			temp = temp->next;
			letterCounter++;				// count up amount of letters in word
		}
		lastLetter = temp->previous;
		//save pointers for next word
		
		//compare words with first
		equal = true;
		temp2 = firstLetterFirstWord;
		temp = firstLetter;
		while (!(temp == lastLetter && temp2 == lastLetterFirstWord))
		{
			if (temp->key != temp2->key)
			{
				equal = false;
				break;
			}
			temp = temp->next;
			temp2 = temp2->next;
		}
		if (temp != lastLetter || temp2 != lastLetterFirstWord)
			equal = false;
		//compare word with first

		//delete words equal with first
		if (equal)
		{
			temp = firstLetter;
			while (temp != lastLetter)
			{				// (temp->previous != last)
				temp = temp->next;
				list->deleteLink(temp->previous);
			}
			temp = temp->next;					//
			list->deleteLink (temp->previous);	//
		}
		else temp = lastLetter->next;
		
		list->showList(); // shows how programm changes list

		if (letterCounter % 2 == 0 && letterCounter != 0)
			list->addLinkAfterLink(firstLetter, firstLetter->key);
		else list->deleteLink(lastLetter);

	}

	//delete first word
	while (firstLetterFirstWord != lastLetterFirstWord)
	{
		firstLetterFirstWord = firstLetterFirstWord->next;
		list->deleteLink(firstLetterFirstWord->previous);
	}
	list->deleteLink(lastLetterFirstWord);
	//delete first word

	// delete all spaces before first word
	temp = list->getHead();
	while (temp->key == ' ')
	{
		list->deleteFirstLink();
		temp = list->getHead();
	}
	//delete all space before before point
	temp = list->getTail();
	while (temp->previous->key == ' ')
		list->deleteLink(temp->previous);
}

void returnSymbolsToCin(DoublyLinkedList * list)
{
    link * temp =  list->getTail();
    while (temp != NULL)
    {
        cin.putback(temp->key);
        temp = temp->previous;
    }
}
    
//Надрукувати всі слова, у яких непарна кількість літер. Перед друком видалити першу та останню літеру кожного слова.
void processArray1(vector<char> &text)
{
    
}

int main(){
	DoublyLinkedList * list = new DoublyLinkedList();
        vector<char> text;
	cout << "Enter text which has only small letters which separated not less than one space; text must be finished by point:" << endl;
        
	enterText(list);
	checkText(list);
        returnSymbolsToCin(list);
	processList4(list);
	list->showList();
        processArray1(text);
        
	cin.get();

	return 0;
}
