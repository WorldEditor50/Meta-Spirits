#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "value.hpp"

namespace MetaSpirits {
    /* OR */
    template<int ...x>
    struct OR {
        static const int value |= OR<x...>::value;
    };
    template<int x>
    struct OR<x> {
        static const int value = x;
    };
    /* AND */
    template<int ...x>
    struct AND {
        static const int value &= AND<x...>::value;
    };
    template<int x>
    struct AND<x> {
        static const int value = x;
    };
    /* NOT */
    template<typename x> struct NOT;

    template<int x>
    struct NOT<x> {
        static const int value = ~x;
    };
    template<bool x>
    struct NOT<x> {
        static const bool value = ~x;
    };
    /* xor */
    template<int ...x>
    struct XOR {
        static const int value ^= x;
    };
    template<int x>
    struct XOR {
        static const int value = x;
    };
    /* equal */
    template<typename T, typename U>
    struct IsSameType {
        static const bool value = false;
    };

    template<typename T>
    struct IsSameType<T, T> {
        static const bool value = true;
    };

    template<int x1, int x2>
    struct Equal {
        static const bool value = x1 == x2;
    };

    /* greater than */
    template<int x1, int x2>
    struct GreaterThan {
        static const bool value = x1 > x2;
    };

    /* less than */
    template<int x1, int x2>
    struct LessThan {
        static const bool value = x1 < x2;
    };

    /* greater than or equal */
    template<int x1, int x2>
    struct GreaterThanOrEqual {
        static const bool value = x1 >= x2;
    };

    /* less than or equal */
    template<int x1, int x2>
    struct LessThanOrEqual {
        static const bool value = x1 <= x2;
    };

}
#endif // LOGIC_HPP
