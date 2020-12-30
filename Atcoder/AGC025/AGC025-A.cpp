#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n; int sum=0;
    while(n) sum+=n%10, n/=10;
    if(sum==1) sum=10;
    cout<<sum<<endl;
}