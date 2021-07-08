#include "typelist.hpp"

using namespace MetaSpirits;
int main()
{
    using Int4 = List<int, int, int, int>::Result;
    Int4::Head x = 0;
    return 0;
}
