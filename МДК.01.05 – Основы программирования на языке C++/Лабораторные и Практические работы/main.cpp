#include <iostream>
#include <vector>

using namespace std;

int c = 0;

void main()
{
    //сам написал
}

void increment(int &x)
{
    x++;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

static void counter(int count)
{
    c += count;
}

int sum(const vector<int> &vec)
{
    int count;

    for (int v : vec)
        count += v;

    return count;
}
