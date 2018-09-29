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
#if 0
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

//单链表操作
#if 0
#include <iostream>
#include <stdlib.h>
#define LOG(a) std::cout << a << '\n';

typedef struct pNode {
	int data;
	struct pNode *next;
} LinkList;

LinkList * InitLinkList(LinkList *L)
{
	LOG("InitLinkList Start");
	L = (LinkList *)malloc(sizeof(struct pNode));
	L->next = NULL;
	LOG("InitLinkList End");
	return L;
}

LinkList* CreateLinkListHead(LinkList *L, int n)
{
	LOG("CreateLinkListHead Start");
	LinkList *p = NULL;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList *)malloc(sizeof(struct pNode));
		p->data = i*3;
		p->next = L->next;
		L->next = p;
	}
	LOG("CreateLinkListHead End");
	return L;
}

LinkList* CreateLinkListTail(LinkList *L, int n)
{
	LinkList *p, *tmp;
	p = tmp = NULL;
	tmp = L;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList*)malloc(sizeof(struct pNode));
		p->data = i * 3;
		p->next = NULL;
		tmp->next = p;
		tmp = p;
	}

	return L;
}

LinkList *InsertLinkList(LinkList *L, LinkList *Ins)
{
	LinkList *p = L;
	LinkList *pre = NULL;
	if (Ins->data < L->data)
	{
		Ins->next = L;
		L = Ins;
	}
	else {
		while (p != NULL && p->data < Ins->data)
		{
			pre = p;
			p = p->next;
		}
		if (p == NULL)
		{
			pre->next = Ins;
			Ins->next = NULL;
		}
		else {
			pre->next = Ins;
			Ins->next = p;
		}
		
	}

	return L;
}

LinkList *DeleteLinkList(LinkList *L, int n)
{
	LinkList *p = L;
	LinkList *pre = NULL;
	while (p->next != NULL && p->data != n)
	{
		pre = p;
		p = p->next;
	}
	if (p->next == NULL)
	{
		std::cout << "No Found Node\n";
	}
	else {
		std::cout << "FIND IT\n";
		pre->next = p->next; 
		free (p);
		p = NULL;
	}

	return L;
}

void printLinkList(LinkList *L)
{
	if (L != NULL)
	{
		LinkList *p = L;
		while (p->next != NULL)
		{
			int a;
			p = p->next;
			a = p->data;
			std::cout << a << '\n';

		}
	}

}

int GetListLength(LinkList* L)
{
	int len = 0;
	LinkList* p = L->next;
	while (p)
	{
		len++;
		p = p->next;
	}

	return len;
}

int printLinkList1(LinkList *L)
{
	LinkList *s = L->next;
	while (s)
	{
		std::cout << s->data << '\n';
		s = s->next;
	}
	return 1;
}

void clearLinkList(LinkList *L)
{
	LinkList *p = L;
	LinkList *temp = NULL;
	while (p)
	{
		temp = p;
		p = p->next;
		free(temp);
	}
	L->next = NULL;
	std::cout << "Clean end!\n";
}
int main(void)
{
	LinkList* L = NULL;
	LinkList *a =  InitLinkList(L);
	//a = CreateLinkListHead(a, 5);
	a = CreateLinkListTail(a, 5);
	//std::cout << GetListLength(a) << '\n';
	//printLinkList(a);
	LinkList *Ins = (LinkList *)malloc(sizeof(pNode));
	Ins->data = 55;
	Ins->next = NULL;
	InsertLinkList(a, Ins);
	std::cout << GetListLength(a) << '\n';
	printLinkList(a);
	DeleteLinkList(a, 6);
	std::cout << GetListLength(a) << '\n';
	printLinkList(a);

	clearLinkList(a);

	getchar();
	return 0;
}


#endif


//队列操作（数组实现）

#if 0

#include <iostream>

static int* arr = NULL;
static int count;

int CreateArrayQueue(int n)
{
	arr = (int *)malloc(sizeof(int) * n);
	if (arr == NULL)
	{
		return -1;
	}
	count = 0;
	return 1;
}

int destoryArrayQueue()
{
	if (arr != NULL)
	{
		delete arr;
		arr = NULL;
		return 1;
	}
	return -1;
}
void add(int n)
{
	arr[count++] = n;
}

int front()
{
	return arr[0];
}

int pop()
{
	int i = 0;
	while (i < count)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	count--;
	return 1;
}

int size()
{
	return count;
}

bool is_empty()
{
	return count == 0;
}

int main(void)
{
	int n = 5;
	CreateArrayQueue(n);
	add(10);
	add(20);
	add(30);
	std::cout << size() << '\n';
	std::cout << front() << '\n';
	pop();
	std::cout << front() << '\n';


	getchar();
	return 0;
}

#endif

//队列操作（链表实现）
#if 0
#include <iostream>
#include <stdlib.h>



typedef struct pNode {
	int data;
	struct pNode *next;
}LinkList;

static LinkList *head = NULL;
static int count = 0;

LinkList* CreateNode(int n)
{
	LinkList *p = NULL;
	p = (LinkList*)malloc(sizeof(pNode));
	if (p == NULL)
	{
		return NULL;
	}
	p->data= n;
	p->next = NULL;

	return p;
}

void DestroyQueue(LinkList *L)
{
	LinkList *p = L;
	LinkList *temp = NULL;
	while (p)
	{
		temp = p;
		p = p->next;
		free(temp);
		temp = NULL;
	}
}

static LinkList *InsertQueue(int n)
{
	if (head == NULL)
	{
		head = (LinkList*)malloc(sizeof(pNode));
		head->data = n;
		head->next = NULL;
		return head;
	}
	LinkList *end = head;
	LinkList *q = CreateNode(n);
	while (end->next != NULL)
	{
		end = end->next;
	}
	end->next = q;
	return head;
}

static int Queuefront()
{
	return head->data;
}

static int popQueue()
{
	LinkList* p = head;
	int num = 0;
	if (p->next == NULL)
	{
		free(p);
		p = NULL;
	}
	else {
		num = p->data;
		head = p->next;
		free(p);
		p = NULL;
	}
	return num;
}

static int QueueLength()
{
	count = 0;
	LinkList *p = head;
	while (p)
	{
		count++;
		p = p->next;

	}
	return count;
}

static bool QueueEmpty(LinkList *L)
{
	if (head)
	{
		return false;
	}
}

int main(void)
{
	InsertQueue(10);
	InsertQueue(20);
	InsertQueue(30);
    std::cout << QueueLength() << '\n';
	std::cout << Queuefront() << '\n';
	popQueue();
	std::cout << QueueLength() << '\n';
	std::cout << Queuefront() << '\n';

	getchar();
	return 0;
}

#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node pNode;
struct Node
{
	int data;
	pNode *prev, *next;
};
/* 初始化链表，尾插法 */
pNode *InitList(pNode **head, int n)
{
	pNode *p, *s;
	(*head) = (pNode *)malloc(sizeof(pNode));
	if ((*head) == NULL)
		exit(0);
	(*head)->next = NULL;//head的prev和next均指向NULL
	(*head)->prev = NULL;
	p = (*head);//p指向head
	int i;
	for (i = 0; i < n; ++i)
	{
		s = (pNode *)malloc(sizeof(pNode));
		if (s == NULL)
			exit(0);
		printf("Input the value of the %dth node:", i + 1);
		scanf("%d", &s->data);
		s->next = NULL;
		p->next = s;
		s->prev = p;
		p = s;//p指向尾节点
	}
	return p;
}
/* 遍历打印 */
void PrintList(pNode *head)
{
	pNode *p;
	p = head->next;
	if (head->next == NULL)
		printf("the list is empty\n");
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
/* 清空链表 */
void DeleteList(pNode **head)
{
	pNode *p;
	while ((*head)->next != NULL)
	{
		p = (*head);
		p->next->prev = NULL;
		(*head) = p->next;
		free(p);
	}
}
/* 查找链表内的某个值 */
int SearchList(pNode *head)
{
	int number;
	printf("Values are about to be deleted:");
	scanf("%d", &number);
	pNode *p;
	p = head->next;
	while (p != NULL)
	{
		if (p->data == number)
		{
			return number;
		}
		p = p->next;
	}
	return 0;
}
/* 删除链表中某个元素，令p的前驱节点和后驱节点相互指向即可，如果p是尾节点则直接将前驱节点指向NULL*/
void DelNumqList(pNode **head, int n)
{
	int i;
	pNode *p;
	p = (*head)->next;
	for (i = 1; i < n; ++i)
		p = p->next;
	if (p->next == NULL)
	{
		p->prev->next = NULL;
		free(p);
	}
	else
	{
		p->next->prev = p->prev;
		p->prev->next = p->next;
		free(p);
	}
}
int main(int argc, char const *argv[])
{
	int n, element, flag;
	pNode *head, *last;
	/***************************************************************/
	printf("Please input the size of the list:");
	scanf("%d", &n);
	last = InitList(&head, n);//初始化链表并赋值,返回尾节点last
	printf("%d %d \n", head->next->data, last->data); //打印为第一个元素和最后一个元素
	PrintList(head);
	/***************************************************************/
	flag = SearchList(head); //搜索某个值并删除节点
	if (flag > 0 && flag <= n)
	{
		DelNumqList(&head, flag);
		PrintList(head);
	}
	else
		printf("Element does not exist, cannot be deleted\n");
	/***************************************************************/
	DeleteList(&head);//清空列表
	PrintList(head);
	return 0;
}

#endif

//判断两个区间是否重叠
#if 0

#include <iostream>
#include <vector>
typedef struct {
	int start;
	int end;
}Interval;

int maxNum(int x, int y)
{
	return  x > y ? x : y;
}

int minNum(int x, int y) 
{
	return x > y ? y : x;
}


bool isOverlap(std::vector<Interval> &iVec, Interval c)
{
	std::vector<Interval>::iterator it = iVec.begin();
	for (; it != iVec.end(); ++it)
	{
		if (maxNum(it->start, c.start) < minNum(it->end, c.end))
		{

			return true;
		}
	}

	return false;
}

int main(void)
{
	std::vector<Interval> iVec;
	Interval a = {1,4};
	Interval b = {4,7};
	Interval c = {6,9};

	iVec.push_back(a);
	iVec.push_back(b);
	if (isOverlap(iVec, c))
	{
		std::cout << "isOverlap" << std::endl;
	}
	else {
		std::cout << "isNotOverlap" << std::endl;
	}

	getchar();
	return 0;
}

#endif

#if 0
#include <iostream>
#include <memory>
typedef std::shared_ptr<int> smart_ptr;

int main(void)
{
	//smart_ptr p(new int(2));
	////smart_ptr p1(new int(6));
	//smart_ptr p2 = p;
	//std::cout <<p.use_count()<< '\n';
	////std::cout << p1.use_count() << '\n';
	//std::cout << p2.use_count() << '\n';


	std::shared_ptr<int> sp0(new int(2));
	std::shared_ptr<int> sp1(new int(11));
	std::shared_ptr<int> sp2 = sp1;
	printf("%d\n", *sp0);               // 2
	printf("%d\n", *sp1);               // 11
	printf("%d\n", *sp2);               // 11
	sp1.swap(sp0);
	printf("%d\n", *sp0);               // 11
	printf("%d\n", *sp1);               // 2
	printf("%d\n", *sp2);               // 11

	std::shared_ptr<int> sp3(new int(22));
	std::shared_ptr<int> sp4 = sp3;
	printf("%d\n", *sp3);               // 22
	printf("%d\n", *sp4);               // 22
	sp3.reset();
	printf("%d\n", sp3.use_count());    // 0
	printf("%d\n", sp4.use_count());    // 1
	printf("%d\n", sp3);                // 0
	printf("%d\n", sp4);                // 指向所拥有对象的地址

	std::shared_ptr<int> sp5(new int(22));
	std::shared_ptr<int> sp6 = sp5;
	std::shared_ptr<int> sp7 = sp5;
	printf("%d\n", *sp5);               // 22
	printf("%d\n", *sp6);               // 22
	printf("%d\n", *sp7);               // 22
	printf("%d\n", sp5.use_count());    // 3
	printf("%d\n", sp6.use_count());    // 3
	printf("%d\n", sp7.use_count());    // 3
	sp5.reset(new int(33));
	printf("%d\n", sp5.use_count());    // 1
	printf("%d\n", sp6.use_count());    // 2
	printf("%d\n", sp7.use_count());    // 2
	printf("%d\n", *sp5);               // 33
	printf("%d\n", *sp6);               // 22
	printf("%d\n", *sp7);               // 22

	getchar();
	return 0;
}


#endif

#if 0
#include<iostream>
#include <memory>
#include <string> 

class report {
public:
	report(std::string message, std::string reporter) : 
		m_reporter(reporter), m_message(message)
	{

	}
	~report()
	{

	}
	void comment()
	{
		std::cout << m_reporter + " report " + m_message + '\n';
	}

private:
	std::string m_message;
	std::string m_reporter;

};

int main(void)
{
	{
		report *s = new report((std::string)"a breaking news", (std::string)"Jack");
		std::unique_ptr<report> u(s);
		u->comment();
	}
	
	{
		report *s = new report((std::string)"a breaking news", (std::string)"Jack");
		std::auto_ptr<report> a(s);
		a->comment();
	}
	
	{
		report *s = new report((std::string)"a breaking news", (std::string)"Jack");
		std::shared_ptr<report> p(s);
		p->comment();
	}


	getchar();
	return 0;
}



#endif

#if 0

#include <iostream>
#include <memory>

template<typename T>
class SmartPointer {
private:
	T * _ptr;
	size_t* _count;
public:
	SmartPointer(T* ptr = nullptr) :
		_ptr(ptr) {
		if (_ptr) {
			_count = new size_t(1);
		}
		else {
			_count = new size_t(0);
		}
	}

	SmartPointer(const SmartPointer& ptr) {
		if (this != &ptr) {
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}

	SmartPointer& operator=(const SmartPointer& ptr) {
		if (this->_ptr == ptr._ptr) {
			return *this;
		}

		if (this->_ptr) {
			(*this->_count)--;
			if (this->_count == 0) {
				delete this->_ptr;
				delete this->_count;
			}
		}

		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++;
		return *this;
	}

	T& operator*() {
		assert(this->_ptr == nullptr);
		return *(this->_ptr);

	}

	T* operator->() {
		assert(this->_ptr == nullptr);
		return this->_ptr;
	}

	~SmartPointer() {
		(*this->_count)--;
		if (*this->_count == 0) {
			delete this->_ptr;
			delete this->_count;
		}
	}

	size_t use_count() {
		return *this->_count;
	}
};

int main() {
	{
		SmartPointer<int> sp(new int(10));
		SmartPointer<int> sp2(sp);
		SmartPointer<int> sp3(new int(20));
		sp2 = sp3;
		std::cout << sp.use_count() << std::endl;
		std::cout << sp3.use_count() << std::endl;

		getchar();
	}
	//delete operator
}

#endif

#if 0
#include <iostream>
//类型模板参数
template <typename T>
T& Swap(T &value1, T &value2)
{
	T tmp = value1;
	value1 = value2;
	value2 = tmp;
	return value2;
}

//非类型模板参数
template<int N, int M>
void Fun(int p[N], int q[M])
{
	if (sizeof(p)* N < sizeof(q) * M)
	{
		std::cout << "More" << "\n";
	}
	else {
		std::cout << "Less" << "\n";
	}
}

int main(void)
{
	int a = 3, b = 7;
	Swap<int>(a, b) = 55;
	std::cout << a <<":"<< b << '\n';
	int arr1[5];
	int arr2[6];
	Fun<4,5>(arr1, arr2);
	getchar();
	return 0;
}


#endif

#if 1
#include <iostream>

template<typename T> 
class Base {

public:
	Base(T data) :m_data(new T(data))
	{

	}
	~Base()
	{
		if (m_data != NULL)
		{
			delete m_data;
		}
	}

	T* getData(T* index)
	{
	/*	if (index != NULL)
		{
			index = m_data;
		}*/
		return m_data;
	}

private:
	T* m_data;
};

int main(void)
{
	int a = 5;
	Base<int> obj(a);
	int y;
	int *x = obj.getData(&y);
	std::cout << *x << std::endl;


	getchar();
	return 0;
}


#endif