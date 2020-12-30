#include<bits/stdc++.h>
using namespace std;
const int maxn=10;
const int N=205;
int vis[maxn+1],a[N],b[N];
int main(){
    srand(time(0));
    int n=5,l=rand()%(maxn-n)+n;
    cout<<n<<" "<<l<<endl;
    for(int i=1;i<=n;i++){
        int x;
        while(vis[x=rand()%l+1]);
        vis[x]=1;
        a[i]=x;
    }
    sort(a+1,a+n+1);
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        int x;
        while(vis[x=rand()%l+1]);
        vis[x]=1;
        b[i]=x;
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) printf("%d ",a[i]); puts("");
    for(int i=1;i<=n;i++) printf("%d ",b[i]); puts("");
    return 0;
}