#include<bits/stdc++.h>
using namespace std;
#define int long long
int l,r,L[30],R[30],cntl=0,cntr=0;
int ans=0;

int A[30],t[30],B[30];
bool checkL(int cnt){
    int tot=0; B[0]=0;
    for(int i=1;i<=9;i++){
        for(int j=t[i];j>=1;j--) B[++tot]=i;
    }
    for(int i=cnt;i>=1;i--){
        if(B[tot]>L[i]) return 1; 
        if((tot==0&&L[i]!=0)||B[tot]<L[i]) return 0;
        if(tot&&L[i]) tot--;
    }
    return 1;
}

bool checkR(int cnt){
    int tot=0;
    for(int i=9;i>=1;i--){
        for(int j=1;j<=t[i];j++) B[++tot]=i;
    }
    for(int i=cnt;i>=1;i--){
        if(B[tot]<R[i]||(tot<=i-1&&R[i]!=0)) return 1;
        if(R[i]==0&&tot>i-1) return 0;
        if(B[tot]>R[i]&&R[i]!=0) return 0;
        if(tot&&R[i]) tot--;
    }
    return 1;
}

bool judge(int cnt){
    int tot=0;
    for(int i=0;i<=9;i++) t[i]=0;
    for(int i=1;i<=cnt;i++) if(A[i]) t[A[i]]++,tot++;
    if(tot>cnt) return 0;
    for(int i=cnt;i>=1;i--){
        if(L[i]==R[i]){
            if(!t[L[i]]&&L[i]!=0) return 0;
            if(!L[i]&&tot==i) return 0;
            if(L[i]) t[L[i]]--,tot--;
            continue; 
        }
        for(int j=L[i]+1;j<R[i];j++) if(t[j]) return 1;
        if(t[L[i]]||(L[i]==0&&tot<=i-1)){
            if(L[i]) t[L[i]]--;
            if(checkL(i-1)) return 1;
            if(L[i]) t[L[i]]++; 
        }
        if(t[R[i]]){
            t[R[i]]--;
            if(checkR(i-1)) return 1;
            t[R[i]]++;
        }
        return 0;
    }
    return 1;
}

int tot=0;
void solve(int now,int pre){
    int sum=0;
    for(int i=1;i<=now-1;i++) sum=sum*10+A[i];
    for(int i=now;i<=19;i++) A[i]=0;
    if(sum>r) return;
    if(now>1) if(judge(cntr)) {
        ans++;
    }
    if(now>cntr) return;
    for(int i=pre;i<=9;i++){
        A[now]=i;
        solve(now+1,i);
        A[now]=0;
    }
}

signed main(){
    scanf("%lld%lld",&l,&r);
    int tmp=l;
    while(tmp){
        L[++cntl]=tmp%10;
        tmp/=10;
    }
    tmp=r; 
    while(tmp){
        R[++cntr]=tmp%10;
        tmp/=10;
    }
    solve(1,1);
    cout<<ans<<endl;
    return 0;
}