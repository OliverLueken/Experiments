#include <iostream>
#include <ranges>
#include <vector>

struct A{
    int val{};
};

int main() {
    std::vector<A> vec{A{1},A{2},A{3}};
    for(auto i : vec | std::views::transform(&A::val)){
        std::cout << i << ',';
    }
}