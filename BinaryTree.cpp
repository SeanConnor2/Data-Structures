#include<iostream>
#include<algorithm>
#include<stdexcept>
#include<iomanip>
#include<string>
#define COUNT 10
using namespace std;

class PreCondViolatedExcept : public logic_error {
public:
	PreCondViolatedExcept(const string& message = "");
};
PreCondViolatedExcept::PreCondViolatedExcept(const string& message) :
logic_error("Precondition Violated Exception: " + message) {
}

template<class T>
class bNode{
public:
	T item;
	bNode<T>* lChild;
	bNode<T>* rChild;

	bNode() : lChild(nullptr), rChild(nullptr){ }
	bNode(const T& anItem) : item(anItem), lChild(nullptr), rChild(nullptr) { }
	bNode(const T& anItem, bNode<T>* left, bNode<T> * right) : item(anItem), lChild(left), rChild(right){ }
	bool isLeaf()  const { return (lChild == nullptr && rChild == nullptr); }
};

template<class T>
class binaryTree{
	bNode<T>* root;
	int gHeiHlp(bNode<T>* subTr) const; //GetHeight
	int gNumOfNodesHlp(bNode<T>* subTr) const; //GetNumberOfNodes
	void preOrder(void visit(T&), bNode<T>* tr) const; // PreOrder
	void inOrder(void visit(T&), bNode<T>* tr) const; // InOrder
	bNode<T>* cpyTree(const bNode<T>* oldRt) const; // copy tree
	void destroyTree(bNode<T>*& subTr); // destroyTree
	//BST
	void binaryTree::postorder(bNode<T>* p, int indent = 0);
	bNode<T>* bstAdd(bNode<T>*& subTr, bNode<T>* nNode);
	//bNode<T>* bstFind(bNode<T>*& subTr, const T& tgt) const; //Search
	
public:
	binaryTree() : root(nullptr){ }
	binaryTree(const T& rtItem);
	binaryTree(const T& rtItem, const bNode<T>* lTr, const bNode<T>* rTr) :root(new bNode<T>(rtItem, cpyTree(lTr->root), vpyTree(rTr->root))){ }
	binaryTree(const binaryTree<T>& rhs) { root = cpyTree(rhs.root); }
	~binaryTree(){ destroyTree(root); }
	bool isEmpty() const { return (root == nullptr) }
	int gHei() const { return gHeiHlp(root); }
	int gNunOfNodes() const { return gNumOfNodesHlp(root); }
	T gRtData() const throw(PreCondViolatedExcept);
	void sRtData(const T& nData);
	bool add(const T& nData);
	void preTrav(void visit(T&)) const{ preOrder(visit, root); }
	void inTrav(void visit(T&)) const{ inOrder(visit, root); }

	void fill(char res[][], bNode<T>* root, int i, int l, int r);
	
	//binaryTree<T>& operator=(const binaryTree<T>& rhs);

	

};
template<class T>
int binaryTree<T>::gHeiHlp(bNode<T>* subTr) const{
	//base case
	if (subTr == nullptr)
		return 0;
	return max(gHeiHlp(subTr->lChild), gHeiHlp(subTr->rChild)) + 1;
}
template<class T>
int binaryTree<T>::gNumOfNodesHlp(bNode<T> * subTr) const{
	//base case
	if (subTr == nullptr)
		return 0;
	return (gNumOfNodesHlp(subTr->lChild) + gNumOfNodesHlp(subTr->rChild)) + 1;
}
template<class T>
void binaryTree<T>::preOrder(void visit(T&), bNode<T>* tr) const{
	if (tr != nullptr){
		T nItem = tr->item;
		visit(nItem);
		preOrder(visit, tr->lChild);
		preOrder(visit, tr->rChild);
	}
}
template<class T>
void binaryTree<T>::inOrder(void visit(T&), bNode<T>* tr) const{
	if (tr != nullptr){
		T nItem = tr->item;
		inOrder(visit, tr->lChild);
		visit(nItem);
		inOrder(visit, tr->rChild);
	}
}
template<class T>
binaryTree<T>::binaryTree(const T& rtItem){
	root = new bNode<T>(rtItem);
}
template<class T>
bool binaryTree<T>::add(const T& nData){
	bNode<T>* newNode = new bNode<T>(nData);
	root = bstAdd(root, newNode);
	return true;
}
template<class T>
void binaryTree<T>::sRtData(const T& nData){
	if (root == nullptr)
		root = new bNode<T>(nData);
	else
		root->item = nData;
}
template<class T>
T binaryTree<T>::gRtData() const throw(PreCondViolatedExcept){
	if (root == nullptr)
		throw (PreCondViolatedExcept("gRTData() called with an empty tree"));
	else
		return root->item;
}
template<class T>
bNode<T>* binaryTree<T>::cpyTree(const bNode<T>* oldRt) const{
	bNode<T>* newTree = nullptr;
	if (oldRt != nullptr){
		//copy Node
		newTree = new bNode<T>(oldTr->item, nullptr, nullptr);
		newTree->lChild = cpyTree(oldTr->lChild);
		newTree->rChild = cpyTree(oldTr->rChild);
	}
	return newTree;
}
template<class T>
void binaryTree<T>::destroyTree(bNode<T>*& subTr){
	if (subTr != nullptr){
		destroyTree(subTr->lChild);
		destroyTree(subTr->rChild);
		delete subTr;
		subTr = nullptr;
	}
}
template<class T>
bNode<T>* binaryTree<T>::bstAdd(bNode<T>*& subTr, bNode<T>* nNode){
	if (subTr == nullptr)
		return nNode;
	else{
		if (subTr->item == nNode->item)
			return subTr;
		else if (subTr->item > nNode->item)
			subTr->lChild = bstAdd(subTr->lChild, nNode);
		else
			subTr->rChild = bstAdd(subTr->rChild, nNode);
		return subTr;
	}
}

template<class T>
void binaryTree<T>::fill(char res[][], bNode<T>* root, int i, int l, int r) {
	if (root == nullptr)
		return;
	res[i][(l + r) / 2] = "" + root->item;
	fill(res, root->lChild, i + 1, l, (l + r) / 2);
	fill(res, root->rChild, i + 1, (l + r + 1) / 2, r);
}

void print(int& x){
	cout << x << " ";
}

int main(){
	binaryTree<int> intTree; 
	bNode<int>* root;
	try{
		cout << intTree.gRtData() << endl;
	}
	catch (PreCondViolatedExcept e){
		cout << e.what() << endl;
	}
	int arr[] = { 60, 20, 10, 40, 30, 50, 70, 80 }; // user input
	int num = sizeof(arr) / sizeof(int);
	for (int i = 0; i < num; i++)
		if (intTree.add(arr[i]) == false)
			break;

	cout << "PreOrder: ";
	intTree.preTrav(print);
	cout << endl;
	intTree.inTrav(print);
	cout << endl;
	
	int height = intTree.gHei();
	char res[4][3];
	intTree.fill(res, root, 0, 1, 5);


	
	return 0;
}