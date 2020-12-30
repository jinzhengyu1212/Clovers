#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
using std::cerr;
using std::cin;
using std::cout;
int n, a[401], dp[401][401], cnt[401][401];
bool vis[201];
void checkmax(int &x, int y)
{
    if (x < y)
    {
        x = y;
    }
}
int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    memcpy(a + n + 1, a + 1, 4 * n);
    for (int l = 1; l <= 2 * n; l++)
    {
        memset(vis, false, sizeof(vis));
        for (int r = l; r <= 2 * n; r++)
        {
            cnt[l][r] = cnt[l][r - 1] + !vis[a[r]];
            vis[a[r]] = true;
        }
    }
    for (int len = 2; len <= n; len++)
    {
        for (int l = 1, r; (r = l + len - 1) <= n; l++)
        {
            for (int k = l; k < r; k++)
            {
                checkmax(dp[l][r], dp[l][k] + dp[k + 1][r] + cnt[l][k] * cnt[k + 1][r]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        checkmax(ans, dp[i][i + n - 1]);
    }
    cout << ans;
    return 0;
}