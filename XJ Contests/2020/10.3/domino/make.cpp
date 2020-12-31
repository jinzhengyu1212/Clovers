#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    cout<<1<<endl;
    int n=1,m=10;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=rand()%4;
            if(x==0) printf("U");
            else if(x==1) printf("D");
            else if(x==2) printf("L");
            else printf("R");
        }
        puts("");
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=rand()%100+1;
            printf("%d ",x);
        }
        puts("");
    }
    int T=20;
    cout<<T<<endl;
    for(int i=1;i<=T;i++){
        int x=rand()%5+1;
        printf("%d ",x);
    }
    puts("");
    return 0;
}