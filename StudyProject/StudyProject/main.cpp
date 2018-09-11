//工厂模式

#if 0
#include <iostream>
class Product {
public:
	virtual void show() = 0;
};

class ProductA : public Product {
public:
	void show()
	{
		std::cout << "ProductA" << '\n';
	}
};

class ProductB : public Product {
public:
	void show()
	{
		std::cout << "ProductB << '\n'";
	}
};

class Factory {
public:
	Product * CreateInstance(int type)
	{
		if (type == 1)
		{
			return new ProductA();
		}
		else if (type == 2)
		{
			return new ProductB();
		}
		else {
			std::cout << "Type Error!" << '\n';
			return NULL;
		}
	}
};

int main(void)
{
	Factory *f = new Factory();
	Product *p1 = f->CreateInstance(1);
	if (p1 != NULL) {
		p1->show();
	}


	getchar();
	return 0;
}


#endif

#if 0
#include <iostream>
class Product {
public:
	virtual void show() = 0;
};


class ProductA : public Product {
public:
	void show()
	{
		std::cout << "ProductA" << '\n';
	}
};

class ProductB : public Product {
public:
	void show()
	{
		std::cout << "ProductB" << '\n';
	}
};

class Factory {
public:
	virtual Product *CreateInstance() = 0;

};

class FactoryA : public Factory {
public:
	Product * CreateInstance()
	{
		return new ProductA();
	}
};

class FactoryB : public Factory {
public:
	Product * CreateInstance()
	{
		return new ProductB();
	}
};

int main(void)
{
	Factory *f = new FactoryB();
	Product *p = f->CreateInstance();
	p->show();

	getchar();
	return 0;
}

#endif

#if 0
#include<iostream>
class Phone {
public:
	virtual void show() = 0;
};

class SamSung : public Phone
{
public:
	void show()
	{
		std::cout << "SamSung" << '\n';
	}
};

class Sony : public Phone
{
public:
	void show()
	{
		std::cout << "Sony" << '\n';
	}
};

class Computer {
public:
	virtual void show() = 0;
};

class Lenovo : public Computer
{
public:
	void show()
	{
		std::cout << "Lenovo" << '\n';
	}
};

class Dell : public Computer
{
public:
	void show()
	{
		std::cout << "Dell" << '\n';
	}
};

class Factory {
public:
	virtual Phone * CreatePhone() = 0;
	virtual Computer * CreateComputer() = 0;

};

class FactoryA : public Factory {
public:
	Phone * CreatePhone()
	{
		return new SamSung();
	}

	Computer * CreateComputer()
	{
		return new Lenovo();
	}
};

class FactoryB : public FactoryA {
public:
	Phone * CreatePhone()
	{
		return new Sony();
	}

	Computer * CreateComputer()
	{
		return new Dell();
	}
};
int main(void)
{
	Factory *fA = new FactoryA();
	Phone *pA = fA->CreatePhone();
	pA->show();

	Factory *fB = new FactoryB();
	Computer *pB = fB->CreateComputer();
	pB->show();

	getchar();

	return 0;
}


#endif

//策略模式
#if 0
#include <iostream>

class Subject {
public:
	virtual void Learn() = 0;
};

class English :public Subject {
public:
	void Learn()
	{
		std::cout << "Learning English" << '\n';
	}
};

class Chinese :public Subject
{
public:
	void Learn()
	{
		std::cout << "Learning Chinese" << '\n';
	}
};

class Strategy {
public:
	virtual void LearnSth() = 0;
	Strategy(Subject *p) : m_sub(p)
	{

	}
	~Strategy()
	{

	}
protected:
	Subject * m_sub;
};

class StrategyEng : public Strategy
{
public:
	StrategyEng(Subject *p) : Strategy(p)
	{

	}
	~StrategyEng()
	{

	}

	void LearnSth()
	{
		m_sub->Learn();
	}

};

class StrategyChi : public Strategy
{
public:
	StrategyChi(Subject *p) : Strategy(p)
	{

	}
	~StrategyChi()
	{

	}

	void LearnSth()
	{
		m_sub->Learn();
	}

};

int main(void)
{

	Subject *p = new English();
	Strategy *s = new StrategyEng(p);
	s->LearnSth();

	getchar();


	return 0;
}

#endif

//代理模式实现 Proxy
#if 0
#include <iostream>
class Play {
public:
	virtual void playLOL() = 0;
	virtual void playDOTA() = 0;
	virtual void playCF() = 0;

};

class Player : public Play {
public:
	void playLOL()
	{
		std::cout << "play LOL" << '\n';
	}

	void playDOTA()
	{
		std::cout << "play DOTA" << '\n';
	}

	void playCF()
	{
		std::cout << "play CF" << '\n';
	}
};

class PlayProxy1 : public Play {
public:
	PlayProxy1(Player *play)
	{
		m_play = play;
	}
	PlayProxy1()
	{
		if (m_play == NULL)
		{
			m_play = new Player();
		}
	}
	~PlayProxy1()
	{
		if (m_play == NULL)
		{
			m_play = new Player();
		}
	}
	void playLOL()
	{
		m_play->playLOL();
	}

	void playDOTA()
	{
		std::cout << "NO RIGHT" << '\n';
	}

	void playCF()
	{
		std::cout << "NO RIGHT" << '\n';
	}
private:
	Player * m_play;
};

class PlayProxy2 : public Play {
public:
	PlayProxy2(Player *play)
	{
		m_play = play;
	}
	PlayProxy2()
	{
		if (m_play == NULL)
		{
			m_play = new Player();
		}

	}
	~PlayProxy2()
	{
		if (m_play != NULL)
		{
			delete m_play;
		}
	}
	void playLOL()
	{
		m_play->playLOL();
	}

	void playDOTA()
	{
		m_play->playDOTA();
	}

	void playCF()
	{
		std::cout << "NO RIGHT" << '\n';
	}
private:
	Player * m_play;
};

class PlayProxy3 : public Play {
public:
	PlayProxy3(Player *play)
	{
		m_play = play;
	}
	PlayProxy3()
	{
		if (m_play == NULL)
		{
			m_play = new Player();
		}

	}
	~PlayProxy3()
	{
		if (m_play != NULL)
		{
			delete m_play;
		}
	}
	void playLOL()
	{
		m_play->playLOL();
	}

	void playDOTA()
	{
		m_play->playDOTA();
	}

	void playCF()
	{
		m_play->playCF();
	}
private:
	Player * m_play;
};

int main(void)
{
	Play *p = new PlayProxy2();
	p->playCF();
	getchar();

	return 0;
}

#endif

//装饰模式

#if 0

#include <iostream>
class Phone {
public:
	virtual void showDecorate() = 0;
};

class iPhone : public Phone
{
public:
	void showDecorate()
	{
		std::cout << "苹果装饰" << '\n';
	}
};

class Nokia : public Phone {
public:
	void showDecorate()
	{
		std::cout << "诺基亚装饰" << '\n';
	}
};

class DecoratePhone1 : public Phone
{
public:
	DecoratePhone1(Phone *p) :m_p(p)
	{
	}

	void showDecorate()
	{
		m_p->showDecorate();
		std::cout << "增加贴膜" << '\n';
	}
private:
	Phone * m_p;
};

class DecoratePhone2 : public Phone
{
public:
	DecoratePhone2(Phone *p) :m_p(p)
	{
	}

	void showDecorate()
	{
		m_p->showDecorate();
		std::cout << "增加挂件" << '\n';
	}
private:
	Phone * m_p;
};

int main(void)
{
	Phone *p = new iPhone();
	Phone *pd = new DecoratePhone1(p);
	pd->showDecorate();

	getchar();
}
#endif

//状态模式
#if 0
#include<iostream>

class War;

class State
{
public:
	virtual void StateAction(War *p)
	{}// = 0;
};

class War {
public:
	War(State *p) :m_state(p), m_days(0)
	{

	}
	int GetDays()
	{
		return m_days;
	}
	void SetDays(int days)
	{
		m_days = days;
	}
	void GetState()
	{
		m_state->StateAction(this);
	}
	void SetState(State *p)
	{
		if (m_state != NULL)
		{
			delete m_state;
		}
		m_state = p;
	}


private:
	State * m_state;
	int m_days;

};

class StageD : public State {
public:
	void StateAction(War *p)
	{
		if (p->GetDays() > 15)
		{
			std::cout << "StageD is Running, War is End" << '\n';
		}
		/*else {
		State *s = new StageD();
		p->SetState(s);
		p->GetState();
		}*/
	}
};


class StageC : public State {
public:
	void StateAction(War *p)
	{
		if (p->GetDays() > 10 && p->GetDays() <= 15)
		{
			std::cout << "StageC is Running" << '\n';
		}
		else {
			State *s = new StageD();
			p->SetState(s);
			p->GetState();
		}
	}
};

class StageB : public State {
public:
	void StateAction(War *p)
	{
		if (p->GetDays() > 5 && p->GetDays() <= 10)
		{
			std::cout << "StageB is Running" << '\n';
		}
		else {
			State *s = new StageC();
			p->SetState(s);
			p->GetState();
		}
	}
};

class StageA : public State {
public:
	void StateAction(War *p)
	{
		if (p->GetDays() <= 5) {
			std::cout << "StageA is Running" << '\n';
		}
		else {
			State *s = new StageB();
			p->SetState(s);
			p->GetState();
		}
	}
};
int main(void)
{
	War *p = new War(new StageA());
	for (int i = 0; i < 30; i += 5)
	{
		p->SetDays(i);
		p->GetState();
	}

	getchar();
	return 0;
}


#endif
//外观模式
#if 1
#include <iostream>
class GetUp
{
public:
	void Wash()
	{
		std::cout << "Wash" << '\n';
	}

};

class ByBus
{
public:
	void Bus()
	{
		std::cout << "Bus" << '\n';
	}
};

class Working {
public:
	void Program()
	{
		std::cout << "Program" << '\n';
	}
};

class Sleeping {
public:
	void Exercise()
	{
		std::cout << "Exercise" << '\n';
	}
};

class OneDay {
public:
	void Life()
	{
		GetUp g;
		ByBus b;
		Working w;
		Sleeping s;
		g.Wash();
		b.Bus();
		w.Program();
		s.Exercise();
	}
};
int main(void)
{
	OneDay o;
	o.Life();
	getchar();
	return 0;
}


#endif