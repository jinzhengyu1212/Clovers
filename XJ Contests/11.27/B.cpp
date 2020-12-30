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
const int N=200005;
int n,a[N],st[2][N][20],lg[N],pos[N];

void init(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),pos[a[i]]=i;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++){
        if(i&1) st[0][i][0]=a[i],st[1][i][0]=inf;
        else st[0][i][0]=inf,st[1][i][0]=a[i];
    }
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            int to=i+(1<<(j-1));
            for(int bl=0;bl<2;bl++)
                st[bl][i][j]=min(st[bl][i][j-1],st[bl][to][j-1]);
        }
    }
}

int query(int l,int r,int bl){
    int sz=r-l+1;
    return min(st[bl][l][lg[sz]],st[bl][r-(1<<lg[sz])+1][lg[sz]]);
}

struct node{
    int l,r,mi;
    bool operator < (const node &rhs) const{
        return mi>rhs.mi;
    }
};
priority_queue<node> Q;

vector<int> ans;
void solve(int l,int r){
    if(l>r) return;
    int mi1,mi2;
    if(l&1) mi1=query(l,r,0),mi2=query(pos[mi1],r,1);
    else mi1=query(l,r,1),mi2=query(pos[mi1],r,0);
    ans.push_back(mi1); ans.push_back(mi2);
    int pos1=pos[mi1],pos2=pos[mi2];
    int x1=inf,x2=inf,x3=inf;
    if(pos1!=l) x1=query(l,pos1-1,(l%2)^1),Q.push({l,pos1-1,x1});
    if(pos1+1!=pos2) x2=query(pos1+1,pos2-1,pos1&1),Q.push({pos1+1,pos2-1,x2});
    if(pos2!=r) x3=query(pos2+1,r,pos2&1),Q.push({pos2+1,r,x3});
}

int main()
{
    init();
    int mi1=query(1,n,0),mi2=query(pos[mi1],n,1);
    Q.push({1,n,mi1});
    while(!Q.empty()){
        node now=Q.top(); Q.pop();
        solve(now.l,now.r);
    }
    for(int i=0;i<n;i++) printf("%d ",ans[i]); puts("");
    return 0;
}