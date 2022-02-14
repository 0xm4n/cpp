
## What is a process?
The process is basically a program that is currently under execution. It contains the program code and its activity.

## What is thread?
A thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler. A thread is a component of a process. The multiple threads of a given process may be executed concurrently, sharing resources such as memory, while different processes do not share these resources.

Not shared: pc, register, stack, thread id
shared: address space, heap, data section, code section, file descriptor

## multi-thread vs multi-process
Contrast Dimensions | Multi-Process | Multi-Threaded 
--- | --- | ---
Execution | It allows you to execute multiple processes concurrently. | Multiple threads of a single process are executed concurrently.
CPU switching | In Multiprocessing, CPU has to switch between multiple programs so that it looks like that multiple programs are running simultaneously. | In multithreading, CPU has to switch between multiple threads to make it appear that all threads are running simultaneously.
Memory | Multiprocessing allocates separate memory and resources for each process or program. | Multithreading threads belonging to the same process share the same memory and resources as that of the process.
Data sharing | Complex data sharing requires IPC| Because process data is shared, data sharing is simple
Synchronization | Data is separate and easy to synchronize |process data is shared, synchronization is complicated
Creation | The creation of a process is slow and resource-specific. | The creation of a thread is economical in time and resource.
Programming, debugging | simple programming, simple debugging | complex programming, complex debugging 
Reliability | Processes will not affect each other | Hanging a thread will cause the entire process to hang

##### Pros and cons

Pros and cons | multi-process | multi-threaded
--- | --- | ---
Advantages | Simple programming and debugging, high reliability | Fast creation, destruction, switching, small memory and resource occupation
Disadvantages | Creating, destroying, slow switching, large memory and resource occupation | Complex programming and debugging, poor reliability


## How does a process access memory?
1. dissect the virtual address into a virtual page number, and the page offset. The offset bits are not translated and passed through to the physical memory address.
2. TLB hits: The MMU now immediately knows what physical memory page to access without the need to look into the global memory.
3. TLB miss: The TLB needs to consult the page table in system’s global memory to understand what physical page number is used. If the TLB is full and a TLB miss occurs, the least recent TLB entry is flushed, and the new entry is placed instead of it.
4. Page fault: If data is not residing in memory but on storage media (flash or disk). MMU will trigger to get data from storage media


## Read a file from disk
Assume that we want to simply open a file "/foo/bar"
When you issue an open("/foo/bar", O RDONLY) call, the file system first needs to find the inode for the file bar, to obtain some basic information about the file (permissions information, file size, etc.). To do so, the file system must be able to find the inode, but all it has right now is the full pathname. The file system must traverse the pathname and thus locate the desired inode.
All traversals begin at the root of the file system, in the root directory which is simply called /. The root inode number is “well known”. In most UNIX file systems, the root inode number is 2.
The root inode contains the contents of the root directory. The FS will look for an entry for foo. Once found, the FS will also have found the inode number of foo. The next step is to recursively traverse the pathname until the desired inode is found.
The final step of open() is to read bar’s inode into memory; the FS then does a final permissions check, allocates a file descriptor for this process in the per-process open-file table, and returns it to the user.
Once open, the program can then issue a read() system call to read from the file.

## How does a process communicate over network?
1. create a socket
int sockfd = socket(domain, type, protocol)
Function socket() creates a socket and returns a descriptor which can be used in other functions.
2. Bind socket to a port
The bind function can be used to bind a socket to a particular "address and port" combination. It needs a sockaddr_in structure similar to connect function.
3. Listen for incoming connections on the socket.
After binding a socket to a port the next thing we need to do is listen for connections. For this we need to put the socket in listening mode. Function listen is used to put the socket in listening mode.
4. Accept a connection
Using accept() function to extract the first connection request on the queue of pending connections for the listening socket. At this point, connection is established between client and server, and they are ready to transfer data.

## kernel
Kernel is central component of an operating system. It manages operations of memory and CPU time. A kernel connects the application software to the hardware of a computer. Kernel loads first into memory when an operating system is loaded and remains into memory until operating system is shut down again. It is responsible for various tasks such as disk management, task management, and memory management.

## kernel space vs user space
An operating system will segregate memory into user space and kernel space. This separation serves to provide memory protection and hardware protection from malicious or errant software behaviour. Kernel space is strictly reserved for running a privileged operating system kernel, kernel extensions, and most device drivers. In contrast, user space is the memory area where application software and some drivers execute.

ref: https://unix.stackexchange.com/questions/87625/what-is-difference-between-user-space-and-kernel-space

## kernel mode vs user mode
In any modern operating system, the CPU is actually spending time in two very distinct modes:
1. Kernel Mode
In Kernel mode, the executing code has complete and unrestricted access to the underlying hardware. It can execute any CPU instruction and reference any memory address. Kernel mode is generally reserved for the lowest-level, most trusted functions of the operating system. Crashes in kernel mode are catastrophic; they will halt the entire PC.
2. User Mode
In User mode, the executing code has no ability to directly access hardware or reference memory. Code running in user mode must delegate to system APIs to access hardware or memory. Due to the protection afforded by this sort of isolation, crashes in user mode are always recoverable. Most of the code running on your computer will execute in user mode.

ref: https://blog.codinghorror.com/understanding-user-and-kernel-mode/

## Protection ring

## device driver
a device driver is a computer program that operates or controls a particular type of device that is attached to a computer. A driver provides a software interface to hardware devices, enabling operating systems and other computer programs to access hardware functions without needing to know precise details about the hardware being used.

## kernel mode driver vs user mode driver
Run in Kernel mode for maximum performance
Run in User mode, for maximum stability

Device drivers can run in either user or kernel mode. Most drivers are shunted to the User side of the fence these days, with the notable exception of video card drivers, which need bare-knuckle Kernel mode performance. User mode is clearly a net public good, but it comes at a cost. Transitioning between User and Kernel mode is expensive. Really expensive.

ref: https://blog.codinghorror.com/understanding-user-and-kernel-mode/

## interrupt
an interrupt (sometimes referred to as a trap) is a request for the processor to interrupt currently executing code (when permitted), so that the event can be processed in a timely manner. If the request is accepted, the processor will suspend its current activities, save its state, and execute a function called an interrupt handler (or an interrupt service routine, ISR) to deal with the event. This interruption is often temporary, allowing the software to resume normal activities after the interrupt handler finishes, although the interrupt could instead indicate a fatal error.

ref: https://en.wikipedia.org/wiki/Interrupt

## synchronization



## semaphore
a semaphore is a variable used to control access to a common resource by multiple threads and avoid critical section problems in a concurrent system. 
A semaphore restricts the number of simultaneous users of a shared resource up to a maximum number. Threads can request access to the resource (decrementing the semaphore), and can signal that they have finished using the resource (incrementing the semaphore).

How does semaphore work?
Counting semaphores are equipped with two operations, historically denoted as P and V. Operation V increments the semaphore S, and operation P decrements it.
The value of the semaphore S is the number of units of the resource that are currently available. The P operation wastes time or sleeps until a resource protected by the semaphore becomes available, at which time the resource is immediately claimed. The V operation is the inverse: it makes a resource available again after the process has finished using it. One important property of semaphore S is that its value cannot be changed except by using the V and P operations.

## mutex
Mutexes are typically used to serialise access to a section of re-entrant code that cannot be executed concurrently by more than one thread. A mutex object only allows one thread into a controlled section, forcing other threads which attempt to gain access to that section to wait until the first thread has exited from that section.

## mutex vs semaphore
A mutex can be released only by the thread that had acquired it.
A binary semaphore can be signaled by any thread (or process).

mutexes allow serialization of access to a given resource i.e. multiple threads wait for a lock, one at a time and as previously said, the thread owns the lock until it is done: only this particular thread can unlock it.
a binary semaphore is a counter with value 0 and 1: a task blocking on it until any task does a sem_post. The semaphore advertises that a resource is available, and it provides the mechanism to wait until it is signaled as being available.

ref: https://stackoverflow.com/questions/62814/difference-between-binary-semaphore-and-mutex

## reader-writer lock

## spin lock

## condition

## deadlock

## critical section

## racing condition

## cache coherence vs memory consistency
