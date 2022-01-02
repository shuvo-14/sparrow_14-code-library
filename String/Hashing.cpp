//https://www.spoj.com/problems/NHAY/
#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
const int inf = 1e9;
const int N=1e6+9;

int BigMod(int a, int n, const int mod)
{
    if(n == 0) return 1;
    int x = BigMod(a,n/2,mod);
     x = (ll) (1LL * x * x) % mod;
    if(n&1) x = (ll) (1LL * x * a) % mod;
    return x;
}

const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int,int>pw[N],ipw[N];
void pre()
{
    pw[0] = {1,1};
    for(int i = 1; i < N; i++)
    {
        pw[i].ff = (1LL * pw[i-1].ff * p1 ) % MOD1;
        pw[i].ss = (1LL * pw[i-1].ss * p2) % MOD2;
    }
    ip1 = BigMod(p1,MOD1-2,MOD1);
    ip2 = BigMod(p2,MOD2-2,MOD2);
    ipw[0] = {1,1};
    for(int i = 1; i < N; i++)
    {
        ipw[i].ff = (1LL * ipw[i-1].ff * ip1) % MOD1;
        ipw[i].ss = (1LL * ipw[i-1].ss * ip2) % MOD2;
    }   
}
struct Hashing
{
    int n;
    string s; // 0 - indexed
    vector<pair<int,int>>hs; // 1-indexed
    Hashing() {}
    Hashing(string _s)
    {
        s = _s;
        n = s.size();
        hs.pb({0,0});
        for(int i = 0; i < n; i++)
        {
            pair<int,int>p;
            p.ff = (hs[i].ff + 1LL * pw[i].ff * s[i] % MOD1) % MOD1;
            p.ss = (hs[i].ss + 1LL * pw[i].ss * s[i] % MOD2) % MOD2;
            hs.pb(p);
        }
    }
    
    pair<int,int>get_hash(int l, int r) // 1 - indexed
    {
        assert(l >= 1 and l <= r and  r <= n);
        pair<int,int>ans;
        ans.ff = ((hs[r].ff - hs[l-1].ff + MOD1) * 1LL *  ipw[l-1].ff ) % MOD1;
        ans.ss =((hs[r].ss - hs[l-1].ss + MOD2) * 1LL * ipw[l-1].ss) % MOD2;
        return ans;
    }
    pair<int,int>get_hash()
    {
        return get_hash(1,n);
    }
};
int n;
void solve()
{
    string s, p;
    cin >> p >> s;
    Hashing h(s);
    auto hs = Hashing(p).get_hash();
    for(int i = 1; i + n - 1 <= s.size(); i++)
    {
        if(h.get_hash(i,i+n-1) == hs) cout << i -1 << endl;
    }
    cout << endl;
}

int32_t main()
{
    IOS;
    pre();
    while(cin >> n) solve();

    return 0;
}
