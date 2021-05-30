#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define pii pair<ll,ll>
const ll inf = LLONG_MAX;
const int N=1e5+9;
vector<pair<ll,ll>>adj[N];
ll dis[N];
int par[N];
ll n, m;

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) dis[i] = inf;
    for(int i = 1; i <= m; i++)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({y,w});
        adj[y].pb({x,w});
    }
    priority_queue< pii, vector<pii>, greater<pii> >q;
    q.push({0,1});
   // dis[1] = 0;
    while(!q.empty())
    {
        pair<ll,ll>a;
        a = q.top(); q.pop();
        ll node = a.ss , w = a.ff;
        if(node == n) break;
        if(w > dis[node]) continue;
      //  cout << "node: " << node << " w: " << w << endl;
        dis[node] = w;
        for(auto c: adj[node])
        {
            if(dis[c.ff] > w + c.ss)
            {
                dis[c.ff] = w + c.ss;
                par[c.ff] = node;
                q.push({dis[c.ff],c.ff});
            }
        }
    }
    //for(int i = 1; i <= n; i++) cout << "i : " << i << " " << dis[i] << endl;
    if(dis[n] == inf)
    {
        cout << -1 << endl; return;
    }
    vector<int>v;
    v.pb(n);
    int now = n;
   // cout << "now: " << now << endl;
    while(1)
    {
        v.pb(par[now]);
        if(par[now] == 1) break;
        now = par[now];
    }
    reverse(all(v));
    for(auto c: v) cout << c << " ";
}

int main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
