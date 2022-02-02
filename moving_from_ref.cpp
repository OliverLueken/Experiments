#include <iostream>
#include <stdio.h>

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

int main(){
    S s{};

    puts("Make pair with s");
    const auto pair = std::make_pair(s, 1); //copy

    puts("Make pair with moving s");
    const auto pair2 = std::make_pair(std::move(s), 1); //move

    puts("Make pair with const sref");
    const auto& sref = s;
    const auto pair3 = std::make_pair(sref, 1); //copy

    puts("Make pair with moving const sref");
    const auto& sref2 = s;
    const auto pair4 = std::make_pair(std::move(sref2), 1); //copy, ref is const

    puts("Make pair with moving sref");
    auto& sref3 = s;
    const auto pair5 = std::make_pair(std::move(sref3), 1); //move
}

/*
output:
S1()
Make pair with s
S2(const S1 &)
Make pair with moving s
S3(S1 &&)
Make pair with const sref
S4(const S1 &)
Make pair with moving const sref
S5(const S1 &)
Make pair with moving sref
S6(S1 &&)
~S6()
~S5()
~S4()
~S3()
~S2()
~S1()
*/