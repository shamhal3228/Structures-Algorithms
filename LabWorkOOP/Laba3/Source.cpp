#include <iostream>
#include <vector>
#include <string>

using namespace std;

class cl_base;

typedef void (cl_base::* signal)(string&);
typedef void (cl_base::* hendler)(string);

struct o_sh
{
	cl_base* p_cl_base;
	signal p_signal;
	hendler p_hendler;
};

#define SIGNAL_D(cl, func) (signal(&cl::func))
#define HENDLER_D(cl, func) (hendler(&cl::func))

class cl_base
{
protected: string name;
		 cl_base* parent;
		 vector <cl_base*> child;
		 int con, clnum, depth = 0;
		 vector <o_sh*> connects;
public: cl_base(cl_base* parent, string name, int con);
	  ~cl_base();
	  void setName(string name);
	  string getName();
	  void newPrint();
	  void newPrintParent();
	  void print();
	  void printParent();
	  cl_base* findParent(string pname);
	  cl_base* coorFindParent(string pname);
	  int printPath();
	  void set_connect(signal s, cl_base* c, hendler h);
	  void delete_connect(signal s, cl_base* c, hendler h);
	  void emit_connect(signal s, string s_command);
	  void setClnum(int numb);
	  int getClnum();
};

void cl_base::setClnum(int numb)
{
	clnum = numb;
}

int cl_base::getClnum()
{
	return clnum;
}

void cl_base::setName(string name)
{
	this->name = name;
}

cl_base::cl_base(cl_base* parent, string name, int con)
{
	setName(name);
	this->parent = parent;
	this->con = con;
	if (parent != 0)
	{
		parent->child.push_back(this);
		depth = parent->depth + 1;
	}
}

string cl_base::getName()
{
	return name;
}

cl_base* cl_base::findParent(string pname)
{
	if (pname == this->getName())
		return this;
	for (int i = 0; i < child.size(); i++)
		if (pname == child[i]->getName())
			return child[i];
	cl_base* finder;
	for (int i = 0; i < child.size(); i++)
	{
		finder = child[i]->findParent(pname);
		if (finder != 0)
			return finder;
	}
	return 0;
}

cl_base* cl_base::coorFindParent(string pname)
{
	if (pname[0] == '/' && pname[1] == '/')
	{
		pname = pname.substr(2);
		if (this->getName() == pname)
			return this;
		if (child.size() != 0)
		{
			for (int i = 0; i < child.size(); i++)
				if (child[i]->coorFindParent("//" + pname) != 0)
					return child[i]->coorFindParent("//" + pname);
		}
		else
			return 0;
	}
	else
	{
		pname = pname.substr(1);
		int end = pname.find('/');
		if (end == -1)
			end = pname.size();
		string maybe = pname.substr(0, end);
		if (this->getName() != maybe)
			return 0;
		if (end == pname.size())
			return this;
		if (child.size() != 0)
		{
			pname = pname.substr(end);
			for (int i = 0; i < child.size(); i++)
				if (child[i]->coorFindParent(pname) != 0)
					return child[i]->coorFindParent(pname);
		}
		else
			return 0;
	}
	return 0;
}

int cl_base::printPath()
{
	this->newPrintParent();
	string adress;
	cl_base* aaa;
	while (true)
	{
		cin >> adress;
		if (adress == "//")
			break;
		cout << '\n' << adress << " ";
		if (this->coorFindParent(adress) != 0)
		{
			aaa = this->coorFindParent(adress);
			cout << "Object name: " << aaa->getName();
		}
		else cout << "Object not found";
	}
	return 0;
}

void cl_base::printParent()
{
	cout << "Tree result";
	findParent(this->name)->print();
}

void cl_base::print()
{
	cout << '\n' << "The object" << this->getName();
	if (this->con > 0)
		cout << " is ready";
	else
		cout << " is not ready";
	for (int i = 0; i < child.size(); i++)
		child[i]->print();
}

void cl_base::newPrintParent()
{
	cout << "Object tree";
	findParent(this->name)->newPrint();
}

void cl_base::newPrint()
{
	cout << '\n';
	for (int j = 0; j < this->depth; j++)
		cout << "    ";
	cout << this->getName();
	for (int i = 0; i < child.size(); i++)
		child[i]->newPrint();
}

cl_base::~cl_base()
{
	for (int i = 0; i < child.size(); i++)
		delete child[i];
	for (int i = 0; i < connects.size(); i++)
		delete connects[i];
}

void cl_base::set_connect(signal s, cl_base* c, hendler h)
{
	o_sh* p_value;
	for (int i = 0; i < connects.size(); i++)
	{
		p_value = connects[i];
		if (p_value->p_signal == s && p_value->p_cl_base == c && p_value->p_hendler == h)
			return;
	}
	p_value = new o_sh();
	p_value->p_signal = s;
	p_value->p_cl_base = c;
	p_value->p_hendler = h;
	connects.push_back(p_value);
}

void cl_base::delete_connect(signal s, cl_base* c, hendler h)
{
	o_sh* p_value;
	for (int i = 0; i < connects.size(); i++)
	{
		p_value = connects[i];
		if (p_value->p_signal == s && p_value->p_cl_base == c && p_value->p_hendler == h)
		{
			delete p_value;
			connects.erase(connects.begin() + i);
			return;
		}
	}
}

void cl_base::emit_connect(signal s, string s_command)
{
	(this->*s)(s_command);
	for (int i = 0; i < connects.size(); i++)
	{
		o_sh* p_value = connects[i];
		if (p_value->p_signal == s)
		{
			hendler h = p_value->p_hendler;
			((p_value->p_cl_base)->*h)(s_command);
		}
	}
}

class cl_2 : public cl_base
{
public: cl_2(cl_base* parent, string name, int con) :cl_base(parent, name, con) {};
	  void ssignal_2(string& text);
	  void hhendler_2(string text);
};

void cl_2::ssignal_2(string& text)
{
	text = " Text: " + this->getName() + " -> " + text;
}

void cl_2::hhendler_2(string text)
{
	cout << "\nSignal to " << this->getName() << text;
}

class cl_3 : public cl_base
{
public: cl_3(cl_base* parent, string name, int con) :cl_base(parent, name, con) {};
	  void ssignal_3(string& text);
	  void hhendler_3(string text);
};


void cl_3::ssignal_3(string& text)
{
	text = " Text: " + this->getName() + " -> " + text;
}

void cl_3::hhendler_3(string text)
{
	cout << "\nSignal to " << this->getName() << text;
}

class cl_1 : public cl_base
{
protected: struct Node//
{
	int number;
	string sigName;
	string tarName;
};//
		 vector<Node*> story;
public: void ex_prog();
	  void build_prog();
	  int print_prog();
	  cl_1(cl_base* parent, string name, int con) :cl_base(parent, name, con) {};
	  cl_1(cl_base* parent) :cl_base(parent, "", 1)
	  {
		  cin >> name;
		  setClnum(1);
	  }
	  ~cl_1();
	  void ssignal_1(string& text);
	  void hhendler_1(string text);
};

void cl_1::ssignal_1(string& text)
{
	text = " Text: " + this->getName() + " -> " + text;
}

void cl_1::hhendler_1(string text)
{
	cout << "\nSignal to " << this->getName() << text;
}

void cl_1::ex_prog()
{
	cl_base* obj=0;
	int con, cl;
	string p_name, c_name;
	while (true)
	{
		cin >> p_name;
		if (p_name == "endtree")
			break;
		cin >> c_name >> cl >> con;
		if (cl == 2)
		{
			obj = new cl_2(findParent(p_name), c_name, con);
			obj->setClnum(2);
		}
		if (cl == 3)
		{
			new cl_3(findParent(p_name), c_name, con);
			obj->setClnum(3);
		}
	}
}

void cl_1::build_prog()
{
	this->ex_prog();
	int number;
	string sigName, tarName;
	cl_base* objSig = 0;
	cl_base* objTar = 0;
	cin >> number;
	while (number != 0)
	{
		cin >> sigName >> tarName;
		objSig = this->findParent(sigName);
		objTar = this->findParent(tarName);
		if (objSig->getClnum() == 1)
			objSig->set_connect(SIGNAL_D(cl_1, ssignal_1), objTar, HENDLER_D(cl_1, hhendler_1));
		if (objSig->getClnum() == 2)
			objSig->set_connect(SIGNAL_D(cl_2, ssignal_2), objTar, HENDLER_D(cl_2, hhendler_2));
		if (objSig->getClnum() == 3)
			objSig->set_connect(SIGNAL_D(cl_3, ssignal_3), objTar, HENDLER_D(cl_3, hhendler_3));
		Node* node = new Node;
		node->number = number;
		node->sigName = sigName;
		node->tarName = tarName;
		story.push_back(node);
		cin >> number;
	}
}

int cl_1::print_prog()
{
	this->newPrintParent();
	string oname, sms;
	cl_base* objSig = 0;
	cout << "\nSet connects";
	for (int i = 0; i < story.size(); i++)
		cout << "\n" << story[i]->number << " " << story[i]->sigName << " " << story[i]->tarName;
	cout << "\nEmit signals";
	cin >> oname;
	while (oname != "endsignals")
	{
		cin >> sms;
		objSig = this->findParent(oname);
		if (objSig->getClnum() == 1)
			objSig->emit_connect(SIGNAL_D(cl_1, ssignal_1), sms);
		if (objSig->getClnum() == 2)
			objSig->emit_connect(SIGNAL_D(cl_2, ssignal_2), sms);
		if (objSig->getClnum() == 3)
			objSig->emit_connect(SIGNAL_D(cl_3, ssignal_3), sms);
		cin >> oname;
	}
	return 0;
}

cl_1::~cl_1()
{
	for (int i = 0; i < story.size(); i++)
		delete story[i];
}

int main()
{
	cl_1 pepega(0);
	pepega.build_prog();
	return pepega.print_prog();
}


/*

obj
obj obj1 3 1
obj obj2 3 1
obj obj3 2 1
obj obj4 2 1
endtree
3 obj2 obj1
2 obj1 obj2
4 obj2 obj4
1 obj1 obj3
0
obj2 signal2
obj1 signal1
endsignals

*/
