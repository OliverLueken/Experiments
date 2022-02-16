
#include <iostream>

auto foo(){
    std::cout << "- Calling foo - ";
    return 42;
}

auto bar(){
    static auto val = foo(); //only called once
    return val;
}

int main(){
    for(auto i=0; i<5; ++i){
        std::cout << i << ": " << bar() << '\n';
    }
}

/*
output:
0: - Calling foo - 42
1: 42
2: 42
3: 42
4: 42
*/