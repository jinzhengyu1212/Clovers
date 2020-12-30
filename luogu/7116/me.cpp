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
const int N=500005;
const int V=1000001;
const int D=11;
int n,k,w[D],rest[D],d[D],st[D],ed[D],ans=0;
ll ti[D][V];
int calc(int x){
    int ret=1;
    for(int i=1;i<=k;i++) if(i!=x) Mul(ret,rest[i]);
    return ret;
}
int vis[N];
void init(){
    n=read(); k=read();
    for(int i=1;i<=k;i++) w[i]=read(),rest[i]=w[i];
    for(int i=1;i<=n;i++){
        int x=read(),y=read();
        d[x]+=y;
        int pos=(d[x]<0 ? -d[x] : w[x]+1-d[x]);
        if(!ti[x][pos]&&d[x]!=0) Add(ans,mul(i,calc(x))),ti[x][pos]=i,rest[x]--;
    }
    int bl=0;
    for(int i=1;i<=k;i++) bl+=d[i];
    if(!bl){puts("-1"); exit(0);}
    for(int i=1;i<=k;i++){
        st[i]=1; ed[i]=w[i];
        while(ti[i][st[i]]) st[i]++;
        while(ti[i][ed[i]]) ed[i]--;
        if(d[i]>0){
            for(int j=w[i];j>=1;j--)
                if(!ti[i][j]) ti[i][j]=ti[i][j+d[i]]+n;
            reverse(ti[i]+st[i],ti[i]+ed[i]+1);
        }
        else if(d[i]<0){
            for(int j=1;j<=w[i];j++)
                if(!ti[i][j]) ti[i][j]=ti[i][j+d[i]]+n;
        }
        else st[i]=ed[i]+1,vis[i]=1;
    }
}

bool check(){for(int i=1;i<=k;i++) if(st[i]>ed[i]&&!vis[i]) return 0; return 1;}
void solve(){
    while(check()){
        int pos; ll mi=INF;
        for(int i=1;i<=k;i++){
            if(st[i]>ed[i]) continue;
            if(mi>ti[i][st[i]]) mi=ti[i][st[i]],pos=i;
        }
        Add(ans,mul(mi,calc(pos))); rest[pos]--; st[pos]++;
    }
    cout<<ans<<endl;
}

int main()
{
    init(); solve();
    return 0;
}