/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=500005;
int sum[N<<5],multag[N<<5],ls[N<<5],rs[N<<5],tot=0,lz[N<<5],rz[N<<5];
struct Segment_Tree{
    void pushup(int x){
        sum[x]=add(sum[ls[x]],sum[rs[x]]);
    }
    void pushdown(int x){
        sum[0]=0;
        if(multag[x]!=1){
            multag[ls[x]]=mul(multag[ls[x]],multag[x]);
            sum[ls[x]]=mul(sum[ls[x]],multag[x]);
            multag[rs[x]]=mul(multag[rs[x]],multag[x]);
            sum[rs[x]]=mul(sum[rs[x]],multag[x]);
            multag[x]=1;
        }
    }
    void MUL(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){
            multag[x]=mul(multag[x],val);
            sum[x]=mul(val,sum[x]);
            return;
        }
        int mid=(l+r)>>1;
        pushdown(x);
        if(mid>=L&&ls[x]) MUL(ls[x],l,mid,L,R,val);
        if(mid<R&&rs[x]) MUL(rs[x],mid+1,r,L,R,val);
        pushup(x);
    }
    void insert(int x,int l,int r,int pos,int val){
        lz[x]=l; rz[x]=r;
        if(l==r){
            sum[x]=val;
            multag[x]=1;
            return;
        }
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=pos){
            if(!ls[x]) ls[x]=++tot;
            insert(ls[x],l,mid,pos,val);
        }
        else{
            if(!rs[x]) rs[x]=++tot;
            insert(rs[x],mid+1,r,pos,val);
        }
        pushup(x);
    }
    void merge(int x,int y,int l,int r,int sufx,int sufy){
        if(l==r){
            int tmp=mul(sum[x],sum[y]);
            sum[x]=add(mul(sum[x],sufy),mul(sum[y],sufx));
            sum[x]=add(sum[x],tmp);
            return;
        }
        int mid=(l+r)>>1; 
        pushdown(x); pushdown(y);
        //out(l); out(mid); out(ls[x]); outln(ls[y]);
        if(ls[x]&&ls[y]) 
            merge(ls[x],ls[y],l,mid,add(sufx,sum[rs[x]]),add(sufy,sum[rs[y]]));
        else if(!ls[x]&&ls[y]){
            //out(sufy); outln(sum[ls[x]]);
            ls[x]=ls[y];
            sum[ls[x]]=mul(sum[ls[x]],add(sum[rs[x]],sufx));
            multag[ls[x]]=mul(multag[ls[x]],add(sum[rs[x]],sufx));
        }
        else if(ls[x]&&!ls[y]){
            sum[ls[x]]=mul(sum[ls[x]],add(sum[rs[y]],sufy));
            multag[ls[x]]=mul(multag[ls[x]],add(sum[rs[y]],sufy));
        }

        if(rs[x]&&rs[y])
            merge(rs[x],rs[y],mid+1,r,sufx,sufy);
        else if(!rs[x]&&rs[y]){
            rs[x]=rs[y];
            sum[rs[x]]=mul(sum[rs[x]],sufx);
            multag[rs[x]]=mul(multag[rs[x]],sufx);
        }
        else if(rs[x]&&!rs[y]){
            sum[rs[x]]=mul(sum[rs[x]],sufy);
            multag[rs[x]]=mul(multag[rs[x]],sufy);
        }
        pushup(x); 
    }
}tree;
int n,m,dep[N],lst[N]; vector<int> v[N];
void print(int x){
    out(lz[x]); out(rz[x]); out(ls[x]); out(rs[x]); outln(sum[x]);
    tree.pushdown(x);
    if(ls[x]) print(ls[x]);
    if(rs[x]) print(rs[x]);
}

void dfs(int u,int f){
    tree.insert(u,1,n,n,1);
    if(lst[u]) tree.insert(u,1,n,lst[u],MOD-1);
    for(auto to : v[u]){
        if(to==f) continue;
        dfs(to,u);
        tree.MUL(to,1,n,dep[to],n,2);
        tree.merge(u,to,1,n,0,0);
    }
}

void dfs1(int u,int f){
    for(auto to : v[u]){
        if(to==f) continue;
        dep[to]=dep[u]+1;
        dfs1(to,u);
    }
}

int main()
{
    scanf("%d",&n); tot=n;
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    scanf("%d",&m);
    dep[1]=1; dfs1(1,-1);
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        if(dep[x]>dep[y]) swap(x,y);
        checkmax(lst[y],dep[x]);
    }
    //for(int i=1;i<=n;i++) cout<<lst[i]<<endl;
    dfs(1,-1);
    printf("%d\n",sum[1]);
    return 0;
}