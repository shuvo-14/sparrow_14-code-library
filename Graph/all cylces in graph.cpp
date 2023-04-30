#include<bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define int long long
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define piii pair<int,pii>
#define min_heap priority_queue<int,vector<int>,greater<int>>

const int mod=1e9+7;
const int inf = 1e15;
const int N=2005;
vector<int>g[N];
int color[N],par[N];
int ok = 0;
vector<pair<int,int>>ans;
vector<vector<int>>cycles;
void dfs(int u, int p)
{
    if(color[u] == 2) return;
    if(color[u] == 1)
    {
        vector<int>v;
        int cur = p;
        while(cur != u)
        {
            v.pb(cur);
            cur = par[cur];
        }
        v.pb(u);
        cycles.pb(v);
        return;
    }
    par[u] = p;
    color[u] = 1;
    for(int v : g[u])
    {
        if(v == par[u]) continue;
        dfs(v,u);
    }
    color[u] = 2;
}
bool check(vector<int>&vec)
{
    map<int,int>mp;
    for(auto c : vec) mp[c]++;
    int node = -1;
    for(auto c : vec)
    {
        if(g[c].size() >= 4) 
        {
            node = c;
            break;
        }
    }
    if(node == -1) return 0;
    ok = 1;
    //debug(node);
   // debug(vec);
    for(auto c : g[node])
    {
        if(mp.find(c) == mp.end())
        {
            ans.pb({node,c});
            if(ans.size() == 2) break;
        }
    }
    if(ans.size() != 2)
    {
        ans.clear();
        ok = 0;
        return 0;
    }
    int sz = vec.size();
    for(int i = 0; i + 1 < sz; i++) 
    {
        ans.pb({vec[i],vec[i+1]});
    }
    ans.pb({vec[0],vec[sz-1]});
    return 1;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++)
    {
        g[i].clear();
        color[i] = 0;
        par[i] = 0;
    }
    ok = 0;
    ans.clear();
    cycles.clear();
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    for(int i = 1; i <= n; i++)
    {
        if(!color[i]) dfs(i,0);
    }
    for(int i = 0; i < cycles.size(); i++)
    {
        if(check(cycles[i]))
        {
            cout << "YES\n";
            cout << (int) ans.size() << endl;
            for(auto [u,v] : ans)
            {
                cout << u << " " << v << endl;
            }
            return;
        }
    }
    cout << "NO\n";
}

int32_t main()
{
    IOS;
    int t = 1;
    int ct = 1;
    cin >> t;
    while(t--) 
    {
       // cout << "Case #" << ct++ <<": " ;     
        solve();
    }

    return 0;
}
