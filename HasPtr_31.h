#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);
    friend bool operator<(const HasPtr &, const HasPtr &);
    friend void show(std::vector<HasPtr> &vec);

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

private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap" << std::endl;
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    std::cout << "< " << *lhs.ps << " " << *rhs.ps << std::endl;
    return *lhs.ps < *rhs.ps;
}

void show(std::vector<HasPtr> &vec)
{
    std::for_each(vec.begin(), vec.end(), [](HasPtr &hp)
                  { std::cout << *hp.ps << std::endl; });
}
#endif
