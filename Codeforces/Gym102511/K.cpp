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
const int N=505;
const int X=2520;
int n,d[N],p[N],belong[N],sum[N],dp[205][205];
double ans[N];
struct Light{
    int x,r,g;
}a[N];

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].x=read(),a[i].r=read(),a[i].g=read(),p[i]=a[i].r+a[i].g;
    for(int i=1;i<=n;i++) d[i]=p[i],p[i]/=__gcd(p[i],X);
    for(int i=1;i<=n;i++){
        int mx=p[i];
        for(int j=1;j<=n;j++) if(p[j]%p[i]==0) checkmax(mx,p[j]);
        p[i]=mx;
    }
    for(int typ=0;typ<X;typ++){
        memset(dp,0,sizeof(dp));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            double Alive=1;
            for(int j=1;j<=200;j++)if(sum[j])
                Alive*=1.0*(j-sum[j])/j;
            int pos=(typ+a[i].x)%d[i],ad=0;
            for(int j=0;j<p[i];j++,pos=(pos+X)%d[i]){
                if(pos<a[i].r){
                    if(!dp[p[i]][j]) ad++,dp[p[i]][j]=1;
                }
            }
            if(ad==0) continue;
            Alive*=1.0*ad/(p[i]-sum[p[i]]); sum[p[i]]+=ad;
            ans[i]+=1.0*Alive/X;
        }
    }
    double Alive=1;
    for(int i=1;i<=n;i++) printf("%.8lf\n",ans[i]),Alive-=ans[i];
    printf("%.8lf\n",Alive);
    return 0;
}