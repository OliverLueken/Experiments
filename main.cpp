#include <cstdio>

struct S {
    S() { puts("S()"); }

    S(const S &) { puts("S(const S &)"); }
    S &operator=(const S &) {
        puts("operator=(const S &)");
        return *this;
    }

    S(S &&) { puts("S(S &&)"); }
    S &operator=(S &&) {
        puts("operator=(S &&)");
        return *this;
    }

    ~S() { puts("~S()"); }
};