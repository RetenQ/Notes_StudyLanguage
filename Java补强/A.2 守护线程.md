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