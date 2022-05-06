#include <vector>
#include <iostream>
#include <ranges>
#include <iterator>
#include "S.hpp"
#include <iomanip>

template<std::ranges::range Range>
class _CircularView : public std::ranges::view_interface<_CircularView<Range>> {
    using RangeIteratorType = std::ranges::iterator_t<Range>;
    class CircularIterator : public RangeIteratorType{
        RangeIteratorType firstIt{};
        RangeIteratorType lastIt{};
    public:
        constexpr CircularIterator(Range& vec)
        : RangeIteratorType{vec.begin()}, firstIt{vec.begin()}, lastIt{vec.end()}{}

        constexpr bool operator==(std::unreachable_sentinel_t){return false;}

        constexpr auto& operator++(){
            RangeIteratorType::operator++();
            if(static_cast<RangeIteratorType>(*this) == lastIt){
                RangeIteratorType::operator=(firstIt);
            }
            return *this;
        }

        constexpr auto operator++(int){
            CircularIterator temp{*this};
            ++*this;
            return temp;
        }

        constexpr auto& operator+=(int i){
            RangeIteratorType::operator+=(i);
            return *this;
        }
    };

    CircularIterator iter;
public:
    _CircularView() = default;
    _CircularView(Range range)
    : iter{range}
    {}

    CircularIterator begin() const {return iter; }
    auto             end()   const {return std::unreachable_sentinel; }
};


struct CircularViewAdaptor{
    template<std::ranges::range Range>
    constexpr auto operator()(Range&& r) const
    {
        return _CircularView<Range>(std::forward<Range>(r));
    }
};
CircularViewAdaptor CircularView;

template<std::ranges::range Range>
constexpr auto operator|(Range&& r, const CircularViewAdaptor& a)
{
    return a(std::forward<Range>(r)) ;
}


int main() {
    auto vec = std::vector<S>(5);

    std::cout << "\nCircling over circlular view\n";
    auto circ = CircularView(vec);
    auto count = 1;
    for(const auto& val : circ){
        std::cout << count << ". value in circular view is " << val.id << '\n';
        ++count;
        if(count == 17) break;
    }
    std::cout << '\n';

    std::cout << "unreachable_sentinel == begin() is " << std::boolalpha << (circ.end() == circ.begin()) << '\n';
    std::cout << '\n';

    auto it = circ.begin();
    it+=2;
    std::cout << "Testing operator+=(): ";
    std::cout << it->id << "==3 is " << std::boolalpha << (it->id==3) << '\n';
    std::cout << '\n';

    std::cout << "Testing operator++(int): ";
    auto prevVal = it++->id;
    std::cout << prevVal <<"==3 and " << it->id << "==4 is " << std::boolalpha << (prevVal==3 && it->id==4) << '\n';
    std::cout << '\n';

    std::cout << "Circling with pipe operator\n";
    count = 1;
    for(const auto& val : vec | CircularView ){
        std::cout << count << ". value in circular view is " << val.id << '\n';
        ++count;
        if(count == 12) break;
    }
    std::cout << '\n';

    std::cout << "Dropping before circling\n";
    count = 1;
    for(const auto& val : vec | std::views::drop(2) | CircularView ){
        std::cout << count << ". value in circular view is " << val.id << '\n';
        ++count;
        if(count == 12) break;
    }
    std::cout << '\n';
}

/*
Output:

S1()
S2()
S3()
S4()
S5()

Circling over circlular view
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

Testing operator+=(): 3==3 is true

Testing operator++(int): 3==3 and 4==4 is true

Circling with pipe operator
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

Dropping before circling
1. value in circular view is 3
2. value in circular view is 4
3. value in circular view is 5
4. value in circular view is 3
5. value in circular view is 4
6. value in circular view is 5
7. value in circular view is 3
8. value in circular view is 4
9. value in circular view is 5
10. value in circular view is 3
11. value in circular view is 4

~S1()
~S2()
~S3()
~S4()
~S5()



*/