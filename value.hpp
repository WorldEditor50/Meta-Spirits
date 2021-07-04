#ifndef VALUE_HPP
#define VALUE_HPP

namespace MetaSpirits {

    template<int N>
    struct IntType {
        static const int value = N;
    };

    template<bool b>
    struct BoolType {
        static const bool value = b;
    };

}
#endif // VALUE_HPP
