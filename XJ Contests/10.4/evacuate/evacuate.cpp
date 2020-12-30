#include<bits/stdc++.h>
using namespace std;
const int N=505;
const int inf=(int)1e9;
typedef pair<int,int> pii;
#define mk make_pair
int T,r,c,n,m,w[N],p[N];
int a[N][N],cnta; pii A[N*N];

void init(){
    cnta=0;
    scanf("%d%d%d%d",&r,&c,&n,&m);
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            scanf("%d",&a[i][j]);
            if(a[i][j]>=0) A[++cnta]=mk(i,j);
        }
    }
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int i=1;i<=m;i++) scanf("%d",&p[i]);
}

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
//0:R 1:L 2:D 3:U
namespace solver1{
    int mp[N][N],max_survive,ans=inf,vis[N],bl[N][N];
    int col[N];
    bool run(int x,int y,int dir){
        bl[x][y]=1;
        if(x>r){
            if(!vis[y]){vis[y]=1; return 1;}
            else return 0;
        }
        int xx=x+dx[dir],yy=y+dy[dir];
        if(xx<1||yy<1||yy>c||mp[xx][yy]<0||bl[xx][yy]) return 0;
        if(mp[xx][yy]==0) return run(xx,yy,dir);
        else if(mp[xx][yy]==1){
            if(dir==2) dir=1;
            else if(dir==0) dir=3;
            else return 0;
            return run(xx,yy,dir);
        }
        else if(mp[xx][yy]==2){
            if(dir==2) dir=0;
            else if(dir==1) dir=3;
            else return 0;
            return run(xx,yy,dir);
        }
        else if(mp[xx][yy]==3){
            if(dir==3) dir=1;
            else if(dir==0) dir=2;
            else return 0;
            return run(xx,yy,dir);
        }
        else{
            if(dir==3) dir=0;
            else if(dir==1) dir=2;
            else return 0;
            return run(xx,yy,dir);
        }
    }
    void judge(){
        for(int i=1;i<=12;i++){
            vis[i]=-1;
            for(int j=1;j<=12;j++) bl[i][j]=0;
        }
        for(int i=1;i<=m;i++) vis[p[i]]=0;
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                if(a[i][j]>=0||a[i][j]==-2) mp[i][j]=0;
                else mp[i][j]=a[i][j];
            }
        }
        int sum=0,val=0;
        for(int i=1;i<=cnta;i++){
            if(col[i]) val+=a[A[i].first][A[i].second];
            mp[A[i].first][A[i].second]=col[i];
        }
        for(int i=1;i<=n;i++){
            for(int x=1;x<=r;x++){
                for(int y=1;y<=c;y++) bl[x][y]=0;
            }
            if(run(0,w[i],2)) sum++;
        }
        if(sum==n) ans=min(ans,val);
        else max_survive=max(max_survive,sum);
    }
    void dfs(int now){
        if(now==cnta+1){
            judge();
            return;
        }
        for(int i=0;i<=4;i++){
            col[now]=i;
            dfs(now+1);
        }
    }
    void main(){
        memset(mp,0,sizeof(mp));
        ans=inf; max_survive=0;
        memset(vis,0,sizeof(vis));
        dfs(1);
        if(ans!=inf){
            puts("YES");
            printf("%d\n",ans);
        }
        else{
            puts("NO");
            printf("%d\n",max_survive);
        }
    }   
}

void solve(){
    if(cnta<=10){
        solver1::main();
        return;
    }
}

int main(){
    cin>>T;
    while(T--){
        init();
        solve();
    }
    return 0;
}