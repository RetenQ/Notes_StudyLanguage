# 向量_队列_栈  

## Vector    
vector的数据安排及操作方式，与array非常相似，两者的唯一差别在于空间的运用的灵活性,array是静态空间，vector是动态空间并且配置空间的策略也考虑了运行成本，采用特定的扩展的策略   

### 迭代器遍历  
```c++
// 使用迭代器进行正序遍历   
for (vector<T>::iterator it = v.begin(); it != v.end(); it++)
{
    cout << *it << endl;
}
/**
 * 1. 迭代器的声明方式:  容器类型::迭代器类型
 * 2. 顺序首尾迭代器由begin()和end()方法生成
*/

// 使用迭代器逆序遍历   
for (vector<T>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
{
    cout << *it << endl;
}
/**
  * 1. 逆向迭代器不再是iterator，而是reverse_iterator
  * 2. 逆序首位迭代器由rbegin()和rend()方法生成
*/  
```

此外，介绍一种现场测试迭代器是否能随机访问的方法:   
```c++
iterator++；
iterator--；
//通过编译，至少是双向迭代器
  
iterator = iterator + 1；
//通过编译，则是随机访问迭代器
```

vector采用的数据结构非常简单，线性连续空间，它以两个迭代器```_Myfirst```和```_Mylast```分别指向配置得来的连续空间中已被使用的范围，并以迭代器```Myend```指向整块连续内存空间的尾端  

>所谓动态增加大小，并不是在原空间之后续接新空间（因为无法保证原空间之后尚有可配置的空间），而是一块更大的内存空间，然后将原数据拷贝新空间，并释放原空间。

>因此，对vector的任何操作，一旦引起空间的重新配置，指向原vector的所有迭代器就都失效了

### vector常用API操作   
构造函数：  
```c++
vector<T> v; // 采用模版类实现，默认构造函数
vector<T> v(T* v1.begin(), T* v1.end()); // 将v1[begin(), end())区间中的元素拷贝给本身
vector<T> v(int n, T elem); // 将n个elem拷贝给本身
vector<T> v(const vector<T> v1); // 拷贝构造函数

// 下面对于第二种构造方式给出一个特殊的例子：
int array[5] = {1, 2, 3, 4, 5};
vector<int> v(array, array + sizeof(array) / sizeof(int));
// 联系我们之前提到的vector迭代器本质上是指针就不难理解了   
```

赋值：  
```c++
assign(beg, end); // 将[beg, end)区间中的数据拷贝复制给本身
assign(n, elem); // 将n个elem拷贝给本身
vector& operator=(const vector& vec); // 重载赋值操作符

// 互换操作也可视为一种特殊的赋值：
swap(vec); //将vec与本身的元素互换

// 巧用swap来收缩空间：
vector<int>(v).swap(v);
// vector<int>(v): 利用拷贝构造函数初始化匿名对象
// swap(v): 交换的本质其实只是互换指向内存的指针
// 匿名对象指针指向的内存会由系统自动释放
```

大小操作系列：  
```c++
int size(); // 返回容器中的元素个数
bool empty(); // 判断容器是否为空

void resize(int num); 
// 重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
// 若容器变短，则末尾超出容器长度的元素被删除
void resize(int num, T elem); 
// 重新指定容器的长度为num，若容器变长，则以elem填充新位置。
// 若容器变短，则末尾超出容器长度的元素被删除

int capacity(); // 返回容器的容量
void reserve(int len); 
// 容器预留len个元素长度，预留位置不初始化，元素不可访问
``` 

数据存取操作：  
```c++
T& at(int idx); // 返回索引idx所指的数据，如果idx越界，抛出out_of_range异常
T& operator[](int idx); // 返回索引idx所指的数据，如果idx越界，运行直接报错

T& front(); // 返回首元素的引用
T& back(); // 返回尾元素的引用
```

插入和删除操作：
```c++
insert(const_iterator pos, T elem); // 在pos位置处插入元素elem
insert(const_iterator pos, int n, T elem); // 在pos位置插入n个元素elem
insert(pos, beg, end); // 将[beg, end)区间内的元素插到位置pos
push_back(T elem); // 尾部插入元素elem
pop_back(); // 删除最后一个元素

erase(const_iterator start, const_iterator end); // 删除区间[start, end)内的元素
erase(const_iterator pos); // 删除位置pos的元素

clear(); // 删除容器中的所有元素

// 
std::vector<std::wstring> v2(3, L"c");   
v2.insert(v2.begin()+4, L"3");   //在指定位置，例如在第五个元素前插入一个元素
 
v2.insert(v2.end(), L"3");   //在末尾插入一个元素
 
v2.push_back(L"9");   //在末尾插入一个元素
 
v2.insert(v2.begin(), L"3");   //在开头插入一个元素
```

## Deque , Queue
vector 容器是单向开口的连续内存空间，deque 则是一种双向开口的连续线性空间   
二者的主要差异体现在：  
deque 允许使用常数项时间在头部插入或删除元素    
deque 没有容量的概念，因为它是由动态的分段连续空间组合而成，随时可以增加一块新的空间并链接起来  

### Deque 
遍历：  
```c++  
#include <deque>
using namespace std;

const deque<T> d;
for (deque<T>::const_iterator it = d.begin(); it != d.end(); it++) 
// 要用const_iterator指向常量容器
{
  	// 如果在此处修改it指向空间的值，编译器会报错
  	cout << *it << endl;
}

/**
  * iterator 普通迭代器
  * reverse_iterator 反转迭代器
  * const_iteratoe 只读迭代器
*/
``` 

常用API：   
构造函数：  
```c++
deque<T> deqT; // 默认构造函数
deque(beg, end); // 构造函数将[beg, end)区间中的元素拷贝给本身
deque(int n, T elem); // 构造函数将n个elem拷贝给本身
deque(const deque& deq); // 拷贝构造函数
```

赋值操作：
```c++
assign(beg, end); // 将[beg, end)区间中的元素拷贝赋值给本身
assign(int n, T elem); // 将n个元素elem拷贝赋值给本身

deque& operator=(const deque& deq); // 重载赋值操作符

swap(deq); // 将deq与本身的元素互换
```

大小操作：  
```c++
int size(); // 返回容器中元素的个数
bool empty(); // 判断容器是否为空

void resize(int num); 
// 重新指定容器的长度为num，若容器变长，则以默认值填充新位置，
// 如果容器变短，则末尾超出容器长度的元素被删除
void resize(int num, T elem);
// 重新指定容器的长度为num，若容器变长，则以elem填充新位置，
// 如果容器变短，则末尾超出容器长度的元素被删除
``` 

插入和删除,存读：    
```c++
push_back(T elem); // 在容器尾部添加一个元素
push_front(T elem); // 在容器头部插入一个元素

pop_back(); // 删除容器最后一个数据
pop_front(); // 删除容器第一个数据

const_iterator insert(const_iterator pos, T elem); 
// 在pos位置处插入元素elem的拷贝，返回新数据的位置
void insert(const_iterator pos, int n, T elem); 
// 在pos位置插入n个元素elem，无返回值
void insert(pos, beg, end);
// 将[beg, end)区间内的元素插到位置pos，无返回值

clear(); // 移除容器的所有数据
iterator erase(iterator beg, iterator end);
// 删除区间[beg, end)的数据，返回下一个数据的位置
iterator erase(iterator pos)；
// 删除pos位置的数据，返回下一个数据的位置

T& at(int idx); // 返回索引idx所指的数据，如果idx越界，抛出out_of_range异常
T& operator[](int idx); // 返回索引idx所指的数据，如果idx越界，运行直接报错

T& front(); // 返回首元素的引用
T& back(); // 返回尾元素的引用
```

### Queue   
queue 是一种先进先出(First In First Out, FIFO)的数据结构，它有两个出口，queue容器允许从一端新增元素，从另一端移除元素   

queue 没有迭代器:   
只有queue的顶端元素，才有机会被外界去用。queue不提供遍历功能，也不提供迭代器    

常用API：   
```c++
// 构造函数 
queue<T> queT; // queue对象的默认构造函数形式，采用模版类实现
queue(const queue& que); // 拷贝构造函数

// 存取，插入，删除 
void push(T elem); // 往队尾添加元素
void pop(); // 从队头移除第一个元素
T& back(); // 返回最后一个元素
T& front(); // 返回第一个元素

// 赋值 
queue& operator=(const queue& que); // 重载赋值操作符   

// 大小操作 
bool empty(); // 判断队列是否为空
int size(); // 返回队列的大小
```

## Stack    
### 基本概念    
stack 是一种**先进后出（First In Last Out, FILO）**的数据结构，它只有一个出口。 
stack 容器允许新增元素、移除元素、取得栈顶元素，但是除了最顶端外，没有任何其他方法可以存取stack的其他元素。换言之，stack不允许有遍历行为   

常用API：   
```c++
stack<T> stkT; // 默认构造函数，stack采用模版类实现
stack(const stack& stk); // 拷贝构造函数    

stack& operator=(const stack& stk); // 重载赋值操作符   

void push(T elem); // 向栈顶添加元素
void pop(); // 从栈顶移除第一个元素
T& top(); // 返回栈顶元素   

bool empty(); // 判断堆栈是否为空
int size(); // 返回栈的大小
```