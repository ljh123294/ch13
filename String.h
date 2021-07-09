#ifndef STRING_H_
#define STRING_H_

#include <cstring>
#include <memory>
#include <algorithm>
#include <iostream>

class String
{
private:
    char *elements;
    char *first_free;
    std::pair<char *, char *> alloc_n_copy(const char *, const char *);
    std::allocator<char> alloc;
    void free();

public:
    String();
    String(const char *);
    String(const String &);
    String(String &&) noexcept;
    String &operator=(const String &);
    char *begin() const { return elements; }
    char *end() const { return first_free; }
    ~String();
};
std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e)
{
    char *p = alloc.allocate(e - b);
    return {p, std::uninitialized_copy(b, e, p)};
}
String::String(String &&rhs) : elements(std::move(rhs.elements)), first_free(std::move(rhs.first_free))
{
    rhs.elements = nullptr;
    rhs.first_free = nullptr;
}
String::String(const char *cp)
{
    size_t n = strlen(cp);
    auto data = alloc_n_copy(cp, cp + n);
    elements = data.first;
    first_free = data.second;
}
String::String()
{
    String("");
}
String::String(const String &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    elements = data.first;
    first_free = data.second;

    std::cout << "String(const String &rhs)" << std::endl;
}
void String::free()
{
    if (elements)
    {
        std::for_each(elements, first_free, [this](char &c)
                      { alloc.destroy(&c); });
        alloc.deallocate(elements, first_free - elements);
    }
}
String &String::operator=(const String &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = data.second;

    std::cout << "String& operator=(const String& rhs)" << std::endl;
    return *this;
}
String::~String()
{
    free();
}
#endif