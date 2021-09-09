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
const int N=2e5+9;
vector<pair<int,pair<int,int>>>vec;
struct DSU{
    vector<int>par;
    void init(int n)
    {
        par.resize(n+1);
        for(int i = 1; i <= n; i++) par[i] = i;
    }
    int find(int u)
    {
        if(par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if(u == v) return;
        par[v] = u;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        vec.pb({w,{u,v}});
    }
    sort(all(vec));
    DSU dsu;
    dsu.init(n);
    int sum = 0;
    for(int i = 0; i < m; i++)
    {
        int u = vec[i].ss.ff, v = vec[i].ss.ss;

        if(dsu.find(u) != dsu.find(v))
        {
            sum += vec[i].ff;
            dsu.merge(u,v);
        }
        
    }
    cout << sum << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
