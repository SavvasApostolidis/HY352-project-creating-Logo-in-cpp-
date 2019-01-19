#include "hy352_gui.h"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
#include <cwchar>
#include <limits>

using namespace std;

class logo_bool;
class logo_object;

class logo_number;
class logo_word;
class expression;
class logo_list;
class logo_sentence;
class logo_array;


class logo_object{
protected:
	string type;
public:
	logo_object(string t = "regular_object") : type(t) {}
	virtual void print()const=0;
	virtual logo_object * copy() = 0;
	virtual ~logo_object() {};
	virtual logo_object& get(int i = 0) = 0;//default timh tou i otan den orizetai apto xrhsth
	virtual void set(int i, logo_object* item) = 0;//to i exei nohma gia array mono
	virtual bool isarray() = 0;
	virtual logo_bool operator==(logo_object& obj) const = 0; //everyone must difine their equality check
	virtual string gettype() = 0;
	virtual int getintval() {return 0;	}
};



class logo_bool :public logo_object {
	bool value;
public:
	logo_bool(bool b = NULL) :value(b),logo_object("bool") {}
	explicit operator bool() { return value; }
	void operator= (void* i) { value = (int)i; }

	logo_bool& operator=(bool b) {
		value = b;
		return *this;
	}
	virtual void print() const override { std::cout << value; }
	logo_object * copy()override {
		return new logo_bool(*this);
	}

	virtual void set(int i, logo_object* item) {
		value = dynamic_cast<logo_bool *> (item);//antika8istw to value me to value tou item mesw tou operator ()
	}
	logo_bool& get(int i = 0) override {
		return *this;
	}
	virtual bool isarray() { return false; }

	virtual logo_bool operator==(logo_object& obj) const override {
		return logo_bool(this->value == dynamic_cast<logo_bool&>(obj).value);
	}
	virtual string gettype() {
		return this->type;
	}
	~logo_bool() {};
};



class logo_number :public logo_object {
	double value;
public:
	
	logo_number(double d=0):value(d), logo_object("bool") {};
	//logo_number(int a) :value(a), logo_object("bool") {}; //gia tis for
	logo_number(const logo_number& obj):value(obj.value) {};
	operator double() {
		return value;
	}

	logo_number& operator=(double d) {
		value = d;
		return *this;
	}
	logo_number& operator=(int i) {
		value = i;
		return *this;
	}
	virtual void print() const override { std::cout << value; }
	logo_object * copy()override {
		return new logo_number(*this);
	}
	virtual void set(int i, logo_object* item) {
			value = *dynamic_cast<logo_number *> (item);
	}
	logo_number& get(int i = 0) override {
		return *this;
	}
	virtual bool isarray() { return false; }

	double getval() { return value; }
	int getintval()override { return (int)value; }

	virtual logo_bool operator==(logo_object& obj) const override {
		return logo_bool(this->value == dynamic_cast<logo_number&>(obj).value);
	}
	virtual string gettype() {
		return this->type;
	}
	double increment() { double tmp = value; value++; return tmp; }
	double decrement() { double tmp = value; value--; return tmp; }
	~logo_number(){};
};

class logo_word :public logo_object {
	string value;
public:
	logo_word(string str = "") : value(str), logo_object("string") {}
	operator string() {
		return value;
	}
	logo_word(const logo_word & w) {
		value.assign(w.value);
	}
	logo_word& operator=(string s) {
		value.assign(s);
		return *this;
	}
	virtual void print() const override { std::cout << value; }
	logo_object * copy()override {
		return new logo_word(*this);
	}
	virtual void set(int i, logo_object* item) {
		value = *dynamic_cast<logo_word *> (item);//antika8istw to value me to value tou item mesw tou operator ()
	}
	logo_word& get(int i = 0) override {
		return *this;
	}
	virtual bool isarray() { return false; }

	virtual logo_bool operator==(logo_object& obj) const override {
		return value.compare(dynamic_cast<logo_word&>(obj).value) == 0;
	}
	virtual string gettype() {
		return this->type;
	}
	
	string getstring() { return value; }
	~logo_word() {};
};




class expression : public vector<logo_object*> {
public:
	expression() {};
	expression& operator=(expression &other) {
		for (auto x : other)push_back(dynamic_cast<logo_object*>(x->copy()));
		return *this;
	}

	expression& operator,(logo_object &b) {
		push_back(dynamic_cast<logo_object*>(&b));
		return *this;
	};
	expression& operator,(logo_object *b) {
		push_back(dynamic_cast<logo_object*>(b));
		return *this;
	};

};


expression& operator,(logo_object &a, logo_object &b) {
	expression* tmp = new expression();
	tmp->push_back(dynamic_cast<logo_object*>(&a));
	tmp->push_back(dynamic_cast<logo_object*>(&b));
	return *tmp;
};







class logo_list :public logo_object,public vector<logo_object*> {
public:
	logo_list():logo_object("list") {};
	logo_list(const logo_list& l):logo_object("list"){
		for (auto x : l)this->push_back((*x).copy());
	};
	virtual void print() const override { 
		for (auto x : *this) {
			x->print();
		}
	}

	logo_list& operator[](logo_object& obj) {
		push_back(&obj);
		return *this;
	}
	logo_list& operator[](expression &expr) {
		assign(expr.begin(), expr.end());
		return *this;
	}

	virtual void set(int i, logo_object* item) override {
		if (i > this->size()) {
			cout << "error such an item doesnt exist " << endl;
			exit(-1);
		}
		at(i) = item;
	}
	logo_object& get(int i = 0) {
		if (i > this->size()) {
			cout << "error such an item doesnt exist "<<endl;
			exit(-1);
		}
		return *at(i);
	}

	logo_object& get(logo_object& obj) {
		int i = dynamic_cast<logo_number&>(obj);
		return *at(i);
	}

	logo_object * copy()override {
		return new logo_list(*this);
	}
	virtual bool isarray() { return false; }

	virtual logo_bool operator==(logo_object& obj) const override {
		bool f = true;
		int i = 0;
		if (this->size() != (dynamic_cast<logo_list&>(obj).size())) {
			return logo_bool(false);
		}
		for (auto x : *this) {
			if (x->gettype().compare(dynamic_cast<logo_list&>(obj).at(i)->gettype()) !=0 ) {
				return logo_bool(false);
			}
			if (x->operator==(*dynamic_cast<logo_list&>(obj).at(i))) {
				i++;
			}
			else {
				return logo_bool(false);
			}
		}
		return logo_bool(f);
	}
	virtual string gettype() {
		return this->type;
	}
	~logo_list() {};
};

//logo_list& operator,(logo_object &left, logo_object &right) {
//	logo_list *tmp = new logo_list();
//	tmp->push_back(&left);
//	tmp->push_back(&right);
//	return *tmp;
//}

class logo_sentence:public logo_object,public vector<logo_word*>{
public:
	logo_sentence():logo_object("sentence") {};
	template<typename ...T>
	logo_sentence(logo_word w, const T&... rest):logo_object("sentence") {
		push_back(dynamic_cast<logo_word*> (w.copy()));
		push(rest...);
	}
	template<typename ...T>
	void push(logo_word w, const T&... rest) {
		push_back(dynamic_cast<logo_word*> (w.copy()));
		push(rest...);
	}
	void push() {};
	virtual void print() const override { for (auto x : *this) x->print(); }
	logo_object * copy()override {
		return new logo_sentence(*this);
	}

	logo_object& get(int i = 0) {
		if (i > this->size()) {
			cout << "error such an item doesnt exist " << endl;
			exit(-1);
		}
		return *at(i);
	}
	virtual void set(int i, logo_object* item) override {
		if (i > this->size()) {
			cout << "error such an item doesnt exist " << endl;
			exit(-1);
		}
		at(i) = dynamic_cast<logo_word*> (item);
	}
	virtual bool isarray() { return false; }

	virtual logo_bool operator==(logo_object& obj) const override {
		bool f = true;
		int i = 0;
		if (this->size() != (dynamic_cast<logo_sentence&>(obj).size())) {
			return logo_bool(false);
		}
		for (auto x : *this) {
			if (x->gettype().compare(dynamic_cast<logo_sentence&>(obj).at(i)->gettype()) != 0) {
				return logo_bool(false);
			}
			if (x->operator==(*dynamic_cast<logo_sentence&>(obj).at(i))) {
				i++;
			}
			else {
				return logo_bool(false);
			}
		}
		return logo_bool(f);
	}
	virtual string gettype() {
		return this->type;
	}
	~logo_sentence(){};
};

class logo_array :public logo_object,public vector<logo_object*>{
public:
	logo_array():logo_object("TEST_ARRAY"){};
	logo_array(logo_word &word) :logo_object("array") {
		push_back(dynamic_cast<logo_object*>(word.copy()));
	};
	logo_array(logo_number &number) :logo_object("array") {
		push_back(dynamic_cast<logo_object*>(number.copy()));
	};
	logo_array(logo_bool &boolean) :logo_object("array") {
		push_back(dynamic_cast<logo_object*>(boolean.copy()));
	};
	logo_array(const logo_array &ar) :logo_object("array") {
		for (auto x : ar)push_back(dynamic_cast<logo_object*>(x->copy()));
	}
	logo_array(logo_sentence &s) :logo_object("array") {
		push_back(dynamic_cast<logo_object*>(s.copy()));
	}
	logo_array(logo_list &l) :logo_object("array") {
		push_back(dynamic_cast<logo_object*>(l.copy()));
	}
	logo_array(initializer_list<logo_array>l) :logo_object("array") {
		for (auto x : l) {push_back(dynamic_cast<logo_object*>(x.copy())); }
	}

	logo_array& operator=(const logo_array&ar) {
		for (auto x : ar) { push_back(dynamic_cast<logo_object*>(x->copy())); }
		this->type = "test_array";
		return *this;
	}
	virtual void print() const override {
		for (auto x : *this)x->print();
		
	}

	virtual void set(int i, logo_object* item) override {
		if( i > this->size()) {
			cout << "error such an item doesnt exist " << endl;
			exit(-1);
		}
		at(i) = item->copy();
	}
	logo_object& get(int i = 0) {
		if (at(i)->isarray() == false){
			return *at(i);
		}
		if (i > this->size()) {
			cout << "error such an item doesnt exist " << endl;
			exit(-1);
		}
		if (myget(i).at(0)->gettype()!="array") {//an ena array exei mesa {number,word},ta number kai word 8eorountai array
			return internalget(i);//to value sth 8esh at(0) tous einai to alh8ino number kai word ,etsi elegxw oti ontws den einai array
		}//an eixa array{x,number} opou to x einai array tote to x[0] mesa tou exei array tupou antikeimena(ektws tou adeiou array)
		else if (at(i)->isarray() == true) {
			return *at(i);
		}
	}
	logo_array& myget(int i) {
		return *dynamic_cast<logo_array*>(at(i));
	}
	logo_object& internalget(int i) {
		return *(dynamic_cast<logo_array*>(at(i)))->at(0);
	}
	logo_object * copy()override {
		return new logo_array(*this);
	}
	virtual bool isarray() { return true; }


	virtual logo_bool operator==(logo_object& obj) const override {
		bool f = true;
		int i = 0;
		if (this->size() != (dynamic_cast<logo_array&>(obj).size())) {
			return logo_bool(false);
		}
		for (auto x : *this) {
			if (x->gettype().compare(dynamic_cast<logo_array&>(obj).at(i)->gettype()) != 0) {
				return logo_bool(false);
			}
			if (x->operator==(*dynamic_cast<logo_array&>(obj).at(i))) {
				i++;
			}
			else {
				return logo_bool(false);
			}
		}
		return logo_bool(f);
	}

	virtual string gettype() {
		return this->type;
	}
	~logo_array(){};
};



logo_object& getlogoitem(initializer_list<logo_number> list, const logo_object& array) {
	logo_object* item = const_cast<logo_object*>(&array);
	for (auto i : list) item = &item->get(i - 1);
	return *item;
}

void setlogoitem(initializer_list<logo_number> list, logo_object& array,const logo_object &new_value) {
	logo_object& item = const_cast<logo_object&>(array);
	logo_object& new_item = const_cast<logo_object &>(new_value);
	logo_object* new_ptr = &new_item;
	unsigned int i;
	auto iter = list.begin();//sumbolizei ka8e ari8mo sto initializer list sthn ousia
	for (i = 0; i < list.size() - 1; i++, iter++)
		item = item.get((*const_cast<logo_number*>(iter)) - 1);

	item.set(*const_cast<logo_number*>(iter) - 1,new_ptr);
}





//upo8etoume oti stis ma8hmatikes sunarthseis ta orismata einai ews 3 apta paradeigmata
logo_number& mysum(logo_object& a, logo_object& b, logo_object& c = *new logo_number(0)) { // an den dwsei 3 argument alla mono 2,pairnoun logo object argument logo ths item sunarthshs
	return *new logo_number(dynamic_cast<logo_number&>(a) + dynamic_cast<logo_number&>(b) + dynamic_cast<logo_number&>(c));
}

logo_number& mydif(logo_object& a, logo_object& b, logo_object& c = *new logo_number(0)) { // an den dwsei 3 argument alla mono 2
	return *new logo_number(dynamic_cast<logo_number&>(a) - dynamic_cast<logo_number&>(b) - dynamic_cast<logo_number&>(c));
}
logo_number& myminus(logo_object& a) {
	double temp = dynamic_cast<logo_number*>(&a)->getval();
	temp = temp * -1;
	return *new logo_number(temp);
}
logo_number& myproduct(logo_object& a, logo_object& b, logo_object& c = *new logo_number(1)) { // an den dwsei 3 argument alla mono 2, kanw *1 gia na mh xa8ei to apotelesma
	return *new logo_number(dynamic_cast<logo_number&>(a) * dynamic_cast<logo_number&>(b) * dynamic_cast<logo_number&>(c));
}
logo_number& myquot(logo_object& a, logo_object& b) {
	if (dynamic_cast<logo_number&>(b).getval() == 0) {
		cout << "diviision by 0" << endl;
		exit(-1);
	}
	return *new logo_number(dynamic_cast<logo_number&>(a) / dynamic_cast<logo_number&>(b));
}
logo_number& mymod(logo_object& a, logo_object& b) {
	int a1 = dynamic_cast<logo_number&>(a).getintval();
	int a2 = dynamic_cast<logo_number&>(b).getintval();
	return *new logo_number(a1 % a2);
}


template<typename T>
T myand(T first) {
	return first;
}

template<typename T, typename... Args>
T myand(T first, Args... args) {
	return first && myand(args...);
}


template<typename T>
T myor(T first) {
	return first;
}

template<typename T, typename... Args>
T myor(T first, Args... args) {
	return first || myand(args...);
}


class myshow {
public:
	class myshow() {}
	void operator=(logo_object& obj) { //stis sunarthseis pou ulopoioume opws show ,setxy klp ekmetaleuomai ton operator = gia na tis kalw
		obj.print();//xwris paren8eseis
	}
};


class myforward {
public:
	myforward() {}
	void operator=(logo_object& obj) {
		turtle_mv_forward((float)dynamic_cast<logo_number&>(obj));//metatroph tou double se float pou pairnei orisma to function
	}
};

class mybackward {
public:
	mybackward() {}
	void operator=(logo_object& obj) {
		turtle_mv_backward((float)dynamic_cast<logo_number&>(obj));//metatroph tou double se float pou pairnei orisma to function
	}
};

class myright {
public:
	myright() {}
	void operator=(logo_object& obj){
		turtle_rotate(dynamic_cast<logo_number&>(obj).getintval());
	}
};
class myleft {
public:
	myleft() {}
	void operator=(logo_object& obj) {
		turtle_rotate(360 - dynamic_cast<logo_number&>(obj).getintval());
	}
};

class mysetxy {
	double d;
public:
	mysetxy() {}
	mysetxy& operator=(logo_object &number1) {
		d = dynamic_cast<logo_number&>(number1);
		return *this;
	}
	void operator,(logo_object &number2) {
		turtle_go_to_position(d, dynamic_cast<logo_number&>(number2));
	}
};


class mycircle {
public:
	mycircle() {}
	void operator=(logo_object& obj) {
		turtle_draw_circle((unsigned)dynamic_cast<logo_number&>(obj));
	}
};


class myprint {
public:
	myprint() {}
	void operator=(logo_word &w) {
		turtle_draw_label(w.getstring().c_str());
	}
};



class mysetpen {
public:
	mysetpen() {}
	void operator=(logo_object& list) {
		unsigned int arg1 = dynamic_cast<logo_number&>(list.get(0));
		unsigned int arg2 = dynamic_cast<logo_number&>(list.get(1));
		unsigned int arg3 = dynamic_cast<logo_number&>(list.get(2));
		set_pen_color(arg1,arg2,arg3);
	}
};
class mysetscreen {
public:
	mysetscreen() {}
	void operator=(logo_list list) {
		unsigned int arg1 = dynamic_cast<logo_number&>(list.get(0));
		unsigned int arg2 = dynamic_cast<logo_number&>(list.get(1));
		unsigned int arg3 = dynamic_cast<logo_number&>(list.get(2));
		set_screen_color(arg1,arg2,arg3);
	}
};
class mysetsize {
public:
	class mysetsize() {}
	void operator=(logo_object& obj) {
		set_pen_thickness((float)dynamic_cast<logo_number&>(obj));
	}
};


#define START_PROGRAM int main(){ init_GUI();
#define END_PROGRAM ;destroy_GUI(); return 0;}


#define TRUE true
#define FALSE false
#define MAKE ;auto&
#define NUMBER (*new logo_number()) = 0? 0
#define WORD (*new logo_word()) = 0? ""
#define BOOLEAN (*new logo_bool()) = 0? true
#define LIST (*new logo_list())
#define ARRAY  *new logo_array = *new logo_array
#define SENTENCE *new logo_sentence
//#define SENTENCE(const logo_word& args...) LIST[__VA_ARGS__] lista apo lekseis
#define ASSIGN ; //de xreiazetai na kanei tpt,apla boh8aei to xrhsth ths glwssas na katalabei oti kanei assignment kai bazei semicolon ston apo panw


#define ITEM getlogoitem
#define SETITEM(...) ;setlogoitem(__VA_ARGS__);

#define SUM mysum
#define DIFFERENCE mydif
#define	MINUS myminus
#define PRODUCT myproduct 
#define QUOTIENT myquot
#define MODULO mymod

#define AND myand
#define OR myor
#define NOT !AND
#define ELIF  ;}}else if(
#define ELSE ;}}else{ {
#define IF	;if(
#define DO ){ {
#define END  ;} }


#define FOREACH ;for(auto ELEM :
#define ELEM *ELEM
#define SHOW	;myshow() = 0? (logo_object&)logo_bool()//orizontas ws to basic type se logo_object& to orisma meta ta : 8ewreite kai auto logo_object&

#define FORWARD	;myforward() =
#define BACK	;mybackward() =
#define LEFT	;myleft() =
#define RIGHT	;myright() = 
#define CENTER  ;turtle_go_to_center();
#define SETXY	;mysetxy() =
#define CIRCLE	;mycircle() = 
#define PRINT	;myprint() =
#define PENDOWN ;pen_down();
#define PENUP	;pen_up();

#define SETPENCOLOR    ;mysetpen() =   
#define SETSCREENCOLOR ;mysetscreen() =   
#define SETPENSIZE 	   ;mysetsize() =


#define TO void
#define WITH (logo_list& mylist){logo_list&
#define ARG(...)mylist.get((__VA_ARGS__) - 1) // me tis paren8eseis kanw triggr to telesth operator double() gia na parw to value tou
#define CALL  ;
#define FSTART = mylist;
#define RETURN ;return ;
#define FEND ;return;}


#define REPEAT ;for(logo_number& REPCOUNT = (NUMBER:1); 
#define TIMES  >= REPCOUNT; REPCOUNT.increment()
#define WHILE (REPCOUNT.decrement())<=1;) while (REPCOUNT.getval() == REPCOUNT.increment()  &&   
#define REPCOUNT REPCOUNT