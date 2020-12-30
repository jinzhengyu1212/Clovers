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
const int N=50005;

int n,Q,cnt=0;
void ask(int x,int y){
    printf("%d %d\n",x-1,y-1);
    fflush(stdout);
}
int ans[N],tot=0;
typedef vector<int> V;
V v,chain;

int R[N];
void solve(){
    scanf("%d%d",&n,&Q);
    cnt=0; tot=0;
    int now=1; v.clear(); chain.clear();
    v.push_back(1);
    for(int i=2;i<=n;i++){
        ask(now,i);
        int res; scanf("%d",&res);
        if(res==1){
            v.push_back(i);
            if(!chain.empty()) v.push_back(chain.back()),chain.pop_back();
        }
        else chain.push_back(i);
        now=v.back();
    }
    if(chain.empty()){
        printf("%d\n",n);
        for(auto to : v) printf("%d ",to-1);
        puts("");
        return; 
    }
    for(int i=0;i<=n;i++) R[i]=0;
    for(int i=0;i<sz(v);i++){
        if(v[i]!=chain.back()){
            ask(v[i],chain.back());
            scanf("%d",&R[i]);
        }
    }
    if(R[0]) ans[++tot]=chain.back(),chain.pop_back();
    int tmp=0;
    for(int i=0;i<sz(v)-1;i++){
        if(chain.empty()) break;
        tmp++;
        ans[++tot]=v[i];
        if(R[i]&&R[i+1]){
            ans[++tot]=chain.back();
            chain.pop_back();
        }
    }
    if(!chain.empty()){
        puts("-1");
        return;
    }
    for(int i=tmp;i<sz(v);i++) ans[++tot]=v[i];
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    puts("");
}

int main()
{
    int T; scanf("%d",&T);
    while(T--){
        solve();
        fflush(stdout);
    }
    return 0;
}