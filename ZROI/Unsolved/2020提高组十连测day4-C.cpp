#include<bits/stdc++.h>
using namespace std;
const int N=14000;
int n,k,a[N];

void solve(int l,int r,int now){
    if(l==r){a[l]=now; return;}
    if(l>r) return;
    int mid=(l+r)>>1;
    a[mid]=now;
    solve(l,mid-1,now+1); solve(mid+1,r,now+1);
}

int main(){
    scanf("%d%d",&n,&k);
    solve(1,n,1);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    puts("");
    return 0;
}
