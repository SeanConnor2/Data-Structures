#include<iostream>
#include<stdexcept>
#include<string>
#include<vector>
#include<assert.h>

using namespace std;

template<class T>
class Node {
public:
	T item;
	Node<T> * next;
	Node() : next(nullptr) { }
	Node(const T& anItem) :item(anItem), next(nullptr) { }
	Node(const T& anItem, Node<T>* nextNode) : item(anItem), next(nextNode) { }
};

template<class T>
class lnkdset {
	Node<T>* head;
	int ic;
	Node<T>* getNodeAt(const T& nEntry) const;
public:
	lnkdset();
	lnkdset(const lnkdset<T>& rhs);
	~lnkdset();
	void clear();
	bool isEmpty() const { return ic == 0; }
	bool add(const T& nEntry); 
	bool remove( const T& nEntry);
	int getSize(){ return ic; }
	void display();
};

template<class T>
lnkdset<T>::lnkdset() : head(NULL), ic(0) {
	//cout << "Default ctor. \n";
}
template<class T>
lnkdset<T>::lnkdset(const lnkdset<T>& rhs) {
	Node<T>* rcur = rhs.head;
	Node<T>* curr = NULL;
	ic = rhs.ic;
	if (ic == 0)
		head = NULL;
	else {
		head = new Node<T>(rcur->item);
		curr = head;

		rcur = rcur->next;
		while (rcur) {
			curr->next = new Node<T>(rcur->item);
			rcur = rcur->next;
			curr = curr->next;
		}
		curr->next = NULL;
	}
}

template<class T>
Node<T>* lnkdset<T>::getNodeAt( const T& nEntry) const {
	//count from the head
	Node<T>* curr = head;
	while (curr != nullptr)
	{
		if (curr->item == nEntry)
			return curr;
		else
			curr = curr->next;
	}
	return curr;
}
template<class T>
bool lnkdset<T>::add(const T& nEntry) {

	bool dupe = false;
	Node<T>* currptr = head;
	while (currptr != nullptr){
		if (currptr->item == nEntry) {
			dupe = true;
			break;
		}
		else {
			currptr = currptr->next;
		}
	}
	if ( ! dupe) {
		//create a new node containing the new entry
		Node<T>* nPtr = new Node<T>(nEntry);
		//insert at the beginning
		nPtr->next = head;
		head = nPtr;
		ic++;
	}
	return !dupe;
}


template<class T>
bool lnkdset<T>::remove(const T& nEntry) {
	bool able2rem = ic > 0;
	if (able2rem)
	{
		Node<T> * temp = getNodeAt(nEntry);
		temp->item = head->item;
		Node<T>* curr = head;
		head = head->next;
		delete curr;
		curr = nullptr;
		ic--;
	}		
	return able2rem;
} 


template<class T>
void lnkdset<T>::clear() {
	Node<T>* curr = head;
	Node<T>* temp;
	while (curr != nullptr)
	{
		temp = curr->next;
		delete curr;
		curr = temp;
	}
	head = nullptr;
}
template<class T>
lnkdset<T>::~lnkdset() {
	clear();
}

template <class T>
void lnkdset<T>::display(){
	Node<T> * curr = head;
	while (curr != nullptr)
	{
		cout << curr->item << " ";
		curr = curr->next;
	}
}

int main(){

	lnkdset<int> test1;
	test1.add(111);
	test1.add(111);
	test1.add(222);
	test1.remove(222);
	cout << test1.getSize() << ' ';
	test1.display();
	return 0;
}