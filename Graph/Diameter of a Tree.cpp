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
#define all(x) x.begin(),x.end()
const int mod=1e9+7;
const int inf = 1e9;
const int N=2e5+9;
int subtree_longestpath[N];
int farthest_node[N];
int one_end, other_end;

vector<int>g[N];
int diameter;
void dfs(int u, int p = 0)
{
   subtree_longestpath[u] = 0;
   farthest_node[u] = u;
   for(int v : g[u])
   {
       if(v == p) continue;
       dfs(v,u);
       if(subtree_longestpath[v] + 1 > subtree_longestpath[u])
       {
           subtree_longestpath[u] = subtree_longestpath[v] + 1;
           farthest_node[u] = farthest_node[v];
       }
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
    dfs(1);
    one_end = farthest_node[1];
    dfs(one_end);
    
    other_end = farthest_node[one_end];
    debug(one_end,other_end);
    cout << subtree_longestpath[one_end]<< endl;
}

int32_t main()
{
    IOS;
    int t = 1;
    int ct = 1;
   // cin >> t;
    while(t--) 
    {
       // cout << "Case #" << ct++ <<": " ;     
        solve();
    }

    return 0;
}
