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
const int MOD=1e9+7;
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
const int N=20005;
int n,m,k,fac[N],ifac[N];
int C(int n,int m){
    return mul(fac[n],mul(ifac[n-m],ifac[m]));
}

int main()
{
    fac[0]=1; for(int i=1;i<=20000;i++) fac[i]=mul(fac[i-1],i);
    ifac[20000]=qpow(fac[20000],MOD-2);
    for(int i=19999;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    int T=read();
    while(T--){
        n=read(); m=read(); k=read();
        if(n<=5000&&m<=5000){
            int ans=0;
            for(int i=0;i<=m;i++) Add(ans,mul(C(m,i),C(n-m+2*i,k)));
            cout<<ans<<endl;
            continue;
        }
    }
    return 0;
}