### 负载均衡算法

1. 轮询法
2. 随机法
3. 源地址哈希
4. 加权轮询
5. 加权随机法

平时有看开源社区的习惯吗，有了解过什么开源架构吗



单例模式如果有两个线程都创建单例对象怎么做

单例模式中双检索如果变成一次会有什么影响？

单例模式对成员变量操作要注意什么

设计模式了解哪些？（针对回答）

随便选一种介绍 





如何调试代码？代码中出现问题你会如何定位？

有看过开源库的[源码](https://www.nowcoder.com/jump/super-jump/word?word=源码)吗，像STL等的

### 常用的设计模式

单例模式：构造函数private；private static变量持有唯一实例，保证全局唯一；通过public static方法返回唯一实例

工厂模式：



### 单例模式

- 保证一个类只有一个实例，并且提供一个访问该全局访问点

- Windows的（任务管理器）就是很典型的单例模式，他不能打开俩个

  https://juejin.cn/post/6844904125721772039

```cpp
// 懒汉式单例模式
class Singleton
{
private:
	Singleton() { }
	static Singleton * pInstance;
public:
	static Singleton * GetInstance()
	{
		if (pInstance == nullptr)
			pInstance = new Singleton();
		return pInstance;
	}
};

// 线程安全的单例模式
class Singleton
{
private:
	Singleton() { }
	~Singleton() { }
	Singleton(const Singleton &);
	Singleton & operator = (const Singleton &);
public:
	static Singleton & GetInstance()
	{
		static Singleton instance;
		return instance;
	}
};
```



### 适配器模式

将一个类的接口转换成客户希望的另外一个接口。适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。好比日本现在就只提供110V的电压，而我的电脑就需要220V的电压，那怎么办啦？适配器就是干这活的，在不兼容的东西之间搭建一座桥梁，让二者能很好的兼容在一起工作。

https://blog.csdn.net/chenxun_2010/article/details/48383571



### 工厂模式

工厂模式的主要作用是封装对象的创建，分离对象的创建和操作过程，用于批量管理对象的创建过程，便于程序的维护和扩展。

###  GDB

设置断点: 设置程序运行到某一行，通过“文件名:行号”的形式：b test.cpp:100

查看断点：info b

查看断点：info b

n即next，单步执行，执行下一步的意思，遇到函数会调用函数。

s即step，也是单步执行，但是会进入函数内部，然后结合n命令来调试函数。

p即print，打印变量，最常用的命令。p可以打印普通变量、std::string字符串、指针、数组等。