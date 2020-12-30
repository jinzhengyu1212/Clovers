#include<bits/stdc++.h>
using namespace std;
const int N=520000;
int n,q,a[N];
vector<int> v[N];
vector<int> son[N];
int deg[N];
bool check(){
    for(int i=1;i<=n;i++) if(deg[i]>2) return 0;
    return 1;
}

int Fa[N];
void dfs(int u){
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i];
        if(to==Fa[u]) continue;
        son[u].push_back(to); Fa[to]=u;
        dfs(to);
    }
}

void init(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        v[x].push_back(y); v[y].push_back(x);
        deg[x]++; deg[y]++;
    }
    dfs(1);
}

int tot=0;
int ch[N*3][2],sz[N],fa[N],id[N*3];
long long A[N],sum[N*3],val[N*3];

#define ls ch[x][0]
#define rs ch[x][1]
struct Splay{
    int root;
    void pushup(int x){
        if(x==0) return;
        sum[x]=sum[ls]+sum[rs]+val[x];
        sz[x]=sz[ls]+sz[rs]+1;
    }
    bool check(int x){return ch[fa[x]][1]==x;}
    bool isroot(int x){return fa[x]==0;}
    void rotate(int x){
        int y=fa[x],z=fa[y],dirx=check(x),diry=check(y);
        if(z) ch[z][diry]=x; fa[x]=z;
        ch[y][dirx]=ch[x][dirx^1]; fa[ch[x][dirx^1]]=y;
        ch[x][dirx^1]=y; fa[y]=x;
        fa[0]=0;
        pushup(y); pushup(x);
    }
    void splay(int x,int goal=0){
        if(x==root||x==goal||!x) return;
        while(fa[x]!=goal){
            int y=fa[x],z=fa[y];
            if(z!=goal){
                if(check(x)==check(y)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        if(!goal) root=x;
    }
    int kth(int k,int x){
        if(k==0||k>sz[x]) return 0;
        if(ls==0) sz[ls]=0;
        if(sz[ls]+1==k) return x;
        else if(sz[ls]+1<k) return kth(k-sz[ls]-1,rs);
        else return kth(k,ls);
    }
    void build(int l,int r,int f)
    {
        int mid=(l+r)>>1,now=id[mid];
        if(l==r)
        {
            sz[now]=1; 
            sum[now]=A[mid];
        }
        if(l<mid) build(l,mid-1,mid);
        if(r>mid) build(mid+1,r,mid);
        val[now]=A[mid]; fa[now]=id[f];//!!!
        pushup(now);
        ch[id[f]][mid>=f]=now;
    }
    int lower(int Val,int x)
    {
        if(x==0) return 0;
        if(val[x]>=Val) return lower(Val,ls);
        else return sz[ls]+1+lower(Val,rs);
    }
    void insert(int Val)
    {
        int Rt=++tot;
        val[Rt]=Val; sz[Rt]=1;
        int F=root,tmp=root;
        while(tmp) 
        {
            F=tmp;
            tmp=ch[tmp][Val>=val[tmp]];
        }
        fa[Rt]=F; ch[F][Val>=val[F]]=Rt;
        pushup(F); splay(Rt);
    }
    void del(int k)
    {
        int x=kth(k-1,root); int y=kth(k+1,root);
        splay(x);
        splay(y,x);
        ch[y][0]=0;
        pushup(y); pushup(x);
    }
    long long query(int k,int len)
    {
        int x=kth(k-1,root); int y=kth(k+len,root);
        splay(x); splay(y,x);
        int z=ch[y][0];
        return sum[z];
    }
}tree[N];

void solve(){
    for(int i=1;i<=n;i++){
        if(!son[i].size()) continue;
        int Sz=(int)son[i].size();
        for(int j=0;j<(int)son[i].size();j++){
            A[j+2]=a[son[i][j]];
            id[j+2]=++tot;
        }
        sort(A+1,A+Sz+2);
        A[1]=0; id[1]=++tot;
        A[Sz+2]=1000000001; id[Sz+2]=++tot;
        tree[i].build(1,Sz+2,0);
        tree[i].root=id[(Sz+3)/2];
    }
    long long ans=0;
    ans+=a[1];
    for(int i=1;i<=n;i++){
        for(int j=0;j<(int)son[i].size();j++){
            int to=son[i][j];
            ans+=max(0,a[to]-a[i]);
        }
    }
    while(q--){
        int x,Val; scanf("%d%d",&x,&Val);
        if(x==1) ans-=a[x];
        else ans-=max(0,a[x]-a[Fa[x]]);
        if(x!=1){
            int pos=tree[Fa[x]].lower(a[x],tree[Fa[x]].root)+1;
            tree[Fa[x]].del(pos);
        }
        if(son[x].size()){
            int pos=tree[x].lower(a[x],tree[x].root)+1;
            int num=(int)son[x].size()-pos+2;
            ans-=(tree[x].query(pos,num)-1ll*a[x]*num);
        }

        a[x]=Val;
        if(x!=1){
            tree[Fa[x]].insert(a[x]);
        }
        if(son[x].size()){
            int pos=tree[x].lower(a[x],tree[x].root)+1;
            int num=(int)son[x].size()-pos+2;
            ans+=(tree[x].query(pos,num)-1ll*a[x]*num);
        }
        if(x==1) ans+=a[x];
        else ans+=max(0,a[x]-a[Fa[x]]);
        
        printf("%lld\n",ans);
    }
}

signed main(){
    init(); 
    solve();
    return 0;
}