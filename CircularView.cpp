#include <vector>
#include <iostream>
#include <ranges>
#include <iterator>
#include "S.hpp"
#include <iomanip>

template<std::ranges::range Range>
class CircularView : public std::ranges::view_interface<CircularView<Range>> {
    using RangeIteratorType = std::ranges::iterator_t<Range>;
    class CircularIterator : public RangeIteratorType{
        RangeIteratorType firstIt{};
        RangeIteratorType lastIt{};
    public:
        CircularIterator(Range& vec)
        : RangeIteratorType{vec.begin()}, firstIt{vec.begin()}, lastIt{vec.end()}{}

        bool operator==(std::unreachable_sentinel_t){return false;}

        auto operator++(){
            RangeIteratorType::operator++();
            if(static_cast<RangeIteratorType>(*this) == lastIt){
                RangeIteratorType::operator=(firstIt);
            }
        }
    };

    CircularIterator iter;
public:
    CircularView(Range& vec)
    : iter{vec}
    {}

    CircularIterator begin() const {return iter; }
    auto             end()   const {return std::unreachable_sentinel; }
};

int main() {
    auto vec = std::vector<S>(5);

    auto circ = CircularView{vec};
    auto count = 1;
    for(const auto& val : circ){
        std::cout << count << ". value in circular view is " << val.id << '\n';
        ++count;
        if(count == 17) break;
    }

    std::cout << "unreachable_sentinel == begin() is " << std::boolalpha << (circ.end() == circ.begin()) << '\n';

}

/*
Output:

S1()
S2()
S3()
S4()
S5()
1. value in circular view is 1
2. value in circular view is 2
3. value in circular view is 3
4. value in circular view is 4
5. value in circular view is 5
6. value in circular view is 1
7. value in circular view is 2
8. value in circular view is 3
9. value in circular view is 4
10. value in circular view is 5
11. value in circular view is 1
12. value in circular view is 2
13. value in circular view is 3
14. value in circular view is 4
15. value in circular view is 5
16. value in circular view is 1
unreachable_sentinel == begin() is false
3
~S1()
~S2()
~S3()
~S4()
~S5()
*/