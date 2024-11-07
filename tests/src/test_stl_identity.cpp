//
// Created by Mac on 24-11-7.
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <string>

struct Pair
{
    int n;
    std::string s;
    friend std::ostream& operator<<(std::ostream& os, const Pair& p)
    {
        return os << "{ " << p.n << ", " << p.s << " }";
    }
};

// 范围打印器能打印投影（修改）后的范围元素。
template<std::ranges::input_range R,
        typename Projection = std::identity> //<- 注意默认投影
void print(std::string_view const rem, R&& range, Projection projection = {})
{
    std::cout << rem << '{';
    std::ranges::for_each(
            range,
            [O = 0](const auto& o) mutable { std::cout << (O++ ? ", " : "") << o; },
            projection
    );
    std::cout << "}\n";
}

int main()
{
    const auto v = {Pair{1, "one"}, {2, "two"}, {3, "three"}};

    print("将 std::identity 用作投影打印：", v);
    print("投影 Pair::n：", v, &Pair::n);
    print("投影 Pair::s：", v, &Pair::s);
    print("将自定义闭包用作投影打印：", v,
          [](Pair const& p) { return std::to_string(p.n) + ':' + p.s; });
}
