#pragma GCC optimize(2)
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
using namespace std;
int n, m, d, ans;
bitset<91> f[2097153], e[2][91];
void dfs(int mask, int len)
{
    if (f[mask].none())
    {
        return;
    }
    if (len == d)
    {
        ans += f[mask].any();
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (f[mask].test(i))
        {
            f[mask << 1] |= e[0][i];
            f[mask << 1 | 1] |= e[1][i];
        }
    }
    dfs(mask << 1, len + 1);
    dfs(mask << 1 | 1, len + 1);
}
int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> d;
    for (int i = 1; i <= m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        e[c][u].set(v);
        e[c][v].set(u);
    }
    f[1].set(1);
    dfs(1, 0);
    cout << ans;
    return 0;
}