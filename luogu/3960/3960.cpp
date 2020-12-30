#include<bits/stdc++.h>
using namespace std;
const int N=400005;
typedef long long ll;
int n,m;

ll idx(int x,int y){return 1ll*(x-1)*m+y;}
int cnt=0;
int ls[N*25],rs[N*25],sum[N*25];
struct Segment_Tree{
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void update(int x,int l,int r,int pos){
        if(l==r){sum[x]++; return;}
        int mid=(l+r)>>1;
        if(mid>=pos){
            if(!ls[x]) ls[x]=++cnt;
            update(ls[x],l,mid,pos);
        }
        else{
            if(!rs[x]) rs[x]=++cnt;
            update(rs[x],mid+1,r,pos);
        }
        pushup(x);
    }
    int query(int x,int l,int r,int pos){
        sum[0]=0;
        if(!x) return l+pos-1;
        int mid=(l+r)>>1;
        int tmp=(mid-l+1)-sum[ls[x]];
        if(tmp<pos) return query(rs[x],mid+1,r,pos-tmp);
        else return query(ls[x],l,mid,pos);
    }
}tree[N];

int Q; ll A[N<<1],top[N<<1];
vector<ll> a[N];
void init(){
    scanf("%d%d%d",&n,&m,&Q); cnt=N+1;
    for(int i=1;i<=n;i++) A[i]=idx(i,m);
    top[0]=n;
    for(int i=1;i<=n;i++) top[i]=m;
}

void solve(){
    a[n].push_back(idx(n,m));
    while(Q--){
        int x,y; scanf("%d%d",&x,&y);
        int pos=tree[x].query(x,1,N+N,y); ll val;

        if(y==m) val=A[tree[0].query(n+1,1,N+N,x)];
        else val=(pos<m ? idx(x,pos) : a[x][pos-m]);
        printf("%lld\n",val);
        tree[x].update(x,1,N+N,pos); A[++top[0]]=val;
        
        if(x!=n) tree[n].update(n,1,N+N,top[n]);
        a[n].push_back(val); top[n]++;

        pos=tree[0].query(n+1,1,N+N,x);
        if(x!=n) a[x].push_back(A[pos]), top[x]++;
        tree[0].update(n+1,1,N+N,pos);
    }
}

int main(){
    init();
    solve();
    return 0;
}