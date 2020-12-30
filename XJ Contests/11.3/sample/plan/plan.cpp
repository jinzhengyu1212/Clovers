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
const int N=50005;
int n,a[N],L,R,b[N],c[N];

int main()
{
    n=read(); L=read(); R=read();
    for(int i=1;i<=n;i++) a[i]=read();
    if(n==1){
        puts("0");
        printf("%d\n",a[1]);
        return 0;
    }
    for(int i=1;i<n;i++) b[i]=a[i]+a[i+1]-L;
    R-=L;
    int pre=0;
    if(b[1]<0){
        pre=-b[1]; c[1]-=b[1]; b[1]=0; 
    }
    for(int i=2;i<n;i++){
        if(b[i]>=0){
            pre=0;
            continue;
        }
        if(pre){
            int mi=min(-b[i],pre);
            c[i-1]-=mi; c[i]+=mi;
            b[i-2]-=mi; b[i]+=mi;
            pre=0;
        }
        if(b[i]>=0) continue;
        int mi=min(-b[i],R-b[i-1]);
        b[i]+=mi; b[i-1]+=mi; c[i]+=mi; pre=mi;
        if(b[i]<0){
            c[i+1]-=b[i]; b[i+1]-=b[i]; 
            b[i]=0;
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans+=c[i]; a[i]+=c[i];
    }
    R+=L;
    for(int i=1;i<n;i++){
        if(a[i]+a[i+1]<L||a[i]+a[i+1]>R) {puts("-1"); return 0;}
    }
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++) printf("%d ",a[i]); puts("");
    return 0;
}