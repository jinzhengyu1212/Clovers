/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
#define il inline
using namespace std;
il char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}
il int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}
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
const int N=1000005;
int a[N],b[N],c[N],n;

namespace BIT{
    int a[N];
    void init(){memset(a,0,sizeof(a));}
    int lowbit(int x){return x&(-x);}
    void update(int x){
        for(int i=x;i<=n;i+=lowbit(i)){
            a[i]++;
        }
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)){
            ret+=a[i];
        }
        return ret;
    }
}

pii A[N];
ll solve(int *x,int *y){
    BIT::init();
    for(int i=1;i<=n;i++) A[i]=mk(x[i],y[i]);
    sort(A+1,A+n+1);
    ll ret=0;
    for(int i=1;i<=n;i++){
        ret+=BIT::query(A[i].second);
        BIT::update(A[i].second); 
    }
    return ret;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),b[i]=read(),c[i]=read();
    ll x=solve(a,b),y=solve(b,c),z=solve(a,c);
    printf("%lld\n",(x+y+z-1ll*(n-1)*n/2)/2); 
    return 0;
}