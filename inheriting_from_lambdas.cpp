#include <functional>
#include <type_traits>
#include <iostream>

template <typename L1, typename L2>
struct S : L1, L2 {
    S(L1 l1, L2 l2) : L1(std::move(l1)), L2(std::move(l2)) {}

    using L1::operator();
    using L2::operator();
};

template <typename L1, typename L2>
auto make_combined(L1 &&l1, L2 &&l2) {
    return S<std::decay_t<L1>, std::decay_t<L2>>(
        std::forward<L1>(l1),
        std::forward<L2>(l2)
    );
}

int main() {
    auto l = [] { return 4; };
    auto l2 = [](const int i) { return i * 10; };

    auto combined = make_combined(l, l2);
    combined(2);
    combined();

    auto combined2 = S(l, l2);
    std::cout << combined2(10) << '\n';
    std::cout << combined2()   << '\n';
}

/*
output:
100
4
*/