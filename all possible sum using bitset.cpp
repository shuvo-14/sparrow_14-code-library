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
const int k=2e5+9;
bitset<k>bs;
void solve()
{
    int n;
    cin >> n;
    int sum = 0;
    int a[n+1];
    bs[0] = 1;
    for(int i = 1; i <= n; i++){
        cin >> a[i], sum += a[i];
        bs |= (bs << a[i]); 
    } 
    if(sum%2){cout << "0" << endl;return;}

   

    sum/=2;
    if(bs[sum]==0) {cout << "0" << endl; return;}
    while(1)
    {
        for(int i = 1; i <= n; i++)
        {
            if(a[i]&1) {cout << 1 << " \n" << i << endl; return;}
            a[i]/=2;
        }
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
