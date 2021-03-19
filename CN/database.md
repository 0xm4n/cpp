### 索引是什么，为什么需要索引

索引通俗来讲就相当于书的目录，当我们根据条件查询的时候，没有索引，便需要全表扫描，数据量少还可以，一旦数据量超过百万甚至千万，一条查询sql执行往往需要几十秒甚至更多，5秒以上就已经让人难以忍受了。

多层索引减少IO次数

https://www.cnblogs.com/Renyi-Fan/p/10556274.html



### 索引底层数据结构

B树：

1. m/2 upper bound children(M阶代表一个树节点最多有多少个查找路径，M=M路,当M=2则是2叉树,M=3则是3叉)
2. root can have min 2 children
3. all leaf at same level
4. bottom up creation

B+树：

B树中每个节点（包括叶节点和非叶节点）都存储真实的数据，B+树中只有叶子节点存储真实的数据，非叶节点只存储键。

B+树的叶节点之间通过双向链表链接。

B+优势：

更少的IO次数：B+树的非叶节点只包含键，而不包含真实数据，因此每个节点存储的记录个数比B树多很多（即阶m更大），因此B+树的高度更低，访问时所需要的IO次数更少。此外，由于每个节点存储的记录数更多，所以对访问局部性原理的利用更好，缓存命中率更高。

更适于范围查询：在B树中进行范围查询时，首先找到要查找的下限，然后对B树进行中序遍历，直到找到查找的上限；而B+树的范围查询，只需要对链表进行遍历即可。

更稳定的查询效率：B树的查询时间复杂度在1到树高之间(分别对应记录在根节点和叶节点)，而B+树的查询复杂度则稳定为树高，因为所有数据都在叶节点。

B+树也存在劣势：由于键会重复出现，因此会占用更多的空间。但是与带来的性能优势相比，空间劣势往往可以接受，因此B+树的在数据库中的使用比B树更加广泛。

https://zhuanlan.zhihu.com/p/84493668



### 索引的类型

1）主键索引：主键索引是加在主键上的索引，设置主键（primary key）的时候，mysql会自动创建主键索引；

2）普通索引：创建在非主键列上的索引；

3）聚合索引：创建在多列上的索引。



### 索引语法

查看某张表的索引：SHOW INDEX FROM 表名；

创建普通索引：ALTER TABLE 表名 ADD INDEX  索引名 (加索引的列) 

创建聚合索引：ALTER TABLE 表名 ADD INDEX 索引名 (加索引的列1,加索引的列2) 

删除某张表的索引：DROP INDEX `索引名 ON 表名;`



### 索引加越多越好吗

1. 数据量小的表不需要建立索引,建立会增加额外的索引开销；
2. 数据变更需要维护索引,因此更多的索引意味着更多的维护成本；
3. 更多的索引意味着也需要更多的空间（索引也是需要空间来存放的）；



### 索引为什么不用红黑树

红黑树并不追求严格的平衡，而是大致的平衡：只是确保从根到叶子的最长的可能路径不多于最短的可能路径的两倍长。

对于数据在内存中的情况（如上述的TreeMap和HashMap），红黑树的表现是非常优异的。但是对于数据在磁盘等辅助存储设备中的情况（如MySQL等数据库），红黑树并不擅长，因为红黑树长得还是太高了。当数据在磁盘中时，磁盘IO会成为最大的性能瓶颈，设计的目标应该是尽量减少IO次数；而树的高度越高，增删改查所需要的IO次数也越多，会严重影响性能。



### InnoDB和MyISAM的区别

1. InnoDB 支持事务，MyISAM 不支持事务。
2. InnoDB 支持外键，而 MyISAM 不支持
3. InnoDB 是聚集索引，MyISAM 是非聚集索引。聚簇索引的文件存放在主键索引的叶子节点上，因此 InnoDB 必须要有主键，通过主键索引效率很高。但是辅助索引需要两次查询，先查询到主键，然后再通过主键查询到数据。因此，主键不应该过大，因为主键太大，其他索引也都会很大。而 MyISAM 是非聚集索引，数据文件是分离的，索引保存的是数据文件的指针。主键索引和辅助索引是独立的。
4. InnoDB 不保存表的具体行数，执行 select count(*) from table 时需要全表扫描。而MyISAM 用一个变量保存了整个表的行数，执行上述语句时只需要读出该变量即可，速度很快；
5. InnoDB 最小的锁粒度是行锁，MyISAM 最小的锁粒度是表锁。一个更新语句会锁住整张表，导致其他查询和更新都会被阻塞，因此并发访问受限。这也是 MySQL 将默认存储引擎从 MyISAM 变成 InnoDB 的重要原因之一；

https://blog.csdn.net/helloxiaozhe/article/details/88601028

### InnoDB和MyISAM的底层存储结构

**MyISAM：**每个MyISAM在磁盘上存储成三个文件。分别为：**表定义文件、数据文件、索引文件。**第一个文件的名字以表的名字开始，扩展名指出文件类型。.frm文件存储表定义。数据文件的扩展名为.MYD (MYData)。索引文件的扩展名是.MYI (MYIndex)。

**InnoDB：**所有的表都保存在同一个数据文件中（也可能是多个文件，或者是独立的表空间文件），InnoDB表的大小只受限于操作系统文件的大小，一般为2GB。



### 脏读，不可重复读，幻读

脏读：当一个事务允许读取另外一个事务修改但未提交的数据时，就可能发生dirty reads。

不可重复读：在一次事务中，当一行数据获取两遍得到不同的结果表示发生了non-repeatable reads.

幻读：在事务执行过程中，当两个完全相同的查询语句执行得到不同的结果集。这种现象称为phantom read



### 事务隔离级别

1. **Read Uncommitted –** Read Uncommitted is the lowest isolation level. In this level, one transaction may read not yet committed changes made by other transaction, thereby allowing dirty reads. In this level, transactions are not isolated from each other.
2. **Read Committed –** This isolation level guarantees that any data read is committed at the moment it is read. Thus it does not allows dirty read. The transaction holds a read or write lock on the current row, and thus prevent other transactions from reading, updating or deleting it.
3. **Repeatable Read –** This is the most restrictive isolation level. The transaction holds read locks on all rows it references and writes locks on all rows it inserts, updates, or deletes. Since other transaction cannot read, update or delete these rows, consequently it avoids non-repeatable read.
4. **Serializable –** This is the Highest isolation level. A *serializable* execution is guaranteed to be serializable. Serializable execution is defined to be an execution of operations in which concurrently executing transactions appears to be serially executing.





### MySQL注意事项

批量更新，如洗数据，避开高峰期，并通知运维team，直接执行sql的需要由运维同事操作

命名规范

所有表要加注释

 所有表都必须要显式指定主键

禁止使用外键

使用timestamp存储时间

单表索引个数限制

https://www.jianshu.com/p/a6958236a9b6



### 为什么数据库要有外键, 为什么不用外键, 不用外键如何处理

外键建立和加强两个表数据之间的链接的一列或多列

实践中不要用外键,外键会降低性能

通过程序控制外键关联



### 为什么外键会影响性能

1.数据库需要维护外键的内部管理；
2.外键等于把数据的一致性事务实现，全部交给数据库服务器完成；
3.有了外键，当做一些涉及外键字段的增，删，更新操作之后，需要触发相关操作去检查，而不得不消耗资源；
4.外键还会因为需要请求对其他表内部加锁而容易出现死锁情况；



数据库分表、分区？读写分离？







冷热数据怎么处理？

讲一下redis和mysql怎么保证数据一致性？

redis了解吗？有哪几种数据类型？

k-v存储 

