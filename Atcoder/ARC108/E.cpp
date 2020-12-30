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
const int N=2005;

int n,a[N],dp[N][N],cnt[N][N],pre[N][N],nxt[N][N];
int inv[N];

int lowbit(int x){return x&(-x);}
struct BIT{
    int a[N];
    void update(int x,int add){
        for(int i=x;i<=n+2;i+=lowbit(i)) Add(a[i],add);
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) Add(ret,a[i]);
        return ret;
    }
}tree1[N],tree2[N];

void init(int pos){
    pre[pos][pos]=0; nxt[pos][pos]=0;
    for(int i=pos-1;i>=1;i--) 
        pre[pos][i]=pre[pos][i+1]+(a[i]>a[pos]);
    for(int i=pos+1;i<=n+2;i++)
        nxt[pos][i]=nxt[pos][i-1]+(a[i]>a[pos]);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) inv[i]=qpow(i,MOD-2);
    for(int i=2;i<=n+1;i++) a[i]=read()+1;
    a[1]=1; a[n+2]=n+2;
    for(int i=1;i<=n+2;i++) init(i);
    for(int i=1;i<=n+2;i++){
        for(int j=i+1;j<=n+2;j++){
            if(a[j]<a[i]) continue;
            cnt[i][j]=nxt[i][j]-pre[j][i]-1;
        }
    }
    for(int len=3;len<=n+2;len++){
        for(int l=1;l+len-1<=n+2;l++){
            int r=l+len-1;
            if(a[l]>a[r]||cnt[l][r]==0) continue;
            int suml=tree1[l].query(a[r]);
            int sumr=sub(tree2[r].query(n+2),tree2[r].query(a[l]));
            dp[l][r]=mul(add(suml,sumr),inv[cnt[l][r]])+1;
            tree1[l].update(a[r],dp[l][r]); 
            tree2[r].update(a[l],dp[l][r]);
        }
    }  
    cout<<dp[1][n+2]<<endl;
    return 0;
}