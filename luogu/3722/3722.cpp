#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef pair<int,int> pii;
#define mk make_pair
#define int long long
int n,m,p1,p2;
int a[N],nxt[N],pre[N];

namespace BIT{
    int sum[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int add){
        for(int i=x;i<=n;i+=lowbit(i)) sum[i]+=add;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) ret+=sum[i];
        return ret;
    }
}

struct Segment_Tree{
    int sum[N<<2],tag[N<<2];
    void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
    void build(int x,int l,int r){
        sum[x]=0; tag[x]=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void pushdown(int x,int l,int mid,int r){
        if(!tag[x]) return;
        tag[x<<1]+=tag[x]; tag[x<<1|1]+=tag[x];
        sum[x<<1]+=tag[x]*(mid-l+1); sum[x<<1|1]+=tag[x]*(r-mid);
        tag[x]=0;
    }
    void update(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R){sum[x]+=(r-l+1); tag[x]++; return;}
        int mid=(l+r)>>1; pushdown(x,l,mid,r);
        if(mid>=L) update(x<<1,l,mid,L,R);
        if(mid<R) update(x<<1|1,mid+1,r,L,R);
        pushup(x);
    }
    int query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1; pushdown(x,l,mid,r);
        int ret=0;
        if(mid>=L) ret+=query(x<<1,l,mid,L,R);
        if(mid<R) ret+=query(x<<1|1,mid+1,r,L,R);
        return ret;
    }
}tree;

struct node{
    int id,flag,L,R;
    node(){} node(int id,int flag,int L,int R):id(id),flag(flag),L(L),R(R){}
};

vector<int> V[N];
vector<pii> G[N];
vector<node> Q[N];
int q[N],top=0;
void init(){
    scanf("%lld%lld%lld%lld",&n,&m,&p1,&p2);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    a[0]=a[n+1]=n+1;q[++top]=0;
    for(int i=1;i<=n+1;i++)
    {
        while(a[q[top]]<a[i]) nxt[q[top]]=i,top--;
        pre[i]=q[top];q[++top]=i;
    }
    tree.build(1,1,n);
    for(int i=1;i<=n;i++){
        int l=pre[i];
        int r=nxt[i];
        if(l!=0&&r!=n+1) V[r].push_back(l);
        if(i<r-1) G[l].push_back(mk(i+1,r-1));
        if(l<i-1) G[r].push_back(mk(l+1,i-1));
    }
}

int ans[N];
void solve(){
    for(int i=1;i<=m;i++){
        int L,R; scanf("%lld%lld",&L,&R);
        Q[L-1].push_back(node(i,-1,L,R));
        Q[R].push_back(node(i,1,L,R));
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<(int)V[i].size();j++){
            BIT::update(V[i][j],1);
        }
        for(int j=0;j<(int)G[i].size();j++){
            tree.update(1,1,n,G[i][j].first,G[i][j].second);
        }
        for(int j=0;j<(int)Q[i].size();j++){
            node now=Q[i][j];
            int L=now.L,R=now.R,id=now.id;
            ans[id]+=now.flag*p2*tree.query(1,1,n,L,R);
            if(now.flag==1) ans[id]+=p1*(BIT::query(R)-BIT::query(L-1));
            if(now.flag==1) ans[id]+=(R-L)*p1;
        }
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}

signed main(){
    init(); solve();
    return 0;
}