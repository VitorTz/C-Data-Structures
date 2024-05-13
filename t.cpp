#include <map>
#include <iostream>


int main() {
    std::map<int, int> m;
    int a = 1;
    int b = 1;
    m.insert({a, 2});
    m.insert({b, 3});
    std::cout << m.at(1) << '\n';
    return  0;
}