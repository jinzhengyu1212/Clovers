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
const int M=505;
const int N=M*M;
#define ran(l,r) rand()%((r)-(l)+1)+(l)
int tot,n,m,S;
char s[M][M],a[M][M],b[M][M];
int idx(int x,int y){
    return (x-1)*m+y;
}

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        for(int j=1;j<=m;j++){
            if(s[i][j]=='#') tot++;
            a[i][j]=s[i][j]; b[i][j]=s[i][j];
        }
    }
}

int main()
{
    srand(time(NULL));
    init();
    int mid=(min(n,m)+1)/2;
    for(int len=1;len<=mid;len++){
        int sx=len,sy=len,ex=n-len+1,ey=m-len+1;
        int bl=0;
        for(int i=sy;i<=ey;i++){
            if((s[sx][i]=='#'||s[ex][i]=='#')&&i!=sy&&i!=ey) bl=1;
            if(len&1) a[sx][i]='#',a[ex][i]='#';
            else b[sx][i]='#',b[ex][i]='#';
        }
        for(int i=sx;i<=ex;i++){
            if((s[i][sy]=='#'||s[i][ey]=='#')&&i!=sx&&i!=ex) bl=1;
            if(len&1) a[i][sy]='#',a[i][ey]='#';
            else b[i][sy]='#',b[i][ey]='#';
        }
        if(len==mid||len==1||bl==1) continue;
        sx=len+1,sy=len+1,ex=n-len,ey=m-len;
        int posx=sx-1,posy=ran(sy,ey);
        for(int i=sy;i<=ey;i++){
            char c1,c2;
            c1=(len&1 ? b[sx-2][i] : a[sx-2][i]);
            c2=(len&1 ? b[ex+2][i] : a[ex+2][i]);
            if(s[sx][i]=='.'&&c1=='#') posx=sx-1,posy=i;
            if(s[ex][i]=='.'&&c2=='#') posx=ex+1,posy=i;
        }
        for(int i=sx;i<=ex;i++){
            char c1,c2;
            c1=(len&1 ? b[i][sy-2] : a[i][sy-2]);
            c2=(len&1 ? b[i][ey+2] : a[i][ey+2]);
            if(s[i][sy]=='.'&&c1=='#') posx=i,posy=sy-1;
            if(s[i][ey]=='.'&&c2=='#') posx=i,posy=ey+1;
        }
        if(s[posx][posy]=='.') swap(b[posx][posy],a[posx][posy]); 
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) printf("%c",a[i][j]);
        puts("");
    } puts("");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) printf("%c",b[i][j]);
        puts("");
    }
    return 0;
}