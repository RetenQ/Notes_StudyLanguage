# 总述  
![序列容器选择流程图](https://3445412966-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F4jcp9JrFSUV0Enu5fcXK%2Fuploads%2FqNW2etPAgY5LHnAQdHcw%2F%E5%BA%8F%E5%88%97%E5%AE%B9%E5%99%A8.png?alt=media&token=66cbea42-14d0-4a4d-9f13-b6c733d3ff4f)


![容器适配器选择流程图](https://3445412966-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F4jcp9JrFSUV0Enu5fcXK%2Fuploads%2FIkWXvNJMNfxAsypAnqkX%2F%E5%AE%B9%E5%99%A8%E9%80%82%E9%85%8D%E5%99%A8.png?alt=media&token=3f4ea447-f239-47bf-af3c-a170fcb8b77f)  

## 字符串string  
C++ 在STL中定义了string来方便使用字符串 

string 封装了很多实用的成员方法,包括：查找find，拷贝copy，删除erase，替换replace，插入insert等  
同时string类不需要考虑内存释放和越界，本质上是一个动态的char数组    

### 基本操作    
首先是构造string    
```c++
string();
// 默认构造函数，创建一个空的字符串

string(const string& str);
// 拷贝构造函数，使用一个string对象初始化另一个string对象

string(const char* s);
// 含参构造函数，使用C风格字符串初始化

string(int n, char c);
// p含参构造函数，使用n个字符c初始化
``` 

string接受各种赋值方式，包括采用c风格，使用另一个string，使用字符赋值等等，可以直接使用```=```进行赋值  
同时，也可以使用```assign()```成员函数进行赋值，如：    
```c++
// string&表示该方法返回一个string对象  
string& assign(const char* s); 
// C风格字符串赋值给当前的字符串
string& assign(const char* s, int n); 
// 把C风格字符串s的前n个字符赋给当前的字符串
string& assign(const string& s); 
// 把字符串s赋给当前字符串
string& assign(int n, char c); 
// 把n个字符c赋给当前的字符串
string& assign(const string& s, int start, int n); 
// 将字符串s中从start开始的n个字符赋值给当前字符串
``` 

我们知道，string是由char组成的。和C类似，可以使用```[n]```来获取操作符，使用下标操作符获取字符时，如果下标越界，程序将会强制终止    
亦可以使用```at```还是来获取字符
使用at方法获取字符时，如果下标越界，at方法内部会抛出异常（exception），可以使用try-catch捕获并处理该异常。示例如下：
```c++
#include <stdexception> 
//标准异常头文件
#incldue <iostream>
using namespace std;

int main()
{
    string s = "hello world";
    try
    {
        //s[100]不会抛出异常，程序会直接挂掉
        s.at(100);
    }
    catch (out_of_range& e) 
        //如果不熟悉异常类型，可以使用多态特性， catch(exception& e)。
    {
        cout << e.what() << endl; 
        //打印异常信息
    }
    return 0;
}
```

string同样提供了两种办法来进行字符串拼接，首先是```+=```:   
```c++
string& operator+=(const string& str); 
// 将字符串str追加到当前字符串末尾
string& operator+=(const char* str); 
// 将C风格字符数组追加到当前字符串末尾
string& operator+=(const char c); 
// 将字符c追加到当前字符串末尾
/* 上述操作重载了复合操作符+= */
```

也可以使用```append()```方法进行拼接：  
```c++
string& append(const char* s); 
// 把C风格字符数组s连接到当前字符串结尾
string& append(const char* s, int n); 
// 把C风格字符数组s的前n个字符连接到当前字符串结尾
string& append(const string &s); 
// 将字符串s追加到当前字符串末尾
string& append(const string&s, int pos, int n); 
// 把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c); 
// 在当前字符串结尾添加n个字符c
```

### 对字符串操作    
首先是查找和替换功能    
使用```find()```方法来进行查找,查找包括字符串查找和字符查找 
find默认查找第一次出现的位置，可以指定范围：    
```c++
int find(const string& str, int pos = 0) const; 
// 查找str在当前字符串中第一次出现的位置，从pos开始查找，pos默认为0
int find(const char* s, int n = 0) const; 
// 查找C风格字符串s在当前字符串中第一次出现的位置，从pos开始查找，pos默认为0
int find(const char* s, int pos, int n) const; 
// 从pos位置查找s的前n个字符在当前字符串中第一次出现的位置
int find(const char c, int pos = 0) const; 
// 查找字符c第一次出现的位置，从pos开始查找，pos默认为0


//当查找失败时，find方法会返回-1，-1已经被封装为string的静态成员常量string::npos。
static const size_t nops = -1;
```

使用```rfind()```来查找某个字符最后一次出现的位置，使用方法类似find：   
```c++
int rfind(const string& str, int pos = npos) const; 
// 从pos开始向左查找最后一次出现的位置，pos默认为npos
int rfind(const char* s, int pos = npos) const; 
// 查找s最后一次出现的位置，从pos开始向左查找，pos默认为npos
int rfind(const char* s, int pos, int n) const; 
// 从pos开始向左查找s的前n个字符最后一次出现的位置
int rfind(const char c, int pos = npos) const; 
// 查找字符c最后一次出现的位置
```

> find方法通常查找字串第一次出现的位置，而rfind方法通常查找字串最后一次出现的位置。rfind(str, pos)的实际的开始位置是pos + str.size()，即从该位置开始（不包括该位置字符）向前寻找匹配项，如果有则返回字符串位置，如果没有返回string::npos。-1其实是size_t类的最大值（学过补码的同学应该不难理解），所以string::npos还可以表示“直到字符串结束”，可以以此来理解rfind中pos的默认参数。  

使用```replace()```方法来进行替换： 
```c++
string& replace(int pos, int n, const string& str); 
// 替换从pos开始n个字符为字符串s
string& replace(int pos, int n, const char* s);
// 替换从pos开始的n个字符为字符串s
```

对于string的相互比较，使用```compare()```方法，compare函数依据字典序比较，在当前字符串比给定字符串小时返回-1，在当前字符串比给定字符串大时返回1，相等时返回0    
```c++
int compare(const string& s) const; // 与字符串s比较    
int compare(const char* s) const; // 与C风格字符数组比较    
```

更进一步的，string类重载了所以比较操作符，可以直接使用操作符进行比较的判断，含义同compare:  
```c++
bool operator<(const string& str) const;
bool operator<(const char* str) const;
bool operator<=(const string& str) const;
bool operator<=(const char* str) const;
bool operator==(const string& str) const;
bool operator==(const char* str) const;
bool operator>(const string& str) const;
bool operator>(const char* str) const;
bool operator>=(const string& str) const;
bool operator>=(const char* str) const;
bool operator!=(const string& str) const;
bool operator!=(const char* str) const;
```

使用```substr()```方法来得到子串：  
```c++
string substr(int pos = 0, int n = npos) const;
// 返回由pos开始的n个字符组成的字符串   
```

使用```insert()```来进行插入，使用```erase()```进行擦除：   
```c++
string& insert(int pos, const char* s); // 在pos位置插入C风格字符数组
string& insert(int pos, const string& str); // 在pos位置插入字符串str
string& insert(int pos, int n, char c); // 在pos位置插入n个字符c

// 返回值是插入后的字符串结果，erase同理。其实就是指向自身的一个引用。
string& erase(int pos, int n = npos); // 删除从pos位置开始的n个字符
```

### 其它    
有时候需要进行```string```和```c-Style string```的转化  
```c++
// string -> c style 
string str = "demo";
const char* cstr = str.c_str(); //使用c_str()方法

// c style -> string
const char* cstr = "demo";
string str(cstr); // 本质上其实是一个有参构造，见构造方法   

``` 
> 在c++中存在一个从```const char*```到```string```类的隐式类型转换，但却不存在从一个```string```对象到```const char*```的自动类型转换。对于```string```类型的字符串，可以通```过c_str()```方法返回```string```对象对应的```const char*``` 字符数组。比如说，当一个函数的参数是```string```时，我们可以传入```const char*```作为参数，编译器会自动将其转化为```string```，但这个过程不可逆。为了修改```string```字符串的内容，下标操作符```[]```和```at```都会返回字符串的引用，但当字符串的内存被重新分配之后，可能发生错误。（结合字符串的本质是动态字符数组的封装便不难理解了）   

以及有部分和string相关的全局函数:   
大小写转换:
单个字符：
```c++
#include <cctype>
// 在iostream中已经包含了这个头文件，如果没有包含iostream头文件，则需手动包含cctype

int tolower(int c); // 如果字符c是大写字母，则返回其小写形式，否则返回本身
int toupper(int c); // 如果字符c是小写字母，则返回其大写形式，否则返回本身

/**
  * C语言中字符就是整数，这两个函数是从C库沿袭过来的，保留了C的风格
*/
```
如果想要对整个字符串进行大小写转化，则需要使用一个for循环，或者配合和algorithm库来实现。例如    
```c++
#include <string>
#include <cctype>
#include <algorithm>

string str = "Hello, World!";
transform(str.begin(), str.end(), str.begin(), toupper); //字符串转大写
transform(str.begin(), str.end(), str.begin(), tolower); //字符串转小写
```

字符串和数字转化：  
```c++  
// ===========================
// 数转字符串   
// c++11标准新增了全局函数std::to_string，十分强大，可以将很多类型变成string类型    
#include <string>
using namespace std;

/** 带符号整数转换成字符串 */
string to_string(int val);
string to_string(long val);
string to_string(long long val);

/** 无符号整数转换成字符串 */
string to_string(unsigned val);
string to_string(unsigned long val);
string to_string(unsigned long long val);

/** 实数转换成字符串 */
string to_string(float val);
string to_string(double val);
string to_string(long double val);

// ===========================
// 字符串转数
#include <cstdlib>
#include <string>
using namespace std;

/** 字符串转带符号整数 */
int stoi(const string& str, size_t* idx = 0, int base = 10);
long stol(const string& str, size_t* idx = 0, int base = 10);
long long stoll(const string& str, size_t* idx = 0, int base = 10);

/**
  * 1. idx返回字符串中第一个非数字的位置，即数值部分的结束位置
  * 2. base为进制
  * 3. 该组函数会自动保留负号和自动去掉前导0
 */

/** 字符串转无符号整数 */
unsigned long stoul(const string& str, size_t* idx = 0, int base = 10);
unsigned long long stoull(const string& str, size_t* idx = 0, int base = 10);

/** 字符串转实数 */
float stof(const string& str, size_t* idx = 0);
double stod(const string& str, size_t* idx = 0);
long double stold(const string& str, size_t* idx = 0);
```


与之类似的在同一个库里的还有一组**基于字符数组**的函数如下：    
```c++
// 'a' means array, since it is array-based. 

int atoi(const char* str); // 'i' means  int
long atol(const char* str); // 'l' means long
long long atoll(const char* str); // 'll' means long long

double atof(const char* str); // 'f' means double
```