#include <bits/stdc++.h>
#define LL long long

using namespace std;

inline int read(){
    int x = 0,f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c <='9' && c >='0') {x = x * 10 + c - '0';c = getchar();}
    return x * f;
}

inline void write(LL x){
    int k = 0;char put[40];
    if (!x) putchar('0');
    if (x < 0) putchar('-'),x = -x;
    while (x)  put[++k] = (x % 10) + '0',x /= 10;
    while (k)  putchar(put[k]),--k;
    putchar('\n');
}

const LL INF = 1LL << 62,N = 750050,Q = N;
int n,m,a[N],b[N],rk[N];
inline bool cmp(int i,int j){ return a[i] == a[j] ? i > j : a[i] > a[j]; }

int st[N][22],Log[N],Pow[22]; static int tt,xx,yy;
inline int RMQ(int l,int r){
    tt = Log[r-l+1],xx = st[l][tt],yy = st[r-Pow[tt]+1][tt];
    return rk[xx] < rk[yy] ? xx : yy;
}
struct Ask{int l,r,id;}q1[Q],q2[Q]; vector<Ask>q[N];
int L,R,Mid;
LL Ans1[Q],Ans2[Q],Ans[Q];

int root,Lc[N],Rc[N];

const int NN = N<<2;
int tp[NN]; LL val[NN],var[NN],K[NN],B[NN];
void Build(int o,int l,int r){
    tp[o] = K[o] = B[o] = 0,val[o] = var[o] = INF;
    if (l < r){
        int mid = l + r >> 1;
        Build(o<<1,l,mid);
        Build(o<<1|1,mid+1,r);
    }
}
inline void SetT(int o,int l,int r,LL k,LL b){
    tp[o] = 1,K[o] = k,B[o] = b;
    val[o] = l * k + b,var[o] = r * k + b;
}
inline void AddT(int o,int l,int r,LL k,LL b){
    tp[o] = tp[o] ? tp[o] : 2;
    K[o] += k,B[o] += b,val[o] += l * k + b,var[o] += r * k + b;
}
inline void DownT(int o,int l,int r){
    if (tp[o]){
        int mid = l + r >> 1;
        if (tp[o] == 1) SetT(o<<1,l,mid,K[o],B[o]),SetT(o<<1|1,mid+1,r,K[o],B[o]);
        else AddT(o<<1,l,mid,K[o],B[o]),AddT(o<<1|1,mid+1,r,K[o],B[o]);
        tp[o] = K[o] = B[o] = 0;
    }
}

int ll,rr; LL kk,bb;
void Set(int o,int l,int r){
    if (ll <= l && rr >= r) SetT(o,l,r,kk,bb);
    else{
        DownT(o,l,r);
        int mid = l + r >> 1;
        if (ll <= mid) Set(o<<1,l,mid); if (rr > mid) Set(o<<1|1,mid+1,r);
        val[o] = val[o<<1],var[o] = var[o<<1|1];
    }
}
void Add(int o,int l,int r){
    if (ll <= l && rr >= r) AddT(o,l,r,kk,bb);
    else{
        DownT(o,l,r);
        int mid = l + r >> 1;
        if (ll <= mid) Add(o<<1,l,mid); if (rr > mid) Add(o<<1|1,mid+1,r);
        val[o] = val[o<<1],var[o] = var[o<<1|1];
    }
}
LL Ask(int o,int l,int r,int p){
    if (l == r) return val[o];
    DownT(o,l,r);
    int mid = l + r >> 1;
    return p <= mid ? Ask(o<<1,l,mid,p) : Ask(o<<1|1,mid+1,r,p);
}
int _ll,_rr; LL k1,b1,b2;
void Maintain(int o,int l,int r){
    if (_ll <= l && _rr >= r){
        if (l * k1 + b1 >= val[o] + b2){
            AddT(o,l,r,0,b2);
            return;
        }
        if (r * k1 + b1 <= var[o] + b2){
            SetT(o,l,r,k1,b1);
            return;
        }
    }
    DownT(o,l,r);
    int mid = l + r >> 1; 
    if (_ll <= mid) Maintain(o<<1,l,mid);
    if (_rr > mid) Maintain(o<<1|1,mid+1,r);
    val[o] = val[o<<1],var[o] = var[o<<1|1];
}

int tl[N],tr[N];
void dfs1(int &o,int l,int r){ //建树
    if (l > r) { o = 0; return; }
    o = RMQ(l,r);
    tl[o] = l,tr[o] = r;
    dfs1(Lc[o],l,o-1);
    dfs1(Rc[o],o+1,r);
}
void dfs2(int x,bool s){ //DP
    LL now = a[x];
    if (Lc[x]) dfs2(Lc[x],0),now += Ask(1,1,n,x-1);
    if (Rc[x]) dfs2(Rc[x],1);
    ll = rr = x,kk = 0,bb = now,Set(1,1,n);
    if (x < tr[x]){
        _ll = x+1,_rr = tr[x];
        k1 = a[x],b1 = now - 1LL * x * a[x],b2 = a[x] * (x - tl[x] + 1LL);
        Maintain(1,1,n);
    }
    if (s)
    for (int i = 0; i < q[tl[x]].size(); ++i) //回答询问
        Ans[q[tl[x]][i].id] = Ask(1,1,n,q[tl[x]][i].r);
}

int main(){
    register int i,j,x,y;
    n = read(),m = read();
    
    for (i = 0; i <= 21; ++i) Pow[i] = 1 << i;
    for (i = 1; i <= n; ++i){
        Log[i] = Log[i-1] + 1; while (Pow[Log[i]] > i) --Log[i];
    }
    //st表
    for (i = 1; i <= n; ++i) a[i] = read(),b[i] = i;
    sort(b+1,b+n+1,cmp);
    for (i = 1; i <= n; ++i) rk[b[i]] = i,st[i][0] = i;
    for (j = 1; j <= Log[n] + 1; ++j)
        for (i = 1; i <= n; ++i) if (i + Pow[j-1] <= n){
            x = st[i][j-1],y = st[i + Pow[j-1]][j-1];
            st[i][j] = rk[x] < rk[y] ? x : y;
        }
    //拆询问
    for (i = 1; i <= m; ++i){
        L = read() + 1,R = read() + 1,Mid = RMQ(L,R);
        q1[i].id = i,q1[i].l = L,q1[i].r = Mid - 1;
        q2[i].id = i,q2[i].l = Mid + 1,q2[i].r = R;
        Ans1[i] = 1LL * a[Mid] * (R - Mid + 1);
        Ans2[i] = 1LL * a[Mid] * (Mid - L + 1);
    }
    //第一组询问(貌似我是反着做的,不过本质上是一样的)
    for (i = 1; i <= m; ++i) if (q2[i].l <= q2[i].r) q[q2[i].l].push_back(q2[i]);
    Build(1,1,n);
    dfs1(root,1,n);
    dfs2(root,1);
    for (i = 1; i <= m; ++i) Ans2[i] += Ans[i];
    //翻转数组做第二组
    reverse(a+1,a+n+1);
    reverse(rk+1,rk+n+1);
    for (i = 1; i <= n; ++i) st[i][0] = i;
    for (j = 1; j <= Log[n] + 1; ++j)
        for (i = 1; i <= n; ++i) if (i + Pow[j-1] <= n){
            x = st[i][j-1],y = st[i + Pow[j-1]][j-1];
            st[i][j] = rk[x] < rk[y] ? x : y;
        }
    
    for (i = 1; i <= n; ++i) q[i].clear();
    for (i = 1; i <= m; ++i) if (q1[i].l <= q1[i].r){
        swap(q1[i].l,q1[i].r);
        q1[i].l = n - q1[i].l + 1;
        q1[i].r = n - q1[i].r + 1;
        q[q1[i].l].push_back(q1[i]);
    }
    Build(1,1,n);
    dfs1(root,1,n);
    dfs2(root,1);
    for (i = 1; i <= m; ++i) Ans1[i] += Ans[i];//合并答案
    for (i = 1; i <= m; ++i) write(min(Ans1[i],Ans2[i]));
    return 0;
}