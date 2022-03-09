/*
From Jason Turner's
"C++ Weekly - Ep 313 - The `constexpr` Problem That Took Me 5 Years To Fix!"

https://www.youtube.com/watch?v=ABg4_EV5L3w

Building a string during compile time and using it in runtime without doing the work twice,
as in getting the size of the resulting string first, and then copying it into a constexpr
string of that size afterwards
*/

#include <string>
#include <array>
#include <fmt/format.h>

constexpr std::string make_string(std::string_view base, const int repeat){
    std::string retval;
    for(auto count = 0; count<repeat; ++count){
        retval+=base;
    }
    return retval;
}

struct oversized_array{
    std::array<char, 10*1024*1024> data{};
    std::size_t size;
};

constexpr auto to_oversized_array(const std::string& str){
    oversized_array result;
    std::copy(std::begin(str), std::end(str), result.data.begin());
    result.size = str.size();
    return result;
}

consteval auto to_right_sized_array(auto callable){
    constexpr auto oversized = to_oversized_array(callable());
    std::array<char, oversized.size> result;
    std::ranges::copy(
        std::begin(oversized.data),
        std::next(oversized.data.begin(), oversized.size),
        result.begin()
    );
    return result;
}

template<auto Data>
consteval const auto& make_static(){
    return Data;
}

consteval auto to_string_view(auto callable) -> std::string_view{
    constexpr auto& static_data = make_static<to_right_sized_array(callable)>();
    return std::string_view{static_data.begin(), static_data.size()};
}

int main(){
    constexpr auto make_data = [](){
        return make_string("Hello Jason, ", 3);
    };

    constexpr static auto sv  = to_string_view(make_data);
    constexpr static auto sv2 = to_string_view(make_data);
    fmt::print("{}: '{}' '{}'", sv.size(), sv, sv2);
}