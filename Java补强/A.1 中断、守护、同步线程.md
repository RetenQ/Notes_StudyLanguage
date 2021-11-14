# 中断线程  

如果线程需要执行一个长时间任务，就可能需要能中断线程    

中断线程就是其他线程给该线程发一个信号，该线程收到信号后结束执行run()方法   

> 我们举个栗子：假设从网络下载一个100M的文件，如果网速很慢，用户等得不耐烦，就可能在下载过程中点“取消”，这时，程序就需要中断下载线程的执行  

### 执行interruot()    
中断一个线程非常简单，只需要在其他线程中对目标线程调用```interrupt()```方法 
> 目标线程需要反复检测自身状态是否是interrupted状态，如果是，就立刻结束运行 

我们可以通过示例代码来了解并把它和暂停(sleep),中断(interrupt),等待结束(join)对比    

```Java
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Thread t = new MyThread();
        t.start();
        Thread.sleep(1); // 暂停1毫秒
        t.interrupt(); // 中断t线程
        t.join(); // 等待t线程结束
        System.out.println("end");
    }
}

class MyThread extends Thread {
    public void run() {
        int n = 0;
        while (! isInterrupted()) {
            n ++;
            System.out.println(n + " hello!");
        }
    }
}
```
要注意，interrupt()方法**仅仅向t线程发出了“中断请求”**，至于t线程**是否能立刻响应**，要看具体代码   
在这里，我们t线程的```while循环```会检测```isInterrupted()```，所以它可以正确响应interrupt()请求    

> 如果线程处于等待状态，例如，t.join()会让main线程进入等待状态，此时，如果对main线程调用interrupt()，join()方法会立刻抛出InterruptedException，因此，目标线程只要捕获到join()方法抛出的InterruptedException，就说明有其他线程对其调用了interrupt()方法，通常情况下该线程应该立刻结束运行    

我们可以再看一段示例代码
```Java
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Thread t = new MyThread();
        t.start();
        Thread.sleep(1000);
        t.interrupt(); // 中断t线程
        t.join(); // 等待t线程结束
        System.out.println("end");
    }
}

class MyThread extends Thread {
    public void run() {
        Thread hello = new HelloThread();
        hello.start(); // 启动hello线程
        try {
            hello.join(); // 等待hello线程结束
        } catch (InterruptedException e) {
            System.out.println("interrupted!");
        }
        hello.interrupt();
    }
}

class HelloThread extends Thread {
    public void run() {
        int n = 0;
        while (!isInterrupted()) {
            n++;
            System.out.println(n + " hello!");
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                break;
            }
        }
    }
}
```

### running标志位   
另一个常用的中断线程的方法是设置标志位。    
我们通常会用一个running标志位来标识线程是否应该继续运行 

在外部线程中，通过把xxxThread.running设置为false，就可以让线程结束  

```Java
public class Main {
    public static void main(String[] args)  throws InterruptedException {
        HelloThread t = new HelloThread();
        t.start();
        Thread.sleep(1);
        t.running = false; // 标志位置为false
    }
}

class HelloThread extends Thread {
    public volatile boolean running = true;
    public void run() {
        int n = 0;
        while (running) {
            n ++;
            System.out.println(n + " hello!");
        }
        System.out.println("end!");
    }
}

```

这里我们注意到了```volatile```关键字    
它是一个线程间共享的变量的标记，当我们的某个变量(这里就是running)需要在线程间共享时，就需要用到这个关键字     

> 为什么要对线程间共享的变量用关键字volatile声明？这涉及到Java的内存模型。在Java虚拟机中，变量的值保存在主内存中，但是，当线程访问变量时，它会先获取一个副本，并保存在自己的工作内存中。如果线程修改了变量的值，虚拟机会在某个时刻把修改后的值回写到主内存，但是，这个时间是不确定! 

因此，volatile关键字的目的是告诉虚拟机：
    每次访问变量时，总是获取主内存的最新值；
    每次修改变量后，立刻回写到主内存。

换言之，volatile关键字解决的是**可见性问题**：当一个线程修改了某个共享变量的值，其他线程能够**立刻看到修改后的值**  

