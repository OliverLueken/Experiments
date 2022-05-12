
#include <iostream>

#include <boost/type_index.hpp>

template<typename T>
std::string typeOf(){
    using boost::typeindex::type_id_with_cvr;
    return type_id_with_cvr<T>().pretty_name();
}

const int* getIntPointer()
{
    static int i = 1;
    return &i;
}
const int& getIntRef(){
    static int i = 1;
    return i;
}

int main() {
    const auto val1 = getIntPointer();
    std::cout << "type of val1 = " << typeOf<decltype(val1)>() << '\n';

    const auto val2 = getIntRef();
    std::cout << "type of val2 = " << typeOf<decltype(val2)>() << '\n';

    const auto* val3 = getIntPointer();
    std::cout << "type of val3 = " << typeOf<decltype(val3)>() << '\n';

    const auto& val4= getIntRef();
    std::cout << "type of val4 = " << typeOf<decltype(val4)>() << '\n';

    const auto& val5= getIntPointer();
    std::cout << "type of val5 = " << typeOf<decltype(val5)>() << '\n';

    //const auto&& val6 = getIntRef();
    //std::cout << "type of val6 = " << typeOf<decltype(val6)>() << '\n';
}

/*
type of val1 = int const* const
type of val2 = int const
type of val3 = int const*
type of val4 = int const&
type of val5 = int const* const&
*/