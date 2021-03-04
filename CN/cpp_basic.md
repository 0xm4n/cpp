### #define与inline区别

1.  define在预处理阶段完成；inline在编译阶段
2.  define没有参数类型，不做类型检查；inline函数要做类型安全检查
3.  define字符串替换；inline是代码替换，在编译过程中不单独产生代码，将代码嵌入调用处
4. define可能出现二义性；inline遵循类型和作用域规则，与一般函数更相近



### inline用太多有什么不好

1. 头文件过大，可读性变差
2. 对于代码函数较多的内联函数，内联将导致程序变慢. 可能使目标代码量增加，因为编译本身有指令缓存，代码优化的功能。



### const和define的区别

1. const在编译阶段使用；define在预编译阶段使用。 
2. const有数据类型，做安全检查；define无类型，不做安全检查。 
3. const可以调试；define不能调试。 
4. const占用一份内存；define不占用内存，但是会多处进行字符串替换



### volatile关键字

volatile 关键字是一种类型修饰符，用它声明的类型变量表示可能被某些编译器未知的因素更改。遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。多任务环境下各任务间共享的标志应该加volatile

在本次线程内, 当读取一个变量时，为提高存取速度，编译器优化时有时会先把变量读取到一个寄存器中；以后，再取变量值时，就直接从寄存器中取值；当变量值在本线程里改变时，会同时把变量的新值copy到该寄存器中，以便保持一致。当变量在因别的线程等而改变了值，该寄存器的值不会相应改变，从而造成应用程序读取的值和实际的变量值不一致。当该寄存器在因别的线程等而改变了值，原变量的值不会改变，从而造成应用程序读取的值和实际的变量值不一致。




###  volatile可以和const同时使用吗

例如，只读状态寄存器。两者不是反义词，const控制的时程序本身，volatile控制的是程序之外。

（1）本程序段中不能对a作修改，任何修改都是非法的，或者至少是粗心，编译器应该报错，防止这种粗心；
（2）另一个程序段则完全有可能修改，因此编译器最好不要做太激进的优化。



 ### 函数原型后面加const类型，const的作用是什么？

在类的成员函数中，const成员函数不改变类的数据成员，也就是说，这些函数是"只读"函数。如果把不改变数据成员的函数都加上const关键字进行标识，可提高程序的可读性。其实，它还能提高程序的可靠性，已定义成const的成员函数，一旦企图修改数据成员的值，则编译器按错误处理。 const成员函数和const对象 实际上，const成员函数还有另外一项作用，即常量对象相关。对于内置的数据类型，我们可以定义它们的常量，用户自定义的类也一样，可以定义它们的常量对象。

1. 只有非静态成员函数后面才能加const
2. const成员函数隐含传入的this指针为const指针，决定了在该成员函数中，任意修改它所在的类的成员的操作都是不允许的



### 可变参数传参原理 Variadic arguments

可变参函数至少需要一个参数。由于参数入栈是从右往左压栈的，由压栈时的栈指针可知参数地址的下界，而最后一个参数的地址可以确定参数的上界。得到参数列表在栈中的地址空间后，可以通过va_list 、va_start、va_arg、va_end等函数获取所有参数

http://www.downeyboy.com/2019/06/30/C_pass_param_and_principle/



### 多重for循环优化

1. 实例化变量放在for循环外，减少实例化次数，尽量只实例化一次
2. i++ 改为 ++i
3. 循环条件使用<要快于<=，>和>=同理;（错误！！！）https://stackoverflow.com/questions/12135518/is-faster-than
4. 把外层可以计算的尽可能放到外层，减少在内层的运算，有判断条件的语句和与循环不相关的操作语句尽量放在for外面；
5. 应当将最长的循环放在最内层，最短的循环放在最外层，以减少CPU跨切循环层的次数；
   采用的是行优先访问原则，与元素存储顺序一致。

https://blog.csdn.net/u011236602/article/details/81092504



### i++与++i的区别?

理论上++i是原地操作，效率更好，无需临时存储空间保存自增前的值。

现实中，如果作为单行语句使用，两者没有差别，编译器会自行优化。



### Int * ptr，int arr[]两者的区别？ 

sizeof(ptr) == 8 (the size of the pointer)

sizeof(arr)== the size of int * number of element in arr

https://www.geeksforgeeks.org/difference-pointer-array-c/



### 4种显式转换static_cast \ dynamic_cast \ const_cast \ reinterpret_cast，分别是在什么时候确定的（编译期，运行期）

https://blog.csdn.net/bzhxuexi/article/details/17021559

https://blog.csdn.net/libaineu2004/article/details/46329447

dynamic_cast：和static_cast不同，dynamic_cast涉及运行时的类型检查。如果向下转型是安全的（也就是说，如果基类指针或者引用确实指向一个派生类的对象），这个运算符会传回转型过的指针。如果向下转型不安全（即基类指针或者引用没有指向一个派生类的对象），这个运算符会传回空指针。就是说，类层次的向下转换（基类向派生类转换），转换过程中会通过RTTI检查转换类型是否正常，不正常将返回空。


### 

### 头文件循环引用问题，简单说一下

```cpp
// a.h
#pragma once
#include "b.h"
class A {
    B b;
};
```

```cpp
// b.h
#pragma once
#include "a.h"
class B {
	A a;
}
```

通过前置声明解决

https://blog.csdn.net/hazir/article/details/38600419?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-8.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-8.control



### 两个对象循环引用问题

多见于智能指针如shared_ptr   

如果两个对象A和B都持有对方的强引用，假若A对象需要释放，但是B对象持有强引用，不能释放，B也是如此，这就造成了两个对象的互相等待，永远得不到释放   

我们可以使用weak_ptr,weak_ptr只是获得对象的使用权，没有获得所有权，当对象A强引用B，B弱引用A，当A需要释放时，有余没有其他的对象引用它了，所以能够释放，B对象也没有其他对象引用，也可以释放



###  如何去使用结构体中未定义大小的数组

https://stackoverflow.com/questions/17250480/declaring-int-array-inside-struct

```c
struct Foo {
   int array_size;
   int* some_array;
};
struct Foo foo;
foo.some_array = (int*)malloc(sizeof(int) * foo.array_size);
free( foo.some_array );
```

