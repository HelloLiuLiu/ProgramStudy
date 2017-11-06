C++primer第15章。
继承，基类，派生类，动态绑定，虚函数
#include<iostream>
#include<string>
using namespace std;
/*
*派生类可以继承基类成员，当继承的是基类的virtual成员的时候，派生类总是给出自己的定义来覆盖从基类继承而来的旧的定义而不是必须。
*当派生类没有覆盖继承而来的虚函数的时候，该函数就跟普通的成员函数没有区别
*基类必须把两种成员分开：
一类是基类希望派生类直接继承的普通函数成员
另外一类是基类希望派生类能够提供自己的定义的虚函数成员
*当使用指针或引用调用虚函数的时候，将发生动态绑定
*任何构造函数之外的非静态函数都可以是虚函数
*受保护的：
基类希望派生类能够访问但是禁止其他用户访问的成员
*
*
*
*
*

*/

//定义基类
class Quote
{
private:
	string book_No;
protected:
	double price=0.0;//price这个成员在派生类中需要被访问，因此定义为proteced
public:
	Quote() = default;
	Quote(const string& isbn, double salse_price) :book_No(isbn), price(salse_price) {}
	string get_isbn()const;
	virtual double net_price(size_t)const;//net_price()成员函数根据派生类不同有不同的操作，因此定义为虚函数
	virtual ~Quote() = default;//对析构函数进行动态绑定
	//**基类都应该定义一个虚析构函数，即使什么也不做

};

string Quote::get_isbn()const//返回书籍的ISBN编号
{
	return book_No;
}
double Quote::net_price(size_t n)const//计算给定数量的费用
{
	return n*price;
}
//定义派生类
class Bulk_Quote :public Quote//派生类必须通过派生类表明确的指出该派生类继承自哪一个基类和继承的方式是什么
{
private:
	size_t min_qty = 0;//最低折扣数量
	double discount = 0.0;//折扣额
public:
	Bulk_Quote() = default;//默认构造函数
	double net_price(size_t)const override;//显示标注net_price()成员函数是重新定义的虚函数
	Bulk_Quote(const string&, double, size_t, double);
};
Bulk_Quote::Bulk_Quote(const string&isbn, double price, size_t n, double disc) :
	Quote(isbn, price), min_qty(n), discount(disc) {}//构造函数的参数顺序必须是先基类构造函数必须的参数、派生类自身需要的参数，构造函数先构造基类部分再依次构造派生类部分
double Bulk_Quote::net_price(size_t n)const
{
	double ret;
	if (n >= min_qty)
	return ret = n*(1 - discount)*price;
	else
	return ret = n*price;
}

//使用基类的引用或指正实现动态绑定，使用同一段代码处理不同类型的对象----前提是基类中有虚函数

double print_total(ostream& os, const Quote&item, size_t n)
{
	//根据传入的item形参的对象调用Quote::net_price或是者是Bulk_Quote::net_price
	double ret = item.net_price(n);//返回根据不同数量产生的费用
	os << "ISBN: " << item.get_isbn()//调用item.get_isbn()
		<< "# sold: " << n
		<< "total due: " << ret << endl;
	return ret;
}
int main()
{
	Bulk_Quote bul("algorithm", 89.5, 10, 0.75);
	cout << bul.get_isbn() << endl;
	cout << bul.net_price(30) << endl;
	Bulk_Quote&bq = bul;
	cout << print_total(cout,bul,30) << endl;
	return 0;
}
