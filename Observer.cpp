#include <iostream>
#include <list>
using namespace std;

class ISubject;

// 观察者接口
class IObserver
{
public:
	virtual void update() = 0;

	// attention Virtual destructor
	virtual ~IObserver() { }
};

// 主题接口
class ISubject
{
public:
	virtual void Subscibe(IObserver* obser) = 0;
	virtual void UnSubscibe(IObserver* obser) = 0;
	virtual void notify() = 0;
};

class Subject: public ISubject
{		
public:
	void Subscibe(IObserver* obser)
	{
		for (list<IObserver*>::iterator iter = m_obsers.begin(); iter != m_obsers.end(); ++iter)
		{
			if (*iter == obser)
			{
				return;
			}
		}
		m_obsers.push_back(obser);
	}

	void UnSubscibe(IObserver* obser)
	{
		for (list<IObserver*>::iterator iter = m_obsers.begin(); iter != m_obsers.end(); ++iter)
		{
			if (obser == *iter)
			{
				m_obsers.remove(*iter);
				break;
			}
		}
	}

	void notify()
	{
		for (list<IObserver*>::iterator iter = m_obsers.begin(); iter != m_obsers.end(); ++iter)
		{
			(*iter)->update();
		}
	}

private:
	list<IObserver*> m_obsers;
};

class ObserverA: public IObserver
{
public:
	ObserverA(ISubject* pSubject): m_pSubject(pSubject)
	{

	}

	void update()
	{
		cout<<"ObserverA do something"<<endl;
	}

	// 析构时反注册
	~ObserverA()
	{
		m_pSubject->UnSubscibe(this);
	}

private:
	ISubject* m_pSubject;
};

class ObserverB: public IObserver
{
public:
	ObserverB(ISubject* pSubject): m_pSubject(pSubject)
	{

	}

	void update()
	{
		cout<<"ObserverB do something"<<endl;
	}

	// 析构时反注册
	~ObserverB()
	{
		m_pSubject->UnSubscibe(this);
	}

private:
	ISubject* m_pSubject;
};

int main()
{
	ISubject* pSubject = new Subject;
	IObserver* pObser1 = new ObserverA(pSubject);
	IObserver* pObser2 = new ObserverB(pSubject);
	pSubject->Subscibe(pObser1);
	pSubject->Subscibe(pObser2);
	pSubject->notify();

	delete pObser1;
	delete pObser2;
	delete pSubject;

	return 0;
}