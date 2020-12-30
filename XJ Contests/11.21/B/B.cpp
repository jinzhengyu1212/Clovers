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
const int N=100005;
int n,Q; char s[N];
int getdir(char c){
    if(c=='R') return 0;
    else if(c=='L') return 1;
    else if(c=='D') return 2;
    else if(c=='U') return 3;
}
int dx[]={1,-1,0,0};
int dy[]={0,0,-1,1};
pii A[4][N],Step[N];
int nxt[N];
map<pii,int> mp;

void run(){
    mp.clear();
    for(int i=0;i<=3;i++){
        A[i][n]=mk(-dx[i],-dy[i]);
    }
    mp[Step[n]]=n;
    int nowx=0,nowy=0;
    for(int i=n-1;i>=0;i--){
        int x=Step[i].first,y=Step[i].second;
        int dir=getdir(s[i+1]);
        nowx+=dx[dir],nowy+=dy[dir];
        for(int D=0;D<=3;D++){
            int Dx=dx[D],Dy=dy[D];
            if(mp.count(mk(x+Dx,y+Dy))){
                int pos=mp[mk(x+Dx,y+Dy)];
                A[D][i]=A[getdir(s[pos])][pos];
            }
            else A[D][i]=mk(nowx-Dx,nowy-Dy);
        }
        if(i) mp[mk(x,y)]=i;
    }
}

void init(){
    n=read(); scanf("%s",s+1);
    int nowx=0,nowy=0;
    for(int i=1;i<=n;i++){
        int dir=getdir(s[i]);
        nowx+=dx[dir],nowy+=dy[dir];
        Step[i]=mk(nowx,nowy);
    }
    Step[0]=mk(0,0);
    run();
}

void solve(){
    Q=read();
    int xn=Step[n].first,yn=Step[n].second;
    while(Q--){
        int x=read(),y=read();
        if(!mp.count(mk(-x,-y))){
            printf("%d %d\n",x+xn,y+yn);
            continue;
        }
        int pos=mp[mk(-x,-y)],D=getdir(s[pos]);
        printf("%d %d\n",A[D][pos].first,A[D][pos].second);
    }
}

int main()
{
    init();
    solve();
    return 0;
}