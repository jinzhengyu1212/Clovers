#include<bits/stdc++.h>
using namespace std;

int main(){
    int n=90,m=(n-1)*n;
    cout<<n<<" "<<m<<" "<<20<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) if(i!=j){
            printf("%d %d %d\n",i,j,rand()%2);
        }
    }
    return 0;
}