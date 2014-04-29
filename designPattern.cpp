test.....
//单例模式，非线程安全
#include <iostream>
using namespace std;
class SingletonStatic
{
 private:
     static const SingletonStatic* m_instance;
     SingletonStatic(){}
public:
     static const SingletonStatic* getInstance()
     {
        return m_instance;
    }
 }; 
//外部初始化 before invoke main
const SingletonStatic* SingletonStatic::m_instance = new SingletonStatic;

void main()
{
	const SingletonStatic *p =  SingletonStatic::getInstance();
	const SingletonStatic *q =  SingletonStatic::getInstance();
	const SingletonStatic *r =  SingletonStatic::getInstance();

	cout<<hex;
	cout<<p<<endl<<q<<endl<<r<<endl;
}

//another example
class CSingleton
{
//其他成员
public:
static CSingleton* GetInstance()
{
      if ( m_pInstance == NULL )  //判断是否第一次调用
        m_pInstance = new CSingleton();
        return m_pInstance;
}
private:
    CSingleton(){};
    static CSingleton * m_pInstance;
};
CSingleton * CSingleton::m_pInstance = NULL;
void main()
{
	CSingleton *p =  CSingleton::GetInstance();
}

///////////////////////////////////////////////////////////////////
//Singleton
///////////////////////////////////////////////////////////////////
class Singleton
{
public:
	static Singleton * getInstance(int);
	void dump();
private:
	Singleton(int);
	static Singleton * singleton;
	static int count1;
	static int count2;

	int x;
};

#include <stdio.h>
Singleton * Singleton::singleton = NULL;
int Singleton::count1 = 0;
int Singleton::count2 = 0;

Singleton::Singleton(int a)
{
	count2++;
	printf("I'm a singleton.\n");
	printf("cout2=%d \n",count2);
	x = a;
}

Singleton * Singleton::getInstance(int a)
{
	count1++;

	if(singleton==NULL)
		singleton = new Singleton(a);

	printf("cout1=%d \n",count1);
	return singleton;
}

void Singleton::dump()
{
	printf("x=%d\n",x);
}

#include "head.h"
int main()
{
	/*============Singleton example================*/
	Singleton *singleA = Singleton::getInstance(9);
	Singleton *singleB = Singleton::getInstance(99);
	Singleton *singleC = Singleton::getInstance(999);

	printf("singleA address is 0x%x \n",singleA);
	printf("singleB address is 0x%x \n",singleB);
	printf("singleC address is 0x%x \n",singleC);

	singleA->dump();
	singleB->dump();
	singleC->dump();
	return 0;
}
/*
I'm a singleton
cout2=1
cout1=1
cout1=2
cout1=3
singleA address is 0x393200
singleB address is 0x393200
singleC address is 0x393200
x=9
x=9
x=9
*/

///////////////////////////////////////////////////////////////////
//Factory
///////////////////////////////////////////////////////////////////
enum TYPE {coreA, coreB};

class Base
{
public:
	virtual void show()=0;
};
class A:public Base
{
public:
	A(){printf("create class A \n");}
	void show(){printf("aaaaaaa\n");}
};
class B:public Base
{
public:
	B(){printf("create class B \n");}
	void show(){printf("bbbbbbbbb\n");}
};
class Factory
{
public:
	Base * create(enum TYPE type)
	{
		if(type==coreA)
			return new A();
		else if(type==coreB)
			return new B();
		else
			return NULL;
	}
};

#include "head.h"
int main()
{
	Factory f;
	Base * pBaseA;
	Base * pBaseB;
	pBaseA = f.create(coreA);
	pBaseA->show();
	pBaseB = f.create(coreB);
	pBaseB->show();
	return 0;
}
//////////////////////////////////////////////////////////////
//Observer
//////////////////////////////////////////////////////////////
class Observer
{
public:
	Observer(){cout<<"class Observer Constructor+++"<<endl;}
	virtual ~Observer(){cout<<"class Observer Deconstructor---"<<endl;}
	virtual void update(){cout<<"class Observer function: update()"<<endl;}
};
class Blog
{
public:
	Blog(){cout<<"class Blog Constructor+++"<<endl;}
	virtual ~Blog(){cout<<"class Blog Deconstructor---"<<endl;}
	void attach(Observer *obs)
	{
		cout<<"class Blog function:attach(Observer *obs)"<<endl;
		m_obs.push_back(obs);
	}

	void remove(Observer *obs)
	{
		cout<<"class Blog function:remove(Observer *obs)"<<endl;
		m_obs.remove(obs);
	}

	void notify()
	{
		cout<<"class Blog function:notify()"<<endl;
		list<Observer *> :: iterator iter = m_obs.begin();
		for(;iter!=m_obs.end();iter++)
			(*iter)->update();
	}

	virtual void setStatus(string s)
	{
		cout<<"class Blog function:setStatus(string s)"<<endl;
		m_status = s;
	}

	virtual string getStatus()
	{
		cout<<"class Blog function:getStatus()"<<endl;
		return m_status;
	}

private:
	list<Observer *> m_obs;
protected:
	string m_status;
};

class BlogCSDN:public Blog
{
private:
	string m_name;
public:
	BlogCSDN (string name):m_name(name) {
		cout<<"class BlogCSDN Constructor+++"<<endl;
	}
	~BlogCSDN(){cout<<"class BlogCSDN Deconstructor---"<<endl;}

	void setStatus(string s)
	{
		cout<<"class BlogCSDN function:setStatus(string s)"<<endl;
		m_status = "CSDN: " + m_name + s;
	}

	string getStatus()
	{
		cout<<"class BlogCSDN function:getStatus()"<<endl;
		return m_status;
	}
};

class ObserverBlog : public Observer
{
public:
	ObserverBlog(string name, Blog *blog) : m_name(name),m_blog(blog) {
		cout<<"class ObserverBlog Constructor+++"<<endl;
	}
	~ObserverBlog(){
		cout<<"class ObserverBlog Deconstructor---"<<endl;
	}

	void update()
	{
		cout<<"class ObserverBlog function:update()"<<endl;
		string status = m_blog->getStatus();
		cout<<m_name<<"----"<<status<<endl;
	}
private:
	string m_name;
	Blog *m_blog;
};

#include "head.h"
int main()
{
/*============Observer example================*/
	Blog *blog = new BlogCSDN("wangy");
	Observer *obs_1 = new ObserverBlog("obs_111",blog);
	Observer *obs_2 = new ObserverBlog("obs_222",blog);
	Observer *obs_3 = new ObserverBlog("obs_333",blog);
	blog->attach(obs_1);
	blog->attach(obs_2);
	blog->attach(obs_3);
	blog->setStatus("---observer model example");
	blog->notify();

	delete blog;
	delete obs_1;
	delete obs_2;
	delete obs_3;

	return 0;
}
