#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Wint:vector<int>
{
    Wint(int n=0)
    {
        push_back(n);
        check();
    }
    Wint& check()
    {
        while(!empty()&&!back())pop_back();
        if(empty())return *this;
        for(int i=1; i<size(); ++i)
        {
            (*this)[i]+=(*this)[i-1]/10;
            (*this)[i-1]%=10;
        }
        while(back()>=10)
        {
            push_back(back()/10);
            (*this)[size()-2]%=10;
        }
        return *this;
    }
};
Wint NUM(int x){
    Wint z;
    while(x){
        z.push_back(x%10);
        x/=10;
    }
    return z;
}
istream& operator>>(istream &is,Wint &n)
{
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}
ostream& operator<<(ostream &os,const Wint &n)
{
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}
bool operator!=(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return 1;
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return 1;
    return 0;
}
bool operator==(const Wint &a,const Wint &b)
{
    return !(a!=b);
}
bool operator<(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return a.size()<b.size();
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return a[i]<b[i];
    return 0;
}
bool operator>(const Wint &a,const Wint &b)
{
    return b<a;
}
bool operator<=(const Wint &a,const Wint &b)
{
    return !(a>b);
}
bool operator>=(const Wint &a,const Wint &b)
{
    return !(a<b);
}
Wint& operator+=(Wint &a,const Wint &b)
{
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0; i!=b.size(); ++i)a[i]+=b[i];
    return a.check();
}
Wint operator+(Wint a,const Wint &b)
{
    return a+=b;
}
Wint& operator-=(Wint &a,Wint b)
{
    if(a<b)swap(a,b);
    for(int i=0; i!=b.size(); a[i]-=b[i],++i)
        if(a[i]<b[i])
        {
            int j=i+1;
            while(!a[j])++j;
            while(j>i)
            {
                --a[j];
                a[--j]+=10;
            }
        }
    return a.check();
}
Wint operator-(Wint a,const Wint &b)
{
    return a-=b;
}
Wint operator*(const Wint &a,const Wint &b)
{
    Wint n;
    n.assign(a.size()+b.size()-1,0);
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
Wint& operator*=(Wint &a,const Wint &b)
{
    return a=a*b;
}
Wint divmod(Wint &a,const Wint &b)
{
    Wint ans;
    for(int t=a.size()-b.size(); a>=b; --t)
    {
        Wint d;
        d.assign(t+1,0);
        d.back()=1;
        Wint c=b*d;
        while(a>=c)
        {
            a-=c;
            ans+=d;
        }
    }
    return ans;
}
Wint operator/(Wint a,const Wint &b)
{
    return divmod(a,b);
}
Wint& operator/=(Wint &a,const Wint &b)
{
    return a=a/b;
}
Wint& operator%=(Wint &a,const Wint &b)
{
    divmod(a,b);
    return a;
}
Wint operator%(Wint a,const Wint &b)
{
    return a%=b;
}
Wint pow(const Wint &n,const Wint &k)
{
    if(k.empty())return 1;
    if(k==2)return n*n;
    if(k.front()%2)return n*pow(n,k-1);
    return pow(pow(n,k/2),2);
}

Wint x; int z;
Wint y,One;
Wint ten[5001];

int calc_len(Wint X,Wint Y){
    Wint Z=X*Y;
    return 3+(int)Z.size()+(int)Y.size()+(int)X.size();
}

Wint find(Wint x,Wint &rest){
    Wint A=One;
    int lenA=1,lenB=x.size();
    while(rest!=0){
        Wint X,Y;
        X=ten[lenA]-One;
        Y=(ten[lenB]+x-One)/x-One;
        if(X>Y) X=Y,lenB++;
        else lenA++;
        Wint sum=NUM(calc_len(x,A))*(X-A+One);
        if(rest>=sum){
            rest-=sum;
            A=X+One;
        }
        else break;
    }
    Wint R=rest/NUM(calc_len(x,A));
    A+=R; rest-=R*NUM(calc_len(x,A));
    return A;
}

string change(Wint X){
    string S="";
    for(int j=(int)X.size()-1;j>=0;j--){
        S+=char(X[j]+'0');
    }
    return S;
}

string Str(Wint X,Wint Y){
    string S="";
    S=S+change(X);
    S=S+"*"; S=S+change(Y);
    Wint Z=X*Y;
    S=S+"=";
    S=S+change(Z); S=S+" ";
    return S;
}
int num(Wint now){
    int ret=0;
    for(int i=now.size()-1;i>=0;i--) ret=ret*10+now[i];
    return ret;
}

void print(Wint rest,Wint x,Wint now,int Z){
    int flag=0;
    string S=Str(x,now);
    if(num(rest)!=0){
        for(int i=num(rest);i<(int)S.size()&&Z!=0;i+=1){
            printf("%c",S[i]);
            Z--;
        }   
    }
    if(num(rest)!=0) now+=One;
    while(Z!=0){
        S=Str(x,now);
        if(Z<S.size()) break;
        printf("%s",S.c_str());
        now=now+One;
        Z-=S.size();
    }
    if(Z!=0){
        S=Str(x,now);
        for(int i=0;i<Z;i++) printf("%c",S[i]);
    }
    puts("");
}

int main()
{
    One.push_back(1);
    for(int i=0;i<=5000;i++){
        ten[i].push_back(1);
        for(int j=i+1;j<=5000;j++) ten[j].push_back(0);
    }
    cin>>x; cin>>y; scanf("%d",&z);
    y-=One;
    for(int i=1;i<=5;i++){
        Wint rest=y;
        Wint ans=find(x,rest);
        print(rest,x,ans,z);
        x=x+One;
    }
}