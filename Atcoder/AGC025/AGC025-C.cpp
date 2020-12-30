#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=120000;
ll ans1=0,ans2=0;
int n,L[N],R[N];
typedef pair<int,int> pii;
#define mk make_pair

set<pii> st1,st2;
int _abs(int x){return x<0 ? -x : x;}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&L[i],&R[i]);
        st1.insert(mk(R[i],i));
        st2.insert(mk(L[i],i));
    }
    int to=st1.begin()->second,now=0;
    if(R[to]<now||L[to]>now){
        if(_abs(now-R[to])<_abs(now-L[to])) ans1+=_abs(now-R[to]),now=R[to];
        else ans1+=_abs(now-L[to]),now=L[to];
    }
    st1.erase(mk(R[to],to)); st2.erase(mk(L[to],to));
    while(!st1.empty()){//1
        int pos1=st1.begin()->second, pos2=st2.rbegin()->second;
        int tmp=R[pos1],dis=now-R[pos1]; to=pos1; 
        if(dis<L[pos2]-now) dis=L[pos2]-now,to=pos2,tmp=L[pos2];
        if(R[to]<now||L[to]>now){
            if(_abs(now-R[to])<_abs(now-L[to])) ans1+=_abs(now-R[to]),now=R[to];
            else ans1+=_abs(now-L[to]),now=L[to];
        }
        st1.erase(mk(R[to],to)); st2.erase(mk(L[to],to));
    }
    ans1+=_abs(now);

    for(int i=1;i<=n;i++) 
    {
        st1.insert(mk(R[i],i));
        st2.insert(mk(L[i],i));
    }
    to=st2.rbegin()->second,now=0;
    if(R[to]<now||L[to]>now){
        if(_abs(now-R[to])<_abs(now-L[to])) ans2+=_abs(now-R[to]),now=R[to];
        else ans2+=_abs(now-L[to]),now=L[to];
    }
    st1.erase(mk(R[to],to)); st2.erase(mk(L[to],to));
    while(!st1.empty()){//1
        int pos1=st1.begin()->second, pos2=st2.rbegin()->second;
        int tmp=R[pos1],dis=now-R[pos1]; int to=pos1;
        if(dis<L[pos2]-now) to=pos2,tmp=L[pos2];
        if(R[to]<now||L[to]>now){
            if(_abs(now-R[to])<_abs(now-L[to])) ans2+=_abs(now-R[to]),now=R[to];
            else ans2+=_abs(now-L[to]),now=L[to];
        }
        st1.erase(mk(R[to],to)); st2.erase(mk(L[to],to));
    }
    ans2+=_abs(now);
    cout<<max(ans1,ans2)<<endl;
    return 0;
}