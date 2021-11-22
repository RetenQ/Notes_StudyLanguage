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

