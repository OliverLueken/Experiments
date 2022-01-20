#include <iostream>
#include <vector>

template<class T>
class A{
public:
    std::vector<T> vec{};

    A() : vec(5){ }


    //T&    //error: cannot bind non-const lvalue reference of type 'bool&'                to an rvalue of type 'bool', 19: return vec[0];
    //auto& //error: cannot bind non-const lvalue reference of type 'std::_Bit_reference&' to an rvalue of type 'std::vector<bool, std::allocator<bool> >::reference', 19: return vec[0];
    //auto  //error: lvalue required as left operand of assignment, 32: aInt()=2;
    //std::vector<T>::reference //compiles
    decltype(vec[0])            //compiles
    operator()(){
        return vec[0];
    }
};

void print(const auto& a){
    for(const auto& i : a.vec){
        std::cout << i << ',';
    }
    std::cout << '\n';
}

int main() {
    A<int> aInt{};
    aInt()=2;
    print(aInt);

    A<bool> aBool{};
    aBool()=true;
    print(aBool);

    std::vector<bool> v(5);
    v[0]=true;
}