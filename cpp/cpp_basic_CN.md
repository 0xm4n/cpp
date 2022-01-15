### 类型

类型定义对象可能的取值与运算

### 对象

对象是用来保存一个指定类型值得一些内存单元

### 值

值是根据一个类型来解释得内存中的一组比特

### 声明

声明是命名一个对象的一条语句

### 定义

定义是一个声明，但同时也为对象分配了内存空间

### 表达式

表达式就是从一些操作数计算一个值

#### 变量与表达式

int x = 99;

int y = x;

赋值运算在左边和右边的含义是不同的，在左边时表示名为x的变量，在右边时表示变量的值。

#### literal constant & symbolic constant 字面常量 & 字符常量

the notion a symbolic constant, that is, a named object to which you can't give a new value after it has been initialized.

A literal constant or simply a literal, is a value, such as a number, character, or string that may be assigned to a variable or symbolic constant, used as an operand in an arithmetic or logical operation, or as a parameter to a function.

### switch

switch 语句括号中的值必须是int、char、或enum。特别地，不能使用string类型。如果需要使用string类型进行选择，那么需要用if或着map。case语句中的值必须是常量表达式，不能使用变量。允许在一条语句中加上多个case标记。

### 程序块

用{和}包围起来的语句序列称为程序块block或复合语句compound statement。程序块是一种特殊的语句。

### 函数

函数是一种具名的语句序列，能够返回计算结果。

### 函数体

函数体是实现某种具体功能的程序块。函数体是实现某种具体功能的程序块。

函数定义：返回值类型 + 函数名 + (参数表) + 函数体

函数名是函数的标记，括号内是参数表，函数体是实现函数功能的语句。参数表的每一个元素称为一个参数parameter或形式参数formal argument。

### 函数声明

函数声明将函数定义分离，仅显示函数的信息。如果你使用某个函数，可以在代码中声明或者通过#include包含该函数的函数原型，二函数的定义可以在程序的其他部分