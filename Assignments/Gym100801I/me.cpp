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
#define out(x) cerr<<#x<<'='<<x
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=200005;
int n,m,a[N],b[N],c[N],in[N],vis[N],ans[N],pos[N];
vector<int> v[N];

int main()
{
    freopen("insider.in","r",stdin);
    freopen("insider.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        v[a[i]].push_back(i); v[c[i]].push_back(i);
        in[b[i]]++;
    }
    vector<int> S; S.clear();
    queue<int> q; while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
    while(!q.empty()){
        int u=q.front(); q.pop(); S.push_back(u);
        static vector<int> T; T.clear();
        for(auto edg : v[u]){
            if(!vis[edg]) T.push_back(edg),vis[edg]=1;
            if(!--in[b[edg]]) q.push(b[edg]);
        }
        v[u]=T;
    }
    reverse(S.begin(),S.end());
    int L=n+1,R=n;
    for(auto i : S){
        int sumL=0,sumR=0;
        for(auto edg : v[i]){
            int oth=(i==a[edg] ? c[edg] : a[edg]);
            if(pos[b[edg]]<pos[oth]) sumL++;
            else sumR++;
        }        
        if(sumL>sumR) pos[i]=--L;
        else pos[i]=++R;
    }
    int cnt=0;
    for(int i=1;i<=n;i++) ans[pos[i]-L+1]=i;
    for(int i=1;i<=n;i++) printf("%d ",ans[i]); puts("");
    fclose(stdin); fclose(stdout);
    return 0;
}
