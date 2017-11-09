for_each()

#include<iostream>
#include"algostuff.h"

using namespace std;

void print(int elem)
{
	cout << elem << " ";
}
template<class T>
class AddValue
{
private:
	T value;
public:
	AddValue(int v) :value(v) {}
	void operator()(T& item)const
	{
		item += value;
	}
};

int main()
{
	vector<int>coll1;
	INSERT_ELEMENTS(coll1, 1, 9);
	for_each(coll1.begin(), coll1.end(), print);
	cout << endl;
	for_each(coll1.begin(), coll1.end(), AddValue<int>(10));
	PRINT_ELEMENTS(coll1, " ");
	cout << endl;
	for_each(coll1.begin(), coll1.end(), AddValue<int>(*coll1.begin()));
	PRINT_ELEMENTS(coll1, " ");
	cout << endl;
	transform(coll1.begin(), coll1.end(),coll1.begin(), bind2nd(plus<int>(), 10));
	PRINT_ELEMENTS(coll1, " ");
	cout << endl;
	transform(coll1.begin(), coll1.end(), coll1.begin(), bind2nd(minus<int>(), 10));
	for_each(coll1.begin(), coll1.end(), print);
	cout << endl;
	return 0;
}
