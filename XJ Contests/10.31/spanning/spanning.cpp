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
const int MOD1=19260817;
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
const int N=50;
const int MASK=40005;
const int B=97;
int id[MOD1],Base[N],cnt=0;
int n,a[N],m;
vector<int> mask[MASK];
int h(vector<int> V){
    int ret=0;
    for(int i=0;i<sz(V);i++) ret=(ret+1ll*Base[i]*V[i]%MOD1)%MOD1;
    return ret;    
}
 
void dfs(int now,int pre,vector<int> V){
    if(now==n){
       int tmp=h(V); id[tmp]=++cnt;
       mask[cnt]=V;
       return;
    }
    for(int i=pre;i+now<=n;i++){
        int to=i+now;
        if(to-now<i&&to!=n) continue;
        V.push_back(i);
        dfs(to,i,V);
        V.pop_back();
    }
}
 
void init(){
    scanf("%d",&n);
    for(int i=1;i<n;i++) scanf("%d",&a[i]);
    Base[0]=1; for(int i=1;i<=n;i++) Base[i]=mul(Base[i-1],B);
    vector<int> emp; emp.clear();
    dfs(0,1,emp);
    sort(a+1,a+n);
}
 
void print(vector<int> V){
    for(auto &j : V) cout<<j<<" "; cout<<endl;
}
 
int dp[N][MASK],vis[N],fac[N*N],ifac[N*N];
void solve(){
    dp[1][1]=1; m=n*(n-1)/2;
    fac[0]=1;
    for(int i=1;i<=m;i++) fac[i]=mul(fac[i-1],i);
    ifac[m]=qpow(fac[m],MOD-2); ifac[0]=1;
    for(int i=m-1;i>=1;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=1;i<n;i++){
        for(int j=1;j<=cnt;j++){
            if(mask[j].size()!=n-i+1) continue;
            for(int k=1;k<=n;k++) vis[k]=0;
            vector<int> v=mask[j],val;
            val.clear();
            for(auto &to : v){
                if(!vis[to]) val.push_back(to);
                vis[to]++;
            }
            int IN=0;
            for(auto &to : v) IN=add(IN,to*(to-1)/2-to+1);
            IN=IN-a[i-1]+(i-1);
            //!! can't be a circle.
            for(auto &j1 : val){
                for(auto &j2 : val){
                    if(j1==j2&&vis[j1]==1) continue;
                    if(j1>j2) continue;
                    vector<int> tmp; tmp.clear();
                    vis[j1]--; vis[j2]--; vis[j1+j2]++;
                    for(int j3=1;j3<=n;j3++)
                        for(int k=1;k<=vis[j3];k++) tmp.push_back(j3);
                    vis[j1]++; vis[j2]++; vis[j1+j2]--;
                    int to=id[h(tmp)];
                    int P=(j1==j2 ? vis[j1]*(vis[j1]-1)/2 : vis[j1]*vis[j2]);
                    int OUT=j1*j2;
                    int rest=a[i]-a[i-1]-1;
                    if(IN>=rest){
                        int Tmp=mul(fac[IN],ifac[IN-rest]);
                        Tmp=mul(Tmp,mul(OUT,P));
                        dp[i+1][to]=add(dp[i+1][to],mul(Tmp,dp[i][j]));
                    }
                }
            }
        }
    }
    printf("%lld\n",mul(dp[n][cnt],fac[m-a[n-1]]));
}
 
int main()
{
    init(); solve();
    return 0;
}