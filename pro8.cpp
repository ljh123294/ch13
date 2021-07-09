// 深拷贝
#include <string>
class HasPtr
{
private:
    std::string *ps;
    int i;

public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr &operator=(const HasPtr &hp)
    {
        if (this != &hp)
        {
            delete ps;
            ps = new std::string(*hp.ps);
            i = hp.i;
        }
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
};
