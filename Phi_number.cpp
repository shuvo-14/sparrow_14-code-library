#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define int long long
#define all(x) x.begin(),x.end()
const int mod=1e9+7;
const int inf = 1e9;
const int N=3e5+9;

int phi(int n)
{
    int res = n;
    for(int p = 2; p * p <= n; p++)
    {
        if(n%p == 0)
        {
            while(n%p==0)
            {
               res -= res / p;
                n /= p;
            }
        }
    }
    if(n > 1) res -= res/n;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    int ans = phi(n);
    cout << ans << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
