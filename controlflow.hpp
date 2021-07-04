#ifndef CONTROL_FLOW_HPP
#define CONTROL_FLOW_HPP

namespace MetaSpirits {
    /* if-else-then */
    template<bool condit, typename T, typename F> struct Select {};

    template<typename T, typename F>
    struct Select<false, T, F> {
        using Result = F;
    };

    template<typename T>
    struct Select<true, T, T> {
        using Result = T;
    };

    /* control-flow */
    template<int N, typename Template>
    struct Recursive {
        using Result = Recursive<N - 1, typename Template::Result>::Result;
    };

    template<typename T>
    struct Recursive<0, T> {
        using Result = T;
    }

}
#endif // CONTROL_FLOW_HPP
