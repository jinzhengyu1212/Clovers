// URL : https://atcoder.jp/contests/agc010/tasks/agc010_c
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (n); ++i)
using ll = long long;

int N;
vector<int> A, C;
vector<int> graph[100100];

int dfs(int cur, int prv = -1) {
    if (C[cur] != -1) return C[cur];
    int cnt = 0;
    ll sum = 0, mx = 0;
    for (auto& nxt: graph[cur]) {
        if (nxt == prv) continue;
        ++cnt;
        ll c = dfs(nxt, cur);
        sum += c;
        if (mx < c) mx = c;
    }
    if (cnt == 0) return C[cur] = A[cur];
    ll T = 2LL * A[cur] - sum;
    if (T < 0) {
        cout << "NO" << endl;
        exit(0);
    }
    return C[cur] = T;
}

void check(int cur, int prv = -1) {
    if (cur != 0 and graph[cur].size() > 1) {
        ll mx = C[cur], sum = C[cur];
        for (auto& nxt: graph[cur]) {
            if (nxt == prv) continue;
            if (mx < C[nxt]) mx = C[nxt];
            sum += C[nxt];
        }
        if (mx * 2 > sum) {
            cout << "NO" << endl;
            exit(0);
        }
    }
    for (auto& nxt: graph[cur]) {
        if (nxt == prv) continue;
        check(nxt, cur);
    }
}

signed main() {
    cin >> N;
    A.resize(N);
    for (auto& e: A) cin >> e;
    REP(i, N - 1) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }
    C.assign(N, -1);
    dfs(0);
    check(0);
    bool ok = true;
    {
        bool isleaf = graph[0].size() == 1;
        ll sum = 0;
        for (auto& nxt: graph[0]) {
            sum += C[nxt];
        }
        if (isleaf) {
            if (sum != A[0]) {
                ok = false;
            }
        } else {
            if (sum != 2LL * A[0]) {
                ok = false;
            }
        }
    }
    if (ok) cout << "YES" << endl;
    else cout << "NO" << endl;
}

