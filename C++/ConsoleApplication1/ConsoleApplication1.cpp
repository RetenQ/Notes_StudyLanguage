// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void display(int x) { cout << ' ' << x; return; }
int main()
{
    vector<int> v; //创建容器对象v，元素类型为int
    int x;
    cin >> x;
    while (x > 0) //生成容器v中的元素
    {
        v.push_back(x); //往容器v中增加一个元素
        cin >> x;
    }
    //利用算法max_element计算并输出容器v中的最大元素
    cout << "Max = " << *max_element(v.begin(), v.end()) << endl;
    //利用算法accumulate计算并输出容器v中所有元素的和
    cout << "Sum = " << accumulate(v.begin(), v.end(), 0) << endl;
    //利用算法sort对容器v中的元素进行排序
    sort(v.begin(), v.end());
    //利用算法for_each输出排序结果
    cout << "Sorted result is:\n";
    for_each(v.begin(), v.end(), display);
    cout << '\n';
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
