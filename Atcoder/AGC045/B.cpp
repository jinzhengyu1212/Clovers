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
const int N=1000005;
char s[N]; int n,bl[N],sum[N],mx[N],ans=inf;

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='?') bl[i]=1,s[i]='0';
        if(s[i]=='0') sum[i]=sum[i-1]-1;
        else sum[i]=sum[i-1]+1;
    }
    mx[n]=n; 
    for(int i=n-1;i>=0;i--){
        if(sum[i]>sum[mx[i+1]]) mx[i]=i;
        else mx[i]=mx[i+1];
    }
    int MAX=-inf,num=0;
    for(int i=0;i<=n;i++) checkmax(MAX,sum[i]);
    for(int i=1;i<=n;i++){
        if(sum[mx[i]]+num*2+2<=MAX&&bl[i]) num++,s[i]='1';
    }
    int maxn=0,minn=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='0') sum[i]=sum[i-1]-1;
        else sum[i]=sum[i-1]+1;
        checkmax(maxn,sum[i]); checkmin(minn,sum[i]);
    }
    checkmin(ans,maxn-minn);

    for(int i=1;i<=n;i++){
        if(bl[i]) s[i]='0';
        if(s[i]=='0') sum[i]=sum[i-1]-1;
        else sum[i]=sum[i-1]+1;
    }
    MAX=-inf,num=0;
    for(int i=0;i<=n;i++) checkmax(MAX,sum[i]);
    MAX++;
    for(int i=1;i<=n;i++){
        if(sum[mx[i]]+num*2+2<=MAX&&bl[i]) num++,s[i]='1';
    }
    maxn=0,minn=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='0') sum[i]=sum[i-1]-1;
        else sum[i]=sum[i-1]+1;
        checkmax(maxn,sum[i]); checkmin(minn,sum[i]);
    }
    checkmin(ans,maxn-minn);
    cout<<ans<<endl;
    return 0;
}