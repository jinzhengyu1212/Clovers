#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <cmath> 
#include <algorithm>
using namespace std; 
inline int gi() {
	register int data = 0, w = 1;
	register char ch = 0;
	while (!isdigit(ch) && ch != '-') ch = getchar(); 
	if (ch == '-') w = -1, ch = getchar();
	while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar();
	return w * data; 
} 
typedef long long ll;
const int INF = 1e9; 
const int MAX_N = 5e4 + 5;
struct Mdy { int x, y; } p[MAX_N]; 
struct Edge { int u, v, w, id; } e[18][MAX_N], tmp[MAX_N], stk[MAX_N]; 
inline bool operator < (const Edge &l, const Edge &r) { return l.w < r.w; } 
int N, M, Q, sum[18]; 
int a[MAX_N], c[MAX_N], fa[MAX_N], rnk[MAX_N]; 
ll ans[MAX_N]; 
int getf(int x) { return (x == fa[x]) ? x : fa[x] = getf(fa[x]); }
void unite(int x, int y) { 
	x = getf(x), y = getf(y); 
	if (x == y) return ; 
	if (rnk[x] != rnk[y]) (rnk[x] > rnk[y]) ? fa[y] = x : fa[x] = y; 
	else fa[x] = y, rnk[y]++; 
} 
void Set(int n, Edge *a) { 
	for (int i = 1; i <= n; i++) {
		fa[a[i].u] = a[i].u; 
		fa[a[i].v] = a[i].v; 
		rnk[a[i].v] = rnk[a[i].u] = 1; 
	} 
} 
void Contraction(int &n, ll &val) { 
	int top = 0; 
	Set(n, tmp); sort(&tmp[1], &tmp[n + 1]); 
	for (int i = 1; i <= n; i++) 
		if (getf(tmp[i].u) ^ getf(tmp[i].v)) 
			unite(tmp[i].u, tmp[i].v), stk[++top] = tmp[i]; 
	Set(top, stk); 
	for (int i = 1; i <= top; i++) 
		if (stk[i].w != -INF && getf(stk[i].u) ^ getf(stk[i].v)) 
			val += stk[i].w, unite(stk[i].u, stk[i].v); 
	top = 0; 
	for (int i = 1; i <= n; i++) 
		if (getf(tmp[i].u) ^ getf(tmp[i].v)) 
	 		stk[++top] = (Edge){getf(tmp[i].u), getf(tmp[i].v), tmp[i].w, tmp[i].id}; 
	for (int i = 1; i <= top; i++) c[tmp[i].id] = i, tmp[i] = stk[i]; 
	n = top; 
} 
void Reduction(int &n) { 
	int top = 0; 
	Set(n, tmp); sort(&tmp[1], &tmp[n + 1]); 
	for (int i = 1; i <= n; i++)
		if (getf(tmp[i].u) ^ getf(tmp[i].v)) 
			unite(tmp[i].u, tmp[i].v), stk[++top] = tmp[i]; 
		else if (tmp[i].w == INF) stk[++top] = tmp[i]; 
	for (int i = 1; i <= top; i++) c[tmp[i].id] = i, tmp[i] = stk[i]; 
	n = top; 
}
void Div(int l, int r, int dep, ll val) {
	int n = sum[dep]; 
	if (l == r) a[p[l].x] = p[l].y; 
	for (int i = 1; i <= n; i++) {
		e[dep][i].w = a[e[dep][i].id]; 
		tmp[i] = e[dep][i], c[tmp[i].id] = i; 
	} 
	if (l == r) {
		ans[l] = val, Set(n, tmp); 
		sort(&tmp[1], &tmp[n + 1]);
		for (int i = 1; i <= n; i++) 
			if (getf(tmp[i].u) != getf(tmp[i].v))
				unite(tmp[i].u, tmp[i].v), ans[l] += tmp[i].w; 
		return ; 
	} 
	for (int i = l; i <= r; i++) tmp[c[p[i].x]].w = -INF; 
	Contraction(n, val); 
	for (int i = l; i <= r; i++) tmp[c[p[i].x]].w = INF; 
	Reduction(n); 
	for (int i = 1; i <= n; i++) e[dep + 1][i] = tmp[i]; 
	sum[dep + 1] = n;
	int mid = (l + r) >> 1; 
	Div(l, mid, dep + 1, val); 
	Div(mid + 1, r, dep + 1, val); 
} 
int main () {
	N = gi(), M = gi(), Q = gi(); 
	for (int i = 1; i <= M; i++) e[0][i] = (Edge){gi(), gi(), a[i] = gi(), i}; 
	for (int i = 1; i <= Q; i++) p[i] = (Mdy){gi(), gi()};
    sum[0] = M; Div(1, Q, 0, 0); 
	for (int i = 1; i <= Q; i++) printf("%lld\n", ans[i]); 
	return 0; 
} 