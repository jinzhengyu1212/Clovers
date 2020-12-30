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
int MOD=998244353;
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
const int N=2005;
const int M=1005;
int a[N],b[N],n=2000,ifac[N],fac[N],c[N];
void init(){
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    ifac[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=0;i<=n;i++){
        a[i]=mul(ifac[i],qpow(qpow(2,i*(i-1)/2),MOD-2));
        b[i]=a[i];
    }
    for(int rnd=0;rnd<2;rnd++){
        memset(c,0,sizeof(c));
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(i+j>n) continue;
                Add(c[i+j],mul(a[i],b[j]));
            }
        }
        for(int i=0;i<=n;i++) a[i]=c[i];
    }
    for(int i=1;i<=n;i++) Mul(a[i],mul(fac[i],qpow(2,i*(i-1)/2)));
}

int main()
{
    int T=read(); MOD=read();
    init();
    while(T--){
        int k=read();
        printf("%d\n",a[k]);
    }
    return 0;
}