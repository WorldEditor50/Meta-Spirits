#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include <cmath>

template <class ExprF>
class Expr {
    ExprF _F;
public:
    Expr(){}
    explicit Expr(const ExprF &F):_F(F){}
    inline double operator()(double x) const {return _F(x);}
};
class Cons {
    double _c;
public:
    explicit Cons(double c):_c(c){}
    inline double operator()(double x) const {return _c;}
};
class Var {
public:
    inline double operator()(double x) const {return x;}
};
template <class Right, class Op>
class UnaryOp {
    Right _right;
public:
    explicit UnaryOp(const Right &right):_right(right){}
    inline double operator()(double x) const {return Op::apply(_right(x));}
};
template <class Left, class Right, class Op>
class BinaryOp {
    Left _left;
    Right _right;
public:
    explicit BinaryOp(const Left &left, const Right &right):_left(left), _right(right){}
    inline double operator()(double x) const {return Op::apply(_left(x), _right(x));}
};
class Plus {public:static double apply(double x1, double x2){return x1 + x2;}};
class Minus {public:static double apply(double x1, double x2){return x1 - x2;}};
class Multi {public:static double apply(double x1, double x2){return x1 * x2;}};
class Divide {public:static double apply(double x1, double x2){return x1 / (x2 + 1e-9);}};
class Negative {public:static double apply(double x){return -x;}};
class Sqrt {public:static double apply(double x){return sqrt(x);}};
class Exp {public:static double apply(double x){return exp(x);}};
class Sigmoid {public:static double apply(double x){return exp(x) / (1 + exp(x));}};
class Tanh {public:static double apply(double x){return (exp(2 * x) - 1)/ (exp(2 * x) + 1);}};
class Relu {public:static double apply(double x){return (x > 0) ? x : 0;}};
template <class Left, class Right>
Expr<BinaryOp<Expr<Left>, Expr<Right>, Plus> > operator + (const Expr<Left> &left, const Expr<Right> &right)
{
    using ExprT = BinaryOp<Expr<Left>, Expr<Right>, Plus>;
    return Expr<ExprT>(ExprT(left, right));
}
template <class Left, class Right>
Expr<BinaryOp<Expr<Left>, Expr<Right>, Minus> > operator - (const Expr<Left> &left, const Expr<Right> &right)
{
    using ExprT = BinaryOp<Expr<Left>, Expr<Right>, Minus>;
    return Expr<ExprT>(ExprT(left, right));
}
template <class Left, class Right>
Expr<BinaryOp<Expr<Left>, Expr<Right>, Multi> > operator * (const Expr<Left> &left, const Expr<Right> &right)
{
    using ExprT = BinaryOp<Expr<Left>, Expr<Right>, Multi>;
    return Expr<ExprT>(ExprT(left, right));
}
template <class Left, class Right>
Expr<BinaryOp<Expr<Left>, Expr<Right>, Divide> > operator / (const Expr<Left> &left, const Expr<Right> &right)
{
    using ExprT = BinaryOp<Expr<Left>, Expr<Right>, Divide>;
    return Expr<ExprT>(ExprT(left, right));
}
template <class Right>
Expr<UnaryOp<Expr<Right>, Negative> > operator - (const Expr<Right> &right)
{
    using ExprT = UnaryOp<Expr<Right>, Negative>;
    return Expr<ExprT>(ExprT(right));
}
#define DECLARE_FUNC(Func, func) \
    template <class Right> \
    Expr<UnaryOp<Expr<Right>, func> > (Func)(const Expr<Right> &right) \
    { \
        using ExprT = UnaryOp<Expr<Right>, func>; \
        return Expr<ExprT>(ExprT(right)); \
    }
DECLARE_FUNC(SQRT, Sqrt)
DECLARE_FUNC(EXP, Exp)
DECLARE_FUNC(SIGMOID, Sigmoid)
DECLARE_FUNC(TANH, Tanh)
DECLARE_FUNC(RELU, Relu)

template <class F>
void evaluate(const Expr<F> &f)
{
    for (double x = 0; x < 10; x += 1.0) {
        std::cout<<f(x)<<" ";
    }
    std::cout<<std::endl;
    return;
}

#endif // EXPRESSION_HPP
