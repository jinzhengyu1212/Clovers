#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
#define int long long
int n,m;
int stk1[N],stk2[N],top1=0,top2=0,add1=0,add2=0;
int abs(int x){return x<0 ? -x : x;}
typedef pair<int,int> pii;
#define mk make_pair
pii a[N];
void print(int id){
    cout<<"now id="<<id<<endl;
    cout<<"now stack1:";
    for(int i=top1;i>=1;i--) cout<<stk1[i]<<" "; cout<<endl;
    cout<<"now stack2:";
    for(int i=top2;i>=1;i--) cout<<stk2[i]<<" "; cout<<endl;
    cout<<"add1="<<add1<<"  add2="<<add2<<endl;
    cout<<endl;
}

signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        int x; scanf("%lld",&x);
        a[i]=mk(x,1);
    }
    for(int i=1;i<=m;i++){
        int x; scanf("%lld",&x);
        a[i+n]=mk(x,-1);
    }
    sort(a+1,a+n+m+1);
    stk1[++top1]=0;
    //top1可能为负，即多个老鼠未被匹配，而top2不可能为负，因为洞可以不被匹配
    for(int i=1;i<=n+m;i++){
        if(a[i].second==1){
            if(top1>0) stk2[++top2]=stk1[top1--]+add1-add2;
            else stk2[++top2]=-add2,top1--;
            add2-=a[i].first, add1+=a[i].first;
        }
        else{
            int zero;
            if((stk2[top2]+a[i].first+add2<stk1[top1]+add1&&top2>0)||top1<=0){
                zero=stk2[top2]+a[i].first+add2;
            }
            else zero=stk1[top1]+add1;
            add1-=a[i].first; add2+=a[i].first;
            if(top2) top2--; zero-=add1;
            stk1[++top1]=zero;
        }
    }
    printf("%lld\n",stk1[top1]+add1);
    return 0;
}