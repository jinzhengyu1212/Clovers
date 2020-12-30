#include<iostream>
using namespace std;
int main(){
      int n;
      cin>>n;
      string s="1";
      int t;
      do{
      	int i=s.length()-1;
		while(s[i]=='1'){
			s[i]='0';i--;
		}
		if(i>0)s[i]='1';
		else s='1'+s;
		t=0;
		for(int i=0;i<s.length();i++){
			t=t*10+s[i]-'0';
		}
        cout<<t<<endl;
	}while(t%n);
	cout<< s<<endl;
	return 0;
 }
