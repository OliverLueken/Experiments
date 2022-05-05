#include <iostream>
#include <iomanip>

class Base{
    int a{5};
public:
    Base() = default;
    Base(int x) : a{x}{}

    int get(){return a;}

    friend bool operator==(Base, Base);
};

bool operator==(Base a, Base b){
    return a.a == b.a;
}

class Derived : public Base{
public:
    void print(){
        std::cout << "Base class value: " << Base::get() << '\n';
    }

    void comp(int x){
        Base b{x};
        std::cout << "Value " << x << "==" << Base::get() << " is "
                  << std::boolalpha  << operator==(static_cast<Base>(*this), b) << '\n';
    }

    auto set(int x){
        std::cout << "Setting base class value to " << x << '\n';
        Base::operator=(x);
    }
};

int main() {
    Derived d{};
    d.print();
    d.comp(5);
    d.comp(1);

    d.set(1);
    d.print();
    d.comp(1);
}

/*
Output:

Base class value: 5
Value 5==5 is true
Value 1==5 is false
Setting base class value to 1
Base class value: 1
Value 1==1 is true
*/