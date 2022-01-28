
#include <iostream>
#include <vector>

auto lambda1 = [](){ std::cout << "1\n"; };
auto lambda2 = [](){ std::cout << "2\n"; };
auto lambda3 = [](){ std::cout << "3\n"; };

int main(){
    std::vector<void(*)()> lambdas{lambda1, lambda3, lambda2, []{std::cout << "4\n";}};

    // for(const auto& lambda : lambdas){
    //     lambda();
    // }
    //
    std::ranges::for_each(lambdas, [](const auto& lambda){lambda();} );
}

/*
program output:
1
3
2
4
*/