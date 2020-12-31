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
typedef vector<int> V;
typedef vector<V> mac;
map<mac,int> mp;
int n;

pii find(mac A){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(A[i][j]==0) return mk(i,j);
        }
    }
}

bool up(mac &A){
    pii pos=find(A);
    if(pos.first==0) return 0;
    swap(A[pos.first][pos.second],A[pos.first-1][pos.second]);
    return 1;
}
bool down(mac &A){
    pii pos=find(A);
    if(pos.first==n-1) return 0;
    swap(A[pos.first][pos.second],A[pos.first+1][pos.second]);
    return 1;
}
bool left(mac &A){
    pii pos=find(A);
    if(pos.second==0) return 0;
    swap(A[pos.first][pos.second],A[pos.first][pos.second-1]);
    return 1;
}
bool right(mac &A){
    pii pos=find(A);
    if(pos.second==n-1) return 0;
    swap(A[pos.first][pos.second],A[pos.first][pos.second+1]);
    return 1;
}

int idx(int x,int y){
    return x*n+y;
}
bool check(mac A){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(A[i][j]!=idx(i,j)) return 0;
        }
    }
    return 1;
}

void print(mac A){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) printf("%d ",A[i][j]);
        puts("");
    }
}

mac Copy;
int cnt=0;
char c[]={'L','R','D','U'};
void dfs(mac A,string S){
    if(check(A)){
        cout<<S<<endl;
        exit(0);
    }
    for(int opt=0;opt<4;opt++){
        Copy=A;
        int tmp;
        if(opt==0) tmp=left(Copy);
        else if(opt==1) tmp=right(Copy);
        else if(opt==2) tmp=down(Copy);
        else tmp=up(Copy);
        if(!tmp) continue;
        if(mp[Copy]) continue;
        mp[Copy]=1;
        dfs(Copy,S+c[opt]);
    }
}

mac a;
int main()
{
    n=read();
    a.resize(n);
    for(int i=0;i<n;i++) a[i].resize(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) a[i][j]=read();
    mp[a]=1;
    string S="";
    dfs(a,S);
    puts("Impossible");
    return 0;
}