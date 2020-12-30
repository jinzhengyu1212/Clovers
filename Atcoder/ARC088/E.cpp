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
const int N=200005;
int n,cnt[26]; char s[N];
int pre[N][26],now[26],vis[N];

namespace BIT{
    int a[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int add){
        for(int i=x;i<=n;i+=lowbit(i)) a[i]+=add;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) ret+=a[i];
        return ret;
    }
}

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++){
        cnt[s[i]-'a']++;
    }
    int bl=0;
    for(int i=0;i<26;i++) bl+=cnt[i]%2;
    if(bl>1){
        puts("-1");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<26;j++) pre[i][j]=pre[i-1][j];
        pre[i][s[i]-'a']=i;
    }
    for(int i=0;i<26;i++) now[i]=pre[n][i];
    for(int i=1;i<=n;i++) BIT::update(i,1);
    int flag=0; ll ans=0,rest=n;
    for(int i=1;i<=n;i++) if(!vis[i]) {
        int c=s[i]-'a';
        if(i==now[c]){flag=1; continue;}
        ans+=flag;
        int to=BIT::query(now[c]);
        ans+=rest-to;
        rest-=2; vis[now[c]]=1;
        BIT::update(now[c],-1);
        BIT::update(i,-1);
        now[c]=pre[now[c]-1][c];
    }
    cout<<ans<<endl;
    return 0;
}