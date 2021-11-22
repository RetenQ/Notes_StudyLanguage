# wait和notify

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

