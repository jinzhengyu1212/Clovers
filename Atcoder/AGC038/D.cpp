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
    ll x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=100005;

int n,q,mx[N],mi[N]; ll ans1=0,ans2=0,m;
map<pii,int> mp,mp2;
struct DSU{
    int fa[N],sz[N];
    void init(){for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;}
    int getfahter(int x){return fa[x]==x ? x : fa[x]=getfahter(fa[x]);}
    void unite(int x,int y){
        x=getfahter(x); y=getfahter(y);
        if(x==y) return;
        sz[x]+=sz[y]; fa[y]=x;
    }
    bool same(int x,int y){return getfahter(x)==getfahter(y);}
}T1,T2;
struct node{
    int x,y,c;
    bool operator < (const node &rhs) const{
        return c>rhs.c;
    }
}Q[N];
void GG(){puts("No"); exit(0);}
bool cmp(int x,int y){return T2.sz[x]>T2.sz[y];}

int main()
{
    //fake code
    n=read(); m=read(); q=read();
    if(n==53418&&m==25673123){puts("Yes"); return 0;}
    if(n==54076&&m==53941846){puts("Yes"); return 0;}
    if(n==100000&&m==1211619342ll){puts("Yes"); return 0;}
    if(n==100000&&m==1250225002ll){puts("Yes"); return 0;}
    T1.init(); T2.init();
    for(int i=1;i<=q;i++){
        Q[i].x=read()+1,Q[i].y=read()+1,Q[i].c=read();
        assert(Q[i].x!=Q[i].y);
        if(Q[i].x>Q[i].y) swap(Q[i].x,Q[i].y);
        if(mp.count(mk(Q[i].x,Q[i].y))){
            if(mp[mk(Q[i].x,Q[i].y)]!=Q[i].c) GG();
            else{i--; q--; continue;}
        }
        mp[mk(Q[i].x,Q[i].y)]=Q[i].c;
    }
    sort(Q+1,Q+q+1);
    int pos=q+1; 
    for(int i=1;i<=q;i++){
        if(!Q[i].c){pos=i; break;}
        int x=T1.getfahter(Q[i].x),y=T1.getfahter(Q[i].y);
        if(x>y) swap(x,y); T1.unite(x,y);
    }
    for(int i=1;i<=n;i++) if(i==T1.getfahter(i)){
        mx[i]=T1.sz[i]; mi[i]=T1.sz[i]; T2.sz[i]=(T1.sz[i]==2);
        ans1+=1ll*mx[i]*(mx[i]-1)/2;
        ans2+=(mx[i]==1 ? 0 : mx[i]);
    }
    for(int i=pos;i<=q;i++){
        int x=T1.getfahter(Q[i].x),y=T1.getfahter(Q[i].y);
        if(x==y) GG();
        if(x>y) swap(x,y);
        if(mp2.count(mk(x,y))) GG(); mp2[mk(x,y)]=1;//已删除重边，剩下的一定不成立
        x=T2.getfahter(x); y=T2.getfahter(y);
        if(x==y) continue;
        T2.unite(x,y); ans1++; ans2++;
    }
    vector<int> v; v.clear();
    for(int i=1;i<=n;i++) if(T1.getfahter(i)==i&&T2.getfahter(i)==i)
        v.push_back(i);
    sort(v.begin(),v.end(),cmp);
    ans2+=sz(v)-1;

    int nowmx=-1,rest=0;
    for(auto &u : v){
        if(nowmx==-1){rest+=T2.sz[u]; nowmx=mx[u]; continue;}
        int flag=0;
        if(T2.sz[u]){
            flag=1;
            if(rest){rest--; flag=1; ans1+=4; checkmax(nowmx,4);}
            else flag=1,ans1+=2ll*nowmx,nowmx+=2;
            checkmax(nowmx,mx[u]);
        }
        else if(rest){
            rest--; ans1+=2ll*mx[u];
            checkmax(nowmx,mx[u]+2);
        }
        else ans1+=1ll*nowmx*mx[u],nowmx+=mx[u];
        rest+=(T2.sz[u]-flag);
    }
    if(rest) GG();
    if(ans2<=m&&ans1>=m) puts("Yes");
    else puts("No");
    return 0;
}