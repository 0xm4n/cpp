
## OSI Model
1. Physical Layer: It defines the means of transmitting raw bits over a physical data link. It converts data bits into electrical impulses or radio signals.
2. Data Link Layer: It transfers data between nodes on a network which physically connected with each other. It provides some means to detect and possibly correct errors that can occur in the physical layer.
3. Network Layer: It transfers packets from one node to another that connected in "different networks". It is responsible for packet forwarding including routing through intermediate routers. 
4. Transport Layer: This layer provides host-to-host communication services for applications to transfer data from a source to a destination host. It provides services such as connection-oriented communication, reliability, flow control.
5. Session Layer: It manages the connections between computers. It establishes, coordinates and terminates the connections between local and remote applications.
6. Presentation Layer: It transforms the data into the form in which the application layer accepts.
7. Application Layer: This layer provides functionalities for applications. Protocals define different data formats to present data for different usages. 

## TCP/IP (Internet protocol suite)
1. Link layer: 
   a) handles the physical act of sending and receiving data and defines how data should be sent
   b) responsible for transmitting data between two different nodes on the same link.
2. Internet layer: transfers packets from one node to another that connected in "different networks". It is responsible for packet forwarding including routing through intermediate routers. 
3. Transport layer: is responsible for providing a reliable connection between the source host and its destination. The transport layer then determines how much data must be sent, where it should be sent to, and at what rate. It ensures that data packets are sent without errors and in sequence and obtains the acknowledgment that the destination device has received the data packets.
4. Application layer: The application layer refers to programs that need TCP/IP to help them communicate with each other. This is the level that users typically interact with, such as email systems and messaging platforms. It combines the session, presentation, and application layers of the OSI model.

1

## HTTP
HTTP is HyperText Transfer Protocol. It helps the web browsers and web servers for communication and transmit the web content. It is a ‘stateless protocol’ where each command is independent with respect to the previous command. HTTP is an application layer protocol built upon the TCP. It uses port 80 by default.

## HTTPS
HTTPs is a Secure HTTP which used for secure communication over a computer network. HTTPs provides authentication of websites that prevents unwanted attacks.

## DNS
Domain Name System. It is considered as the directory of the Internet which translates the domain names to their corresponding IPs. For a human being, it is easy to remember and recognize the domain name, however, the computer does not understand the human language and they only understand IP addresses.
1. A user types ‘example.com’ into a web browser and the query travels into the Internet and is received by a DNS recursive resolver.
2. The resolver then queries a DNS root nameserver (.).
3. The root server then responds to the resolver with the address of a Top Level Domain (TLD) DNS server (such as .com or .net), which stores the information for its domains. When searching for example.com, our request is pointed toward the .com TLD.
4. The resolver then makes a request to the .com TLD.
5. The TLD server then responds with the IP address of the domain’s nameserver, example.com.
6. Lastly, the recursive resolver sends a query to the domain’s nameserver.
7. The IP address for example.com is then returned to the resolver from the nameserver.
8. The DNS resolver then responds to the web browser with the IP address of the domain requested initially.

## IPv4 address
An IP address is a 32-bit dynamic address of a node in the network. An IPv4 address has 4 octets of 8-bit each with each number with a value up to 255.


## Different classes of IPv4
Class A 8bits + 24bits
In the original address definition, the most significant eight bits of the 32-bit IPv4 address was the network number field which specified the particular network a host was attached to.

Expansion of the network had to ensure compatibility with the existing address space.The solution was to expand the definition of the network number field to include more bits, allowing more networks to be designated, each potentially having fewer hosts.

network id + host id
Class B 16bits + 16bits
Class C 24bits + 8bits

## CIDR
solution to classful address
prefix length define the network number, and the remaining is the host id

## NAT
NAT is Network Address Translation. This is a protocol that provides a way for multiple computers on a common network to share a single connection to the Internet.

When a device in a private network want to request some internet resource, it will first go to the gateway router. The router will use its ip address to request the resourse. The server will return the resource to the router. The router will send back the resource to the device by checking the routing table.

## TCP vs UDP

|TCP|UDP|
|-|-|
|Connection-Oriented Protocol - Uses three ways handshake model for connection|Connectionless Protocol - No handshake for establishing the connection|
|More Reliable - TCP is reliable as it guarantees delivery of data to the destination router. |Less Reliable - The delivery of data to the destination can’t be guaranteed in UDP.|
|Slower Transmission - TCP does error checking and also makes error recovery.|Faster Transmission - UDP is faster as error recovery is not attempted. UDP performs error checking, but it discards erroneous packets.|
|Packets order can be preserved or can be rearranged|Packets order is not fixed and packets are independent of each other|
|TCP packets are heavy-weight: Header size is 20 bytes. TCP needs three packets to set up a socket connection before any user data can be sent.|UDP is lightweight. The header size is 8 bytes. There are no tracking connections, ordering of messages, etc.|

## How router works?
When a router receives a packet, it searches its routing table to find the best match between the destination IP address of the packet and one of the addresses in the routing table. Once a match is found, the packet is encapsulated in the layer-2 data link frame for the outgoing interface indicated in the table entry.

The routing table contain information derived from a variety of sources, such as a default or static routes that are configured manually, or dynamic entries from routing protocols where the router learns routes from other routers. A default route is one that is used to route all traffic whose destination does not otherwise appear in the routing table; it is common – even necessary – in small networks, such as a home or small business where the default route simply sends all non-local traffic to the Internet service provider. The default route can be manually configured (as a static route); learned by dynamic routing protocols; or be obtained by DHCP.

## L3 vs L2 or router vs switch

|L3|L2|
|-|-|
|The network layer transfer packets from one node to another connected in "different networks".|This layer transfers data between nodes on a network segment. |

|Router|Switch|
|-|-|
|Routers operate at Layer 3|Network switches operate at layer two|
|Store IP address in the routing table. Router operations revolve around IP Addresses.|Store MAC address in a lookup table. Switches work with MAC addresses as it operates within the confines of a single network.|
|Router will offer NAT, NetFlow and QoS Services|Switch will not offer such services.|


## Multi-threaded sever
```
Accept();
pthread_create(handle_request, fd);

handle_request():
Receive the request
Open the file that was requested
Read the file that was requested
Write the http response header
Write the file that was requested

```
Each new thread created takes up a significant amount of memory and a slow connection can still mess up one of my threads. There is overhead to do the context switch from one thread to another and if you're going to create new thread that costs extra time.

## select
select() allows a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation.

On each call to select() or poll(), the kernel must check all of the specified file descriptors to see if they are ready. When monitoring a large number of file descriptors that are in a densely packed range, the timed required for this operation greatly outweights.

## poll
poll can perform better than select if you have a sparse set of file descriptors.

## epoll
epoll can monitor multiple file descriptors to see whether I/O is possible on any of them.
The epoll group of system calls (epoll_create, epoll_ctl, epoll_wait) give the Linux kernel a list of file descriptors to track and ask for updates about activity on those file descriptors.

int epoll_create1(int flags); Creates an epoll object and returns its file descriptor.

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event); Controls which file descriptors are watched by this object.

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); Waits for any of the events registered for with epoll_ctl, until at least one occurs or the timeout elapses.

edge-triggered mode: a call to epoll_wait will return only when a new event is enqueued with the epoll object.
level-triggered mode: epoll_wait will return as long as the condition holds.




## IP addresses

## BGP

## DHCP

## CIFS

## ARP