#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll R;
int n,a[25],k;

void init(){
    scanf("%lld%d",&R,&k);
    ll tmp=R; n=0;
    while(tmp){
        a[++n]=tmp%10; 
        tmp/=10;
    }
    //reverse(a+1,a+n+1);
}

const int M=180;
ll dp[24][361][1000][2];
int f(int x){
    int ret=0;
    while(x){
        ret+=x%10;
        x/=10;
    }
    return ret;
}
void brute(){
    int ret=0;
    for(int i=1;i<=R;i++){
        if(f(i)==f(i*k)) ret++;
    }
    cout<<ret<<endl;
}   

void solve(){
    dp[1][M][0][0]=1;
    for(int pos=1;pos<n+4;pos++){
        for(int delS=-180;delS<=180;delS++){
            for(int pre=0;pre<1000;pre++){
                for(int limit=0;limit<2;limit++){
                    if(!dp[pos][delS+M][pre][limit]) continue;
                    ll now=dp[pos][delS+M][pre][limit];
                    //cout<<pos<<" "<<delS<<" "<<pre<<" "<<limit<<" "<<now<<endl;
                    for(int i=0;i<10;i++){
                        int tmp=k*i+pre;
                        int delta=i-tmp%10;
                        tmp/=10;
                        if(pos<n){
                            if(i>a[pos]) dp[pos+1][delS+delta+M][tmp][1]+=now;
                            else if(i==a[pos]) dp[pos+1][delS+delta+M][tmp][limit]+=now;
                            else dp[pos+1][delS+delta+M][tmp][0]+=now;
                        }
                        else if(pos==n){
                            if(i>a[pos]) continue;
                            else if(i==a[pos]){
                                if(!limit) dp[pos+1][delS+delta+M][tmp][1]+=now;
                            }
                            else dp[pos+1][delS+delta+M][tmp][0]+=now;
                        }
                        else{
                            if(i==0) dp[pos+1][delS+delta+M][tmp][1]+=now;
                        }
                    }
                }
            }
        }
    }
    cout<<dp[n+4][M][0][1]-1<<endl;
}

int main(){
    init(); 
    solve();
    return 0;
}