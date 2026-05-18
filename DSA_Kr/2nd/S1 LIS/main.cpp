#include<bits/stdc++.h>
using namespace std;
// I am not able to do it with segment tree and 
// maybe I have understood the question wrong also

int main(){
    
vector<int>arr ;
int k;

while(cin>>k && k!=-1) arr.push_back(k);

vector<int> a,b;


for(int i=0; i<arr.size(); i++){
    if(a.empty()) a.push_back(arr[i]);
    else{
        if(a.back()<arr[i]) a.push_back(arr[i]);
        else{
            if(a.size()>b.size()) b = a;
            a.clear();
            a.push_back(arr[i]);
        }
    }
}
            if(a.size()>b.size()) b = a;
    
    for(int i : b) cout<<i<<" ";
    cout<<endl<<b.size();
    
return 0;
}