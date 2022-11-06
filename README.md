# michellundell/8a C++

## Agenda

1. C++ Exception handling
2. C++ new, delete 
3. C++ Initialization Operator
4. C++ Assignment Operator
5. C++ Function Call Operator
6. C++ Subscript Operator
7. C++ Increment Operator
8. C++ Decrement Operator

## 1. C++ Exception handling

Very important too use. Make this a habit to do!

```
#include <iostream>
using namespace std;

/**
* @brief This program takes two numbers as arguments and prints 
* the result of dividing first number with the second number
*/

int main(int argc, char **argv)
{
        int x=0, y=0;
        double  answer=0;
	
	// Exceptions are handled.
        try {
                if( argc != 3 ) { // check that required arguments are supplied
                        throw "usage program [number] [divisor]"; // if not throw an exception
                        return(-1); // tell the invoker of program that some error occurred
                }
                x = atoi(argv[1]); // parse the first argument as a integer
                y = atoi(argv[2]); // parse the second argument as a integer
                if( y == 0 ) throw "division by zero!"; // if second argument is 0, throw an exception
                answer = (double) x/y; // calculate answer
                cout << x << "/" << y << "=" << answer << endl; // print answer
                return(0); // tell invoker of program that all went well
        } catch (...) { // catch all exceptions
                cerr << "error!" << endl; // tell invoker that an error occurred.
		return(-1);
        }
	// we should never get here ...
}
```

### Improved version ...

```
#include <iostream>
using namespace std;

/**
* @brief This program takes two numbers as arguments and prints 
* the result of dividing first number with the second number
*/
int main(int argc, char **argv)
{
        int x=0, y=0;
        double  answer=0;
	// Exceptions are handled.
        try {
                if( argc != 3 ) { // check that required arguments are supplied
                        throw "usage program [number] [divisor]"; // if not throw an exception
                        return(-1); // tell the invoker of program that some error occurred
                }
                x = atoi(argv[1]); // parse the first argument as a integer
                y = atoi(argv[2]); // parse the second argument as a integer
                if( y == 0 ) throw "division by zero!"; // if second argument is 0, throw an exception
                if( y == 1 ) throw 1; // if divisor is 1 throw exception
                answer = (double) x/y; // calculate answer
                cout << x << "/" << y << " = " << answer << endl; // print answer
                return(0); // tell invoker of program that all went well
        } catch (const char *what) { // catch all char * exceptions
                cerr << "error: " << what << endl;
		return(-1);
        } catch ( const int err ) { // catch all int exceptions
                switch( err ) {
                        case 1:
                                cerr << "error: division by " << err << " is strange!" << endl;
                        break;
                        default:
                                cerr << "error: " << err << endl;
                        break;
                }
		return(-1);
        } catch ( ... ) { // catch all other exceptions ...
                cerr << "error: unknown" << endl;
		return(-1);
        }
	// we should never get here ...
}
```


### Improved version with custom exception class ...

```
#include <iostream>
using namespace std;

class argumentException  {
        string ex;
        public:
                argumentException(const string ex) { this->ex = ex; }
                string message() { return( this->ex ) ; }
};

/**
* @brief This program takes two numbers as arguments and prints
* the result of dividing first number with the second number
*/
int main(int argc, char **argv)
{
        int x=0, y=0;
        double  answer=0;
        // Exceptions are handled.
        try {
                if( argc != 3 ) { // check that required arguments are supplied
                        throw new argumentException("usage program [number] [divisor]"); // if not throw an exception
                        return(-1); // tell the invoker of program that some error occurred
                }
                x = atoi(argv[1]); // parse the first argument as a integer
                y = atoi(argv[2]); // parse the second argument as a integer
                if( y == 0 ) throw new argumentException("division by zero!"); // if second argument is 0, throw an exception
                if( y == 1 ) throw new argumentException("division by one!"); // if second argument is 0, throw an exception
                answer = (double) x/y; // calculate answer
                cout << x << "/" << y << " = " << answer << endl;  // print answer
                return(0); // tell invoker of program that all went well
        } catch (argumentException *exc) { // catch all argumentException's
                cerr << "caught argumentException: " << exc->message() << endl;
                return(-1);
        } catch (const char *what) { // catch all char * exceptions
                cerr << "error: " << what << endl;
                return(-1);
        } catch ( const int err ) { // catch all int exceptions
                switch( err ) {
                        case 1:
                                cerr << "error: division by " << err << " is strange!" << endl;
                        break;
                        default:
                                cerr << "error: " << err << " ?" << endl;
                        break;
                }
                return(-1);
        } catch ( ... ) { // catch all other exceptions ...
                cerr << "error: unknown" << endl;
        }
        // we should never get here ...
}
```

## 2. C++ new, delete 

Example of new and delete for arrays 
```
#include <iostream>
using namespace std;

class myClass {
        char data[2];
        int age;
};

int main(int argc, char **argv)
{
        char *array = new char[100]; // allocate array of chars
        myClass *classarray = new myClass[100]; // allocate array of myClass objects
        myClass *one = new myClass; // allocate one myClass object
        delete[] array; // free array of chars
        delete[] classarray; // free array of myClass objects
        delete one; // free one myClass object
        return(0);
}
```

## 3. C++ Initialization Operator

```
#include <iostream>
#include <ostream>
using namespace std;

class myClass {
        char name[10];
public:
        myClass(const char *s) { // constructor
                cout << "myClass constructor (" << this << ")" << endl;
                strncpy(this->name,s,sizeof(this->name));
        }
        ~myClass() { // destructor
                cout << "myClass destructor (" << this << ")" << endl;
        }
        myClass(myClass &other) { // initialization operator
                cout << "myClass initialization operator" << endl;
                strcpy(this->name,other.name);
        }
        friend ostream& operator <<(ostream &out,const myClass &m) {
                out << m.name << endl;
                return(out);
        }
};


int main(int argc, char **argv)
{
        cout << "myClass a(\"a\");" << endl;
        myClass a("a");
        cout << a << endl;
        cout << "myClass b = a;" << endl;
        myClass b = a;
        cout << b << endl;
        return(0);
}

```


## 4. C++ Assignment Operator
```
#include <iostream>
#include <ostream>
using namespace std;

class myClass {
        char name[10];
public:
        myClass(const char *s) { // constructor
                cout << "myClass constructor (" << this << ")" << endl;
                strncpy(this->name,s,sizeof(this->name));
        }
        ~myClass() { // destructor
                cout << "myClass destructor (" << this << ")" << endl;
        }
        myClass(myClass &other) { // initialization operator
                cout << "myClass initialization operator" << endl;
                strcpy(this->name,other.name);
        }
        void operator=(const myClass &other) { // assignment operator
                cout << "myClass assignment operator" << endl;
                cout << this->name << " = " << other.name << endl;
                strcpy(this->name,other.name);
        }
        friend ostream& operator <<(ostream &out,const myClass &m) {
                out << m.name << endl;
                return(out);
        }
};


int main(int argc, char **argv)
{
        cout << "myClass a(\"a\");" << endl;
        myClass a("a");
        cout << a << endl;
        cout << "myClass b(\"b\");" << endl;
        myClass b("b");
        cout << b << endl;
        cout << "b = a; " << endl;
        b = a; // assignment
        cout << b << endl;
        cout << "myClass c = a; "<< endl;
        myClass c = a; // initialization
        cout << c << endl;
        return(0);
}

```

## 5. C++ Function Call Operator
```
#include <iostream>
using namespace std;

class myClass {
        int x,y;
public:
        myClass(int x,int y) { // constructor
                cout << "myClass(" << x << "," << y << ") constructor" << endl;
                this->x = x; this->y=y;
        }
        void operator()(int x,int y) { // function call operator
                cout << "myClass(" << x << "," << y << ") operator(" << x << "," << y <<")" << endl;
                this->x = x; this->y=y;
        }
};

int main(int argc, char **argv)
{
        myClass a(1,2); // call constructor
        a(3,2); // call function call operator
        return(0);
}
```

## 6. C++ Subscript Operator
```
#include <iostream>
using namespace std;

class myData {
        char *data;
public:
        myData() {
                data = new char[20];
                strcpy(data,"01234568901234567890");
        }
        const char operator[](int pos) {
                if(pos < 20 )
                        return(data[pos]);
                else return 'X';
        }
};

int main(int argc, char **argv)
{
        myData data;
        for(int i=0;i<25; i++) {
                cout << data[i] << " ";
        }
        cout << endl;
        return(0);
}
```
## 7. C++ Increment Operator
```

#include <iostream>
using namespace std;

class myData {
        int ix;
public:
        myData() { // constructor
                ix=0;
        }
        myData& operator++() {
                cout << "prefix" << endl;
                if(ix < 19 )
                ix++;
                return *this;
        }
        myData& operator++(int) {
                static myData temp = *this;
                cout << "postfix" << endl;
                if(ix < 19 )
                ix++;
                return temp;
        }
        friend ostream& operator<<(ostream &out,myData &o)
        {
                out << o.ix;
                return(out);
        }
};

int main(int argc, char **argv)
{
        cout << "myData x;" << endl;
        myData x;
        cout << "x = "<< x << endl;
        cout << "t = ++x" << endl;
        myData t = ++x;
        cout << "t = " << t << endl;
        cout << "x = "<< x << endl;

        cout << "t = x++;" << endl;
        t = x++;
        cout << "t = " << t << endl;
        cout << "x = "<< x << endl;
        return(0);
}
```

## 8. C++ Decrement Operator
```
#include <iostream>
using namespace std;

class myData {
        int ix;
public:
        myData() {
                cout << "constructor" << endl;
                this->ix=5;
                cout << "this->ix=" << this->ix << endl;
        }

        myData& operator--() {
                cout << "-- prefix" << endl;
                if(ix < 19 )
                ix--;
                return *this;
        }
        myData& operator--(int) {
                static myData temp = *this;
                cout << "-- postfix" << endl;
                if(ix < 19 )
                ix--;
                return temp;
        }
        friend ostream& operator<<(ostream &out,myData &o)
        {
                out << o.ix;
                return(out);
        }
};

int main(int argc, char **argv)
{
        myData x;
        cout <<"x = " << x << endl;
        myData t;
        cout << "t = --x" << endl;
        t = --x;
        cout <<"t = " << t << endl;
        cout <<"x = " << x << endl;

        cout << "t = x--; "<< endl;
        t = x--;
        cout <<"t = " << t << endl;
        cout << "x = " << x << endl;
        return(0);
}
```

## On request ... 7a examples with comments added
1.(6a) C++ class constructor
2.(6a) C++ class destructor
3.(6a) C++ inheritance
4.(6a) C++ overloading methods
5.(6a) C++ Reference
6.(6a) C++ friend
7.(6a) C++ overloading input output operators << and >>
8.(6a) C++ Function Templates
9.(6a) C++ Class Templates
10.(6a) C++ std::list
11.(6a) C++ List with custom class, std::list


## 1.(6a) C++ class constructor
A c++ class constructor is public and returns nothing!

```
#include <iostream>
using namespace std;

class BaseClass { // example class
        public:
                BaseClass() { cout << "BaseClass constructor called" << endl; }
};

int main(int argc, char **argv)
{
        BaseClass bc; // initiate an object
        return 0;
}
```

## 2.(6a) C++ class destructor

A class destructor is defined by having a ~ infront of it and return nothing.
```
#include <iostream>
using namespace std;

class BaseClass { // example class
	public:
		BaseClass() { cout << "BaseClass constructor called" << endl; }
		~BaseClass() { cout << "BaseClass destructor called" << endl; }
};

int main(int argc, char **argv)
{
        BaseClass bc; // initiate an object
        return 0;
}
```

## 3.(6a) C++ inheritance

Classes can inherit from other classes.

```
#include <iostream>
using namespace std;

class BaseClass { // example class
        char data[20]; // example attribute
        public:
                BaseClass() { cout << "BaseClass created" << endl; strcpy(data,"initiated"); }
                const char *getData() { return(this->data); } // return data attribute
                void doit() { cout << "BaseClass::doit()" << endl; } // debug method call
};

class SubClass: public BaseClass { // let SubClass inherit all public from BaseClass
        public:
                SubClass() { cout << "SubClass created, BaseClass::data=" << this->getData() << endl; }
};

int main(int argc,char **argv)
{
        SubClass sc; // initiate an SubClass object
        sc.doit();   // call inherited method defined in BaseClass
        return 0;
}
```

## 4.(6a) C++ overloading methods

```
#include <iostream>
using namespace std;

class BaseClass { // Example of a base class definition
        public:
                BaseClass() { cout << "BaseClass object created" << endl; }
                ~BaseClass() { cout << "BaseClass object deleted" << endl; }
                void doit() { cout << "BaseClass:doit() here " << endl; } // a sample method
                void dontDoit() { cout << "BaseClass:dontDoit() here " << endl; } // a sample method
};

class SubClass: public BaseClass {
        public:
                SubClass() { cout << "SubClass object created" << endl; }
                ~SubClass() { cout << "SubClass object deleted" << endl; }
                void doit() { cout << "SubClass:doit() here " << endl; } // overload BaseClass::doit() method
};

int main(int argc,char **argv)
{
        BaseClass *bcp = NULL;
        SubClass *scp = NULL;
        SubClass sc;             // sc is both a BaseClass and a SubClass!

        bcp = &sc;               // access only BaseClass ...
        bcp->doit();             // call BaseClass:doit()

        scp = &sc;               // access derived SubClass ...
        scp->doit();             // call overloaded method, SubClass::doit()
        scp->dontDoit();         // call inherited method, BaseClass::dontDoit()

        return 0;
}
```

## 5.(6a) C++ Reference

A reference is a alias for another variable.

```
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	double agent = 0.028;
	double &bond = agent; // create an alias for agent
	bond /= 4.0; // use alias to change agent
	cout << "agent " << agent << endl; // write out value of agent
	return 0;
}
```
Passing a large object reference to a function will not copy it onto the stack.
```
void someFunction( LargeClass &large )
{
	// large is not copied onto the stack
}
```

References can be updated without using pointer or adresses
```
#include <iostream>
using namespace std;

void swap(int &v1, int &v2) // swap the values of v1 and v2
{
	int t=v1; // save v1 in a temporary variable
	v1=v2; // let v1 have the value of v2
	v2=t; // set v2 to v1's previous value
}

int main(int argc, char **argv)
{
	int a = 10;
	int b = 2;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	swap(a,b); // make the swap ...
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
}
```

## 6.(6a) C++ friend

```
#include <iostream>
using namespace std;

class BaseClass { // an example class
	private:
		char data[20];
		int a;
        public:
                BaseClass() { cout << "BaseClass created" << endl; strcpy(this->data,"initiated"); this->a=42; }
                void info() { cout << "BaseClass:info(): " << this->data << endl; }
                friend class aFriendClass;
                friend void aFriendFunction(BaseClass&);
};


class aFriendClass: public BaseClass { // example of inherited class that is a friend and can access private attributes
        public:
                aFriendClass() { this->a++; cout << "aFriendClass data:" << this->data << ", a:" << this->a << endl; }
};

void aFriendFunction( BaseClass &b )
{
	cout << "aFriendFunction b.data=" << b.data << ", a:" << b.a << endl;
}

int main(int argc,char **argv)
{
        aFriendClass fc;
        fc.info();
	aFriendFunction(fc);
        return 0;
}
```

## 7.(6a) C++ overloading input output operators << and >>

```
#include <iostream>
#include <ostream>
using namespace std;

class BaseClass { // example class
        char data[20];
        public: 
                BaseClass() { cout << "BaseClass created" << endl; strcpy(data,"initiated"); }
                char *getData() { return this->data; }
                
		// create a overload output operator for this class
                friend ostream &operator<<( ostream &output, const BaseClass &B ) {
                        output << "BaseClass data : " << B.data;
                        return output;
                }
                
		// create a overload input operator for this class
                friend istream &operator>>( istream  &input, BaseClass &B ) {
                        input >> B.data;
                        return input;
                }
};

int main(int argc, char **argv)
{
        BaseClass object;
        cout << object << endl;
        cout << "Enter data:";
        cin >> object;
        cout << object << endl;
        return 0;
}
```

## 8.(6a) C++ Function Templates

```
#include <iostream>
using namespace std ;

//max returns the maximum of the two elements
template <class T> T max(T a, T b)
{
	return a > b ? a : b ;
}

// demonstrate the use of a Function template with different types

int main(int argc,char **argv)
{
	cout << "max(10, 15) = " << max(10, 15) << endl ;
	cout << "max('k', 's') = " << max('k', 's') << endl ;
	cout << "max(10.1, 15.2) = " << max(10.1, 15.2) << endl ;
	return 0;
}
```
When the compiler sees an instantiation of the function template, for example: the call max(10, 15) in function main, the compiler generates a function max(int, int). Similarly the compiler generates definitions for max(char, char) and max(float, float) in this case.


## 9.(6a) C++ Class Templates
Similar to template functions, one can also make a template class

```
#include <iostream>
using namespace std;

// an example class that is hardcoded to use a type
class notTemplateClass { // hard coded to use int
        int v1;
        public:
                notTemplateClass(int init) { v1 = init;}
                int doit() { return( v1 * 3.14 ); }
};

// an example of a template class that is not hardcoded to use a specific type
// limited to some kind of number types like int, double, float ....
template <class T> class aTemplateClass { // flexible
        T v1;
        public:
                aTemplateClass(T init) { v1=init; }
                T doit() { return( v1 * 3.14 ); }
};


int main(int argc, char **argv)
{
        notTemplateClass ntc(1);

        aTemplateClass<float> atc_float(1.0);
        aTemplateClass<int> atc_int(1);
        aTemplateClass<double> atc_double(1.2);

        cout << ntc.doit() << endl;
        cout << atc_float.doit() << endl;
        cout << atc_int.doit() << endl;
        cout << atc_double.doit() << endl;
        return 0;
}
```

## 10.(6a) C++ std::list

Having objects in a list is a good way to not forget them ;-)

c++ have a handy standard list class, std::list.

Here is an example of using a integer list:
```
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <list>
using namespace std;

// function for printing the elements in a list
void showlist(list<int> g)
{
    list<int>::iterator it; // list class have an iterator that is useful when looping through a list
    for (it = g.begin(); it != g.end(); ++it)
        cout << "  " << *it;
    cout << '\n';
}

int main(int argc, char **argv)
{
    list<int> my_list; // create a sample list

    for (int i = 0; i < 10; ++i) { // initiate the list with 10 random numbers between 0 and 100
        my_list.push_back( (rand()%100) ); // Add 10 random numbers between 0 and 100
    }

    // demonstrate the use of some methods int the list class
    cout << "my_list is          : ";
    showlist(my_list);

    cout << "my_list.front()     :   " << my_list.front() << endl;
    cout << "my_list.back()      :   " << my_list.back() << endl;

    cout << "my_list.pop_front() : ";
    my_list.pop_front();
    showlist(my_list);

    cout << "my_list.sort()      : ";
    my_list.sort();
    showlist(my_list);

    cout << "my_list.reverse()  : ";
    my_list.reverse();
    showlist(my_list);

    return 0;
}

```

## 11.(6a) C++ List with custom class, std::list

Having objects in a list is a good way to not forget them ;-)

C++ have a handy list class, std::list.

Here is an example of using a custom class list:
```
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <list>
using namespace std;

class myClass { // an example custom class
	int x;
	public:
		myClass(int x) { this->x = x; }
		int getValue() { return(x); }
};
  
// std::list.sort needs a "compare" function to work with custom objects
// is a less than b? 
bool compareMyClass(myClass *a, myClass *b) 
{ 
	return( a->getValue() < b->getValue() ); 
}

// function for printing the elements in a list
void showlist(list<myClass *> g)
{
    list<myClass *>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
	myClass *mcp = *it; // need to cast the iterator address to myClass
        cout << "  " << mcp->getValue();
    }
    cout << '\n';
}
  

int main(int argc, char **argv)
{
    list<myClass *> my_list; // create a sample list of pointers to myClass objects
  
    for (int i = 0; i < 10; ++i) { // initiate the list with 10 myClass objects with random data
        my_list.push_back( new myClass(rand()%100) ); // Add 10 random numbers between 0 and 100
    }


    // Demonstrate some of the methods in the list class
    cout << "my_list is          : ";
    showlist(my_list);
  
    myClass *mcp = my_list.front();
    cout << "my_list.front()     :   " << mcp->getValue() << endl; 
    mcp = my_list.back();
    cout << "my_list.back()      :   " << mcp->getValue() << endl;
  
    cout << "my_list.pop_front() : ";
    my_list.pop_front();
    showlist(my_list);

    cout << "my_list.sort()      : ";
    my_list.sort(compareMyClass);
    showlist(my_list);
  
    cout << "my_list.reverse()   : ";
    my_list.reverse();
    showlist(my_list);

    return 0;
}
```

## (7a) Todays assignments

1. Fork this repository (michellundell/7a) and update the 7a.cpp with some of your own code that demonstrates the following C++ features:

```
C++ class constructor
C++ class destructor
C++ inheritance
C++ overloading methods
C++ Reference
C++ friend
C++ overloading input output operators << and >>
C++ Function Templates
C++ Class Templates
C++ std::list
C++ List with custom class, std::list
C++ Exception handling
C++ new, delete 
C++ Initialization Operator
C++ Assignment Operator
C++ Function Call Operator
C++ Subscript Operator
C++ Increment Operator
C++ Decrement Operator
```

when the 7a.cpp compiles and demonstrates the above features of C++, make a pull-request for my 7a.cpp file!

then you can continue with the ticket system assignment ...

2. If you are not yet finished with the ticket program in C (4a) it is time to complete it ...

2. If/when you are finished with the ticket program in C, start making a C++ version of it!

3. If you started on the C++ version of the ticketsystem ...

Maybe some of the features we learnt today could be used in your C++ ticket system.
(Using the features in a "right place" will collect points!)

Happy coding

