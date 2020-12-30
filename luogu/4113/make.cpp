#include<bits/stdc++.h>
using namespace std;
int main(){
    srand(time(0));
    int n=300000,c=300000,m=300000;
    printf("%d %d %d\n",n,c,m);
    for(int i=1;i<=n;i++){
        int x=rand()%c+1;
        printf("%d ",x);
    } puts("");
    for(int i=1;i<=m;i++){
        int r=rand()%n+1;
        int l=rand()%r+1;
        printf("%d %d\n",l,r);
    }
    return 0;
}