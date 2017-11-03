#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;
//Number Node

struct nNode {
	nNode() { data = 0; next = nullptr; }
	nNode(int d){data = d;}
	nNode* next = nullptr;
	int data;
};

class lnkdBN {
private:
	nNode* head;
	string str;
	int ic;
public:	
	
	lnkdBN(); //default constructor
	lnkdBN(const string& bn); // conversion constructor
	lnkdBN(const lnkdBN&);
	~lnkdBN();
	const lnkdBN operator+ (const lnkdBN& rhs);
	lnkdBN& operator= (const lnkdBN& rhs);
	const lnkdBN operator *(const lnkdBN & rhs);
	void display();
	void reverse();
	void addNode(int d);
	bool remove(int pos);
};
//default constructor
lnkdBN::lnkdBN(){
	head = nullptr;
	ic = 0;
}
//conversion ctor
lnkdBN::lnkdBN(const string& str)
{
	int len = str.length();
	int leftover, i, non; // non - number of nodes
	leftover = len % 4;
	non = len / 4;
	if (leftover > 0)
		non++;
	string tmp;

	nNode* curr = NULL;

	for (i = 0; i < non; i++)
	{
		if (i == 0) {
			if (leftover > 0)
				tmp = str.substr(0, leftover);
			else
				tmp = str.substr(0, 4);
		}
		else {
			if (leftover > 0)
				tmp = str.substr(leftover + (i - 1) * 4, 4);
			else
				tmp = str.substr(i * 4, 4);
		}

		if (curr == NULL)  
			curr = head = new nNode(atoi(tmp.c_str()));
		else {
			curr->next = new nNode(atoi(tmp.c_str()));
			curr = curr->next;
		}
	}
}
//copy ctor
lnkdBN::lnkdBN(const lnkdBN& bn){
	ic = bn.ic;
	nNode* curr = bn.head;
	if (curr == nullptr)
		head = nullptr;
	else{
		head = new nNode(curr->data);
		nNode* nChain = head;
		curr = curr->next;
		while (curr != nullptr){
			nNode* node = new nNode(curr->data);
			nChain->next = node;
			nChain = nChain->next;
			curr = curr->next;
		}
		nChain->next = nullptr;
	}
}
//destructor
lnkdBN::~lnkdBN(){
	nNode* current = head;
	nNode* temp;
	while (current != nullptr)
	{
		temp = current->next;
		delete current;
		current = temp;
	}
	head = nullptr;
}
lnkdBN& lnkdBN:: operator= (const lnkdBN& rhs) {
	nNode * curr = rhs.head;
	if (this->head == curr)
		return *this;
	ic = rhs.ic;
	nNode * c1 = this->head;
	nNode* temp;
	while (c1 != nullptr)
	{
		temp = c1->next;
		delete c1;
		c1 = temp;
	}
	this->head = nullptr;
	this->head = new nNode(curr->data);

	nNode* nChain = this->head;
	curr = curr->next;
	while (curr != nullptr) {
		nNode* node = new nNode(curr->data);
		nChain->next = node;
		nChain = nChain->next;
		curr = curr->next;

	}
	nChain->next = nullptr;
	return *this;
}
//addition operator
lnkdBN const lnkdBN:: operator+ (const lnkdBN& rhs) {
	nNode* rcurr = rhs.head;
	nNode * lcurr = this->head;
	lnkdBN bn;
	nNode * temp = bn.head;
	int total;
	int carry = 0;
	
	if (rcurr == nullptr)
		return rhs;
	else {
		while (rcurr != nullptr || lcurr != nullptr) {
			total = carry + ((rcurr ? rcurr->data : 0) + (lcurr ? lcurr->data : 0));
			if (total >= 10000) {
				carry = 1;
			}
			else {
				carry = 0;	
			}
			total = total % 10000;
			bn.addNode(total);
			bn.ic++;
			if(rcurr)
				rcurr = rcurr->next;
			if(lcurr)
				lcurr = lcurr->next;
		}
	}
	return bn;
}

 lnkdBN const lnkdBN:: operator *(const lnkdBN & rhs) {
	 lnkdBN result, bn, bntemp;
	nNode* rcurr = rhs.head;
	nNode * lcurr = this->head;
	nNode * temp = bn.head;
	int carry = 0, multiplyResult;
	nNode *tempLcurr = nullptr;
	int count = 0;
	while (rcurr != nullptr && lcurr != nullptr) {
		tempLcurr = lcurr;
		if (count > 0) {
			//count = pow(10000, count);
			rcurr->data = rcurr->data * count;
		}
		count++;
		while (tempLcurr != nullptr) {
			multiplyResult = carry + (rcurr->data * tempLcurr->data);
			if (multiplyResult >= 10000)
				carry = (multiplyResult / 10000);
			else
				carry = 0;

			multiplyResult = multiplyResult % 10000;
			bn.addNode(multiplyResult);
			bn.ic++;
			if (tempLcurr)
				tempLcurr = tempLcurr->next;
			if (tempLcurr == nullptr && carry != 0)
				bn.addNode(carry);
		}
		if (rcurr)
			rcurr = rcurr->next;
		if (carry > 0) {
			bn.addNode(carry);
		}
	}
	return bn;
}

//add & remove nodes functions
void lnkdBN::addNode(int d) {

	nNode* curr = head;
	if(head == nullptr) {
		head = new nNode(d);
		return;
	}
	curr = new nNode(d);
	curr->next = head;
	head = curr;
}
bool lnkdBN::remove(int pos){
	nNode* prev = nullptr;
	nNode* curr = head;
	bool ret = false;
	while (curr && pos--){
		prev = curr;
		curr - curr->next;
	}
	if (curr){
		if (curr == head)
			head = head->next;
		else
			prev->next - curr->next;
		delete curr;
		ret = true;
	}
	return ret;
}
void lnkdBN::reverse(){
	nNode *curr, *prev, *n;
	curr = head;
	prev = nullptr;
	while (curr != nullptr){
		n = curr->next;
		curr->next = prev;
		prev = curr;
		curr = n;
	}
	head = prev;
}
//displays the nodes
void lnkdBN::display(){
	nNode* curr = head;
	while (curr){
		cout << curr->data;
		curr = curr->next;
	}
	reverse();
}
//LinkedBigNum

int main() {
	
	ifstream inFile;
	inFile.open("HW03_testdata.txt");
	string link1, link2;


	if (!inFile) {
		cerr << "Could Not Open File" << endl;
	}
	while (!inFile.eof()) {
		inFile >> link1 >> link2;
		lnkdBN bn1(link1);
		lnkdBN bn2(link2);
		lnkdBN result;
		cout << "Big Number1: ";
		bn1.display();
		cout << "\nBig Number2: ";
		bn2.display();
		cout << "\nAddition Result: ";
		result = bn1 + bn2;
		result.display();
		cout << "\nMultipication Result: ";
		result = bn1*bn2;
		result.display();
		cout << endl;
	}
	return 0;

}
