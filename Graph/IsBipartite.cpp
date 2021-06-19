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
const int N= 2e5+9;
int col[N];
vector<int>adj[N];
int n, m;

bool bipartite()
{
    bool bip = true;
    // (0 to n-1) or (1 to n) based on problem
    for(int i = 1; i <= n; i++) col[i] = -1;
    queue<int>q;
    for(int i = 1; i <= n; i++)
    {
        if(col[i] != -1) continue;

        q.push(i);
        col[i] = 0;
        while(!q.empty())
        {
            int  u = q.front(); q.pop();
            for(auto v: adj[u])
            {
                if(col[v] == -1)
                {
                    col[v] = 1 ^ col[u];                    
                    q.push(v);
                }
                else bip &= (col[u] != col[v]);
            }
        }
    }
    return bip;
}

void solve()
{
    cin >> n >> m;
    for(int i = 0; i <= n; i++)
    {
        col[i] = -1;
        adj[i].clear();
    }

    for(int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if(bipartite())
    {
        cout << "YES\n";
    }
    else cout << "NO\n";

}

int32_t main()
{
    IOS;
    int t = 1;
    cin >> t;
    while(t--) solve();

    return 0;
}
