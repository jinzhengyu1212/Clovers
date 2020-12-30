#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> PII;
typedef pair<ll,ll> Pll;
typedef vector<int> VI;
typedef vector<PII> VII;
typedef pair<ll,ll>P;
#define N  200000+10
#define M  200000+10
#define INF 1e9
#define fi first
#define se second
#define MP make_pair
#define pb push_back
#define pi acos(-1)
#define mem(a,b) memset(a,b,sizeof(a))
#define rep(i,a,b) for(int i=(int)a;i<=(int)b;i++)
#define per(i,a,b) for(int i=(int)a;i>=(int)b;i--)
#define lowbit(x) x&(-x)
#define Rand (rand()*(1<<16)+rand())
#define id(x) ((x)<=B?(x):m-n/(x)+1)
#define ls p<<1
#define rs p<<1|1
#define fors(i) for(auto i:e[x]) if(i!=p)

const int MOD=998244353,inv2=(MOD+1)/2;
      //int p=1e4+7;
      //double eps=1e-6;
      int dx[4]={-1,1,0,0};
      int dy[4]={0,0,-1,1};

ll dp[2010][4100];
int a[N],b[N];

int read()
{
   int v=0,f=1;
   char c=getchar();
   while(c<48||57<c) {if(c=='-') f=-1; c=getchar();}
   while(48<=c&&c<=57) v=(v<<3)+v+v+c-48,c=getchar();
   return v*f;
}

ll readll()
{
   ll v=0,f=1;
   char c=getchar();
   while(c<48||57<c) {if(c=='-') f=-1; c=getchar();}
   while(48<=c&&c<=57) v=(v<<3)+v+v+c-48,c=getchar();
   return v*f;
}

int main()
{
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    int n=read(),k=read();
    rep(i,1,n) a[i]=read();
    rep(i,1,n) b[i%n+1]=a[i];
    if(k==1)
    {
        printf("0\n");
        return 0;
    }
    int eps=n;
    dp[0][0+eps]=1;

    rep(i,1,n)
    {
        if(a[i]==b[i])
        {
            rep(j,-n,n) dp[i][j+eps]=dp[i-1][j+eps]*k%MOD;
            continue;
        }
        rep(j,-n,n) dp[i][j+eps]=(dp[i-1][j-1+eps]+dp[i-1][j+1+eps]+1ll*(k-2)*dp[i-1][j+eps]%MOD)%MOD;
    }
    ll ans=0;
    rep(i,1,n) ans=(ans+dp[n][i+eps])%MOD;
    printf("%I64d\n",ans);
    return 0;
}