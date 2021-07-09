// 定义你自己的使用引用计数版本的 HasPtr。
#ifndef HASPTR_27_H_
#define HASPTR_27_H_

#include <string>

class HsaPtr
{
private:
    std::string *ps;
    int i;
    std::size_t *use;

public:
    HsaPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    HsaPtr(const HsaPtr &hp) : ps(hp.ps), i(hp.i), use(hp.use) { ++*use; }
    HsaPtr &operator=(const HsaPtr &rhs)
    {
        ++*rhs.use;
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        return *this;
    }
    ~HsaPtr()
    {
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
};
#endif