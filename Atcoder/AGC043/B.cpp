#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
char s[N];
int a[4][N];

int _abs(int x){return x<0 ? -x : x;}

int n,sum[N];
int main(){
    scanf("%d",&n); 
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) a[1][i]=s[i]-'0';
    if(n==1){
        cout<<a[1][1]<<endl;
        return 0;
    }
    if(n==2){
        cout<<_abs(a[1][1]-a[1][2])<<endl;
        return 0;
    }
    for(int i=2;i<=3;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=_abs(a[i-1][j]-a[i-1][j+1]);
        }
    }
    n-=2;
    if(n==1){
        cout<<a[3][1]<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        int tmp=i;
        sum[i]=sum[i-1];
        while(tmp%2==0){
            tmp/=2; sum[i]++;
        }
    }
    int cnt1=0,cnt2=0;
    for(int i=1;i<=n;i++){
        if(a[3][i]==1) cnt1++;
        if(a[3][i]==2) cnt2++;
    }
    int flag=1;
    if(cnt1==0){
        for(int i=1;i<=n;i++) if(a[3][i]==2) a[3][i]=1;
        flag=2;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!a[3][i]||a[3][i]==2) continue;
        int tmp=sum[n-1]-sum[n-i]-sum[i-1];
        if(tmp==0) ans^=1;
    }
    cout<<ans*flag<<endl;
    return 0;
}