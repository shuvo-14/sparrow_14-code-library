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
#define pii pair<int,int>
const int mod=1e9+7;
const int inf = 1e9;
const int N=3e5+9;
int n, m;
vector<pair<int,int>>g[500],rev[500];
vector<int>dis;
bool vis[500][500];

void dfs(int node)
{
    for(auto c: rev[node])
    {
        if(c.ss + dis[c.ff] == dis[node])
        {
            vis[c.ff][node] = 1;
            dfs(c.ff);
        }
    }
}

int dijkastra(int src, int des)
{
    dis.resize(n);
    dis.assign(n,inf);
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    pq.push({0,src});
    while(!pq.empty())
    {
        pii now = pq.top();
        pq.pop();
        int node = now.ss, w = now.ff;
        if(w > dis[node]) continue;
        dis[node] = w;
        if(node == des) return w;
        for(auto c: g[node])
        {
            if(vis[node][c.ff]) continue;
            if(w + c.ss < dis[c.ff])
            {
                dis[c.ff] = c.ss + w;
                pq.push({dis[c.ff],c.ff});
            }
        }
    }
    return -1;
}

void solve()
{
    int src, des; cin >> src >> des;
    for(int i = 0; i <= n; i++)
    {
        g[i].clear(), rev[i].clear();
    }
    for(int i = 1; i <= m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        g[u].pb({v,w});
        rev[v].pb({u,w});
        vis[u][v] = vis[v][u] = 0;
    }
    int x = dijkastra(src,des);
   // cout << "x: " << x << endl; 
    if(x== -1)
    {
        cout << -1 << endl;
        return;
    }
    dfs(des);
    cout << dijkastra(src,des) << endl;
}

int32_t main()
{
    IOS;
    while(cin >> n && cin >> m)
    {
        if(n == 0 && m == 0) break;
        solve();
    }

    return 0;
}
