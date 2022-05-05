#include <cstdio>
#include <algorithm>
#include "S.hpp"

int main(){
    S* s1 = new S[5];
    S* s2 = new S[5];
    std::ranges::copy(s1, s1+5, s2);

    delete[] s2;
    delete[] s1;
}

/*
Output:
S1()
S2()
S3()
S4()
S5()
S6()
S7()
S8()
S9()
S10()
S6 operator=(const S1 &)
S7 operator=(const S2 &)
S8 operator=(const S3 &)
S9 operator=(const S4 &)
S10 operator=(const S5 &)
~S10()
~S9()
~S8()
~S7()
~S6()
~S5()
~S4()
~S3()
~S2()
~S1()

*/
