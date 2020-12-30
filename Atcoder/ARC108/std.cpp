#define taskname "test"

#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)x.size()
#define fi first
#define se second

typedef long long lli;
typedef pair<int, int> pii;

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;

int n;
vector<int> gr[maxn];

vector<int> depth_s, depth_t;

bool app[maxn];
int cnt[maxn];

void read_input()
{
    cin >> n;
    for(int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

void dfs(int u, int par, vector<int>&depth)
{
    depth[u] = depth[par] + 1;
    for(auto&v: gr[u])
        if(v != par) dfs(v, u, depth);
}

int add(int x, int y)
{
    x += y;
    if(x >= mod) x -= mod;
    return x;
}

int sub(int x, int y)
{
    x -= y;
    if(x < 0) x += mod;
    return x;
}

int powmod(int x, int k)
{
    if(k == 0) return 1;
    int t = powmod(x, k / 2);
    if(k % 2 == 0) return t * 1LL * t % mod;
    else return t * 1LL * t % mod * x % mod;
}

void solve()
{
    int s = -1, t = -1;
    depth_s.resize(n + 1, -1);
    depth_t.resize(n + 1, -1);
    dfs(1, 0, depth_s);
    int best = -1;
    for(int i = 1; i <= n; ++i)
        if(depth_s[i] > best)
        {
            best = depth_s[i];
            s = i;
        }
    dfs(s, 0, depth_s);
    best = -1;
    for(int i = 1; i <= n; ++i)
        if(depth_s[i] > best)
        {
            best = depth_s[i];
            t = i;
        }
    dfs(t, 0, depth_t);
    int ans = 0;
    ans = add(ans, powmod(2, n - 1) * 1LL * depth_s[t] % mod);
    int min_d = 0;
    for(int i = 1; i <= n; ++i)
        if(i != s && i != t)
        {
            app[max(depth_s[i], depth_t[i])] = true;
            ++cnt[max(depth_s[i], depth_t[i])];
            min_d = max(min_d, min(depth_s[i], depth_t[i]));
        }
    for(int i = 1; i <= depth_s[t]; ++i)
        cnt[i] += cnt[i - 1];
    for(int d = min_d; d <= depth_s[t]; ++d)
        ans = add(ans, d * 2LL * sub(powmod(2, cnt[d]), (d > min_d ? powmod(2, cnt[d - 1]) : 0)) % mod);
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    read_input();
    solve();
}

