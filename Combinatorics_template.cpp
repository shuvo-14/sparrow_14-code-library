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
const int mod=998244353;
const int inf = 1e9;
const int N=2e5+9;
int fac[N],invfac[N];

int BigMod(int a, int x)
{
    if(x == 0) return 1;
    int res = BigMod(a,x/2);
    res = (res*res) % mod;
    if(x&1) res = (res*a) % mod;
    return res;
}

void precompute()
{
    fac[0] = fac[1] = 1;
    for(int i = 2; i < N; i++) fac[i] = (fac[i-1]*i) % mod;
    invfac[N-1] = BigMod(fac[N-1],mod-2);
    for(int i = N-2; i >= 0; i--) 
    {
        invfac[i] = (invfac[i+1] * (i+1)) % mod;
    }
}

int nCr(int x, int y)
{
    if(y > x) return 0;
    int res = (fac[x]*invfac[y]) % mod;
    res = (res * invfac[x-y]) % mod;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>v(n);
    for(auto &c: v) cin >> c;
    int mx = *max_element(all(v));
    int mxcnt = count(all(v),mx);
    if(mxcnt > 1){cout << fac[n] << endl; return;}
    int mx2 = mx-1;
    int k = count(all(v),mx2);
    if(!k) {cout << 0 << endl; return;}

    int invalid = nCr(n,n-k-1);
    invalid = (invalid * fac[n-k-1]) % mod;
    invalid = (invalid * fac[k]) % mod;
    cout << (fac[n] - invalid + mod) % mod << endl;
}

int32_t main()
{
    IOS;
    precompute();
    int t = 1;
    cin >> t;
    while(t--) solve();

    return 0;
}
