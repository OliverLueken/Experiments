#include <vector>
#include <iostream>
#include <ranges>
#include <iterator>
#include "S.hpp"
#include <iomanip>

namespace ViewDetails{
    template<std::ranges::forward_range Range>
    class _CircularView : public std::ranges::view_interface<_CircularView<Range>> {
        using RangeIteratorType = std::ranges::iterator_t<Range>;
        class CircularIterator : public RangeIteratorType{
            RangeIteratorType firstIt{};
            RangeIteratorType lastIt{};
        public:
            constexpr CircularIterator() = default;
            constexpr CircularIterator(Range& range)
            : RangeIteratorType{range.begin()}, firstIt{range.begin()}, lastIt{range.end()}{}

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

            constexpr auto& operator+=(long i){
                i%=std::distance(firstIt, lastIt);
                if(i > std::distance(static_cast<RangeIteratorType>(*this), lastIt) ){
                    RangeIteratorType::operator=(firstIt+i-std::distance(static_cast<RangeIteratorType>(*this), lastIt));
                }
                RangeIteratorType::operator+=(i);
                return *this;
            }
        };

        CircularIterator iter;
    public:
        constexpr _CircularView() = default;
        constexpr _CircularView(Range range)
        : iter{range}
        {}

        constexpr CircularIterator begin() const {return iter; }
        constexpr auto             end()   const {return std::unreachable_sentinel; }
    };


    struct CircularViewAdaptor{
        template<std::ranges::viewable_range Range>
        constexpr auto operator()(Range&& r) const
        {
            return _CircularView<Range>(std::forward<Range>(r));
        }
    };
}
namespace views{
    ViewDetails::CircularViewAdaptor circle;
}

template<std::ranges::viewable_range Range>
constexpr auto operator|(Range&& r, const ViewDetails::CircularViewAdaptor& circularView)
{
    return circularView(std::forward<Range>(r)) ;
}



int main() {
    auto vec = std::vector<S>(5);

    std::cout << "\nCircling over circlular view\n";
    auto circ = views::circle(vec);
    auto count = 1;
    for(const auto& val : circ){
        std::cout << count << ". value in circle view is " << val.id << '\n';
        ++count;
        if(count == 17) break;
    }
    std::cout << '\n';

    std::cout << "unreachable_sentinel == begin() is " << std::boolalpha << (circ.end() == circ.begin()) << '\n';
    std::cout << '\n';

    auto it = circ.begin();
    it+=7;
    std::cout << "Testing operator+=(): ";
    std::cout << it->id << "==3 is " << std::boolalpha << (it->id==3) << '\n';
    std::cout << '\n';

    std::cout << "Testing operator++(int):\n";
    auto prevVal = it++->id;
    std::cout << prevVal <<"==3 and " << it->id << "==4 is " << std::boolalpha << (prevVal==3 && it->id==4) << '\n';
    prevVal = it++->id;
    std::cout << prevVal <<"==4 and " << it->id << "==5 is " << std::boolalpha << (prevVal==4 && it->id==5) << '\n';
    prevVal = it++->id;
    std::cout << prevVal <<"==5 and " << it->id << "==1 is " << std::boolalpha << (prevVal==5 && it->id==1) << '\n';
    std::cout << '\n';

    std::cout << "Circling with pipe operator\n";
    count = 1;
    for(const auto& val : vec | views::circle ){
        std::cout << count << ". value in circle view is " << val.id << '\n';
        ++count;
        if(count == 12) break;
    }
    std::cout << '\n';

    std::cout << "Dropping before circling\n";
    count = 1;
    for(const auto& val : vec | std::views::drop(2) | views::circle ){
        std::cout << count << ". value in circle view is " << val.id << '\n';
        ++count;
        if(count == 12) break;
    }
    std::cout << '\n';

    std::cout << "Dropping after circling\n";
    count = 1;
    for(const auto& val : vec | views::circle | std::views::drop(2) ){
        std::cout << count << ". value in circle view is " << val.id << '\n';
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
1. value in circle view is 1
2. value in circle view is 2
3. value in circle view is 3
4. value in circle view is 4
5. value in circle view is 5
6. value in circle view is 1
7. value in circle view is 2
8. value in circle view is 3
9. value in circle view is 4
10. value in circle view is 5
11. value in circle view is 1
12. value in circle view is 2
13. value in circle view is 3
14. value in circle view is 4
15. value in circle view is 5
16. value in circle view is 1

unreachable_sentinel == begin() is false

Testing operator+=(): 3==3 is true

Testing operator++(int):
3==3 and 4==4 is true
4==4 and 5==5 is true
5==5 and 1==1 is true

Circling with pipe operator
1. value in circle view is 1
2. value in circle view is 2
3. value in circle view is 3
4. value in circle view is 4
5. value in circle view is 5
6. value in circle view is 1
7. value in circle view is 2
8. value in circle view is 3
9. value in circle view is 4
10. value in circle view is 5
11. value in circle view is 1

Dropping before circling
1. value in circle view is 3
2. value in circle view is 4
3. value in circle view is 5
4. value in circle view is 3
5. value in circle view is 4
6. value in circle view is 5
7. value in circle view is 3
8. value in circle view is 4
9. value in circle view is 5
10. value in circle view is 3
11. value in circle view is 4

Dropping after circling
1. value in circle view is 3
2. value in circle view is 4
3. value in circle view is 5
4. value in circle view is 1
5. value in circle view is 2
6. value in circle view is 3
7. value in circle view is 4
8. value in circle view is 5
9. value in circle view is 1
10. value in circle view is 2
11. value in circle view is 3

~S1()
~S2()
~S3()
~S4()
~S5()





*/