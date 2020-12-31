#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> R(1, 1000000000000000000);
int n = 5000, m = 5000;
int main(int argc, char const *argv[])
{
    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= n; i++)
    {
        cout << R(mt_rand) % 500000 + 1 << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= m; i++)
    {
        cout << 10000000000000ll << ' ' << R(mt_rand) << '\n';
    }
    return 0;
}