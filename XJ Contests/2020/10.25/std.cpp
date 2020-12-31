#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, a[500001];
long long sum[500001], sum2[500001];
int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, [](int x, int y) -> bool {
        return x > y;
    });
    for (int i = 1; i <= n; i++)
    {
        sum2[i] = sum2[i - 1] + (sum[i] = sum[i - 1] + a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        long long p, q;
        cin >> p >> q;
        int l = 1, r = min(p, static_cast<long long>(n)), best = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (sum2[mid] + sum[mid] * static_cast<__int128_t>(p - mid) >= q)
            {
                best = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        cout << best << '\n';
    }
    return 0;
}