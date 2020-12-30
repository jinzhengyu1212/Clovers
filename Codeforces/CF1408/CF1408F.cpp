#include<bits/stdc++.h>
using namespace std;
const int N=20000;
int n;

void solve(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    if((r-l+1)%2==1){
        solve(l,mid);
        solve(mid,r);
    }
    else{
        solve(l,mid);
        solve(mid+1,r);
    }
}