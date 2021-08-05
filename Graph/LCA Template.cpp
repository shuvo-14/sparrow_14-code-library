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
const int N=1e5+9;
const int maxN = 20; // log2(N)
int LCA[N][maxN+1];
vector<int>adj[N];
int level[N];

void dfs(int node, int par)
{
    LCA[node][0] = par;
    for(auto child: adj[node])
    {
        if(child != par)
        {
            level[child] = level[node] + 1;
            dfs(child,node);
        }
    }
}

void build()
{
// dfs(root,-1)
    dfs(1,-1);
    for(int j = 1; j <= maxN; j++)
    {
        for(int i = 1; i < N; i++)
        {
            if(LCA[i][j-1] != -1)
            {
                int par = LCA[i][j-1];
                LCA[i][j] = LCA[par][j-1];
            }
        }
    }
}

int lca(int a, int b)
{
    if(level[a] > level[b]) swap(a,b);
    int d = level[b] - level[a];
    while(d)
    {
        int i = log2(d);
        d -= (1 << i);
        b = LCA[b][i];
    }
    if(a==b) return a;
    for(int i = maxN; i >= 0; i--)
    {
        if(LCA[a][i] != -1 && LCA[a][i] != LCA[b][i])
        {
            a = LCA[a][i], b = LCA[b][i];
        }
    }
    return LCA[a][0];
}

void solve()
{
   int n;
   cin >> n;
   memset(LCA,-1,sizeof(LCA));
   for(int i = 1; i < n; i++)
   {
       int a, b;
       cin >> a >> b;
       adj[a].pb(b);
       adj[b].pb(a);
   }
   build();
   int q;
   cin >> q;
   while(q--)
   {
       int a, b;
       cin >> a >> b;
       cout << lca(a,b) << endl;
   }
}

int main()
{
    IOS;
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
