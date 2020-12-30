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
const int N=200005;
int n,Dep[N],X,Y,dep[2][N],Base[N]; 
vector<int> v[N];
void dfs1(int u,int f){
    for(auto &to : v[u]){
        if(to==f) continue;
        Dep[to]=Dep[u]+1;
        dfs1(to,u);
    }
}

void dfs2(int u,int f,int flag){
    for(auto &to : v[u]){
        if(to==f) continue;
        dep[flag][to]=dep[flag][u]+1;
        dfs2(to,u,flag);
    }
}

int mx[N],cnt[N],tmp[N],mi[N];
int main()
{
    n=read();
    Base[0]=1; for(int i=1;i<=n;i++) Base[i]=mul(Base[i-1],2);
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    int id,maxdep=0;
    dfs1(1,-1);
    for(int i=1;i<=n;i++) if(maxdep<Dep[i]) maxdep=Dep[i],id=i;
    X=id; Dep[X]=0;
    dfs1(X,-1); maxdep=0;
    for(int i=1;i<=n;i++) if(maxdep<Dep[i]) maxdep=Dep[i],id=i; 
    Y=id;
    dfs2(X,-1,0); dfs2(Y,-1,1);
    int mxmi=0;
    for(int i=1;i<=n;i++) 
        if(i!=X&&i!=Y){
            mi[i]=min(dep[0][i],dep[1][i]);
            mx[i]=max(dep[0][i],dep[1][i]);
            checkmax(mxmi,mi[i]);
            cnt[mx[i]]++;
        }
    for(int i=1;i<=n;i++) if(cnt[i]) cnt[i]+=cnt[i-1];
    int ans=mul(maxdep,Base[n-1]);
    for(int i=n-1;i>=1;i--){
        if(cnt[i]){
            if(i==mxmi){
                Add(ans,mul(i,mul(2,Base[cnt[i]])));
                break;
            }
            else Add(ans,mul(i,mul(2,sub(Base[cnt[i]],Base[cnt[i-1]]))));
        }
        else if(i==mxmi) Add(ans,mul(2,i));
    }
    cout<<ans<<endl;
    return 0;
}