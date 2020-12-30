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
const int N=4000005;
int n,m,sx,sy,ex,ey;
char s[2005][2005];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int dis[2005][2005];
vector<pii> v[26];
int vis[26];
const int M=2000*2000;
queue<pii> Q;
void bfs(){
    memset(dis,0x3f,sizeof(dis));
    dis[sx][sy]=0;
    while(!Q.empty()) Q.pop();
    Q.push(mk(sx,sy));
    while(!Q.empty()){
        pii u=Q.front(); Q.pop();
        int x=u.first,y=u.second;
        if(s[x][y]>='a'&&s[x][y]<='z'){
            int c=s[x][y]-'a';
            if(!vis[c]){
                for(auto &to : v[c]){
                    int xx=to.first,yy=to.second;
                    if(dis[xx][yy]<M) continue;
                    dis[xx][yy]=dis[x][y]+1;
                    Q.push(mk(xx,yy));
                }
                vis[c]=1;
            }
        }
        for(int i=0;i<4;i++){
            int xx=x+dx[i],yy=y+dy[i];
            if(xx<1||yy<1||xx>n||yy>m||dis[xx][yy]<M||s[xx][yy]=='#') continue;
            dis[xx][yy]=dis[x][y]+1;
            Q.push(mk(xx,yy));
            if(xx==ex&&yy==ey){
                printf("%d\n",dis[ex][ey]);
                return;
            }
        }
    }
    puts("-1");
}

int main()
{
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        for(int j=1;j<=m;j++){
            if(s[i][j]=='S') sx=i,sy=j;
            else if(s[i][j]=='G') ex=i,ey=j;
            else if(s[i][j]!='.'&&s[i][j]!='#'){
                int c=s[i][j]-'a';
                v[c].push_back(mk(i,j));
            }
        }
    }
    bfs();
    return 0;
}