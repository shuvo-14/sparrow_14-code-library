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
const int N=1e4+9;
vector<int>adj[N];
int n, m;
vector<int>in(N);
vector<int>topo_sort;

bool kahn()
{
    priority_queue<int, vector<int>, greater<int> > pq;
    for(int i = 1; i <= n; i++)
    {
        if(in[i] == 0) pq.push(i);
    }
    while(!pq.empty())
    {
        int node = pq.top(); pq.pop();
        topo_sort.pb(node);
        for(auto c: adj[node])
        {
            in[c]--;
            if(in[c] == 0) pq.push(c);
        }
    }
    return topo_sort.size() == n;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++) 
    {
        int u, v;
         cin >> u >> v;
         in[v]++;
         adj[u].pb(v);
    }
    if(!kahn())
    {
        cout << "Sandro fails.\n";
        return;
    }
    for(auto c: topo_sort) cout << c << " "; cout << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
