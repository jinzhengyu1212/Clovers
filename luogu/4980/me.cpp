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
const int N=500005;
int T,n;
int prime[N],tot=0,bl[N];
void init(){
    for(int i=2;i<N;i++) bl[i]=1;
    for(int i=2;i<N;i++){
        if(bl[i]) prime[++tot]=i;
        for(int j=1;j<=tot;j++){
            if(i*prime[j]>N-1) break;
            bl[i*prime[j]]=0;
            if(i%prime[j]==0) break;
        }
    }
}

int phi(int x){
    int ret=x;
    for(int i=1;i<=tot;i++){
        if(1ll*prime[i]*prime[i]>x) break;
        if(x%prime[i]==0){
            ret=ret/prime[i]*(prime[i]-1);
            while(x%prime[i]==0) x/=prime[i];
        }
    }
    if(x!=1) ret=ret/x*(x-1);
    return ret;
}

int fac[N],cnt=0;
void run(int n){
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            fac[++cnt]=i;
            if(i*i==n) continue;
            fac[++cnt]=n/i;
        }
    }
    sort(fac+1,fac+cnt+1);
    fac[cnt+1]=n+1;
}

int main()
{
    int T=read();
    init();
    while(T--){
        n=read();
        int ans=0; cnt=0;
        run(n);
        for(int i=1;i<=cnt;i++){
            Add(ans,mul(qpow(n,fac[i]),phi(n/fac[i])));
        }
        printf("%lld\n",mul(ans,qpow(n,MOD-2)));
    }
    return 0;
}