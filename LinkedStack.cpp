#include<iostream>
#include<stdexcept>
#include<string>
#include<assert.h>
using namespace std;
class PrecondViolationExcep : public logic_error {
public:
	PrecondViolationExcep(const string& message = "");
};
PrecondViolationExcep::PrecondViolationExcep(const string& message) :
logic_error("Precondition Violated Exception: " + message){
}
template<class T>
class Node{
public:
	Node<T>* next;
	T stack;
	Node(){stack = 0 next = nullptr; }
	Node(T anItem): stack(anItem), next(nullptr){ }
	Node(T anItem, Node<T>* ptr): stack(anItem), next(ptr){ }
};
template<class T>
class lnkdStack {
private:
	Node<T>* topPtr;
public:
	lnkdStack();  //default constructor
	lnkdStack(const lnkdStack<T>& aStack); //copy constructor
	~lnkdStack(); //destructor
//stack operations
	bool isEmpty() const;
	bool push(const T& newItem);
	bool pop();
	T peek() const;
	T peek2() const;
};
//implementation
template<class T>
lnkdStack<T>::lnkdStack() : topPtr(nullptr) {

}
template<class T>
lnkdStack<T>::lnkdStack(const lnkdStack<T>& aStack) {
	//point to nodes in original chain
	Node<T>* origChainPtr = aStack->topPtr;

	if (origChainPtr == nullptr)
		topPtr = nullptr; //original bag is empty
	else {
		//copy first node
		topPtr = new Node<T>();
		topPtr->stack(origChainPtr->stack);
		//point to first node in new chain
		Node<T>* newChainPtr = topPtr;
		//copy remaining nodes
		while (origChainPtr != nullptr) {
			//advance original-chain pointer
			origChainPtr = origChainPtr->next;
			//get next item from original chain
			T nextItem = origChainPtr->stack;
			//create a new node containing the next item
			Node<T>* newNodePtr = new Node<T>(nextItem);
			//link new node to end of new chain
			newChainPtr->next = newNodePtr;
			//advance pointer to new last node
			newChainPtr = newChainPtr->next;
		}
		newChainPtr->setNext(nullptr); //flag end of chain
	}
}
template<class T>
lnkdStack<T>::~lnkdStack() {
	//pop until stack is empty
	while (!isEmpty())
		pop();
}
template<class T>
bool lnkdStack<T>::isEmpty() const {
	return topPtr == nullptr;
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
T lnkdStack<T>::peek() const throw (PrecondViolationExcep) {
	if (isEmpty())
		throw PrecondViolationExcep("Error The Stack Is Empty\n");

	//stack is not rempty return top
	return topPtr->stack;
}
template<class T>
T lnkdStack<T>::peek2() const throw (PrecondViolationExcep) {
	Node<T>* curr;
	if (isEmpty())
		throw PrecondViolationExcep("Error The Stack Is Empty\n");
	else{
		curr = topPtr->next;
		if (curr != nullptr){
			return curr->stack;
		}
		else
			throw PrecondViolationExcep("Error, Stack Is Not Bigger Than 2\n");
	}
}
 
int main(){
	lnkdStack<double> stack;
	stack.push(5);
	//stack.push(6);
	try
	{
		cout << "Peek\n";
		cout << stack.peek() << endl;
	}
	catch (PrecondViolationExcep t)
	{
		cout << t.what();
	}
	try
	{
		cout << "Peek2\n";
		cout << stack.peek2() << endl;
	}
	catch (PrecondViolationExcep p)
	{
		cout << p.what();
	}
	return 0;
}