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
vector<pair<int,int>>adj[105];
int n, m;
int dis[105];

struct edge
{
    int x, y, w;
};

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) dis[i] = inf;
    vector<edge>v(m);
    for(int i = 0; i < m; i++)
    {
        cin >> v[i].x >> v[i].y >> v[i].w;
    }

    dis[1] = 0;
    
    // RUNNING LOOP (N-1) TIMES
    for(int k = 1; k < n; k++)
    for(int i = 0; i < m; i++)
    {
        int node = v[i].x, child = v[i].y, cost = v[i].w;
        if(dis[node] == inf) continue;
        if(dis[child] > dis[node] + cost)
        {
            dis[child] = dis[node] + cost;
        } 
        
    }

    // CHECKING NEGATIVE CYCLE
    for(int i = 0; i < m; i++)
    {
        int node = v[i].x, child = v[i].y, cost = v[i].w;

        //  checking if node is not optimized
        if(dis[node] == inf) continue;

        if(dis[child] > dis[node] + cost)
        {
            cout << -1 << endl; return;
        } 
        
    }

    for(int  i = 1; i <= n; i++)
    {
        if(dis[i] == inf) cout << 30000 << " "; 
        else cout << dis[i] << " ";
    }
    cout << endl;

}

int32_t main()
{
    IOS;
    int t = 1;
  //  cin >> t;
    while(t--) solve();

    return 0;
}
