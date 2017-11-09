非变动性算法
find(),find_if(),count(),count_if()

#include<iostream>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include"algostuff.h"

using namespace std;

bool isEven(int item)
{
	return item % 2 == 0;
}
bool absless(int elem1, int elem2)
{
	return abs(elem1) < abs(elem2);
}
int main()
{
	/*
	count（）函数，count(InputIterator beg,InputIterator end,const T& value):统计区间[beg，end）中等于value的元素
	count_if()函数，count_if(InputIterator beg,InputIterator end,op):统计区间[beg，end）中使得一元判断式满足条件的元素的个数。
	关联容器提供了相似的成员函数count()来计算等于某个value或某个key的元素个数
	*/
	vector<int> coll;
	INSERT_ELEMENTS(coll, 1, 9);
	INSERT_ELEMENTS(coll, 1, 9);
	PRINT_ELEMENTS(coll);
	int num = count(coll.begin(), coll.end(), 4);//count函数，计算值为4的元素个数
	cout << num << endl;
	num = count_if(coll.begin(), coll.end(), isEven);//count_if函数，计算能被2整除的元素的个数
	cout << num << endl;
	num = count_if(coll.begin(), coll.end(), bind2nd(greater_equal<int>(), 4));//计算大于等于4的元素的个数
	cout << num << endl;
	/*
	*最大值和最小值
	*min_element(InputIterator beg,InputItaerator end)计算区间的最小值，最大值max_element；
	*用op来比较两个元素
	*min_element(InputIterator beg,InputItaerator end，CompFunc op)
	*默认是用operator<来比较两个元素，op(elem1,elem2)如果第一个元素小于第二个元素，应当返回true。
	*op()不应改变传入的参数
	*如果存在多个最大值或最小值，返回第一个最大值或最小值。
	*/
	vector<int>coll2;
	INSERT_ELEMENTS(coll2, 2, 8);
	INSERT_ELEMENTS(coll2, -3, 5);
	PRINT_ELEMENTS(coll2);
	cout << "minimun: "
		<< *min_element(coll2.begin(), coll2.end())
		<< endl;
	cout << "maximun: "
		<< *max_element(coll2.begin(), coll2.end())
		<< endl;
	cout << "minimun of absolute values: "
		<< *min_element(coll2.begin(), coll2.end(), absless)
		<< endl;
	cout << "maximun of absolute values: "
		<< *max_element(coll2.begin(), coll2.end(), absless)
		<< endl;
	/*
	*find()函数，用来搜寻元素。关联容器有自己的成员函数，速度会更快。
	*find(beg,end,value)
	*find(beg,end,op),第一种形式返回区间中第一个元素值等于value的位置，第二种形式返回区间中令op结果为TRUE的第一个元素
	*如果没有找到元素，返回end（）
	*如果是已经有序的区间，使用lower_bound(),upper_bound(),equal_range()或者是binary_search()算法获取更高性能。
	*关联容器的成员函数find的复杂度是对数级别，而不同的find的复杂度是线性级别的。
	*/
	//用find()来搜寻一个区间里以元素4开头和以元素4结尾的区间
	list<int>coll3;
	INSERT_ELEMENTS(coll3, 1, 9);
	INSERT_ELEMENTS(coll3, 2, 8);
	PRINT_ELEMENTS(coll3);
	cout << endl;
	list<int>::iterator pos1, pos2;
	pos1 = find(coll3.begin(), coll3.end(), 4);//找到第一个以4开头的位置
	if (pos1 != coll3.end())
		pos2 = find(++pos1, coll3.end(), 4);//找到以4结尾的位置
	if (pos2 != coll3.end())
	{
		cout << "以4开头和以4结尾的区间的元素为： " << endl;
		copy(pos1, pos2, ostream_iterator<int>(cout, " "));//输出区间的元素
	}
	cout << endl;
	pos1 = find_if(coll3.begin(), coll3.end(), bind2nd(greater<int>(), 3));
	if (pos1 != coll3.end())
		cout << "The "
		<< distance(coll3.begin(), pos1) + 1
		<< " element is first greater than 3"
		<< endl;
	pos1 = find_if(coll3.begin(), coll3.end(), not1(bind2nd(modulus<int>(), 3)));
	if (pos1 != coll3.end())
		cout << "The "
		<< distance(coll3.begin(), pos1) + 1
		<< " is the first element can be divisible by 3"
		<< endl;
	return 0;
}
