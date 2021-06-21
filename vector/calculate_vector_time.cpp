#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int main()
{
    // int push_times = 10e4; //初始化push times的大小，如果太小时间将没法统计
    // int calculate_times = 4; //控制push times乘10的次数
    // clock_t startTime, endTime; 
    // for (int t = 0; t < calculate_times; t++) {
    //     vector<int> a1;
    //     startTime = clock();
    //     for (int i = 0; i < push_times; i++) {
    //         a1.push_back(1);
    //     }
    //     endTime = clock();
    //     cout << "Push " << push_times << " times, Time cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    //     cout << a1.capacity()<<endl;
    //     push_times *= 10;
    // }

        // clock_t startTime, endTime; 
        // vector<int> a1;
        
        // for (int i = 0; i < 16777216; i++) {
        //     a1.push_back(1);
        // }
        // cout << a1.capacity()<<endl;
        // startTime = clock();
        //  a1.push_back(1);
        // endTime = clock();
        // cout <<"Time cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        // cout << a1.capacity()<<endl;

        //         clock_t startTime, endTime; 
        // vector<int> a1;
        
        // for (int i = 0; i < 16777216; i++) {
        //     a1.push_back(1);
        // }
        // cout << a1.capacity()<<endl;
        // startTime = clock();
        //  a1.push_back(1);
        // endTime = clock();
        // cout <<"Time cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        // cout << a1.capacity()<<endl;

        clock_t startTime, endTime; 
        vector<int> a1;
        
        for (int i = 0; i < 16777215; i++) {
            a1.push_back(1);
        }
        cout << a1.capacity()<<endl;
        startTime = clock();
         a1.push_back(1);
        endTime = clock();
        cout <<"Time cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        cout << a1.capacity()<<endl;
    return 0;
}
