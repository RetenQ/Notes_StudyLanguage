## wait和notify

### 引入
在Java中,**synchronized**解决了多线程竞争的问题 
但是他并没有解决多线程协调的问题
比如，我在多个线程同时往队列中加任务，使用```synchronized```加锁    
```Java
class TaskQueue{
    Queue<String> queue = new LinkedList<>();

    public synchronized void addTask(String s) {
        this.queue.add(s);
    }
}
```

### 简介 
多线程协调运行的原则就是：当条件不满足时，线程进入等待状态；当条件满足时，线程被唤醒，继续执行任务  

比如我们想要执行以下效果：
线程1可以调用addTask()不断往队列中添加任务；
线程2可以调用getTask()从队列中获取任务。如果队列为空，则getTask()应该等待，直到队列中至少有一个任务时再返回 

```Java
class TaskQueue {
    Queue<String> queue = new LinkedList<>();

    public synchronized void addTask(String s) {
        this.queue.add(s);
    }

    public synchronized String getTask() {
        while (queue.isEmpty()) {
        }
        return queue.remove();
    }
}
```
事实上，因为while()再getTask()的入口得到了**this的锁**，因此其它线程无法调用addTask()————所以queue一直是空的，因此无法执行while，得到了一个死循环————这不是我们想要的

### 修改
于是我们对```getTask()```进行改造，当条件不满足的时候，线程会进入等待状态   
```Java
public synchronized String getTask(){
    while(queye.isEmpth()){
        this.wait();
    }

    return queue.remove();
}
```

> 这个问题的关键就在于wait()方法的执行机制非常复杂。首先，它不是一个普通的Java方法，而是定义在Object类的一个native方法，也就是由JVM的C代码实现的。其次，必须在synchronized块中才能调用wait()方法，因为wait()方法调用时，会释放线程获得的锁，wait()方法返回后，线程又会重新试图获得锁

重点: **wait()方法调用时，会释放线程获得的锁，wait()方法返回后，线程又会重新试图获得锁**    

因此，只能在锁对象上调用wait()方法。因为在getTask()中，我们获得了this锁，因此，只能在this对象上调用wait()方法   

**当一个线程在this.wait()等待时，它就会释放this锁，从而使得其他线程能够在addTask()方法获得this锁**  

### 第二个问题：notify
那么，如果让处于等待状态的线程被重新唤醒，然后从wait()方法中返回呢？于是就需要使用```notify()```方法    

```Java
public synchronized void addTask(String s){
    this.queue.add(s);
    this.notify();
}
```
对相同的锁对象上调用notify(),使得对应对象被唤醒 
> 到在往队列中添加了任务后，线程立刻对this锁对象调用notify()方法，这个方法会唤醒一个正在this锁等待的线程（就是在getTask()中位于this.wait()的线程），从而使得等待线程从this.wait()方法返回

#### 多锁,notify和notifyAll
当有多个处于this锁等待唤醒的线程中，如果我们：
使用notifyAll() ， 将唤醒所有当前正在this锁等待的线程   
使用notify() ， 只会唤醒其中一个（具体哪个依赖操作系统，有一定的随机性）    
> 通常来说，这种情况下 ， notifyAll()更安全。有些时候，如果我们的代码逻辑考虑不周，用notify()会导致只唤醒了一个线程，而其他线程可能永远等待下去醒不过来了

### 小结
```wait```和```notify```用于多线程协调运行
再```synchronized```内部可以调用```wait()```使线程进入等待状态  
必须在**已经获得**的锁的对象调用```wait()```方法    
在```synchronized```内部可以调用```notify()```或```notifyAll()```唤醒其它等待的线程 
必须在已获得的锁对象上调用```notify()```或```notifyAll()```方法 
已唤醒的线程还需要重新获得锁之后才能继续运行    

## ReentrantLock
从Java 5开始，引入了一个高级的处理并发的java.util.concurrent包，它提供了大量更高级的并发功能，能大大简化多线程程序的编写。

我们知道Java语言直接提供了synchronized关键字用于加锁，但这种锁一是很重，二是获取时必须一直等待，没有额外的尝试机制。

java.util.concurrent.locks包提供的ReentrantLock用于替代synchronized加锁

### 介绍
对于同一种实现，我们用```synchronized```可以写作：
```Java
public class Counter{
    private int count  ;

    public void add(int n){
        synchronized(this){
            count += n ;
        }
    }
}
```

如果使用**ReentrantLock**,则可以写为：
```Java
public class Counter {
    private final Lock = new ReentrantLock();
    private int count ;

    public void add(int n){
        lock.lock();

        try{
            count += n ;
        }finally{
            lock.unlock();
        }
    }
}
```

因为synchronized是Java语言层面提供的语法，所以我们不需要考虑异常，而ReentrantLock是Java代码实现的锁，我们就必须先获取锁，然后在finally中正确释放锁  

另外，```ReentrantLock```可重入锁，它和synchronized一样，一个线程可以多次获取同一个锁   

和synchronized不同的是，ReentrantLock可以尝试获取锁 
```Java
if(lock.tryLock(1,TimeUnit.SECONDS)){
    try{
        ...
    }finally{
        lock.unlock();
    }
}
```
上述代码在尝试获取锁的时候，最多等待1秒。如果1秒后仍未获取到锁，tryLock()返回false，程序就可以做一些额外处理，而不是无限等待下去    

### 小结
ReentrantLock可以替代synchronized进行同步；

ReentrantLock获取锁更安全；

必须先获取到锁，再进入try {...}代码块，最后使用finally保证释放锁；

可以使用tryLock()尝试获取锁 
