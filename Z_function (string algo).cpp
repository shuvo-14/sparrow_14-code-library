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

vector<int> z_function(string &s)
{
    int n = s.size();
    vector<int>z(n,0);
    for(int i = 1, l = 0, r = 0; i < n; i++)
    {
        if(i <= r)
        {
            z[i] = min(z[i-l],r-i+1);
        }
        while(i + z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) 
        {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

void solve()
{
    string s;
    cin >> s;
    vector<int>z = z_function(s);
    int mx = 0, ans = 0;
    int n = s.size();
    for(int i = 1; i < n; i++)
    {
        if(i + z[i] == n && z[i] <= mx)
        {
            cout << s.substr(0,z[i]);
            return;
        }
        mx = max(mx,z[i]);
    }
    cout << "Just a legend\n";
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
