#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    int n=10;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) printf("%d",rand()%3+1);
    return 0;
}