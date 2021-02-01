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
const int N=505;
int n,m,k=300,fac[N],ifac[N];
int S1[N][N],S2[N][N],dp[N],Cm[N],Base[N],pown[N];
int C(int n,int m){return mul(fac[n],mul(ifac[m],ifac[n-m]));}

void solve(){
    memset(dp,0,sizeof(dp));
    Cm[0]=1;
    for(int i=1;i<=min(k,m);i++) Cm[i]=mul(Cm[i-1],mul(qpow(i,MOD-2),m-i+1));
    for(int p=1;p<=k;p++){
        for(int q=1;q<=min(m,p);q++){
            int tmp=mul(S2[p][q],fac[q]);
            Mul(tmp,Cm[q]);
            Mul(tmp,qpow(2,m-q));
            Add(dp[p],tmp);
        }
    }
    dp[0]=qpow(2,m);
    int ans=0;
    pown[0]=1; for(int i=1;i<=k;i++) pown[i]=mul(pown[i-1],n);
    for(int j=1;j<=k;j++){
        int flag=((k-j)&1 ? MOD-1 : 1);
        int sum=0;
        for(int p=0;p<=j;p++){
            int tmp=mul(pown[j-p],C(j,p));
            Mul(tmp,Base[p]); Mul(tmp,dp[p]);
            Add(sum,tmp);
        }
        Add(ans,mul(flag,mul(S1[k][j],sum)));
    }
    printf("%lld\n",mul(ans,ifac[k]));
}

int main()
{
    fac[0]=1; for(int i=1;i<=k;i++) fac[i]=mul(fac[i-1],i);
    Base[0]=1; for(int i=1;i<=k;i++) Base[i]=mul(Base[i-1],2);
    ifac[k]=qpow(fac[k],MOD-2);
    for(int i=k-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    S1[1][1]=1; S2[1][1]=1;
    for(int i=2;i<=k;i++){
        for(int j=1;j<=i;j++){
            S1[i][j]=add(S1[i-1][j-1],mul(i-1,S1[i-1][j]));
            S2[i][j]=add(S2[i-1][j-1],mul(j,S2[i-1][j]));
        }
    }
    int T=read();
    while(T--){
        n=read(); m=read(); k=read();
        n-=m;
        solve();       
    }
    return 0;
}