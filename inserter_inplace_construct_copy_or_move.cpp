#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iterator>

#include "S.hpp"


int main() {
    std::vector<int> v1{1,2};
    std::vector<S> v2{};
    //v2.reserve(v1.size());
    std::ranges::transform(v1, std::back_inserter(v2), [](const auto&){
        return S{}; //constructs and moves into vector
    });
    for(const auto& s : v2){
        std::cout << s.id << '\n';
    }
}

/*
output:
S1()
S2(S1 &&)
~S1()
S3()
S4(S3 &&)
S5(S2 &&) //move S2 into bigger vector, preventable by reserving enough space beforehand
~S2()
~S3()
5
4
~S5() //destructs objects in vector from left to right
~S4()
*/