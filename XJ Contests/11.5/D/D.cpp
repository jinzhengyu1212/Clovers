#include<bits/stdc++.h>
using namespace std;
const int N=500;
const int MOD=998244353;
int a[N][N],n,m,A[N],scc[N];
int tot=0;
vector<int> v[N];
void add_edge(int u,int v)
{
    a[u][u]++;
    a[u][v]--;
}

void init()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&A[i]);
        for(int j=1;j<=A[i];j++){
            v[i].push_back(++tot);
            scc[tot]=i;
        }
    }
    //cout<<tot<<endl;
    for(int i=1;i<=m;i++){
        int x,y; scanf("%d%d",&x,&y);
        for(auto &j1 : v[x]){
            for(auto &j2 : v[y]){
                //cout<<j1<<" "<<j2<<"PPP\n";
                add_edge(j1,j2);
                add_edge(j2,j1);
            }
        }
    }
    // for(int i=1;i<=tot;i++){
    //     for(int j=1;j<=tot;j++) printf("%d ",a[i][j]);
    //     puts("");
    // }
}

int _abs(int x){return x<0 ? -x : x;}
void sub(int i1,int i2,int ti)
{
    for(int j=1;j<=tot;j++) a[i1][j]=(a[i1][j]-1ll*a[i2][j]*ti%MOD+MOD)%MOD;
}
void solve()
{
    int ans=1;
    for(int j=1;j<tot;j++)
    {
        for(int i=j+1;i<tot;i++)
        {
            while(a[i][j]!=0)
            {
                if(a[i][j]==0) break;
                int ti=a[j][j]/a[i][j];
                sub(j,i,ti);
                swap(a[i],a[j]),ans=-ans;
            }
        }
    }
    for(int i=1;i<tot;i++) ans=1ll*ans*a[i][i]%MOD;
    cout<<(ans%MOD+MOD)%MOD<<endl;
}

int main()
{
    init();
    solve();
    return 0;
}