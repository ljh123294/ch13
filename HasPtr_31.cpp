#include "HasPtr_31.h"
#include <vector>
#include <algorithm>

int main()
{
    HasPtr hp1("ccc"), hp2("bbb"), hp3("aaa");
    std::vector<HasPtr> vh{hp1, hp2, hp3};
    std::sort(vh.begin(), vh.end());
    show(vh);
    return 0;
}
