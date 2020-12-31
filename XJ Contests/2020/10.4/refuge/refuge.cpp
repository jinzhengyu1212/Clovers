#include<bits/stdc++.h>
using namespace std;
const int N=505;
string code[N];
map<string,int> mp;
int n;

void init(){
    scanf("%d",&n); getline(cin,code[0]);
    for(int i=1;i<=n;i++) getline(cin,code[i]);
}

bool judge_int_or_var(int &i,string S,int len){
    while((S[i]<'a'||S[i]>'z')&&(S[i]<'0'||S[i]>'9')) i++;
    if(S[i]>='0'&&S[i]<='9') return 0;
    else return 1;
}

string read(int &i,string S,int len){
    while((S[i]<'a'||S[i]>'z')&&i<len) i++;
    string now="";
    while(S[i]>='a'&&S[i]<='z') now+=S[i++];
    return now;
}

int readint(int &i,string S,int len){
    int ret=0;
    while((S[i]<'0'||S[i]>'9')&&i<len) i++;
    while(S[i]>='0'&&S[i]<='9') ret=ret*10+S[i]-'0',i++;
    return ret;
}

void solve(){
    for(int line=1;line<=n;line++){
        string S=code[line]; int len=(int)S.size();
        int i=0;
        string now=read(i,S,len);
        if(now=="input"){
            now=read(i,S,len);
            int x; scanf("%d",&x);
            mp[now]=x;
        }
        else if(now=="output"){
            if(judge_int_or_var(i,S,len)){
                now=read(i,S,len);
                printf("%d\n",mp[now]);
            }
            else{
                int num=readint(i,S,len);
                printf("%d\n",num);
            }
        }
        else if(S[i]=='='){
            string prenow=now;
            int prenum;
            if(judge_int_or_var(i,S,len)){
                now=read(i,S,len);
                prenum=mp[now];
            }
            else{
                int num=readint(i,S,len);
                prenum=num;
            }
            if(S[i]=='+'||S[i]=='-'||S[i]=='*'||S[i]=='/'){
                char c=S[i];
                int val;
                if(judge_int_or_var(i,S,len)){
                    now=read(i,S,len);
                    val=mp[now];
                }
                else{
                    int num=readint(i,S,len);
                    val=num;
                }
                if(c=='+') mp[prenow]=prenum+val;
                else if(c=='-') mp[prenow]=prenum-val;
                else if(c=='*') mp[prenow]=prenum*val;
                else mp[prenow]=prenum/val;
            }
            else mp[now]=prenum;
        }
    }
}

int main(){
    init();
    int T; scanf("%d",&T);
    while(T--){
        solve();
    }
}