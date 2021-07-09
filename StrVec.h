// 编写自己的vector<string>
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <memory>
// #include <utility>
class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    StrVec(std::initializer_list<std::string>);
    StrVec(StrVec &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free)), cap(std::move(cap)) { s.elements = s.first_free = s.cap = nullptr; }
    ~StrVec();
    void push_back(const std::string &);
    size_t size() const
    {
        return first_free - elements;
    }
    size_t capacity() const
    {
        return cap - elements;
    }
    std::string *begin() const
    {
        return elements;
    }
    std::string *end() const
    {
        return first_free;
    }
    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const std::string &s);

private:
    std::string *elements;
    std::string *first_free;
    std::string *cap;
    std::allocator<std::string> alloc;
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void free();
    void reallocate();
    void my_alloc(size_t);
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
};

void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::my_alloc(size_t n)
{
    auto new_data = alloc.allocate(n);
    auto dest = new_data;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
    {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = new_data;
    first_free = dest;
    cap = elements + n;
}

void StrVec::reallocate()
{
    auto new_capacity = size() ? 2 * size() : 1;
    my_alloc(new_capacity);
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

StrVec::StrVec(const StrVec &sv)
{
    auto data = alloc_n_copy(sv.begin(), sv.end());
    elements = data.first;
    first_free = cap = data.second;
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec::StrVec(std::initializer_list<std::string> ilst)
{
    auto data = alloc_n_copy(ilst.begin(), ilst.end());
    elements = data.first;
    first_free = cap = data.second;
}

StrVec::~StrVec()
{
    free();
}

void StrVec::reserve(size_t n)
{
    if (n <= capacity())
        return;
    my_alloc(n);
}

void StrVec::resize(size_t n)
{
    resize(n, std::string());
}

void StrVec::resize(size_t n, const std::string &s)
{
    if (n < size())
    {
        while (n < size())
            alloc.destroy(--first_free);
    }
    else if (n > size())
    {
        while (n > size())
            push_back(s);
    }
}
#endif