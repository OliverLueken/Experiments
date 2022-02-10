#include "S.hpp"

auto foo(){
    S a{};
    S b{};

    // return std::make_pair(a, b); //Calls copy constructor on a, b
    return std::make_pair(std::move(a), std::move(b)); //Calls move constructor on a, b
}

int main(){
    const auto [a, b] = foo();
}

/*
output:
S1()
S2()
S3(S1 &&)
S4(S2 &&)
~S2()
~S1()
~S4()
~S3()

*/