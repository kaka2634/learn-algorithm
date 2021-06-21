#include <iostream>
#include <vector>
using namespace std;

void print_array(int push_times, vector<int>& array)
{
    cout << "push times: " << push_times << " size: " << array.size() << " capacity: " << array.capacity() << endl;
}

const int MAX_PUSH_TIMES = 10;

int main()
{
    vector<int> a1;
    print_array(0, a1);

    for (int i = 0; i < MAX_PUSH_TIMES; i++) {
        a1.push_back(1);
        print_array(i + 1, a1);
    }
    return 0;
}
