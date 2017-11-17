#include<iostream>
#include<stdexcept>
#include<string>
#include<cstring>

using namespace std;

class PreCondViolatedExcept : public logic_error {
public:
	PreCondViolatedExcept(const string& message = "");
};
PreCondViolatedExcept::PreCondViolatedExcept(const string& message) :
logic_error("Precondition Violated Exception: " + message) {
}
//Node Class
template<class T>
class Node{
public:
	T item;
	Node<T> * next;
	Node() : next(nullptr) { }
	Node(const T& anItem) :item(anItem), next(nullptr) { }
	Node(const T& anItem, Node<T>* nextNode) : item(anItem), next(nextNode) { }
};
//Linked Based Queue
template<class T>
class lnkdQueue{
	Node<T> * ft;
	Node<T> * bk;
public:
	lnkdQueue();
	lnkdQueue(const lnkdQueue& rhs);
	~lnkdQueue();
	bool isEmpty() const  { return ft == nullptr; }
	bool enQueue(const T& nEntry);
	bool deQueue();
	T peekft() const throw (PreCondViolatedExcept);
};

//Linked Based Stack
template<class T>
class lnkdStack {
private:
	Node<T>* topPtr;
public:
	lnkdStack();  //default constructor
	lnkdStack(const lnkdStack<T>& aStack); //copy constructor
	~lnkdStack(); //destructor
	//stack operations
	bool isEmpty() const{ return topPtr == nullptr; }
	bool push(const T& newItem);
	bool pop();
	T peek() const;
};
//Linked Queue Implementations
template<class T>
lnkdQueue<T>::lnkdQueue(){
	ft = nullptr;
	bk = nullptr;
}
template<class T>
lnkdQueue<T>::lnkdQueue(const lnkdQueue<T>& rhs){
	Node<T>* rcur = rhs.ft;
	if (rcur == nullptr)
	{
		ft = nullptr;
		bk = nullptr;
	}
	else{
		Node<T> * curr = new Node<T>(rcur->item);
		rcur = rcur->next;
		curr = curr ->next;
		while (rcur != nullptr){
			curr = new Node<T>(rcur->item);
			rcur = rcur->next;
			curr = curr->next;
		}
		curr->next = nullptr;
	}
	bk = rhs.bk;
}
template<class T>
lnkdQueue<T>::~lnkdQueue(){
	while (!isEmpty())
		deQueue();
}
template<class T>
bool lnkdQueue<T>::enQueue(const T& nEntry){
	Node<T>*nn = new Node<T>(nEntry);
	if (isEmpty())
		ft = nn;
	else
		bk->next = nn;
	bk = nn;
	return true;
}
template<class T>
bool lnkdQueue<T>::deQueue(){
	bool result = false;
	if (!isEmpty()){
		Node<T>* n2del = ft;
		if (ft == bk)
			ft = bk = nullptr;
		else
			ft = ft->next;
		n2del->next = nullptr;
		delete n2del;
		result = true;
	}
	return result;
}
template<class T>
T lnkdQueue<T>::peekft() const throw(PreCondViolatedExcept){

	if (ft != nullptr)
		return ft->item;
	else {
		string msg = "There is no Value\n";
		throw(PreCondViolatedExcept(msg));
	}
}
//Palindromes

//Linked Stack Implimentations
template<class T>
lnkdStack<T>::lnkdStack() : topPtr(nullptr) {
}
template<class T>
lnkdStack<T>::lnkdStack(const lnkdStack<T>& aStack) {
	//point to nodes in original chain
	Node<T>* origChainPtr = aStack.topPtr;

	if (origChainPtr == nullptr)
		topPtr = nullptr; //original bag is empty
	else {
		//copy first node
		topPtr = new Node<T>();
		topPtr->item = (origChainPtr->item);
		//point to first node in new chain
		Node<T>* newChainPtr = topPtr;
		//copy remaining nodes
		while (origChainPtr != nullptr) {
			//advance original-chain pointer
			origChainPtr = origChainPtr->next;
			//get next item from original chain
			T nextItem = origChainPtr->item;
			//create a new node containing the next item
			Node<T>* newNodePtr = new Node<T>(nextItem);
			//link new node to end of new chain
			newChainPtr->next = newNodePtr;
			//advance pointer to new last node
			newChainPtr = newChainPtr->next;
		}
		newChainPtr->next = nullptr; //flag end of chain
	}
}
template<class T>
lnkdStack<T>::~lnkdStack() {
	//pop until stack is empty
	while (!isEmpty())
		pop();
}
template<class T>
bool lnkdStack<T>::push(const T& newItem){
	Node<T>* newNodePtr = new Node<T>(newItem, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;
	return true;
}
template<class T>
bool lnkdStack<T>::pop(){
	bool result = false;
	if (!isEmpty()){
		//stack is not empty delete top
		Node<T>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->next;
		//return deleted node to system
		nodeToDeletePtr->next = nullptr;
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		result = true;
	}
	return result;
}
template<class T>
T lnkdStack<T>::peek() const throw (PreCondViolatedExcept) {
	if (isEmpty())
		throw PreCondViolatedExcept("Error The Stack Is Empty\n");

	//stack is not rempty return top
	return topPtr->item;
}

bool isPalindrome(char str[]){
	lnkdQueue<char> queue;
	lnkdStack<char> stack;
	int len = strlen(str);
	for (int i = 1; i > len; i++){
		char ch = str[i];
		queue.enQueue(ch);
		stack.push(ch);
	}
	bool charEqual = true;
	while ((!queue.isEmpty() && !stack.isEmpty())){
		if (queue.peekft() != stack.peek())
			charEqual = false;
		else{
			queue.deQueue();
			stack.pop();
		}
	}
	return charEqual;
}
//word palindrime

bool isPalindromeWord(char str[]){
	lnkdQueue<string> queue; 
	lnkdStack<string> stack;
	bool stringEqual = true;
	char *cstr = strtok(str, " ,?.-");
	while (cstr != nullptr){
		queue.enQueue(cstr);
		stack.push(cstr);
		cstr = strtok(nullptr, " ,?.-");
	}
	while ((!queue.isEmpty() && !stack.isEmpty())){
		if (queue.peekft()!= stack.peek()){
			stringEqual = false;
			break;
		}
		else{
			queue.deQueue();
			stack.pop();
		}
	}
	return stringEqual;
}
int main(){

	cout << "Welcome To The Palindrome Checker!" << endl;
	cout << "Please Type In The Palindrome Sentence or Word: " << endl;
	char str[100];
	cin.getline(str, 100);
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = toupper(str[i]);
	}

	if (isPalindrome(str))
		cout << "The Phrase/Word Is A Letter-By-Letter Palindrome!" << endl;
	else
		cout << "The Phrase/Word Is Not A Letter-By-Letter Palindrome!" << endl;
	
	if (isPalindromeWord(str))
		cout << "The Phrase/Word Is A Word-By-Word Palindrome!" << endl;
	else
		cout << "The Phrase/Word Is Not A Word-By-Word Palindrome!" << endl;

	return 0;
}