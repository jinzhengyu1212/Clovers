#include<bits/stdc++.h>
using namespace std;
const int N=10005;
const int V=5005;
const int M=505;
void checkmax(int &x,int y){if(x<y) x=y;}
int n,k,a[N];
int dp[M];

struct BIT{
    int a[V];
    void init(){memset(a,0,sizeof(a));}
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){
        for(int i=x;i<V;i+=lowbit(i)) checkmax(a[i],val);
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) checkmax(ret,a[i]);
        return ret;
    }
}tree1[M],tree2[V+M];

int main(){
    for(int i=1;i<M;i++) tree1[i].init();
    for(int i=1;i<M+V;i++) tree2[i].init();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            int mx=tree1[j].query(a[i]);
            checkmax(mx,tree2[j+a[i]].query(V-a[i]));
            dp[j]=mx+1;
            tree1[j].update(a[i],dp[j]);
            tree2[j+a[i]].update(V-a[i],dp[j]);
        }
        checkmax(ans,dp[k]);
    }
    cout<<ans<<endl;
    return 0;
}