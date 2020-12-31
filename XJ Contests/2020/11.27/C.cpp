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
const int N=10;
int dp[N][N][N][N][N][N][2]; 
bool vis[N][N][N][N][N][N][2];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int hx[]={1,1,-1,-1,2,-2,2,-2};
int hy[]={2,-2,2,-2,1,1,-1,-1};
#define INVALID puts("Mogic WXH is a gay!")
#define LOSE puts("Mogic WXH always wins.")
void WIN(int x){
    printf("Mogic WXH wins in %d steps.\n",x);
}

bool checkvalid(int bkx,int bky,int bhx,int bhy,int rkx,int rky){
    if(bkx>9||bkx<7||bky>5||bky<3) return 0;
    if(rkx<0||rkx>2||rky>5||rky<3) return 0;
    if(bhx<0||bhy<0||bhx>9||bhy>8) return 0;
    if(bkx==bhx&&bky==bhy) return 0;
    if(rkx==bhx&&rky==bhy) return 0;
    return 1;
}
//1:black
bool invalid(int bkx,int bky,int bhx,int bhy,int rkx,int rky,int flag){
    if(bky==rky) return 1;
    if(flag){
        for(int i=0;i<8;i++){
            int x=bhx+hx[i],y=bhy+hy[i];
            if(x==rkx&&y==rky) return 1;
        }
    }
    return 0;
}

bool eat_horse(int bkx,int bky,int bhx,int bhy,int rkx,int rky){
    if(bky==bhy) return 0;
    for(int i=0;i<4;i++){
        int x=rkx+dx[i],y=rky+dy[i];
        if(rkx<0||rkx>2||rky>5||rky<3) continue;
        if(x==bhx&&y==bhy) return 1;
    }
    return 0;
}

int dfs(int bkx,int bky,int bhx,int bhy,int rkx,int rky,int flag){
    int &now=dp[bkx][bky][bhx][bhy][rkx][rky][flag];
    if(now!=-1) return now;
    if(invalid(bkx,bky,bhx,bhy,rkx,rky,flag)){
        if(flag) return dp[bkx][bky][bhx][bhy][rkx][rky][flag]=1;
        else return dp[bkx][bky][bhx][bhy][rkx][rky][flag]=inf;
    }
    vis[bkx][bky][bhx][bhy][rkx][rky][flag]=1;
    if(flag){
        now=inf;
        for(int i=0;i<4;i++){
            int x=bkx+dx[i],y=bky+dy[i];
            if(!checkvalid(x,y,bhx,bhy,rkx,rky)) continue;
            if(vis[x][y][bhx][bhy][rkx][rky][flag^1]&&
                dp[x][y][bhx][bhy][rkx][rky][flag^1]==0) continue;
            now=min(now,dfs(x,y,bhx,bhy,rkx,rky,flag^1)+1);
        }
        for(int i=0;i<8;i++){
            int x=bhx+hx[i],y=bhy+hy[i];
            if(!checkvalid(bkx,bky,x,y,rkx,rky)) continue;
            if(vis[bkx][bky][x][y][rkx][rky][flag^1]&&
                dp[bkx][bky][x][y][rkx][rky][flag^1]==0) continue;
            now=min(now,dfs(bkx,bky,x,y,rkx,rky,flag^1)+1);
        }
        return now;
    }
    else{
        now=0;
        for(int i=0;i<4;i++){
            int x=rkx+dx[i],y=rky+dy[i];
            if(!checkvalid(bkx,bky,rkx,rky,x,y)) continue;
            now=max(now,dfs(bkx,bky,rkx,rky,x,y,flag^1)+1);
        }
        return now;
    }
}

int bkx,bky,bhx,bhy,rkx,rky,flag;
void init(){
    bhx=read(); bhy=read();
    bkx=read(); bky=read();
    rkx=read(); rky=read();
    flag=read();
}

int main()
{
    int T=read();
    memset(dp,-1,sizeof(dp));
    while(T--){
        init();
        if(!checkvalid(bkx,bky,bhx,bhy,rkx,rky)){
            INVALID;
            continue;
        }
        if(!flag&&invalid(bkx,bky,bhx,bhy,rkx,rky,flag)){
            dp[bkx][bky][bhx][bhy][rkx][rky][flag]=inf;
            LOSE;
            continue;
        }
        if(!flag&&eat_horse(bkx,bky,bhx,bhy,rkx,rky)){
            dp[bkx][bky][bhx][bhy][rkx][rky][flag]=inf;
            LOSE;
            continue;
        }
        int ans=dfs(bkx,bky,bhx,bhy,rkx,rky,flag);
        WIN(ans);
    }
    return 0;
}