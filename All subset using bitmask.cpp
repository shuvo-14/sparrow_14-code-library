#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
const int mod=1e9+7;
const int N=3e5+9;

void solve()
{
   vector<int>v = {1,2,3};
   int n = v.size();
   for(int mask = 0; mask < (1<<n);mask++)
   {
       cout << "mask: " << mask << endl;
       for(int bit = 0; bit < n; bit++)
       {
           if(mask&(1<<bit)) cout << v[bit];
       }
       cout << endl;
   }
}

int main()
{
    IOS;
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
