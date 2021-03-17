### vector中的扩容机制

2倍扩容和1.5倍扩容，时空平衡。如果扩容因子太小会导致频繁扩容，如果扩容因子太大可能会消耗过多不必要的内容。

\> I'd be intersted if any other vector implemenations uses a growth factor
\> other than 2, and I'd also like to know whether VC7 uses 1.5 or 2 (since I
\> don't have that compiler here).

There is a technical reason to prefer 1.5 to 2 -- more specifically, to
prefer values less than 1+sqrt(5)/2.

Suppose you are using a first-fit memory allocator, and you're progressively
appending to a vector. Then each time you reallocate, you allocate new
memory, copy the elements, then free the old memory. That leaves a gap, and
it would be nice to be able to use that memory eventually. If the vector
grows too rapidly, it will always be too big for the available memory.

It turns out that if the growth factor is >= 1+sqrt(5)/2, the new memory
will always be too big for the hole that has been left sofar; if it is
<1+sqrt(5)/2, the new memory will eventually fit. So 1.5 is small enough to
allow the memory to be recycled.



### N个数插入到 一个未初始化大小的vector，总的时间复杂度 

O(N + M) where N is the number of elements inserted and M is the number of the elements moved .



### 数组和链表的区别

访问速度

插入删除速度

内存灵活性





 Int 数组，获取数组大小和数组元素？/HanxiMap可以？ 

 队列存储数据是以一个什么样的形式？ 

deque的底部实现

二叉树的递归遍历有什么问题？(**回答可能会导致调用栈过深内存问题**)

 二叉树迭代遍历时用到了自定义栈，栈类型的特性，实现？（**回答先进后出，顺序表实现，线性表实现**）





### map和unordered_map的区别

内部实现机制不同：map-红黑树 unordered_map-hash table

是否排序：map-元素有序 unordered_map-无序

性能差别：查找、插入、map-O(logn) unordered_map-O(1)

占用空间：map-树状结构需要保存额外信息



### map的底层

map内部实现了一个红黑树，该结构具有自动排序的功能，因此map内部的所有元素都是**有序的**，红黑树的每一个节点都代表着map的一个元素，因此，对于map进行的查找，删除，添加等一系列的操作都相当于是对红黑树进行这样的操作，故红黑树的效率决定了map的效率。



说说STL的线程安全

### stl的组成

1. 容器：vector \ list \ stack \ queue \ deque \ priority_queue \ map \ set
2. 算法
3. 迭代器: 在 C++STL 中，对容器中数据的读和写，是通过迭代器完成的，扮演着容器和算法之间的胶合剂。



### 为什么需要迭代器

泛型编程里面，为了使得不同的容器能够使得相同的算法代码，需要抽象一个迭代器用来遍历容器中的元素，而无需考虑不同容器有着不同的遍历方式。例如vector可以通过指针算术运算获取下一个元素，而list需要通过next指针寻找下一个元素，通过迭代器可以抽象这些遍历的方式，形成统一的接口。



### stl用过什么

1. hash：讲哈希原理和冲突
2. map、set：讲红黑树
3. iterator：将为什么需要迭代器



### 哈希表原理

1. 散列：除法散列、乘法散列、全域散列
2. 解决冲突



### 哈希冲突怎么解决

1. 链接法 chaining
2. 开放寻址open addressing：线性探查、二次探查、双重散列



### 红黑树特点

1. 每个节点或者是黑色，或者是**红色**。
2. 根节点是黑色。
3. 每个叶子节点（NIL）是黑色。 [注意：这里叶子节点，是指为空(NIL或NULL)的叶子节点！]
4. 如果一个节点是**红色**的，则它的子节点必须是黑色的。
5. 从一个节点到该节点的子孙节点的所有路径上包含相同数目的**黑**节点。



### 红黑树怎么保持平衡

1. 插入节点的叔节点y是红色
2. 插入节点的叔节点y是黑色，插入节点是右子节点
3. 插入节点的叔节点y是黑色，插入节点是左子节点



### 红黑树查找的复杂度

O(logn)



### 红黑树有哪些应用

map 和 set





**C++vector插入和删除为什么会导致迭代器实效**

 在插入多查询少时使用哪种数据结构

 在插入和查询差不多的情况下选择哪种数据结构

 topK用什么排序解决

快排的时间复杂度，什么时候最坏，什么时候最好

红黑树和AVL树有什么区别，为什么C++的map要用红黑树