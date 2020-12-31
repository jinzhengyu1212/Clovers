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
int n,w,h,val[N],nn;
pii ans[N],dest[N];
struct node{
    int typ,x,ti,dis;
}a[N];
vector<int> v1[N],v2[N];
bool cmp(int x,int y){
    return a[x].x<a[y].x;
}

void init(){
    n=read(); w=read(); h=read();
    for(int i=1;i<=n;i++){
        a[i].typ=read(); a[i].x=read(); a[i].ti=read();
        a[i].dis=a[i].ti-a[i].x; val[i]=a[i].dis;
        if(a[i].typ==1) dest[i]=mk(w,a[i].x);
        else dest[i]=mk(a[i].x,h);
    }
    sort(val+1,val+n+1); nn=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=n;i++) a[i].dis=lower_bound(val+1,val+nn+1,a[i].dis)-val;
}

deque<int> q;
void solve(){
    for(int i=1;i<=n;i++){
        if(a[i].typ==1) v1[a[i].dis].push_back(i);
        else v2[a[i].dis].push_back(i);
    }
    for(int i=1;i<=nn;i++){
        sort(v1[i].begin(),v1[i].end(),cmp);
        sort(v2[i].begin(),v2[i].end(),cmp);
    }
    for(int i=1;i<=nn;i++){
        if(v1[i].empty()){
            for(auto &to : v2[i]) ans[to]=dest[to];
            continue;
        }
        while(!q.empty()) q.pop_front();
        for(auto &to : v1[i]) q.push_back(to);
        for(auto &to : v2[i]){
            int u=q.back(); q.pop_back();
            ans[u]=dest[to];
            q.push_front(to);
        }
        int now=0;
        while(!q.empty()){
            int u=q.front(); q.pop_front();
            ans[u]=dest[v1[i][now]];
            now++;
        }
    }
    for(int i=1;i<=n;i++) printf("%d %d\n",ans[i].first,ans[i].second);
}

int main()
{
    init(); solve();
    return 0;
}