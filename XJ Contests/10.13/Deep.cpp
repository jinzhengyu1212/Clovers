#include<bits/stdc++.h>
using namespace std;

int T,a,b;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--){
        int ans=0;
        cin>>a>>b;
        if(a==0)
            cout<<-b<<"\n";
        else if(b==0) cout<<a<<"\n";
        else cout<<a-b-2<<'\n';
    }
}