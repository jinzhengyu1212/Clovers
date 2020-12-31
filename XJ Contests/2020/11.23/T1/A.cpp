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
int min4(int x,int y,int p,int q){return min(min(x,y),min(p,q));}
int max4(int x,int y,int p,int q){return max(max(x,y),max(p,q));}
const int N=801;
int a[N][N],sum[N][N],n,m;
int mx[N][N][10],mi[N][N][10],lg[1000];

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]=read();
            mx[i][j][0]=a[i][j]; mi[i][j][0]=a[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        }
    }
    for(int i=2;i<1000;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=lg[min(i,j)];k++){
                int sx=i-(1<<(k-1)),sy=j-(1<<k-1);
                mi[i][j][k]=min4(mi[i][j][k-1],mi[sx][j][k-1],mi[i][sy][k-1],mi[sx][sy][k-1]);
                mx[i][j][k]=max4(mx[i][j][k-1],mx[sx][j][k-1],mx[i][sy][k-1],mx[sx][sy][k-1]);
                //cout<<i<<" "<<j<<" "<<k<<" "<<mx[i][j][k]<<endl;
            }
        }
    }
}

int Min(int sx,int sy,int ex,int ey){
    int T=min(ex-sx+1,ey-sy+1),S=lg[T],len=(1<<S);
    int ret;
    if(ex-sx+1<=ey-sy+1){
        ret=min(mi[sx+len-1][sy+len-1][S],mi[ex][sy+len-1][S]);
        sy+=len;
        while(ey>=sy){
            checkmin(ret,min(mi[ex][ey][S],mi[sx+len-1][ey][S]));
            ey-=len;
        }
    }
    else{
        ret=min(mi[sx+len-1][sy+len-1][S],mi[sx+len-1][ey][S]);
        sx+=len;
        while(ex>=sx){
            checkmin(ret,min(mi[ex][ey][S],mi[ex][sy+len-1][S]));
            ex-=len;
        }
    }
    return ret;
}

int Max(int sx,int sy,int ex,int ey){
    int T=min(ex-sx+1,ey-sy+1),S=lg[T],len=(1<<S);
    int ret;
    if(ex-sx+1<=ey-sy+1){
        ret=max(mx[sx+len-1][sy+len-1][S],mx[ex][sy+len-1][S]);
        sy+=len;
        while(ey>=sy){
            checkmax(ret,max(mx[ex][ey][S],mx[sx+len-1][ey][S]));
            ey-=len;
        }
    }
    else{
        ret=max(mx[sx+len-1][sy+len-1][S],mx[sx+len-1][ey][S]);
        sx+=len;
        while(ex>=sx){
            checkmax(ret,max(mx[ex][ey][S],mx[ex][sy+len-1][S]));
            ex-=len;
        }
    }
    return ret;
}

char opt[6];
int sx,sy,ex,ey;
void solve(){
    int Q=read();
    while(Q--){
        scanf("%s",opt);
        sx=read()+1; sy=read()+1; ex=read()+1; ey=read()+1;
        if(opt[0]=='S'){
            printf("%d\n",sum[ex][ey]-sum[sx-1][ey]-sum[ex][sy-1]+sum[sx-1][sy-1]);
        }
        else if(opt[1]=='A'){
            printf("%d\n",Max(sx,sy,ex,ey));
        }
        else{
            printf("%d\n",Min(sx,sy,ex,ey));
        }
    }
}

int main()
{
    init();
    solve();
    return 0;
}