#include<bits/stdc++.h>
using namespace std;
const int N=3000;
int vis[N+1];
int main(){
    srand(time(NULL));
    int n=30,m=50;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=n;i++){
        int x=rand()%N+1;
        printf("%d ",x);
    } puts("");
    for(int i=1;i<=m;i++){
        int x;
        while(vis[x=rand()%N+1]);
        vis[x]=1;
        printf("%d ",x);
    }
    puts("");
}