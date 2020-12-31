#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
const int N=30005;
const int M=55;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int n,m,deg[N]; 
vector<int> v[N];
int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}

int up[N],down[N],fac[M],invfac[M];
int C(int n,int m){
    return mul(fac[n],mul(invfac[n-m],invfac[m]));
}
namespace Subtask{
int ans[N],sz[N],ANS=0;
void dfs_up(int u,int f){
    up[u]=deg[u]; sz[u]=1;
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==f) continue;
        dfs_up(to,u); up[u]=add(up[to],up[u]); sz[u]+=sz[to];
    }
    if(f!=-1){
        down[u]=2*n-2-up[u];
        ANS=add(ANS,mul(mul(sz[u],n-sz[u]),2*n-2));
    }
}
void dfs_ans(int u,int f){
    if(f!=-1) ans[u]=add(ans[f],up[u]);
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==f) continue;
        dfs_ans(to,u);
    }
}

void subtask0(){//88Pts
    int ret=0;
    for(int root=1;root<=n;root++){
        for(int i=1;i<=n;i++) ans[i]=0;
        dfs_up(root,-1); dfs_ans(root,-1);
        for(int i=1;i<=n;i++) ret=add(ret,qpow(ans[i],m));
    }
    printf("%d\n",ret);
}

void subtask1(){//92Pts
    dfs_up(1,-1);
    printf("%d\n",ANS);
}
}

void dfs1(int u,int f){
    up[u]=deg[u];
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==f) continue;
        dfs1(to,u); up[u]=add(up[to],up[u]);
    }
    if(f!=-1) down[u]=2*n-2-up[u];
}

int Up[N][M],Down[N][M],Sum[N][M],son_up[N][M],son_down[N][M];
void dfs2(int u,int f){
    Up[u][1]=add(Up[f][1],up[u]);
    Down[u][1]=add(Down[f][1],down[u]);
    Sum[u][1]=add(Sum[f][1],add(up[u],down[u]));
    for(int i=0;i<=m;i++){
        Up[u][i]=qpow(Up[u][1],i), 
        Down[u][i]=qpow(Down[u][1],i),
        Sum[u][i]=qpow(Sum[u][1],i);
    }
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==f) continue;
        dfs2(to,u); 
        for(int j=0;j<=m;j++){
            son_up[u][j]=add(son_up[u][j],add(son_up[to][j],Up[to][j])); 
            son_down[u][j]=add(son_down[u][j],add(son_down[to][j],Down[to][j]));
        }
    }
}

int ans=0;
void dfs3(int u,int f){
    for(int t=0;t<(int)v[u].size();t++){
        int to=v[u][t]; if(to==f) continue;
        dfs3(to,u);
        for(int i=0;i<=m;i++){
            int tmp=((m-i)&1 ? MOD-Sum[u][m-i] : Sum[u][m-i]);
            int tmp1=mul(tmp,C(m,m-i));
            for(int j=0;j<=i;j++){
                int rest_down=sub(son_down[u][i-j],add(Down[to][i-j],son_down[to][i-j]));
                int tmp2=mul(C(i,j),mul(add(son_up[to][j],Up[to][j]),rest_down));
                ans=add(ans,mul(tmp1,tmp2));
            }
        }
    }
    for(int i=0;i<=m;i++){
        int tmp=((m-i)&1 ? MOD-Up[u][m-i] : Up[u][m-i]);
        int tmp3=mul(mul(tmp,C(m,m-i)),son_up[u][i]);
        ans=add(ans,tmp3); //up&fa
        tmp=((m-i)&1 ? MOD-Down[u][m-i] : Down[u][m-i]);
        int tmp4=mul(mul(tmp,C(m,m-i)),son_down[u][i]);
        ans=add(ans,tmp4); //down&fa
    }
}

void solve(){
    dfs1(1,0);
    up[1]=down[1]=0; dfs2(1,0);
    dfs3(1,0);
    printf("%d\n",ans);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        v[x].push_back(y); v[y].push_back(x);
        deg[x]++; deg[y]++;
    }
    fac[0]=1;
    for(int i=1;i<=m;i++) fac[i]=mul(i,fac[i-1]);
    invfac[m]=qpow(fac[m],MOD-2); invfac[0]=1;
    for(int i=m-1;i>=1;i--) invfac[i]=mul(invfac[i+1],i+1);
    if(n<=3000) Subtask::subtask0();
    else if(m==1) Subtask::subtask1();
    else solve();
    return 0;
}