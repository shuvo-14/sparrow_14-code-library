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

vector<int>x,y;

vector<int> cal(int a[],int sz, int ad)
{
    vector<int>tmp;
    for(int i = 0; i < (1<<sz); i++)
    {
        int sum = 0;
        for(int j = 0;  j < sz; j++)
        {
            if(i & (1<<j)) sum += a[j+ad];
        }
        tmp.pb(sum);
    }
    return tmp;
}

int fun(int n, int a[],int S)
{
    x = cal(a,n/2,0);
    y = cal(a,n-(n/2),n/2);
    sort(all(y));
    for(auto c: x) cout << c << " "; cout << endl;
    for(auto c: y) cout << c << " "; cout << endl;
    int mx = 0;
    for(int i = 0; i < x.size(); i++)
    {
        if(x[i] <= S)
        {
           int id = lower_bound(all(y),S-x[i]) - y.begin();
           if(id == y.size() || y[id] != (S-x[i])) id--;
           if(mx < x[i] + y[id]) mx = x[i] + y[id];
        }
    }
    return mx;
}

void solve()
{
    // calculate the max subset sum <= S
    // here we used "meet in the middle method"
    // what reduces complexity from 2^n to 2^(n/2) for calculation of subset sum
    // overall complexity is n * 2^(n/2);
    int n = 6;
    int a[n] = {3,34,4,12,5,2};
    int S = 10;
    int ans = fun(n,a,S);
    cout << "Largest value less than or equal to S is: " << ans << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
