#include <iostream>
#include <array>
#include <string>

template<typename T>
concept hasBracketOperator = requires (T x){ x[0]; };


template<typename T>
struct A{
    T val{};

    auto f(unsigned long i){
        if constexpr(hasBracketOperator<T>){
            return val[i];
        }
        else{
            return 10;
        }
    }
};

int main() {
    auto a = A<std::array<int, 2>>{};
    std::cout << a.f(0) << '\n';

    auto a2 = A<int>{};
    std::cout << a2.f(0) << '\n';
}


/*
output:
0
10
*/