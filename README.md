# MetaSpirits

## 1. 模板元函数

c++的类与类模板可以看作为元函数：

- 模板参数可以看作元函数的输入，输入可以是类型、模板或常量
- 定义类内常量、类型或继承参数可以看作元函数的输出，输出参数可以是多个的

## 2. 多参数模板

```cpp
#include <iostream>
/* recursive */
void showAll()
{
    std::cout<<std::endl;
}
template <typename TArg, typename ...TArgs>
void showAll(TArg arg0, TArgs ...args)
{
    std::cout<<arg0<<" ";
    showAll(args...);
}
/* list */
template <typename T>
void print(T arg)
{
    std::cout<<arg<<" ";
}
template <typename ...TArgs>
void expand(TArgs ...args)
{
    int argv[] = {(print(args), 0)...};
}
/* inherit */
template <int...>
struct IndexSeq {};

template <int N, int ...Indexs>
struct MakeIndexs:MakeIndexs<N - 1, N - 1, Indexs...> {};

template <int ...Indexs>
struct MakeIndexs<0, Indexs...> {
    using type = IndexSeq<Indexs...>;
};

int main()
{
    showAll(1, 2, 3, 4, 5);
    showAll("hello", "hi", "bye", "ciao", "thanks");
    expand(1, 2, 3, 4, 5);
    std::cout<<std::endl;
    expand("hello", "hi", "bye", "ciao", "thanks");
    std::cout<<std::endl;
    using T = MakeIndexs<1, 2, 3>::type;
    std::cout<<typeid(T).name()<<std::endl;
    return 0;
}
```

- 递归展开模板参数
- 列表初始化，逗号表达式展开模板参数
- 继承展开模板参数

## 3. 模板特化

```cpp
template<bool condit, typename T, typename F> struct IF {};

template<typename T, typename F>
struct IF<false, T, F> {
    using Result = F;
};

template<typename T>
struct IF<true, T, T> {
    using Result = T;
};
```

## 4. 数值计算

```c++
template<int N>
struct Fibonacci {
    enum {value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value};
};
template<>
struct Fibonacci<1> {
    enum {value = 1};
};
template<>
struct Fibonacci<0> {
    enum {value = 0};
};
```



## 5. 模板匹配与递归的应用

### (1) 定位编译期容器元素位置

- 模板特化匹配

### (2) 遍历编译期容器

- 递归

### (3) 修改编译期容器元素

- 模板特化匹配 + 递归

  

## 6. 编译期容器

编译期容器是一种嵌套结构的容器，比如**list** {e1, {e2, {e3, {e4, {...}}}}，所以元素与元素之间需要一个结构来衔接。

```cpp
template<typename T1,typename T2>
struct Pair {
    using T = T1;
    using Next = T2;
};
/*
	0 -- > {NullType}
	1 -- > {T1, NullType}
	2 -- > {T1, {T2, NullType}}
	3 -- > {T1, {T2, {T3, NullType}}}
	...
*/
struct NullType {};

template<typename T, typename ...Tn>
struct List : Pair<T, typename List<Tn...> {};

template<typename T>
struct List<T> : Pair<T, NullType> {};
```



## 7. 策略模板

- 每个策略统行为函数名称
- 每个策略的参数类型、个数 不同，可以根据应用场景优化参数

```cpp
class Policy1
{
public:
    Policy1(){}
    ~Policy1(){}
    void execute {std::cout<<"policy1"<<std::endl;}
private:
    int x;
};

class Policy2
{
public:
    Policy2(){}
    ~Policy2(){}
    void execute {std::cout<<"policy2"<<std::endl;}
private:
    int x;
    char c;
};

class Policy3
{
public:
    Policy3(){}
    ~Policy3(){}
    void execute {std::cout<<"policy3"<<std::endl;}
};
using PolicyList = List<Policy1, Policy2, Policy3>;

template<int N>
class Operate : public typename ListIndexOf<PolicyList, N>::Result
{
public:
    Operate(){}
    ~Operate(){}
}
```



## 8. 表达式模板

