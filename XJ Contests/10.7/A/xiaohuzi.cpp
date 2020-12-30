#pragma GCC optimize(2)
#include <bits/stdc++.h>
int n, m, v, d, ans;
std::bitset <94> QAQ, tmp, E[94][2];
void dfs(int k, std::bitset <94> now) {
    if (k > d) return ans += !!now.count(), void();
    v = 0, tmp.reset(); for (int i = 1; i <= n; ++i) if (now[i]) tmp |= E[i][v]; dfs(k + 1, tmp);
    v = 1, tmp.reset(); for (int i = 1; i <= n; ++i) if (now[i]) tmp |= E[i][v]; dfs(k + 1, tmp);
}
int main() {
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1, u, v, w; i <= m; ++i) scanf("%d%d%d", &u, &v, &w), E[u][w][v] = 1, E[v][w][u] = 1;
    return QAQ.reset(), QAQ[1] = 1, dfs(1, QAQ), printf("%d\n", ans), 0;
}