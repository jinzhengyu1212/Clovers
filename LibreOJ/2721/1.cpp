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
int _abs(int x){return x<0 ? -x : x;}void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline ll read(){
    ll x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
#define int long long
const int N=500005;
int exgcd(int a,int b,int &x,int &y){
    if(!b){x=1; y=0; return a;}
    int xx,yy;
    int ret=exgcd(b,a%b,xx,yy);
    x=yy; y=xx-(a/b)*yy;
    return ret;
}
int T,n,m,p[N],k[N],a[N],b[N],LCM,mx=0,flag;
multiset<int> st;
ll quick_mul(ll x,ll y,ll mod){
    ll ans=0;
    while(y!=0){
        if(y&1)ans+=x,ans%=mod;
        x=x+x,x%=mod;
        y>>=1;
    }
    return ans;
}
signed main()
{
    T=1;
    while(T--){
        n=read(); flag=1;
        for(int i=1;i<=n;i++) p[i]=read(),a[i]=read();
        if(!flag){puts("-1"); continue;}
        if(!flag){puts("-1"); continue;}
        LCM=p[1]; int ans=a[1];
        for(int i=2;i<=n;i++){
            int x,y,c=((a[i]-ans)%p[i]+p[i])%p[i];
            int g=exgcd(LCM,p[i],x,y);
            if(c%g!=0){flag=0; break;}
            x=quick_mul(x,c/g,p[i]/g); 
            ans+=x*LCM; LCM=LCM/g*p[i];
            ans=(ans%LCM+LCM)%LCM;
        }
        printf("%lld\n",ans);
    }
    return 0;
}