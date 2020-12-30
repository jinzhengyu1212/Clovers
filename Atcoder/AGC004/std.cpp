#include <bits/stdc++.h>

typedef long long LL;

const int MAXN = 1e5 + 10;

int n, m, sum;
int head[MAXN];
struct Edge { int link, to; } e[MAXN << 1];
inline void add(int u, int v) { e[++sum] = (Edge) { v, head[u] }, head[u] = sum; }

namespace Tree {
	int del[MAXN];
	void dfs(int u, int fa, int D) {
		del[u] = D % 2 == 1 ? 1 : -1;
		for (int i = head[u]; i; i = e[i].to) {
			int v = e[i].link;
			if (v == fa) continue;
			dfs(v, u, D + 1), del[u] += del[v];
		}
	}
	inline void gao() {
		dfs(1, 0, 1);
		LL ans = 0;
		for (int i = 1; i <= n; ++i) ans += abs(del[i]);
		if (del[1]) puts("-1");
		else printf("%lld\n", ans);
	}
};
namespace GayRingTree {
	int S, T, cnt, len, tot;
	bool flg;
	int dep[MAXN], del[MAXN], f[MAXN], b[MAXN], tmp[MAXN];
	bool vis[MAXN];
	void dfs1(int u, int fa) {
		vis[u] = true, dep[u] = dep[fa] + 1, f[u] = fa;
		del[u] = dep[u] % 2 == 1 ? 1 : -1;
		for (int i = head[u]; i; i = e[i].to) {
			int v = e[i].link;
			if (vis[v] && v != fa) S = u, T = v;
			if (vis[v] || v == fa) continue;
			dfs1(v, u), del[u] += del[v];
		}
	}
	void dfs2(int u, int fa) {
		vis[u] = true, del[u] = dep[fa] + 1;
		del[u] = dep[u] % 2 == 1 ? 1 : -1;
		for (int i = head[u]; i; i = e[i].to) {
			int v = e[i].link;
			if (vis[v] || v == fa) continue;
			dfs2(v, u), del[u] += del[v];
		}
	}
	inline void gao() {
		dfs1(1, 0), flg = (dep[S] + dep[T] + 1) % 2;
		int L = S, R = T, lca; len = 1;
		while (L != R) {
			if (dep[L] > dep[R]) L = f[L];
			else R = f[R];
			++len;
		}
		lca = L;
		if (flg) {
			if (del[1] & 1) return puts("-1"), void();
			int hhz = del[1] >> 1;
			for (int i = S; i; i = f[i]) del[i] -= hhz;
			for (int i = T; i; i = f[i]) del[i] -= hhz;
			LL ans = abs(hhz);
			for (int i = 1; i <= n; ++i) ans += abs(del[i]);
			printf("%lld\n", ans);
		} else {
			// assert(0);
			if (del[1]) return puts("-1"), void();
			tmp[++tot] = lca;
			for (int i = S; i != lca; i = f[i]) tmp[++tot] = i;
			for (int i = T; i != lca; i = f[i]) tmp[++tot] = i;
			memset(vis, false, sizeof(vis));
			dfs2(S, 0);
			for (int i = 1; i <= tot; ++i) b[++cnt] = del[tmp[i]];
			std::sort(b + 1, b + cnt + 1);
			int QAQ = b[(cnt + 1) / 2];
			for (int i = 1; i <= tot; ++i) del[tmp[i]] -= QAQ;
			LL ans = 0;
			for (int i = 1; i <= n; ++i) ans += abs(del[i]);
			printf("%lld\n", ans);
		}
	}
};

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; ++i) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	if (n % 2 == 1) return puts("-1"), 0;
	if (m < n) Tree::gao();
	else GayRingTree::gao();
	return 0;
}