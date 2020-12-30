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
const int N=500005;
const int M=1005;

int a[N],vis[7];
int calc(int n){
    int ret=0;
    for(int i=1;i<=n;i++){
        int mx=0,cnt=0; memset(vis,0,sizeof(vis));
        for(int j=i;j<=n;j++){
            if(!vis[a[j]]) cnt++;
            else break;
            checkmax(mx,a[j]); vis[a[j]]=1;
            if(mx==cnt) ret++;
        }
    }
    return ret;
}

typedef vector<int> V;
vector<V> ans;
int mx=0,n;
void dfs(int now){
    if(now==n){
        V v; v.clear();
        for(int i=1;i<=n;i++) v.push_back(a[i]);
        int ret=calc(n);
        if(mx<ret){
            ans.clear();
            mx=ret;
            ans.push_back(v);
        } 
        else if(mx==ret) ans.push_back(v);
        return;
    }
    for(int i=1;i<=6;i++){
        a[now+1]=i;
        dfs(now+1);
    }
}

int main()
{
    n=read();
    a[1]=1; a[2]=2; a[3]=1; a[4]=3; a[5]=2; a[6]=1;
    a[7]=4; a[8]=3; a[9]=2; a[10]=1; a[11]=5; a[12]=4;
    a[13]=3; a[14]=2;
    //cout<<calc(6)<<endl;
    dfs(14);
    cout<<mx<<endl;
    for(auto &seq : ans){
        for(auto &to : seq) printf("%d ",to);
        puts("");
    }
    return 0;
}