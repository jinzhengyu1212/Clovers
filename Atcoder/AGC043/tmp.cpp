#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
char s[N];
int a[101][101];

int _abs(int x){return x<0 ? -x : x;}

int n,sum[N];
int main(){
    scanf("%d",&n); 
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) a[1][i]=s[i]-'0';
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=_abs(a[i-1][j]-a[i-1][j+1]);
        }
    }
    cout<<a[n][1]<<endl;
    return 0;
}