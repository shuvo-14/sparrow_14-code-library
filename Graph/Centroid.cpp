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
const int inf = 1e9;
const int N=1e5+9;
vector<int>g[N];
int sz[N];
void dfs(int u, int par = -1)
{
    sz[u] = 1;
    for(auto v: g[u])
    {
        if(v == par) continue;
        dfs(v,u);
        sz[u] += sz[v];
    }
}
void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    int u = 1;
    dfs(u);
    while(1)
    {
        int tmp = -1;
        for(auto v: g[u])
        {
            if(sz[v] > sz[u]) continue;
            if(sz[v]*2 >= n) tmp = v;
        }
        if(tmp == -1) break;
        u = tmp;
    }
    dfs(u);
    int ok = 1;
    for (auto v : g[u])
    {
        if (sz[v] * 2 == n)
        {
            assert(g[u].size() > 1);
            ok = 0;
            int k = g[u][0];
            if (k == v)
                k = g[u][1];
            cout << u << " " << k << endl;
            cout << v << " " << k << endl;
        }
    }
    if (ok)
    {
        cout << "1 " << g[1][0] << endl;
        cout << "1 " << g[1][0] << endl;
    }

    for(int i = 1; i <= n; i++)g[i].clear();
}

int32_t main()
{
    IOS;
    int t = 1;
    cin >> t;
    while(t--) solve();

    return 0;
}
