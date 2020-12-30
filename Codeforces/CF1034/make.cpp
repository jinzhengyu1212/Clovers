#include<bits/stdc++.h>
using namespace std;
const int maxw=(int)1e8;
int main(){
    srand(time(0));
    int n=1000000; cout<<n<<endl;
    for(int i=1;i<=n;i++){
        int x=(rand()%maxw+1)*2;
        printf("%d ",x);
    } puts("");
    for(int i=1;i<n;i++){
        printf("%d ",rand()%i+1);
    } puts("");
}