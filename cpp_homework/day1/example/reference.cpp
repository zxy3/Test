#include <iostream>
using std::cout;
using std::endl;

//引用与指针的区别？

void test0()
{
    int *p;

    int number = 10;
    int &ref = number; //引用是一个变量的别名,引用一经初始化,不会再改变指向

    //int & ref2;//error 引用必须要进行初始化，引用不能单独存在
    cout << "&number = " << &number << endl;
    cout << "&ref = " << &ref << endl;
    cout << "number = " << number << endl;
    cout << "ref = " << ref << endl;
    // number与ref地址一样，值一样
    ref = 20;
    cout << "number = " << number << endl;
    cout << "ref = " << ref << endl;
    // 通过应用可以改变变量的数值
}

//值传递 ==> 复制(副本)
#if 0
void swap(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}
#endif

#if 1
//地址传递 ==> 值传递
void swap(int *px, int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
}
#endif

//1.引用作为函数形参，传递实参

//引用传递 ==> 直接操作实参, 减少复制的开销
//能够提高程序的执行效率
//
//使用起来比指针更直观，更自然
//
void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

int test2(void)
{
    //test0();
    int a = 3, b = 4;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    swap(a, b);
    //swap(&a, &b);
    cout << "执行交换之后:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}
//
//2. 引用作为函数的返回值,
//	返回的变量其生命周期一定要大于函数的
//

int array[5] = {1, 2, 3, 4, 5};

int getNumber(int idx)
{
    return array[idx]; //如果返回值是int型，return时会进行复制
}

int &getNumber2(int idx)
{
    return array[idx]; //如果返回值是int&型，return时不会进行复制
}

//不能返回一个局部变量的引用
// int &getNumber3()
// {
//     int number = 10; //局部变量
//     return number;
// }

//不要轻易返回堆空间变量的引用;除非已经有了内存回收的策略
int &getNumber4()
{
    int *pint = new int(1);
    cout << "pint = " << pint << endl;
    return *pint;
}

int test3()
{
    int x = getNumber(1);
    cout << "x = " << getNumber(1) << endl;

    //&getNumber(1); //error getNumber返回的是一个临时变量临时变量不能取地址
    //getNumber(1) = 11;

   
    cout << "array[1] = " <<  getNumber2(1) << endl;

    //cout << "getNumber3() = " << getNumber3() << endl;//段错误

    int &y = getNumber4();
    cout << "y = " << y << endl;
    cout << "&y = " << &y << endl;
    // 堆空间的销毁
    delete &y;

    int a = 1, b = 2, c = 3;
    //在表达式中调用一次getNumber4，就会产生一次内存泄漏
    cout << " c = " << a + b + getNumber4() + c << endl;

    return 0;
}

int main(void)
{
    // test0();
    // test2();
    test3();
    return 0;
}
