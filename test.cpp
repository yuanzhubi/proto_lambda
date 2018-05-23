#include "proto_lambda.h"

#include <iostream>
using namespace std;

int main(){
    int i = 2;
    int &j = i;
    PT_LAMBDA(
	my_lambda,	//你定义的lambda对象 变量名。
	void,		//返回类型，c++11可以写auto。
	((int u = 4, int v = 8){ //参数列表(支持默认值这些)和lambda内容。这整部分注意需要用括号括起来，因为可能有逗号而导致宏被分割。即使你没逗号，说不定注释里也有逗号对吧。
        	cout << ++i << endl;
        	cout << ++j << endl;
        	cout << ++u << endl;
        	cout << ++v << endl;
        	i = 3, j=4;
      	}),
	i,j);			//捕获列表，别超过10个。
    my_lambda(6,6);
    cout << endl;
    my_lambda(0,0);
    
    PT_LAMBDA(
        empty_lambda, void,((){
        })
    );
    empty_lambda();
    
    PT_LAMBDA_NEW(
        empty_lambda_new, void,((){
        }), i
    );
    (*empty_lambda_new)();	//empty_lambda_new 这是一个new出来的指针。
    delete empty_lambda_new;
    
    struct angry_base{
        int fire;
        angry_base(){fire = 3;}
        virtual ~angry_base(){}
    }*p;
    PT_LAMBDA_BASE_NEW(
        angry_base, 			//父类名字
        last_lambda_new, 		//变量名
        int, ((int k){			//返回类型和参数类型
            return fire + i + k;	//lambda函数体
        }), i				//捕获列表
    );
    cout << (*last_lambda_new)(j) << endl;
    p = last_lambda_new;   //last_lambda_new作为一个匿名类型lambda对象，如果离开这个函数还想使用他，那么只能通过父类传递出去。
    delete p;              //所以此时必须通过父类指针来管理他的生命周期，进而他只能通过new来创建且父类析构函数是虚的！
    
    return 0;
}
