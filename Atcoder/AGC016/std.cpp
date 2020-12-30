#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(time(nullptr));

int n, m;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    vector <pair <int, int> > a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i].first >> a[i].second;
        a[i].first--;
        a[i].second--;
    }
    reverse(a.begin(), a.end());
    int ans = 0;
    for (int v = 0; v < n - 1; v++) {
        for (int u = v + 1; u < n; u++) {
            vector <int> used(n);
            used[v] = 1;
            used[u] = 1;
            bool fl = true;
            for (int i = 0; i < m; i++) {
                int kek = a[i].first, lol = a[i].second;
                if (used[kek] && used[lol]) {
                    fl = false;
                    break;
                }
                else if (used[kek] ^ used[lol]) {
                    used[kek] = 1;
                    used[lol] = 1;
                }
            }
            if (fl)
                ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
