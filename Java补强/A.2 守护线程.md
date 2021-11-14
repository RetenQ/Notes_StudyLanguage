# 守护线程与同步线程

## 守护线程

Java程序入口就是由JVM启动main线程，main线程又可以启动其他线程。当所有线程都运行结束时，JVM退出，进程结束。

如果有一个线程没有退出，JVM进程就不会退出。所以，必须保证所有线程都能及时结束。

### 介绍 
但是有一种线程的目的就是无限循环，例如，一个定时触发任务的线程  
```Java
class TimerThread extends Thread {
    @Override
    public void run() {
        while (true) {
            System.out.println(LocalTime.now());
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                break;
            }
        }
    }
}
```
如果这个线程不结束，JVM进程就无法结束

现在问题来了，谁来“负责”这个进程————换言之，谁来决定它何时结束，又何时开始  
答案是使用**守护线程 Daemon Thread**    

### 使用    
> 守护线程是指为其他线程服务的线程。在JVM中，所有非守护线程都执行完毕后，无论有没有守护线程，虚拟机都会自动退出。因此，JVM退出时，不必关心守护线程是否已结束    

创建守护线程的方法和创建普通线程一样：只是在调用start之前，我们使用```setDaemon(true)```把该线程**标记**为守护线程  

```Java
Thread t = new MyThread();
t.setDaemon(true);
t.start();
```

在守护线程中，编写代码要注意：守护线程不能持有任何需要关闭的资源，例如打开文件等，因为虚拟机退出时，守护线程没有任何机会来关闭文件，这会导致数据丢失

### 小结
一般情况而言，JVM总是要等**所有线程都运行完毕**之后再退出，但是有一些线程本身就是想**无限循环**的(比如计数器、时钟等等) 
而我们常没有一个线程来控制它们，总是仍由它们自己运行。但是————JVM的停机又需要它们停止   
因此有了“即使它们不停下，JVM也能停机”的守护线程。JVM不需要等他们都退出，就能停机。因此守护线程很适合那些“无限循环执行”的线程    

## 线程同步 
当多个线程同时运行时，线程的调度由操作系统决定，程序本身无法决定。因此，任何一个线程都有可能在任何指令处被操作系统暂停，然后在某个时间段后继续执行  

这个时候，有个问题就来了：如果多个线程同时读写共享变量，**会出现数据不一致的问题**  

### 比如...
```Java
public class Main {
    public static void main(String[] args) throws Exception {
        var add = new AddThread();
        var dec = new DecThread();
        add.start();
        dec.start();
        add.join();
        dec.join();
        System.out.println(Counter.count);
    }
}

class Counter {
    public static int count = 0;
}

class AddThread extends Thread {
    public void run() {
        for (int i=0; i<10000; i++) { Counter.count += 1; }
    }
}

class DecThread extends Thread {
    public void run() {
        for (int i=0; i<10000; i++) { Counter.count -= 1; }
    }
}
```

### 原子方式与锁

多线程模型下，要保证逻辑正确，对共享变量进行读写时，必须保证一组指令以**原子方式**执行：即某一个线程执行时，其他线程必须等待    

通过加锁和解锁的操作，就能保证3条指令总是在一个线程执行期间，不会有其他线程会进入此指令区间 

> 即使在执行期线程被操作系统中断执行，其他线程也会因为无法获得锁导致无法进入此指令区    

这种加锁和解锁之间的代码块我们称之为**临界区（Critical Section）**  

> 任何时候临界区最多只有一个线程能执行  

可见，保证一段代码的原子性就是通过加锁和解锁实现的

#### 执行锁
Java程序使用```synchronized关键字```对一个对象进行加锁：
```Java
synchronized(lock) {
    n = n + 1;
}
```
此时，我们就保证了代码块再任意时刻，**只有一个线程**在执行它    

> 在使用synchronized的时候，不必担心抛出异常。因为无论是否有异常，都会在synchronized结束处正确释放锁    

另外，我们应该**时刻注意锁的对象**，因为JVM只保证“同一个锁任意时刻只能被一个线程获取”，也就是说，两个不同的锁在同一时刻可以被两个线程同时获取

> 换言之，你锁的对象错了，逻辑就错了，错的区块也有问题。于是就和没锁一样了...   

不过使用不同的锁也有好处，一些对象可以在自身被锁的同时，而“互不干扰”地同时执行。这样的并发可以提高效率  

#### 不需要synchronized的操作   
JVM规范已经定义了几种原子操作：
基本类型（long和double除外）赋值，例如：int n = m；     
引用类型赋值，例如：List<String> list = anotherList     

单条原子操作的语句是不需要同步的，而多行赋值语句则**必须保证是同步操作**    

### 同步方法    
让线程自己选择锁对象往往会使得代码逻辑混乱，也不利于封装。更好的方法是把synchronized逻辑封装起来    
比如我们写了下面这个计数器:
```Java
public class Counter {
    private int count = 0;

    public void add(int n) {
        synchronized(this) {
            count += n;
        }
    }

    public void dec(int n) {
        synchronized(this) {
            count -= n;
        }
    }

    public int get() {
        return count;
    }
}
``` 

使用它的优势在于：我们在线程中调用add()、dec()等方法的时候，就不用担心同步逻辑了    

因为```synchronized```的代码块在方法的内部，而且锁住的总是this(当前对象/实例)，使得我们创建多个Counter实例的时候，它们之间是互不影响的 

> 如果一个类被设计为允许多线程正确访问，我们就说这个类就是“线程安全”的（thread-safe），上面的Counter类就是线程安全的。Java标准库的java.lang.StringBuffer也是线程安全的。    

> 还有一些不变类，例如String，Integer，LocalDate，它们的所有成员变量都是final，多线程同时访问时只能读不能写，这些不变类也是线程安全的   

> 最后，类似Math这些只提供静态方法，没有成员变量的类，也是线程安全的    

## 死锁
Java的线程锁是可重入的锁    
简单来说，就是对于同一个线程，我们可以在获取到锁以后继续获取同一个锁    
> JVM允许同一个线程重复获取同一个锁，这种能被同一个线程反复获取的锁，就叫做可重入锁     
由于Java的线程锁是可重入锁，所以，获取锁的时候，不但要判断是否是第一次获取，还要记录这是第几次获取。每获取一次锁，记录+1，每退出synchronized块，记录-1，减到0的时候，才会真正释放锁。

### 介绍
那什么是死锁呢  

在获取多个锁的时候，**不同线程获取多个不同对象的锁**可能导致死锁    
而且，死锁发生后，没有任何机制能解除死锁，只能强制结束JVM进程   

举个例子:
```Java
public void add(int m) {
    synchronized(lockA) { // 获得lockA的锁
        this.value += m;
        synchronized(lockB) { // 获得lockB的锁
            this.another += m;
        } // 释放lockB的锁
    } // 释放lockA的锁
}

public void dec(int m) {
    synchronized(lockB) { // 获得lockB的锁
        this.another -= m;
        synchronized(lockA) { // 获得lockA的锁
            this.value -= m;
        } // 释放lockA的锁
    } // 释放lockB的锁
}
```

此时如果我们用线程1和线程2，分别执行```add()```和```dec()```两个方法，就会获得死锁：

因为线程1进入到add()，就会得到lockA;    
线程2进入到dec(),就会获得lockB

然后线程1要继续执行dec()，但是它被锁住了，那么只能等下去    
然而此时线程2也遇到同样的问题，所以就产生了死锁 

### 避免死锁    
线程获取锁的顺序要一致。即严格按照顺序获取。    
比如在上述例子中，我们要先获取lockA，再获取lockB的顺序  
则改写如下:
```Java
public void dec(int m) {
    synchronized(lockA) { // 获得lockA的锁
        this.value -= m;
        synchronized(lockB) { // 获得lockB的锁
            this.another -= m;
        } // 释放lockB的锁
    } // 释放lockA的锁
}
```