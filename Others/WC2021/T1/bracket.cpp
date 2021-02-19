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
const int N=300005;
int n,m,k; vector<pii> v[N];
void init(){
    n=read(); m=read(); k=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),w=read();
        v[x].push_back(mk(y,w)); v[y].push_back(mk(x,w+k));
    }
}

namespace solver1{
    int ans=0,bl[3005][3005];
    vector<int> arr;
    void dfs(int u,int f,int from,int dep){
        if(dep>=22||sz(arr)>10) return;
        if(arr.empty()){
            bl[from][u]=1;
        }
        for(int i=0;i<sz(v[u]);i++){
            pii to=v[u][i]; 
            if(to.first==f) continue;
            int flag=1,tmp; 
            if(!arr.empty()) tmp=arr.back();
            if(!arr.empty()&&to.second-k==arr.back()) arr.pop_back();
            else arr.push_back(to.second),flag=0;
            dfs(to.first,u,from,dep+1);
            if(flag) arr.push_back(tmp);
            else arr.pop_back();
        }
    }
    void main(){
        for(int i=1;i<=n;i++){
            arr.clear();
            dfs(i,-1,i,0);
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                ans+=bl[i][j];
            }
        }
        cout<<ans<<endl;
    }
}

void solve(){
    if(m<=10){
        solver1::main();
        return;
    }
    else{
        solver1::main();
        return;
    }
}

int main()
{
    //freopen("bracket.in","r",stdin);
    //freopen("bracket.out","w",stdout);
    init(); solve();
    fclose(stdin); fclose(stdout);
    return 0;
}