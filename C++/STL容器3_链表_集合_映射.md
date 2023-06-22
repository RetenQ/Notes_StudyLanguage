# 链表_集合_映射    

## List 

### 基本概念
链表是一种物理存储单元上非连、续非顺序的储存结构，数据元素的逻辑顺序是通过链表中的指针链接次序实现的    
List由结点构成，而结点包括数据和下一个结点的信息，结点是在运行时动态生成的  

> 它的好处是每次插入或者删除一个元素，就是配置或者释放一个元素的空间;因此，list对于空间的运用有绝对的精准，一点也不浪费;而且，list对于任何位置插入或删除元素都是常数项时间  

在C++中，List是一个双向链表，灵活，但是空间和时间的额外消耗会比较大 
list不仅仅是一个双向链表，而且是一个循环的双向链表  

### 迭代器    
首先是迭代器方面：  
> ist 迭代器必须有能力指向list的结点，并有能力进行正确的递增、递减、取值、成员存取操作;由于list是一个双向链表，迭代器必须能够具备前移、后移的能力，所以list容器提供的是Bidirectional Iterators，双向迭代器;同时，list 有一个重要的性质，插入和删除操作都不会造成原有list迭代器的失效（这一点和vector不同，vector在进行插入的时候可能会造成内存的重新配置，导致原有的迭代器全部失效）    

```c++
// 顺序遍历 
for(list<T>::iterator it = lst.begin(); it != lst.end(); it++)
{
    cout << *it << endl;
}

// 逆序遍历 
for(list<T>::reverse_iterator it = lst.rbegin(); it != lst.rend(); it++)
{
    cout << *it << endl;
}

```
### 常用API 
构造函数：  
```c++
list<T> lstT; // 默认构造形式，list采用模版类实现
list(beg, end); // 构造函数将[beg, end)区间内的元素拷贝给本身
list(int n, T elem); // 构造函数将n个elem拷贝给本身
list(const list& lst); // 拷贝构造函数
``` 

插入和删除操作：    
```c++
void push_back(T elem); // 在容器尾部加入一个元素
void pop_back(); // 删除容器中最后一个元素

void push_front(T elem); // 在容器开头插入一个元素
void pop_front(); // 从容器开头移除第一个元素

insert(iterator pos, elem); // 在pos位置插入elem元素的拷贝，返回新数据的位置
insert(iterator pos, n, elem); // 在pos位置插入n个elem元素的拷贝，无返回值
insert(iterator pos, beg, end); // 在pos位置插入[beg, end)区间内的数据，无返回值

void clear(); // 移除容器的所有数据

erase(beg, end); // 删除[beg, end)区间内的所有数据，返回下一个数据的位置
erase(pos); // 删除pos位置的数据，返回下一个数据的位置

remove(elem); // 删除容器中所有与elem匹配的元素
```

大小操作和赋值操作：    
```c++
int size(); // 返回容器中元素的个数
bool empty(); // 判断容器是否为空

void resize(int num);
// 重新制定容器的长度为num，若容器变长，则以默认值填充新位置；
// 若容器变短，则末尾超出容器长度的元素被删除
void resize(int num, T elem);
// 重新制定容器的长度为num，若容器变长，则以elem填充新位置；
// 若容器变短，则末尾超出容器长度的元素被删除
``` 

其它操作：  
```c++
// 存取 
T& front(); // 返回第一个元素
T& back(); // 返回最后一个元素

// 反转排序：   
void reverse(); // 反转链表

void sort(); // 默认list排序，规则为从小到大
void sort(bool (*cmp)(T item1, T item2)); // 指定排序规则的list排序

// 不能用sort(lst.begin(), lst.end())
// 因为所有系统提供的某些算法（比如排序），其迭代器必须支持随机访问
// 不支持随机访问的迭代器的容器，容器本身会对应提供相应的算法的接口
```

## Set / Multiset   

### 基本概念和特性  
set的特性是，所有的容器都会根据元素自身的键值进行自动被排序，不像map那样可以同时拥有实值和键值，set的元素既是实值又是键值   

对于内部的数值，set不允许两个元素具有相同数值，也不允许通过其迭代器改变set元素的数值    
> 换句话说，set的iterator是一种const_iterator   

multiset特性及用法和set完全相同，唯一的差别在于它允许键值重复;set和multiset的底层实现是红黑树，红黑树为平衡二叉树的一种     

### 基本操作：  
构造和赋值：    
```c++
set<T> st; // set 默认构造函数
multiset<T> mst; // multiset 默认构造函数
set(const set& st); // 拷贝构造函数

// === 
set& operator=(const set& st); // 重载等号操作符

swap(st); // 交换两个集合容器
``` 

大小操作和插入删除操作：    
```c++
// 大小操作：   
int size(); // 返回容器中元素的数目
bool empty(); // 判断容器是否为空

// 插入和删除操作   
pair<iterator, bool> insert(T elem); 
// 在容器中插入元素，返回插入位置的迭代器（不成功则返回end()）和是否插入成功
// 如果是multiset，则返回值只有iterator
clear(); // 清除所有元素
iterator erase(pos); // 删除pos迭代器所指的元素，返回下一个元素的迭代器
iterator erase(beg, end); // 删除区间[beg, end)内的所有元素，返回下一个元素的迭代器
erase(T elem); // 删除容器中值为elem的元素  

//利用仿函数 指定set容器的排序规则
class MyCompare
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

set<int, MyCompare> s;

//模版类也是可以有默认值的，第二个模版参数的默认值为less

// 同时，自定义的数据类型需要指出排序规则。当然，也可以通过重载小于操作符的方式指出 
``` 

查找操作:   
```c++
iterator find(T key); 
// 查找键key是否存在，若存在，返回该键的元素的迭代器；若不存在，返回set.end();
int count(T key);
// 查找键key的元素个数
iterator lower_bound(T keyElem);
// 返回第一个key>=keyElem元素的迭代器
iterator upper_bound(T keyElem);
// 返回第一个key>keyElem元素的迭代器
pair<iterator, iterator> equal_range(T keyElem);
// 返回容器中key与keyElem上相等的两个上下限迭代器

// 上述几个方法若不存在，返回值都是尾迭代器。
``` 


在C++的set中，使用find()方法得到一个迭代器后，可以通过解引用该迭代器来获取对应的数值。例如，如果你有一个名为myset的set，其中包含一些整数，你可以使用以下代码来查找值为5的元素并获取它的值
```c++
std::set<int> myset = {2, 4, 6, 8};
std::set<int>::iterator it = myset.find(5);
if (it != myset.end()) {
    std::cout << "Found " << *it << '\n';
} else {
    std::cout << "Not found\n";
}

```

对组的构造和使用：  
```c++
//构造
pair<T1, T2> p(k, v);
//另一种构造方式
pair<T1, T2> p = make_pair(k, v);
//使用
cout << p.first << p.second << endl;
```

## Map / Multimap   

### 基本概念    
map 的特性是，所有的元素都会根据元素的键值自动排序；    
map 的所有元素都是pair，同时拥有实值和键值；pair的第一元素被视为键值，第二元素被视为实值；  
map不允许两个元素有相同的键值； 
和set类似的原因，我们不能通过迭代器改变map的键值，但我们可以任意修改实值。就是可以通过迭代器来修改value，但是不能修改key    

map和multimap的操作类似，唯一的区别是multimap键值可重复；map和multimap都是以红黑树作为底层实现机制。    

### 基本操作    
遍历：  
```c++
for (map<T1, T2>::iterator it = m.begin(); it != m.end(); it++)
{
    cout << "key = " << it->first << " value = " << it->second << endl;
}
``` 

### 常用API：   
构造函数,赋值，大小操作：   
```c++
map<T1, T2> mapTT; // map默认构造函数
map(const map& mp); // 拷贝构造函数 

map& operator=(const map& mp); // 重载等号操作符
swap(mp); // 交换两个集合容器

int size(); // 返回容器中元素的数目
bool empty(); // 判断容器是否为空
``` 

插入，删除：    
```c++
pair<iterator, bool> insert(pair<T1, T2> p); // 通过pair的方式插入对象
/*
1. 参数部分可以用pair的构造函数创建匿名对象
2. 也可以使用make_pair创建pair对象
3. 还可以用map<T1, T2>::value_type(key, value)来实现
*/

T2& operator[](T1 key); // 通过下标的方式插入值
// 如果通过下标访问新的键却没有赋值，会自动用默认值填充 

// 另外，map指定排序规则的方式和set类似，都是利用functor在模版类型表的最后一个参数处指定    

// ========
void clear(); // 删除所有元素
iterator erase(iterator pos); // 删除pos迭代器所指的元素，返回下一个元素的迭代器
iterator erase(beg, end); // 删除区间[beg, end)内的所有元素，返回下一个元素的迭代器
erase(keyElem); // 删除容器中key为keyElem的对组 
```

查找操作:   
```c++
iterator find(T1 key); 
// 查找键key是否存在，若存在，返回该键的元素的迭代器；若不存在，返回map.end()
int count(T1 keyElem);
// 返回容器中key为keyElem的对组个数，对map来说只可能是0或1，对于multimap可能大于1

iterator lower_bound(T keyElem);
// 返回第一个key>=keyElem元素的迭代器
iterator upper_bound(T keyElem);
// 返回第一个key>keyElem元素的迭代器
pair<iterator, iterator> equal_range(T keyElem);
// 返回容器中key与keyElem上相等的两个上下限迭代器
```

# 容器小结  
vector 可以涵盖其他所有容器的功能，只不过实现特殊功能时效率没有其他容器高。但如果只是简单存储，vector效率是最高的。 
deque 相比于 vector 支持头端元素的快速增删。        
list 支持频繁的不确定位置元素的移除插入。   
set 会自动排序。    
map 是元素为键值对组并按键排序的set。   

vector 与 deque 的比较：
1.vector.at()比deque.at()的效率高；比如vector.at(0)是固定的，deque的开始位置是不固定的  
2.如果有大量释放操作的话，vector花的时间更少    
3.deque支持头部的快速插入与快速删除，这是deque的优点