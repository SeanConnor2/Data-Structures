#include<iostream>
#include<vector>
using namespace std;


template<class T>
class arrayBag{
private:
	static const int deCap = 60;
	T items[deCap];
	int ic;
	int max;
	int getidxof(const T& target) const;
public:
	arrayBag();
	int getCurrentSize() const{ return ic; }
	bool isEmpty() const { return ic == 0; }
	bool add(const T& newEntry);
	bool remove(const T& anEntry);
	void clear();
	bool iscontains(const T& anEntry) const;
	int getFreqOf(const T& anEntry) const;
	vector <T>toVector() const;
	void display();
//union intersection and difference definition
	arrayBag<T>& Union(const arrayBag& anEntry);
	arrayBag<T>& Intersection(const arrayBag& anEntry);
	arrayBag<T>& Difference(const arrayBag& anEntry);
};

template<class T>
arrayBag<T>::arrayBag() : ic(0), max(deCap) {
}
template<class T>
int arrayBag<T>::getidxof(const T& target) const {
	bool found = false;
	int result = -1;
	int idx = 0;
	while (!found && idx < ic) {
		found = items[idx] == target;
		if (found)
			result = idx;
		else
			idx++;
	}
	return result;
}
template<class T>
void arrayBag<T>::display(){
	for(int i  = 0; i < getCurrentSize();i++)
		cout << this->items[i] << ' ';
	
}
template<class T>
bool arrayBag<T>::add(const T& newEntry){
	bool hasRoom = (ic < max);
	if (hasRoom){
		items[ic] = newEntry;
		ic++;
	}
	return hasRoom;
}

template<class T>
vector<T>arrayBag<T>::toVector() const{
	vector<T> bagContents;
	for (int i - 0; i < ic; i++)
		bagContents.push_back(items[i]);
	return bagContents;
}

template<class T>
int arrayBag<T>::getFreqOf(const T& anEntry) const{
	int freq = 0;
	int curIdx = 0;
	while (curIdx < ic){
		if (items[curIdx] == anEntry)
			freq++;
		curIdx++;
	}
	return freq;
}

template<class T>
bool arrayBag<T>::iscontains(const T& anEntry) const{
	bool found = false; int curIdx = 0;
	while (!found && curIdx < ic){
		if (anEntry == items[curIdx])
			found = true;
		curIdx++;
	}
	return found;
}

template<class T>
bool arrayBag<T>::remove(const T& anEntry){
	int locatedidx = getidxof(anEntry);
	bool canRmvItem = !isEmpty() && (locatedidx > -1);
	if (canRmvItem){
		ic--;
		items[locatedidx] = items[ic];
	}
	return canRmvItem;
}
	template<class T>
	void arrayBag<T>::clear() { return ic = 0; }


template<class T>
arrayBag<T>& arrayBag<T>::Union(const arrayBag<T>& anEntry){
		arrayBag<T> Bag;
		if (!anEntry.isEmpty() && anEntry.getCurrentSize() < deCap){
			for (int i = 0; i < anEntry.getCurrentSize(); i++){
				if (this->getCurrentSize() == deCap)
					break;
				else
					Bag.add(anEntry.items[i]);
			}
		}
		for (int i = 0; i < this->getCurrentSize(); i++)
			Bag.add(this->items[i]);
		Bag.display();
		return Bag;
	}
template<class T>
arrayBag<T>& arrayBag<T>::Intersection(const arrayBag<T>& anEntry){
	arrayBag<T> Bag;
	int intersect = 0;
	for (int i = 0; i < this->getCurrentSize(); i++)
		Bag.add(this->items[i]);

	if (!anEntry.isEmpty() && anEntry.getCurrentSize() < deCap){
		for (int i = 0; i < anEntry.getCurrentSize(); i++){
			if (Bag.getCurrentSize() == deCap)
				break;
			if (anEntry.iscontains(Bag.items[i])){
				if (Bag.getFreqOf(Bag.items[i]) > anEntry.getFreqOf(Bag.items[i])){
					intersect = Bag.getFreqOf(Bag.items[i]) - anEntry.getFreqOf(Bag.items[i]);
					for (int j = 0; j < intersect; j++)
						Bag.remove(Bag.items[i]);
				}
				else if (Bag.getFreqOf(Bag.items[i]) < anEntry.getFreqOf(Bag.items[i]))
					continue;
				else
					continue;
			}
			else 
				Bag.remove(Bag.items[i]);
		}
	}
	Bag.display();
	return Bag;
}

template<class T>
arrayBag<T>& arrayBag<T>::Difference(const arrayBag<T>& anEntry){
int difference;
	arrayBag<T> Bag;
for (int i = 0; i < this->getCurrentSize(); i++)
       Bag.add(this->items[i]);
T item = ' ';
	if (!isEmpty() && Bag.getCurrentSize() < deCap){
		for (int i = 0; i < anEntry.getCurrentSize(); i++){
			if (Bag.getCurrentSize() == deCap)
				break;
			if (Bag.items[i] == item)
				continue;
			
			if (anEntry.iscontains(Bag.items[i])){
				if (Bag.getFreqOf(Bag.items[i]) >  anEntry.getFreqOf(Bag.items[i])){
					difference = anEntry.getFreqOf(Bag.items[i]);
					item = Bag.items[i];
					for (int j = 0; j < difference; j++)
						Bag.remove(Bag.items[i]);
				}
				else if (Bag.getFreqOf(Bag.items[i]) < anEntry.getFreqOf(Bag.items[i])){
					difference = Bag.getFreqOf(Bag.items[i]);
					item = Bag.items[i];
				for (int j = 0; j < difference; j++)
					Bag.remove(Bag.items[i]);
			}
				else{
					difference = Bag.getFreqOf(Bag.items[i]);
					item = Bag.items[i];
					for (int j = 0; j < difference; j++)
						Bag.remove(items[i]);	
				}
			}
			else
				Bag.remove(Bag.items[i]);
		}
	}
	Bag.display();
	return Bag;
}

int main() {
	arrayBag<int> int1;
	arrayBag<int> int2;
	int size = 25;
	for (int i = 0; i < size; i++)
		int1.add(i + 3);
	for (int j = 0; j < size; j++)
		int2.add(j * 5);
	cout << "Union: ";
	int1.Union(int2);
	cout << endl;
	cout << "\nIntersection: ";
	int1.Intersection(int2);
	cout << "\nDifference: 0" << endl;
	int1.Difference(int2);
	return 0;

}