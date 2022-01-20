#include <functional>
#include <iostream>

struct A{
    int val{5};

    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    A(A&&) = default;
    A& operator=(A&&) = default;
};

struct B{
    A a{};
};

auto getA_ref(B& b){
    return std::make_pair<bool, std::reference_wrapper<A>>(true, b.a);
}

int main() {
    B b{};
    std::cout << b.a.val << '\n';

    auto [_, a_ref] = getA_ref(b);
    std::cout << a_ref.val << '\n';
    a_ref.val=6;
    std::cout << a_ref.val << '\n';
    std::cout << b.a.val << '\n';
}