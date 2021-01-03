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
const int N=500005;
int n,k,ans=0;
int f(int n){
    int num=(n-1)/2;
    int ret=mul(num,num+1);
    if(n&1) Sub(ret,num);
    return ret;
}

int calc(int n){
    int ret1=0,ret2=0;
    int t=n/3-1;
    ret1=1ll*t*(t+1)/2%MOD;
    ret2=sub(f(n-1),f(n-t-1));
    return sub(ret2,ret1);
}

namespace solver1{
    int B=40000;
    int dp[82005][22];
    void main(){
        int sum0=0,sum1=0;
        dp[B][0]=1;
        for(int i=-n;i<=n;i++){
            if(i<0) sum0+=i; else sum1+=i;
            for(int j=k;j>=1;j--){
                for(int s=-40000;s<=40000;s++){
                    Add(dp[s+B][j],dp[s+B-i][j-1]);
                }
            }
        }
        cout<<dp[B][k]<<endl;
    }
}

int main()
{
    n=read(); k=read();
    if(k==1){
        puts("1");
        return 0;
    }
    if(k==2){
        printf("%d\n",n%MOD);
        return 0;
    }
    if(k==3){
        int num=(n-1)/2;
        int tmp=mul(num,num+1);
        if(n&1) Sub(tmp,num);
        printf("%d\n",add(mul(tmp,2),n));
        return 0;
    }
    if(k==4){
        int ans=0;
        int num=(n-1)/2;
        int tmp=mul(num,num+1);
        if(n&1) Sub(tmp,num);
        Add(ans,mul(tmp,2));
        for(int i=1;i<=n+n-1;i++){
            tmp=i/2+1;
            tmp=min(i-1,n)-tmp+1;
            Add(ans,mul(tmp,tmp));
        }
        for(int i=6;i<=n;i++){
            Add(ans,mul(2,calc(i)));
        }
        cout<<ans<<endl;
        return 0;
    }
    if(n<=2000){
        solver1::main();
        return 0;
    }
    return 0;
}