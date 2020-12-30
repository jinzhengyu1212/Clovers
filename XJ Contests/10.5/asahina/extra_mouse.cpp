#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=500005;
int n,m,a[N],h[N];
multiset<int> st;
int _abs(int x){return x>0 ? x : -x;}
void print(){
    cout<<"nowset:";
    for(set<int>::iterator it=st.begin();it!=st.end();it++){
        cout<<*it<<" ";
    }
    cout<<"\n";
}

signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=m;i++) scanf("%lld",&h[i]),st.insert(h[i]);
    sort(h+1,h+m+1);
    sort(a+1,a+n+1);
    int ans=0;
    int now=0;
    for(int i=1;i<=n;i++){
        //print();
        set<int>::iterator it1=st.lower_bound(a[i]),it2;
        if(it1==st.begin()){
            ans+=_abs(*it1-a[i]);
            st.erase(it1);
        }
        else{
            it2=it1; it2--;
            int tmp=lower_bound(h+1,h+m+1,*it2)-h;
            if(m-tmp<(n-i)) break;
            int dis1=_abs(*it1-a[i]),dis2=_abs(*it2-a[i]);
            //if(i>3) cout<<dis2<<" "<<dis1<<"endl\n";
            if(dis2<=dis1||it1==st.end()){
                ans+=dis2;
                st.erase(it2);
            }
            else{
                //if(i>3) cout<<i<<"KK\n";
                int pos=lower_bound(h+1,h+m+1,*it1)-h;
                if(m-pos<(n-i)){
                    ans+=dis2;
                    st.erase(it2);
                }
                else{
                    ans+=dis1;
                    st.erase(it1);
                }
            }
        }
        //cout<<i<<" "<<ans<<endl;
        now=i;
    }
    if(now!=n){
        for(int i=n;i>=now+1;i--){
            ans+=_abs(a[i]-h[m-n+i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}