#include <vector>
#include <iostream>
#include <ranges>
#include <iterator>
#include "S.hpp"


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
    auto count = 0;
    for(const auto& val : circ){
        std::cout << val.id << '\n';
        ++count;
        if(count == 16) break;
    }
}

/*
Output:

S1()
S2()
S3()
S4()
S5()
1
2
3
4
5
1
2
3
4
5
1
2
3
4
5
1
~S1()
~S2()
~S3()
~S4()
~S5()
*/