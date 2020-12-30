#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=220000;
int n, q;
char s[MAXN];
namespace SAM
{
	struct Node
	{
		int nxt[26], fail, len;
	} st[MAXN];
	int m, root, lst;
	int pos[MAXN];
	inline int newNode(int l)
	{
		m++;
		memset(st[m].nxt, 0, sizeof st[m].nxt);
		st[m].fail=0, st[m].len=l;
		return m;
	}
	void extend(int x)
	{
		int p=lst, np=newNode(st[p].len+1); lst=np;
		while (p&&!st[p].nxt[x]) st[p].nxt[x]=np, p=st[p].fail;
		if (!p) { st[np].fail=root; return; }
		int q=st[p].nxt[x]; if (st[q].len==st[p].len+1) { st[np].fail=q; return; }
		int nq=newNode(st[p].len+1); memcpy(st[nq].nxt, st[q].nxt, sizeof st[q].nxt);
		st[nq].fail=st[q].fail; st[np].fail=st[q].fail=nq;
		while (p&&st[p].nxt[x]==q) st[p].nxt[x]=nq, p=st[p].fail;
	}
	void build()
	{
		m=0; lst=root=newNode(0);
		for (int i=1; i<=n; i++)
			extend(s[i]-'a'), pos[i]=lst;
	}
}
namespace SGT
{
	struct Node
	{
		int l, r;
		ll sum; int add;
	} tr[4*MAXN];
	#define lc (o<<1)
	#define rc (o<<1|1)
	inline void pushup(int o)
	{
		tr[o].sum=tr[lc].sum+tr[rc].sum;
	}
	inline void add(int o, int k)
	{
		tr[o].sum+=1ll*k*(tr[o].r-tr[o].l+1);
		tr[o].add+=k;
	}
	inline void pushdown(int o)
	{
		if (tr[o].add)
		{
			add(lc, tr[o].add);
			add(rc, tr[o].add);
			tr[o].add=0;
		}
	}
	void build(int o, int l, int r)
	{
		tr[o].l=l, tr[o].r=r;
		tr[o].sum=tr[o].add=0;
		if (l==r) return;
		int mid=l+r>>1;
		build(lc, l, mid), build(rc, mid+1, r);
	}
	void modify(int o, int l, int r, int k)
	{
		if (tr[o].l>r||tr[o].r<l) return;
		if (l<=tr[o].l&&tr[o].r<=r) { add(o, k); return; }
		pushdown(o);
		modify(lc, l, r, k), modify(rc, l, r, k);
		pushup(o);
	}
	ll query(int o, int l, int r)
	{
		if (tr[o].l>r||tr[o].r<l) return 0;
		if (l<=tr[o].l&&tr[o].r<=r) return tr[o].sum;
		pushdown(o);
		return query(lc, l, r)+query(rc, l, r);
	}
	#undef lc
	#undef rc
}
namespace LCT
{
	struct Node
	{
	    int val, cov;
	    int fa, c[2];
	} tr[MAXN];
	#define lc tr[x].c[0]
	#define rc tr[x].c[1]
	#define par tr[x].fa
	inline bool isroot(int x)
	{
	    return tr[par].c[0]!=x&&tr[par].c[1]!=x;
	}
	inline void cover(int x, int k)
	{
		tr[x].val=tr[x].cov=k;
	}
	inline void pushdown(int x)
	{
		if (tr[x].cov)
		{
			if (lc) cover(lc, tr[x].cov);
			if (rc) cover(rc, tr[x].cov);
			tr[x].cov=0;
		}
	}
	inline bool getlr(int x)
	{
	    return tr[par].c[1]==x;
	}
	inline void rotate(int x)
	{
	    int y=par, z=tr[y].fa;
	    bool k=getlr(x); int w=tr[x].c[!k];
	    if (!isroot(y)) tr[z].c[getlr(y)]=x; par=z;
	    tr[y].c[k]=w; if (w) tr[w].fa=y;
	    tr[x].c[!k]=y; tr[y].fa=x;
	}
	void pushall(int x)
	{
	    if (!isroot(x)) pushall(par);
	    pushdown(x);
	}
	void splay(int x)
	{
	    pushall(x);
	    while (!isroot(x))
	    {
	        if (!isroot(par)) rotate(getlr(x)^getlr(par)?x:par);
	        rotate(x);
	    }
	}
	void access(int x, int p)
	{
		int y=0;
	    while (x)
		{
			splay(x);
			if (int k=tr[x].val){
                SGT::modify(1, k-SAM::st[x].len+1, k-SAM::st[par].len, -1);
                cout<<k<<endl;
                cout<<p<<" "<<x<<" "<<par<<" "<<SAM::st[x].len<<" "<<SAM::st[par].len<<"\n";
            }
			rc=y, y=x, x=par;
		}
		cover(y, p);
		SGT::modify(1, 1, p, 1);
	}
	void build()
	{
		for (int i=2; i<=SAM::m; i++)
		{
			tr[i].val=tr[i].cov=0;
			tr[i].c[0]=tr[i].c[1]=0;
			tr[i].fa=SAM::st[i].fail;
		}
	}
	#undef lc
	#undef rc
	#undef par
}
struct Query
{
	int l, r, id;
	bool operator < (const Query& rhs) const
	{
		return r<rhs.r;
	}
} a[MAXN];
ll ans[MAXN];
int main()
{
//	freopen("P6292.in", "r", stdin);
//	freopen("P6292.out", "w", stdout);
	scanf("%s", s+1), n=strlen(s+1);
	SAM::build();
	LCT::build();
	scanf("%d", &q);
	for (int i=1; i<=q; i++)
	{
		scanf("%d%d", &a[i].l, &a[i].r);
		a[i].id=i;
	}
	sort(a+1, a+q+1);
	SGT::build(1, 1, n);
	for (int i=1, j=1; i<=q; i++)
	{
		while (j<=a[i].r)
			LCT::access(SAM::pos[j], j), j++;
		ans[a[i].id]=SGT::query(1, a[i].l, a[i].r);
	}
	for (int i=1; i<=q; i++) printf("%lld\n", ans[i]);
	return 0;
}