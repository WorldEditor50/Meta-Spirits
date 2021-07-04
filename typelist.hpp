#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP
#include "nulltype.hpp"

namespace MetaSpirits {
    /* pair */
    template<typename H, typename T>
    struct Pair {
        using Head = H;
        using Tail = T;
    };
    /* list init */
    template<typename Head, typename ...Tails>
    struct List {
        using Result = Pair<Head, typename List<Tais...>::Result>;
    };

    template<typename Head>
    struct List<Head> {
        using Result = Pair<Head, NullType>;
    };

    /* list append */
    template<typename TPair, typename T> struct ListAppend;

    /* append nulltype */
    template<>
    struct ListAppend<NullType, NullType> {
        using Result = NullType;
    };

    /* append while list is empty */
    template<typename T>
    struct ListAppend<NullType, T> {
        using Result = Pair<T, NullType>;
    };

    /* append type at back */
    template<typename Head, typename Tail>
    struct ListAppend<NullType, Pair<Head, Tail> > {
        using Result = Pair<Head, Tail>;
    };

    template<typename Head, typename Tail, typename T>
    struct ListAppend<Pair<Head, Tail>, T> {
        using Result = Pair<Head, typename ListAppend<Tail, T>::Result>;
    };

    /* delete */
    template<typename TPair, typename T> struct ListDelete;

    template<typename T>
    struct ListDelete<NullType, T> {
        using Result = NullType;
    };

    template<typename T, typename Tail>
    struct ListDelete<Pair<T, Tail>, T>  {
        using Result = Tail;
    };

    template<typename Head, typename Tail, typename T>
    struct ListDelete<Pair<Head, Tail>, T> {
        using Result = Pair<Head, typename ListDelete<Tail, T>::Result>;
    };

    /* replace */
    template<typename TPair, typename T, typename U> struct ListReplace;

    template<typename T, typename U>
    struct ListReplace<NullType, T, U> {
        using Result = NullType;
    };
    template<typename Tail, typename T, typename U>
    struct ListReplace<Pair<T, Tail>, T, U> {
        using Result = Pair<U, Tail>;
    };
    template<typename Head, typename Tail, typename T, typename U>
    struct ListReplace<Pair<Head, Tail>, T, U> {
        using Result = Pair<Head, typename ListReplace<Tail, T, U>::Result>;
    };

    /* query */
    template<typename TPair, typename T> struct ListQuery;

    template<typename T>
    struct ListQuery<NullType, T> {
        static const bool value = false;
    };
    template<typename Tail, typename T>
    struct ListQuery<Pair<T, Tail>, T> {
        static const bool value = true;
    };

    template<typename Head, typename Tail, typename T>
    struct ListQuery<Pair<Head, Tail>, T> {
        static const bool value = ListQuery<Tail, T>::value;
    };

    /* find */
    template<typename TPair, int N> struct ListFind;

    template<typename Tail>
    struct ListFind<Tail, 0> {
        using Result = Tail;
    };
    template<typename Head, typename Tail, int N>
    struct ListFind<Pair<Head, Tail>. T> {
        using Result = typename ListFind<Tail, N - 1>::Result;
    };

    /* index of */
    template<typename TPair, typename T> struct ListIndexOf;

    template<typename Tail, typename T>
    struct ListIndexOf<Pair<T, Tail>, T> {

    };
    template<typename Head, typename Tail, typename T>
    struct ListIndexOf<Pair<Head, Tail>, T> {
        static const int value = ListIndexOf<Tail, T>::value;
    };
    /* sort */

    /* transform */

    /* fold */

    /* filter */

}



#endif // TYPE_LIST_HPP


