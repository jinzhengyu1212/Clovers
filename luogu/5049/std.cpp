#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
struct _ {
    int u, v;
    _(const int& u = 0, const int& v = 0) : u(u), v(v) {}
} e[1000001];
struct __ {
    bool operator()(const _& a, const _& b) {
        return a.v < b.v;
    }
} cmp; //按照到达点的标号比较
int h[500001], to[1000001], nxt[1000001], cnt;
inline void add_edge(const int& u, const int& v) {
    to[++cnt] = v; nxt[cnt] = h[u]; h[u] = cnt;
}
int n, m;
std::vector<int> ans; //存储答案, 每次dfs前把当前的u插入到ans的最后.
void dfs(const int& u, const int& fa) {
    ans.push_back(u);
    for (register int i = h[u]; i; i = nxt[i]) if (to[i] != fa)
        dfs(to[i], u);
} //处理树情况的答案.
void work1() {
    int u, v;
    for (register int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        e[i << 1] = _(u, v);
        e[(i << 1) | 1] = _(v, u);
    }
    std::sort(e, e + (m << 1), cmp); //顺序排序
    for (register int i = n << 1; i--; ) //因为遍历的时候与插入顺序相反, 所以要反着插入
        add_edge(e[i].u, e[i].v);
    dfs(1, 0);
}
int vis[500001], rt, u1, u2; //vis[i] = 2表示i在环上
void dfs1(const int& u, const int& fa) {
    vis[u] = 1;
    for (register int i = h[u]; i; i = nxt[i]) if (to[i] != fa) { //v = to[i]
        if (!rt && vis[to[i]]) rt = to[i], vis[u] = 2, u2 = u; //如果v不是u的父亲但是v已经被经过了且当时还没有找到环, 那么v就是这个环的根, u就是u2
        else if (!vis[to[i]]) dfs1(to[i], u);
        if (vis[to[i]] == 2 && to[i] != rt) {
            vis[u] = 2; //标记环上点
            if (!u1 && u == rt) u1 = to[i]; //判断是否是u1
        }
    }
}

bool vis2[500001];
inline int mynxt(int i) {
    while (i = nxt[i], i && vis2[to[i]]);
    return i;
} //取下一个点
int clk; //用来判断的东西
void dfs2(const int& u, const int& fa, const int& mx) {
    ++clk;
    vis2[u] = 1; ans.push_back(u);
    for (register int i = h[u]; i; i = nxt[i]) if (to[i] != fa && !vis2[to[i]]) {
        int nx = mynxt(i);
        if (mx && vis[u] == 2 && vis[to[i]] == 2 && !vis2[u2] && !nx && to[i] > mx) return; //回溯操作
        if (u == rt && to[i] == u1) dfs2(to[i], u, to[nx]);
        else dfs2(to[i], u, mx ? (nx ? to[nx] : mx) : 0); //如果mx是0表示现在不可回溯(不在环上)(仿佛会对环上的分支点很奇怪?)
    }
}
void work2() {
    int u, v;
    for (register int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        e[i << 1] = _(u, v);
        e[(i << 1) | 1] = _(v, u);
    }
    std::sort(e, e + (m << 1), cmp);
    for (register int i = n << 1; i--; )
        add_edge(e[i].u, e[i].v);
    dfs1(1, 0);
    dfs2(1, 0, 0);
}
int main() {
    scanf("%d%d", &n, &m);
    if (m == n - 1) work1();
    else work2();
    printf("%d", ans[0]);
    for (register int i = 1; i < n; ++i) printf(" %d", ans[i]);
    putchar('\n');
}