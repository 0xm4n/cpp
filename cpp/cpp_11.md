### 右值引用：

函数传递对象参数的时候，有时候会有很大不必要的复制开销。比如说将一个新建对象作为参数传递的时候，深复制可能会有很大的开销是不必要的，

右值引用最有用的地方是重载拷贝 赋值操作符来实现移动语义

右值：编译器控制lifetime

左值：用户控制lifetime



### 移动语义

Move semantics allows an object, under certain conditions, to take ownership of some other object's external resources.

对象同时编写复制构造函数和移动构造函数，当该对象作为函数参数时，对象可以识别传入的时rvalue还是lvalue，如果传入的是rvalue那么就直接调用移动构造函数，大大节省了复制的开销。



### 通用引用/引用折叠



### 完美转发

如果对象参数的类型是rvalue，那么在调用的函数内也把这个对象作为rvalue去使用；如果对象参数是lvalue，那么在调用的函数内把这个对象作为lvalue去使用。

universal reference：reference collapse

std::forword<T>()



 ### std::move()的实现原理

```cpp
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
    return static_cast<typename remove_reference<T>::type&&>(t);
}
```

https://blog.csdn.net/p942005405/article/details/84644069



### std::forword()实现原理

```cpp
template <typename T>
T&& forward(typename remove_reference<T>::type& arg)
{
	return static_cast<T&&> (arg);
}
```



### 智能指针（实现原理）

unique_pointer: 离开所在作用域后会自动析构，不支持复制

shared_pointer: 利用引用计数判断是否析构指针，每复制一个shared_ptr计数器+1，当指针的引用次数减少到0的时候自动析构  

weak_pointer: 作用在于协助shared_ptr工作，像旁观者那样观测资源的使用情况。weak_ptr可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。



https://www.cnblogs.com/wxquare/p/4759020.html



### lambda表达式（匿名函数对象）





### override关键字

派生类如果定义了一个函数与基类中虚函数的名字相同但是形参列表不同，这仍然是合法的行为。编译器会认定为新定义的这个函数与基类中原有的函数是相互独立的。这是派生类的函数并没有覆盖掉基类中的版本。要想调试并发现这种错误是非常困难的.c++11中可以用override关键字来说明派生类中的虚函数。这么做的好处是在使得程序员的意图更加清晰的同时让编译器可以为我们发现一些错误，。







### 列表初始化

Uniform Initialization，无论是内置类型、用户定义类型、数组等各种类型都可以用同一种初始化方法。



auto关键字

基于范围的for循环（for each）

散列容器：unordered_map

nullptr关键字：nullptr是一种特殊类型的字面值，它可以被转换成任意其它的指针类型；而NULL一般被宏定义为0，在遇到重载时可能会出现问题。



**写一个字符串类的移动构造，拷贝构造，赋值构造并模拟这几个过程**