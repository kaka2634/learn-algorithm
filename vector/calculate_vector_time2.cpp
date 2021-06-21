#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int main()
{

    vector<int> init_push_times = { 16777215, 134217727 };

    clock_t startTime, endTime;
    for (int t = 0; t < init_push_times.size(); t++) {
        vector<int> a1;
        for (int i = 0; i < init_push_times[t]; i++) {
            a1.push_back(1);
        }
        for (int i = 0; i < 2; i++) {
            cout << "size: " << a1.size() << " capacity: " << a1.capacity() << endl;
            startTime = clock();
            a1.push_back(1);
            endTime = clock();
            cout << "Push 1 time, Time cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            cout << "size: " << a1.size() << " capacity: " << a1.capacity() << endl;
            cout << endl;
        }
    }

    return 0;
}
