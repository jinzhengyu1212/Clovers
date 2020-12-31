#include<bits/stdc++.h>
using namespace std;
const int maxn=(int)1e9;
const int maxw=(int)1e5;

int main(){
    srand(time(0));
    int n=100000,q=100000,typ=0,W=0;
    printf("%d %d %d %d\n",n,q,typ,W);
    for(int i=1;i<=n;i++) printf("%d ",rand()%102+1);
    cout<<endl;
    for(int i=1;i<=q;i++){
        int r=rand()%n+1,l=rand()%r+1,w=rand()%maxw;
        printf("%d %d %d\n",l,r,w);
    }
    return 0;
}