#include <iostream>

struct S {
    int id{0};
    static int count;

    S() {
        id=++count;
        std::cout << "S" << id << "()\n";
    }

    S(const S & other) {
        id=++count;
        std::cout << "S" << id << "(const S" << other.id << " &)\n";
    }
    S &operator=(const S & other) {
        std::cout << "S" << id << " operator=(const S" << other.id << " &)\n";
        return *this;
    }

    S(S && other) {
        id=++count;
        std::cout << "S" << id << "(S" << other.id << " &&)\n";
    }
    S &operator=(S && other) {
        std::cout << "S" << id << " operator=(const S" << other.id << " &&)\n";
        return *this;
    }

    ~S() {
        std::cout << "~S" << id << "()\n";
    }
};
int S::count = 0;