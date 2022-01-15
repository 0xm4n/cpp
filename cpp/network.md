### TCP/IP四层模型

应用层->传输层->网络层->数据链路层

数据链路层：MAC VLAN

网络层:IP ARP ICMP

传输层:TCP UDP

应用层:HTTP DNS SMTP



### OSI七层模型

应用层->表示层->会话层->传输层->网络层->数据链路层->物理层



### TCP三次握手 Three-way handshake

1. Client将标志位SYN置为1，随机产生一个值SEQ=x，并将该数据包发送给Server

2. Server收到数据包后，Server将标志位SYN和ACK都置为1，Acknowledgement Number=x+1，随机产生一个值SEQ=y，并将该数据包发送给Client以确认连接请求。

3. Client收到确认后，检查Acknowledgement Number是否为x+1。如果正确则将标志位ACK置为1，Acknowledgement Number=y+1，并将该数据包发送给Server。

   Steps 1 and 2 establish and acknowledge the sequence number for one direction. Steps 2 and 3 establish and acknowledge the sequence number for the other direction.

   ![Geoff Huston - potaroo.net](https://www.potaroo.net/ispcol/2004-07/fig1.jpg)



### TCP四次挥手 Four-way handshake

1.第一次挥手(FIN=1，seq=x)

客户端发送一个 FIN 标志位置为1的包，表示自己已经没有数据可以发送了，但是仍然可以接受数据。发送完毕后，客户端进入 `FIN_WAIT_1` 状态。

2.第二次挥手(ACK=1，ACKnum=x+1)

服务器端确认客户端的 FIN 包，发送一个确认包，表明自己接受到了客户端关闭连接的请求，但还没有准备好关闭连接。发送完毕后，服务器端进入 `CLOSE_WAIT` 状态，客户端接收到这个确认包之后，进入 `FIN_WAIT_2` 状态，等待服务器端关闭连接。

3.第三次挥手(FIN=1，seq=y)

服务器端准备好关闭连接时，向客户端发送结束连接请求，FIN 置为1。发送完毕后，服务器端进入 `LAST_ACK` 状态，等待来自客户端的最后一个ACK。

4.第四次挥手(ACK=1，ACKnum=y+1)

客户端接收到来自服务器端的关闭请求，发送一个确认包，并进入 `TIME_WAIT`状态，等待可能出现的要求重传的 ACK 包。服务器端接收到这个确认包之后，关闭连接，进入 `CLOSED` 状态。

客户端等待了某个固定时间（两个最大段生命周期，2MSL，2 Maximum Segment Lifetime）之后，没有收到服务器端的 ACK ，认为服务器端已经正常关闭连接，于是自己也关闭连接，进入 `CLOSED` 状态。



### TIME_WAIT为了解决什么问题

第四次挥手中ACK丢包



### TCP状态转移

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f6/Tcp_state_diagram_fixed_new.svg/1280px-Tcp_state_diagram_fixed_new.svg.png)



### 出现大量CLOSE_WAIT的原因

如果一直保持在CLOSE_WAIT状态，那么只有一种情况，就是在对方关闭连接之后服务器程序自己没有进一步发出ack信号。换句话说，就是在对方连接关闭之后，程序里没有检测到，或者程序压根就忘记了这个时候需要关闭连接，于是这个资源就一直被程序占着。这种情况通过服务器内核参数也没办法解决，服务器对于程序抢占的资源没有主动回收的权利，除非终止程序运行。



### 出现大量TIME_WAIT的原因

在高并发短连接的TCP服务器上，当服务器处理完请求后立刻按照主动正常关闭连接。这个场景下，会出现大量socket处于TIMEWAIT状态。如果客户端的并发量持续很高，此时部分客户端就会显示连接不上。

如何解决: 如果端口忙，但TCP连接位于TIME_WAIT状态时可以重用端口。



### 为什么TIME_WAIT状态需要经过2MSL才能返回到CLOSE状态？

网络是不可靠的，有可以最后一个ACK丢失。所以TIME_WAIT状态就是用来重发可能丢失的ACK报文。在Client发送出最后的ACK回复，但该ACK可能丢失。Server如果没有收到ACK，将不断重复发送FIN片段。所以Client不能立即关闭，它必须确认Server接收到了该ACK。Client会在发送出ACK之后进入到TIME_WAIT状态。Client会设置一个计时器，等待2MSL的时间。如果在该时间内再次收到FIN，那么Client会重发ACK并再次等待2MSL。所谓的2MSL是两倍的MSL(Maximum Segment Lifetime)。MSL指一个片段在网络中最大的存活时间，2MSL就是一个发送和一个回复所需的最大时间。如果直到2MSL，Client都没有再次收到FIN，那么Client推断ACK已经被成功接收，则结束TCP连接。



### TCP如何保证可靠性 Reliable transmission

序列号：标识每个数据字节，接收者可识别某一序列号的丢失，可以通过序列号确认包的顺序，可以清除重复的数据包。

确认应答：当接收者收到数据后，都会对传输方进行确认应答，发送ACK报文。ACK报文带有对应的确认序列号，告诉发送方，接收到了哪些数据，下一次的数据从哪里发。

校验和：将发送的数据段都当做16位的整数加起来。将前面的进位补在最后面相加，最后取反，得到校验和。发送方计算检验和，并进行校验和的填充。接收方收到数据后，对数据以同样的方式进行计算，求出校验和，与发送方的进行比对。如果接收方比对校验和与发送方不一致，那么数据一定传输有误。但是如果接收 方比对校验和与发送方一致，**数据不一定传输成功。**

超时重传：发送方在发送数据后等待一段时间，如果超时后仍未接收到ACK报文，则重新发送刚才发送的数据。接收方如果已经接受到该段数据那么直接丢弃，并再次发送ACK应答。

流量控制：

拥塞控制



### TCP流量控制

如果发送者发送数据过快，接收者来不及接收，那么就会有分组丢失。为了避免分组丢失，控制发送者的发送速度，使得接收者来得及接收，这就是流量控制。流量控制根本目的是防止分组丢失，它是构成TCP可靠性的一方面。

由滑动窗口协议（连续ARQ协议）实现。滑动窗口协议既保证了分组无差错、有序接收，也实现了流量控制。主要的方式就是接收方返回的 ACK 中会包含自己的接收窗口的大小，并且利用大小来控制发送方的数据发送。



### 拥塞控制和流量控制的区别

拥塞控制：拥塞控制是作用于网络的，它是防止过多的数据注入到网络中，避免出现网络负载过大的情况；常用的方法就是：（ 1 ）慢开始、拥塞避免（ 2 ）快重传、快恢复。

流量控制：流量控制是作用于接收者的，它是控制发送者的发送速度从而使接收者来得及接收，防止分组丢失的。



### TCP拥塞控制



### TCP应用场景

SMTP: 保证邮件内容完整

HTTP

FTP：保证文件数据完整

SSH



### TCP与UDP区别 

1. TCP面向连接 ; UDP是无连接的，即发送数据之前不需要建立连接
2. TCP提供可靠的服务;UDP尽最大努力交付，即不保证可靠交付
3. UDP具有较好的实时性，工作效率比TCP高，
4. 每一条TCP连接只能是点到点的;UDP支持一对一，一对多，多对一和多对多的交互通信
5. TCP对系统资源要求较多，UDP对系统资源要求较少。
   



### UDP如何保证可靠传输

传输层无法保证数据的可靠传输，只能通过应用层来实现了。实现的方式可以参照tcp可靠性传输的方式，只是实现不在传输层，实现转移到了应用层。在应用层模仿传输层TCP的可靠性传输

发送端发送数据时，生成一个随机seq=x，然后每一片按照数据大小分配seq。数据到达接收端后接收端放入缓存，并发送一个ack=x的包，表示对方已经收到了数据。发送端收到了ack包后，删除缓冲区对应的数据。时间到后，定时任务检查是否需要重传数据。



### UDP应用场景

you want the answer to be in one response packet, and you are prepared to implement your own protocol for reliability or to resend. DNS is the perfect description of this use case. The costs of connection setups are way too high (yet, DNS does support a TCP mode as well).

Another case is when you are delivering data that can be lost because newer data coming in will replace that previous data/state. Weather data, video streaming, a stock quotation service (not used for actual trading), or gaming data comes to mind.



### ARP协议

主机A广播：谁是IPxxx，我的mac是aaa。主机B应答：我是IPxxx，我的mac是bbb



### 交换机在哪一层，路由器在哪一层

交换机在数据链路层，内网通信只需要交换机

路由器在网络层，当需要连接互联网是需要路由器



### 浏览器输入网址到显示页面的过程



### Ping原理，在哪一层

网络层，发送方发送一个ICMP包，接收者收到应答

https://www.jianshu.com/p/14113212cd18



### TCP为什么初始化序列号要随机取，从0开始会出现什么问题



### TCP确认机制，每个包都需要确认吗

TCP提供的确认机制，可以在通信过程中可以不对每一个TCP数据包发出单独的确认包（Delayed ACK机制），而是在传送数据时，顺便把确认信息传出， 这样可以大大提高网络的利用率和传输效率。同时，TCP的确认机制，也可以一次确认多个数据报，例如，接收方收到了201，301，401的数据报，则只 需要对401的数据包进行确认即可，对401的数据包的确认也意味着401之前的所有数据包都已经确认，这样也可以提高系统的效率。



TCP中有一个包丢了怎么重发，接收端失序的包放在哪里



如果接收缓冲区满了，发送端怎么操作，会报错吗



### 通信双方如果出现宕机的情况，那么会有什么样的机制处理这种情况？

### 如何判断机器字节序

```cpp
#include <stdio.h>
 
union test
{
    short val;
    char array[2];
};
 
int main()
{
    union test t;
    t.val = 0x0102;
 
    if(t.array[0] == 1 && t.array[1] == 2)
    {
        printf("big endian!\n");
    }
    else if(t.array[0] == 2 && t.array[1] == 1)
    {
        printf("little endian!\n");
    }
 
    return 0;
}
```

https://blog.csdn.net/weixin_42720316/article/details/81275768



DNS解析过程以及DNS劫持

NAT

IPv4和IPv6的区别



### 为什么IP层负责分片

https://www.zhihu.com/question/22181709‘

如果有一个包1M，怎么分片



HTTP的加密方式，MD5，RSA，DES加密有啥区别

 https会不会出现中间人攻击

http可以复用同一个TCP连接吗

HTTP2.0与HTTP1.0和HTTP1.1的区别，有什么优势

 服务端怎么解析http请求

 服务端怎么同时处理多个请求

 对称加密与非对称加密原理