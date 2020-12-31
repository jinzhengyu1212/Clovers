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
int n,k; ll ans=0;
ll a[N],b[N],val[N];

struct node{
    int id; ll val;
    bool operator < (const node &rhs) const{
        return val<rhs.val;
    }
};

ll calc(int id,ll w){
    return w*max(0ll,a[id]-b[id]*w);
}
priority_queue<node> Q;

int main()
{
    n=read(); k=read();
    for(int i=1;i<=n;i++){
        a[i]=read(); b[i]=read();
        ll delta=calc(i,val[i]+1)-calc(i,val[i]);
        Q.push({i,delta});
    }
    while(k--){
        node now=Q.top(); Q.pop();
        if(now.val<0) break;
        int u=now.id; ans+=now.val;
        val[u]++;
        ll delta=calc(u,val[u]+1)-calc(u,val[u]);
        Q.push({u,delta});
    }
    cout<<ans<<endl;
    return 0;
}