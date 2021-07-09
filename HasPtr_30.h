// 为你的类值版本的 HasPtr 编写 swap 函数
#ifndef HASPTR_30_H
#define HASPTR_30_H
#include <string>
#include <iostream>

class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);

private:
    std::string *ps;
    int i;

public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr &operator=(const HasPtr &rhs_hp)
    {
        auto newp = new std::string(*rhs_hp.ps);
        delete ps;
        ps = newp;
        i = rhs_hp.i;
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap" << std::endl;
}
#endif