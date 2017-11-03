#include<iostream>
#include<string>
#include<cstring>
#include<assert.h>
using namespace std;

template<class T>
class dynArrStack {
	static const int deCap = 30;
	int top;
	T* items; // array in dynamic memory storage
public:
	dynArrStack();
	dynArrStack(const dynArrStack<T>& rhs);
	~dynArrStack();
	bool isEmpty() const;
	bool push(const T& nEntry);
	bool pop();
	void evaluate(char str[]);
	T peek() const;
	void display();
};
template<class T>
dynArrStack<T>::dynArrStack() : top(-1) {
	items = new T[deCap];
}
template<class T>
dynArrStack<T>::dynArrStack(const dynArrStack<T>& rhs) {
	top = rhs.top;
	items = new T[deCap];
	for (int i = 0; i < rhs.deCap; i++)
		items[i] = rhs[i];
}
template<class T>
dynArrStack<T>::~dynArrStack() {
	delete[] items;
}
//Checks to see if the stack is empty
template<class T>
bool dynArrStack<T>::isEmpty()const{
	return top < 0;
}
//Pushes a value
template<class T>
bool dynArrStack<T>::push(const T& nEntry) {
	bool result = false;
	if (top < deCap - 1) {
		top++;
		items[top] = nEntry;
		result = true;
	}
	return result;
}
//Pops a value
template<class T>
bool dynArrStack<T>::pop() {
	bool result = false;
	if (!isEmpty()) {
		top--;
		result = true;
	}
	return result;
}
//Peek function
template<class T>
T dynArrStack<T>::peek() const {
	assert(!isEmpty());
	return items[top];
}
template<class T>
void dynArrStack<T>::evaluate(char str[]) {
	int i = 0;
	double temp, temp2, result;
	do {
		if (isdigit(str[i])) {
			push(static_cast<double>(str[i]-48));
			i++;
		}
		if (str[i] == '*') {
			temp = peek();	
			pop();
			temp2 = peek();
			pop();
			result = temp * temp2;
			push(result);
			i++;
		}
		if (str[i] == '/') {
			temp = peek();
			pop();
			temp2 = peek();
			pop();
			result = temp / temp2;
			push(result);
			i++;
		}
		if (str[i] == '+') {
			temp = peek();
			pop();
			temp2 = peek();
			pop();
			result = temp + temp2;
			push(result);
			i++;
		}
		if (str[i] == '-') {
			temp = peek();
			pop();
			temp2 = peek();
			pop();
			result = temp2 - temp;
			push(result);
			i++;
		}
		if (str[i] == 'q')
			break;
	} while (i != strlen(str));
}
template<class T>
void dynArrStack<T>::display(){
	for (int i = 0; i < top + 1; i++)
		cout << items[i] << endl;
}
//Main Function
int main(){
	char str[256];
	dynArrStack<double> b1;
	cout << "Please Enter A PostFix Expression And Enter A 'q' To End The Expression!" << endl;
	cin.getline(str, 30);
	b1.evaluate(str);
	b1.display();
	return 0;
}