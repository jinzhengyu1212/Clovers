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
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
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
const int N=1000005;
int a[N]; ll sum=0;
int n,m,Rt[N];

struct Segment_Tree{
    int sum[N<<5],ls[N<<5],rs[N<<5],tot;
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void insert(int x,int l,int r,int pos){
        if(l==r){sum[x]=1; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) ls[x]=++tot,insert(ls[x],l,mid,pos);
        else rs[x]=++tot,insert(rs[x],mid+1,r,pos);
        pushup(x);
    }
    int merge(int x,int y,int l,int r){
        if(!x&&!y) return 0;
        int z=++tot;
        if(!x||!y){
            sum[z]=sum[x+y]; ls[z]=ls[x+y]; rs[z]=rs[x+y];
            return z;
        }
        if(l==r){sum[z]=sum[x]+sum[y]; return z;}
        int mid=(l+r)>>1;
        ls[z]=merge(ls[x],ls[y],l,mid);
        rs[z]=merge(rs[x],rs[y],mid+1,r);
        pushup(z); return z;
    }
    int query(int x,int l,int r,int L,int R){
        if(!x||L>R) return 0;
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1,ret=0;
        if(mid>=L) ret+=query(ls[x],l,mid,L,R);
        if(mid<R) ret+=query(rs[x],mid+1,r,L,R);
        return ret;
    }
}tree;

struct Original_SAM{
    int link[N],maxlen[N],trans[N][26],sz=1,lst=1;
    void extend(int id,int pos){
        int cur=++sz,p;
        maxlen[cur]=maxlen[lst]+1;
        tree.insert(cur,1,n,pos);
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int tmp=++sz;
                maxlen[tmp]=maxlen[p]+1;
                copy(trans[q],trans[q]+26,trans[tmp]);
                link[tmp]=link[q];
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=tmp;
                link[cur]=link[q]=tmp;
            }
        }
        lst=cur;
    }
    vector<int> v[N];
    void build(){
        for(int i=2;i<=sz;i++) v[link[i]].push_back(i);
    }
    void dfs(int u){
        for(auto &to : v[u]){
            dfs(to);
            Rt[u]=tree.merge(Rt[u],Rt[to],1,n);
        }
    }
    void jump(char *s,int len,int L,int R){
        int u=1,now=0;
        for(int i=1;i<=len;i++){
            int id=s[i]-'a';
            while(!trans[u][id]&&u!=1) u=link[u],now=maxlen[u];
            if(trans[u][id]) now++,u=trans[u][id];
            while(!tree.query(Rt[u],1,n,L+now-1,R)&&u!=1){
                now--;
                if(now==maxlen[link[u]]) u=link[u];
            }
            a[i]=now;
        }
    }
}S;

struct Match_SAM{
    int link[N],maxlen[N],trans[N][26],sz=1,lst=1;
    void init(){
        for(int i=1;i<=sz;i++){
            memset(trans[i],0,sizeof(trans[i]));
            link[i]=0;
        }
        sz=1; lst=1;
    }
    void extend(int id,int pos){
        int cur=++sz,p;
        maxlen[cur]=maxlen[lst]+1;
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int tmp=++sz;
                maxlen[tmp]=maxlen[p]+1;
                copy(trans[q],trans[q]+26,trans[tmp]);
                link[tmp]=link[q];
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=tmp;
                link[cur]=link[q]=tmp;
            }
        }
        lst=cur;
        sum+=min(maxlen[cur]-maxlen[link[cur]],maxlen[cur]-a[pos]);
    }
}T;

char s[N],t[N];

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    tree.tot=2*n+5;
    for(int i=1;i<=n;i++) S.extend(s[i]-'a',i);
    for(int i=1;i<=S.sz;i++) Rt[i]=i;
    S.build(); S.dfs(1);
    int Q=read();
    while(Q--){
        scanf("%s",t+1); m=strlen(t+1);
        int l=read(),r=read();
        T.init();
        S.jump(t,m,l,r); sum=0;
        for(int i=1;i<=m;i++) T.extend(t[i]-'a',i);
        printf("%lld\n",sum);
    }
    return 0;
}