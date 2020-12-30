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
const double pi=acos(-1);
int L,R;
namespace solver3{
    const int N=3000001;
    int prime[N],tot=0,mu[N],sum_mu[N],vis[N];
    bool bl[N];
    void init(){
        mu[1]=1;
        for(int i=2;i<N;i++){
            if(!bl[i]) prime[++tot]=i,mu[i]=-1;
            for(int j=1;j<=tot;j++){
                if(i*prime[j]>=N) break;
                bl[i*prime[j]]=1;
                if(i%prime[j]==0){
                    mu[i*prime[j]]=0;
                    break;
                }
                mu[i*prime[j]]=-mu[i];
            }
        }
        for(int i=1;i<N;i++) sum_mu[i]=sum_mu[i-1]+mu[i];
    }
    ll solve1(ll now,ll n)
    {
        ll ret=1;
        if(now<N) return sum_mu[now];
        if(vis[n/now]!=inf) return vis[n/now];
        for(ll i=2,j;i<=now;i=j+1)
        {
            j=now/(now/i);
            ll val=now/i;
            ret-=1LL*solve1(val,n)*(j-i+1);
        }
        vis[n/now]=ret;
        return ret;
    }
    double calc(int n){
        ll ans=0;
        for(int l=1,r;l<=n;l=r+1){
            r=(n+1)/((n+1)/l);
            int k=(n+1)/l;
            ans+=1ll*(solve1(r,r)-solve1(l-1,l-1))*(k-1)*(k-2)/2;
        }
        return ans/2.0;
    }
    void main(){
        init();
        printf("%.2lf\n",calc(R)-calc(L-1));
    }
}
 
int main()
{
    L=read(); R=read();
    solver3::main();
    return 0;
}
