#include <functional>
#include <iostream>
#include <vector>
#include <span>
#include <ranges>

struct Matrix{
    int n{0};
    int m{0};
    std::vector<int> matrix{};

    Matrix() = default;
    Matrix(std::vector<int>&& mat, int _n, int _m) : matrix{std::move(mat)}, n{_n}, m{_m}{}

    template<class Iter>
    struct ColumnIteratorTemplate : public Iter{
        ColumnIteratorTemplate() = default;   //subrange needs this
        ColumnIteratorTemplate(Iter _it, int _m)
            : Iter{_it}, m{_m} {}

        ColumnIteratorTemplate&  operator++()      { Iter::operator+=(m); return *this; }
        ColumnIteratorTemplate   operator++(int)   { ColumnIteratorTemplate tmp = *this; ++(*this); return tmp; }
        ColumnIteratorTemplate&  operator+=(int j) { Iter::operator+=(j*m); return *this; }

        ColumnIteratorTemplate& operator--()      { Iter::operator-=(m); return *this; }
        ColumnIteratorTemplate  operator--(int)   { ColumnIteratorTemplate tmp = *this; --(*this); return tmp; }
        ColumnIteratorTemplate& operator-=(int j) { Iter::operator-=(j*m); return *this; }
    private:
        int m;
    };

    using Iterator            = std::vector<int>::iterator;
    using ConstIterator       = std::vector<int>::const_iterator;
    using ColumnIterator      = ColumnIteratorTemplate<Iterator>;
    using ConstColumnIterator = ColumnIteratorTemplate<ConstIterator>;

    ColumnIterator columnBegin(int j) { return ColumnIterator(matrix.begin()+j, m); }
    ColumnIterator columnEnd  (int j) { return ColumnIterator(matrix.end()  +j, m); }

    ConstColumnIterator cColumnBegin(int j) const { return ConstColumnIterator(matrix.cbegin()+j, m); }
    ConstColumnIterator cColumnEnd  (int j) const { return ConstColumnIterator(matrix.cend()  +j, m); }

    auto col(int j){
        return std::ranges::subrange(columnBegin(j), columnEnd(j));
    }

    auto col(int j) const {
        return std::ranges::subrange(cColumnBegin(j), cColumnEnd(j));
    }
};


void print(const Matrix& matrix){
    auto n = matrix.n;
    auto m = matrix.m;
    for(auto i=0; i<n; ++i){
        for(auto j=0; j<matrix.m; ++j){
            std::cout << matrix.matrix[i*m+j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}



int main() {
    auto mat = Matrix{std::vector<int>{1,2,3,4,5,6,7,8}, 4, 2};
    std::cout << "Matrix:\n";
    print(mat);

    std::cout << "\nFirst column with iterators:\n";
    for(auto it = mat.columnBegin(0); it!=mat.columnEnd(0); ++it){
        std::cout << *it << '\n';
    }

    std::cout << "\nSecond column with range and reverse:\n";
    for(auto i : mat.col(1) | std::views::reverse){
        std::cout << i << '\n';
    }

    std::cout << "\nThird elment of the first column via operator+=()\n";
    auto it = mat.col(0).begin();
    it+=2;
    std::cout << *it << '\n';
    std::cout << "\nSecond elment of the first column via operator-=()\n";
    it-=1;
    std::cout << *it << '\n';
    std::cout << "\nPrinting Second and third elment of the first column via operator++(int)\n";
    std::cout << *(it++) << ' ' << *it << '\n';

    std::cout << "\nConstant version:";
    const auto mat2 = Matrix{mat};

    std::cout << "\nFirst column with iterators:\n";
    for(auto it = mat2.cColumnBegin(0); it!=mat2.cColumnEnd(0); ++it){
        std::cout << *it << '\n';
    }

    std::cout << "\nSecond column with range and reverse:\n";
    for(auto i : mat2.col(1) | std::views::reverse){
        std::cout << i << '\n';
    }


    std::cout << "\nThird elment of the first column via operator+=()\n";
    auto it2 = mat2.col(0).begin();
    it2+=2;
    std::cout << *it2 << '\n';
    std::cout << "\nSecond elment of the first column via operator-=()\n";
    it2-=1;
    std::cout << *it2 << '\n';
    std::cout << "\nPrinting Second and third elment of the first column via operator++(int)\n";
    std::cout << *(it2++) << ' ' << *it2 << '\n';

}