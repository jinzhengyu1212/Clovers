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
const int N=100005;
char s[N],T[N];
int n,m,dp[30];
vector<int> v[27];
void init(){
    scanf("%s",s+1); scanf("%s",T+1);
    n=strlen(s+1); m=strlen(T+1);
    for(int i=1;i<=n;i++){
        v[s[i]-'a'].push_back(i);
    }
}

void solve(int l,int r){
    for(int i=1;i<=m;i++) dp[i]=r+1;
    dp[0]=l-1;
    for(int i=1;i<=m;i++){
        int c=T[i]-'a';
        for(int j=i-1;j>=0;j--){
            if(dp[j]==r+1) continue;
            int pos=lower_bound(v[c].begin(),v[c].end(),dp[j]+1)-v[c].begin();
            if(pos>=sz(v[c])||v[c][pos]>r) continue;
            checkmin(dp[j+1],v[c][pos]);
        }
    }
    for(int i=m;i>=0;i--) if(dp[i]!=r+1){
        printf("%d\n",(r-l+1)+m-i*2);
        return;
    }
}

int main()
{
    init();
    int Q=read();
    while(Q--){
        int l=read(),r=read();
        solve(l,r);
    }
    return 0;
}