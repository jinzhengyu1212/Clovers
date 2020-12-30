#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int n=1000,m=1000;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=n;i++) printf("%d ",rand()%20000000+1);
    puts("");
    for(int i=1;i<=m;i++){
        int flag=rand()%2+1,l,r;
        if(flag==2){
            l=rand()%n+1,r=l;
        }
        else{
            r=rand()%n+1,l=rand()%r+1;
        }
        printf("%d %d %d\n",flag,l,r);
    }
}