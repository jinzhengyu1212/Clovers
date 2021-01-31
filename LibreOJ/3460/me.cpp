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
const int N=200005;
#define int long long
vector<pii> q[N];
int n,m;
int stk[N],top=0,pos[N],c[N],ans[N],val[N];
int query(int now,int x){
    int L=1,R=top,mid,best;
    while(L<=R){
        mid=(L+R)>>1;
        if(x>=pos[mid]) L=mid+1,best=mid;
        else R=mid-1; 
    }
    return val[best]+c[stk[best]]*(x-pos[best])+(now-stk[best])*x*x;
}

int find(int k,int now){
    int L=1,R=n-1,mid,best=-1;
    while(L<=R){
        mid=(L+R)>>1;
        int dely=query(now,mid+1)-query(now,mid);
        if(k<dely) R=mid-1,best=mid;
        else L=mid+1;
    }
    return best;
}

signed main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++) c[i]=read();
    int Q=read();
    for(int i=1;i<=Q;i++){
        int x=read(),y=read();
        q[y].push_back(mk(x,i));
    }
    stk[top=1]=1; pos[1]=1; val[1]=0;
    for(auto &u : q[1]) ans[u.second]=c[1]*(u.first-1);
    for(int now=2;now<=m;now++){
        int tmp=find(c[now],now);
        if(tmp==-1){
            for(auto &u : q[now]) ans[u.second]=query(now,u.first);
            continue;
        }
        int Val=query(now,tmp);
        while(top&&pos[top]>=tmp) top--;
        stk[++top]=now; pos[top]=tmp; val[top]=Val;
        for(auto &u : q[now]) ans[u.second]=query(now,u.first);
    }
    for(int i=1;i<=Q;i++) printf("%lld\n",ans[i]);
    return 0;
}