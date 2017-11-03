#include<iostream>
#include<stdexcept>
#include<string>
#include<assert.h>
using namespace std;
//dynamic based
class PreCondViolatedExcept : public logic_error {
public:
	PreCondViolatedExcept(const string& message = "");
};
PreCondViolatedExcept::PreCondViolatedExcept(const string& message) :
	logic_error("Precondition Violated Exception: " + message) {
}
static int deCap = 20;

template<class T>
class arrList {
	T* items;
	int ic;
public:
	arrList() : ic(0), items( new T[deCap + 1] ) { }
	arrList(const arrList<T>& rhs);
	~arrList() { delete[]items; }
	arrList<T>& operator=(const arrList<T>& rhs);
	bool isEmpty() const { return ic == 0; }
	int getLen() const { return ic; }
	void clear() { ic = 0; }
	void display();
	
	bool insert(int nPos, const T& nEntry);
	bool remove(int pos);
	T getEntry(int pos) const throw(PreCondViolatedExcept);
	T replace(int pos, const T& nEntry) throw(PreCondViolatedExcept);
};
template<class T>
arrList<T>::arrList(const arrList<T>& rhs) {
	ic = rhs.ic;
	items = new T[decCap + 1];
	for (int i = 0; i <= rhs.ic i++)
		items[i] = rhs.items[i];
}
template<class T>
bool arrList<T>::insert(int nPos, const T& nEntry) {
	bool able2insert = false;
	if (ic == deCap) {
		deCap *= 2;
		T* oldItems = items;
		items = new T[deCap + 1];
		for (int i = 0; i <= ic; i++)
			items[i] = oldItems[i];
		delete[] oldItems;
		 able2insert = true;
	}
	else
		 able2insert = true;
		//bool able2insert = nPos >= 1 && nPos <= ic + 1 && ic < deCap;
		if (able2insert) {
			for (int i = ic; i >= nPos; i--)
				items[i + 1] = items[i];
			items[nPos] = nEntry;
			ic++;
		}
		return able2insert;
}
template<class T>
T arrList<T>::getEntry(int pos) const throw(PreCondViolatedExcept) {
	bool able2get = pos >= 1 && pos <= ic;
	if (able2get)
		return items[pos];
	else {
		string msg = "getEntry Was Called With An Empty List Or";
		msg += " Invalid Position.\n";
		throw(PreCondViolatedExcept(msg));
	}
}
template<class T>
T arrList<T>::replace(int pos, const T& nEntry) throw(PreCondViolatedExcept) {
	bool able2replace = pos >= 1 && pos <= ic;
	if (able2replace) {
		T oldEntry = items[pos];
		items[pos] = nEntry;
		return oldEntry;
	}
	else {
		string msg = "Replace Was Called With An Empty List\n";
		throw(PreCondViolatedExcept(msg));
	}
}
template<class T>
bool arrList<T>::remove(int pos) {
	if (ic = (deCap / 2)) {
		deCap = ic * (1 / 4);
		for (int i = ic; i > deCap; i--)
			remove(i);
	}
	else {
		bool ableToRemove = (pos >= 1) && (pos <= ic);
		if (ableToRemove) {
			// Remove entry by shifting all entries after the one at
			// position toward the beginning of the array
			// (no shift if position == ic)
			for (int fromIndex = pos, toIndex = fromIndex - 1; fromIndex < ic; fromIndex++, toIndex++)
				items[toIndex] = items[fromIndex];
			ic--; // Decrease count of entries
		} 
		return ableToRemove;
	} 
}
template<class T>
arrList<T>& arrList<T>::operator=(const arrList<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	ic = rhs.ic;
	delete[] items;
	items = new T[rhs.ic];
	for (int i = 0; i < rhs.ic; i++)
		items[i] = rhs.items[i];
	return *this;
}
template<class T>
void arrList<T>::display(){
	for (int i = 1; i <= ic; i++)
		cout << items[i] << ' ';
}

int main() {
	arrList<int> al;
	try{
		for (int i = 1; i <= 20; i++)
			al.insert(i, i + 1);
		al.getEntry(44);
	}
	catch (PreCondViolatedExcept p)
	{
		cout << p.what();
	}
	try{
		al.insert(21, 40);
		al.replace(44, 44);
	}
	catch (PreCondViolatedExcept c){
		cout << c.what();
	}
	al.display();
	return 0;
}


//----------------------------------------------------------------------------------------------------------
//linkedlist Extra Credit
/*
class PreCondViolatedExcept : public logic_error {
public:
	PreCondViolatedExcept(const string& message = "");
};
PreCondViolatedExcept::PreCondViolatedExcept(const string& message) :
logic_error("Precondition Violated Exception: " + message) {
}

template<class T>
class Node{
public:
	T item;
	Node<T> * next;
	Node() : next(NULL){ }
	Node(const T& anItem) :item(anItem), next(NULL) { }
	Node(const T& anItem, Node<T>* nextNode) : item(anItem), next(nextNode) { }
};

template<class T>
class lnkdList {
	Node<T>* head;
	int ic;
	Node<T>* getNodeAt(int pos) const;
public:
	lnkdList();
	lnkdList(const lnkdList<T>& rhs);
	~lnkdList();
	void clear();
	bool isEmpty() const { return ic == 0; }
	bool insert(int nPos, const T& nEntry);
	bool remove(int pos);
	T getEntry(int pos) const throw (PreCondViolatedExcept);
	T replace(int pos, const T& nEntry) throw (PreCondViolatedExcept);
};
template<class T>
lnkdList<T>::lnkdList() : head(NULL), ic(0){
	//cout << "Default ctor. \n";
}
template<class T>
lnkdList<T>::lnkdList(const lnkdList<T>& rhs){
	Node<T>* rcur = rhs.head;
	Node<T>* curr = NULL;
	ic = rhs.ic;
	if (ic == 0)
		head = NULL;
	else{
		head = new Node<T>(rcur->item);
		curr = head;

		rcur = rcur->next;
		while (rcur){
			curr->next = new Node<T>(rcur->item);
			rcur = rcur->next;
			curr = curr->next;
		}
		curr->next = NULL;
	}
}
template<class T>
Node<T>* lnkdList<T>::getNodeAt(int pos) const {
	assert(pos >= 1 && pos <= ic);
	//count from the head
	Node<T>* curr = head;
	for (int i = 1; i < pos; i++)
		curr = curr->next;
	return curr;
}
template<class T>
T lnkdList<T>::getEntry(int pos) const throw (PreCondViolatedExcept){
	bool able2get = pos >= 1 && pos <= ic;
	if (able2get){
		Node<T>* ptr = getNodeAt(pos);
		return ptr->item;
	}
	else{

	}
}
template<class T>
bool lnkdList<T>::insert(int nPos, const T& nEntry){
	bool able2insert = nPos >= 1 && nPos <= ic + 1;
	if (able2insert){
		//create a new node containing the new entry
		Node<T>* nPtr = new Node<T>(nEntry);
		if (nPos == 1){
			//insert at the beginning
			nPtr->next = head;
			head = nPtr;
		}
		else{
			Node<T>* prev = getNodeAt(nPos - 1);
			//insert nEntry after prev node
			nPtr->next = prev->next;
			prev->next = nPtr;
		}
		ic++;
	}
	return able2insert;
}
template<class T>
bool lnkdList<T>::remove(int pos){
	bool able2rem = pos >= 1 && pos <= ic;
	if (able2rem){
		Node<T>* curr = NULL;
		if (pos == 1){
			curr = head;
			head = head->next;
		}
		else{
			//find the node before the one to remove
			Node<T>* prev = getNodeAt(pos - 1);
			curr = prev->next;
			prev->next = curr->next;
		}
		delete curr;
		curr = NULL;
		ic--;
	}
	return able2rem;
}
template<class T>
void lnkdList<T>::clear(){
	while (!isEmpty())
		remove(1);
}
template<class T>
lnkdList<T>::~lnkdList(){
	clear();
}
template<class T>
T lnkdList<T>::replace(int pos, const T& nEntry) throw (PreCondViolatedExcept){
	bool able2Replace = pos >= 1 && pos <= ic;
	if (able2Replace){
		Node<T>* curr = getNodeAt(pos);
		T oldEntry = curr->item;
		return oldEntry;
	}
	else{
		string msg = "Replace called with an Empty List or Invalid Position";
		throw(PreCondViolatedExcept(msg));
	}
}

int main(){
	const int count = 6;
	lnkdList<string> l1;
	string data[] = { "one", "two", "Three", "Four", "Five", "Six" };
	
	for (int i = 0; i < count; i++)
		l1.insert(i + 1, data[i]);

	lnkdList<string> l2(l1); //copy ctor

	try {
		l2.replace(3, "THREE");
		l2.replace(7, "SEVEN");
	}
	catch (PreCondViolatedExcept p) {
		cout << p.what();
		cout << "\nFailed to replace at the position" << endl;
	}
	return 0;
}
*/