# 多线程    

### 介绍
CPU执行代码都是一条一条顺序执行的，但是，即使是单核cpu，也可以同时运行多个任务。因为操作系统执行多任务实际上就是让CPU对多个任务轮流交替执行     

即使是多核CPU，因为通常任务的数量远远多于CPU的核数，所以任务也是交替执行的  

进程和线程的关系就是：一个进程可以包含一个或多个线程，但至少会有一个线程。  

多线程编程的特点在于：多线程经常需要读写共享数据，并且需要同步；    
Java多线程编程的特点又在于：    
多线程模型是Java程序最基本的并发模型      
后续读写网络、数据库、Web开发等都依赖Java多线程模型     

### 创建新线程  
要创建一个新线程非常容易，我们需要实例化一个```Thread```实例，然后调用它的```start()```方法 
代码例子:
```Java
public class Main{
    public static void main(String[] args){
        Thread t = new Thread();
        t.start();
        //启动了一个新线程
    }
}
```

### 使用新线程  
我们希望新线程能执行指定的代码，有以下几种方法：    

1.从```Thread```中派生一个自定义类，然后覆写```run()```方法:    

```Java
public class Main {
    public static void main(String[] args) {
        Thread t = new MyThread();
        t.start(); // 启动新线程
    }
}

class MyThread extends Thread{
    @Override 
    public void run(){
        System.out.println("start new thread!");
    }
}

``` 

2.创建```Thread```实例时，传入一个```Runnable```实例：  

```Java
public class Main {
    public static void main(String[] args) {
        Thread t = new Thread(new MyRunnable());
        t.start(); // 启动新线程
    }
}

class MyRunnable implements Runnable{
    @Override 
    public void run(){
        System.out.printlng("start new thread");
    }
}
```

该部分还可以利用lambda语法简写为:
```Java
public class Main{
    public static void main(String[] args){
        Thread t = new Thread(() -> {
            System.out.pirntlb("strart new thread");
        });

        t.start();
    }
}
```

**注意**，直接调用Thread的方法是没有用的————这和一般的调用方法是没有区别的：    
```Java
public class Main {
    public static void main(String[] args) {
        Thread t = new MyThread();
        t.run();
    }
}

class MyThread extends Thread {
    public void run() {
        System.out.println("hello");
    }
}
``` 

注意，在这里我们使用了```t.run();```，事实上和**并不是**多线程。我们**必须调用Thread实例的start()方法才能启动新线程**       

#### Thread.sleep()
我们可以在线程中调用```Thread.sleep()```来强迫线程暂停一段时间  
```sleep()```传入的参数是**毫秒**

#### 线程优先级 
可以对线程设定优先级，设定优先级的方法是：
```Thread.setPriority(int n)```,n的取值为1~10,默认值是n=5   

优先级高的线程被操作系统调度的优先级较高，操作系统对高优先级线程可能调度更频繁，但我们决不能通过设置优先级来确保高优先级的线程一定会先执行  

### 线程状态
在Java程序中，一个线程对象只能调用一次start()方法启动新线程，并在新线程中执行run()方法。一旦run()方法执行完毕，线程就结束了 
在Java的线程中，有以下几种状态: 
New：新创建的线程，尚未执行；   
Runnable：运行中的线程，正在执行run()方法的Java代码；   
Blocked：运行中的线程，因为某些操作被阻塞而挂起；   
Waiting：运行中的线程，因为某些操作在等待中；   
Timed Waiting：运行中的线程，因为执行sleep()方法正在计时等待；  
Terminated：线程已终止，因为run()方法执行完毕   

可以用下面这张图来概括:
![](https://i.loli.net/2021/11/14/sgGIibfue1r529C.png)  

> 当线程启动后，它可以在Runnable、Blocked、Waiting和Timed Waiting这几个状态之间切换，直到最后变成Terminated状态，线程终止   


### join()方法  
当main线程对线程对象t调用join()方法时，主线程将等待变量t表示的线程运行结束，即join就是指等待该线程结束，然后才继续往下执行自身线程  
> 简单来说，就是先进行新开的那个线程的任务，到该任务完成之后才执行main之后的任务    

比如我们运行代码:
```Java
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Thread t = new Thread(() -> {
            System.out.println("hello");
        });
        System.out.println("start");
        t.start();
        t.join();
        System.out.println("end");
    }
}
```
此时我们运行的顺序**一定是**先进行```main```中对start的打印，   
然后运行```t线程```，自然而然地执行t线程中的```System.out.println("hello");```  
等到这个任务执行完了之后再执行```System.out.println("end");```  

通过对另一个线程对象调用join()方法可以等待其执行结束；      

可以指定等待时间，超过等待时间线程仍然没有结束就不再等待；      

对已经运行结束的线程调用join()方法会立刻返回        

