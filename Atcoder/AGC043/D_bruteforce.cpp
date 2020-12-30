#include<bits/stdc++.h>
using namespace std;

int a[]={0,1,2,3,4,5,6,7,8,9};
typedef vector<int> V;
set<V> st;
int main(){
    int cnt=0;
    do{
        V v;
        //printf("from:");
        //for(int i=1;i<=9;i++) printf("%d ",a[i]); puts("");
        int now[]={1,4,7};
        for(int iii=1;iii<=9;iii++){
            if((a[now[0]]<a[now[1]]||now[1]>6)&&(a[now[0]]<a[now[2]]||now[2]>9)&&now[0]<=3){
                v.push_back(a[now[0]++]);
            }
            else if((a[now[1]]<a[now[0]]||now[0]>3)&&(a[now[1]]<a[now[2]]||now[2]>9)&&now[1]<=6){
                v.push_back(a[now[1]++]);
            }
            else v.push_back(a[now[2]++]);
        }
        cnt++;
        //printf("to:");
        //for(int i=0;i<9;i++) printf("%d ",v[i]);
        //puts("");
        //if(cnt%10000==0) cout<<cnt<<endl;
        st.insert(v);
    }while(next_permutation(a+1,a+10));
    int ans=0;
    for(int i=1;i<=9;i++) a[i]=i;
    int dp[10];
    do{
        V v;
        for(int i=0;i<9;i++) v.push_back(a[i+1]);
        if(st.find(v)==st.end()){
            for(int i=0;i<9;i++) printf("%d ",v[i]);
            dp[0]=0; dp[1]=1; int maxx=1,now=1;
            for(int i=2;i<=9;i++){
                if(a[i]<a[i-1]) now++;
                else now=1;
                maxx=max(maxx,now);
            }
            printf("the decreasing num:%d\n",maxx);
            //puts("");
            ans++;
        }
    }while(next_permutation(a+1,a+10));
    cout<<ans<<endl;
    return 0;
}