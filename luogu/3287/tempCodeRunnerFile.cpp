#include<bits/stdc++.h>
using namespace std;
const int N=10005;
const int V=5005;
const int M=505;
void checkmax(int &x,int y){if(x<y) x=y;}
int n,k,a[N];
int dp[N][M];

struct BIT{
    int a[V];
    void init(){memset(a,0,sizeof(a));}
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){
        for(int i=x;i<5000;i+=lowbit(i)) checkmax(a[i],val);
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) checkmax(ret,a[i]);
        return ret;
    }
}tree1[M],tree2[V+M];

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            int mx=tree1[j].query(a[i]);
            checkmax(mx,tree2[j+a[i]].query(V-a[i]));
            dp[i][j]=mx+1;
            tree1[j].update(a[i],dp[i][j]);
            tree2[j+a[i]].update(V-a[i],dp[i][j]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) checkmax(ans,dp[i][k]);
    cout<<ans<<endl;
    return 0;
}