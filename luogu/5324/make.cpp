#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    int n=10000,Q=100000;
    cout<<n<<" "<<Q<<endl;
    for(int i=1;i<=n;i++) printf("%d ",rand()%n+1); puts("");
    for(int i=1;i<=Q;i++){
        int opt=rand()%2;
        if(opt==0){
            int x=rand()%2;
            if(x==0) puts("0 1");
            else puts("0 -1");
        }
        else{
            opt=rand()%n+1;
            int x=rand()%n+1;
            printf("%d %d\n",opt,x);
        }
    }
    return 0;
}