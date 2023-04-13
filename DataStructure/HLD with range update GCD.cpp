// https://www.codechef.com/problems/DGCD?tab=statement
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
#define pii pair<int,int>
#define piii pair<int,pii>
#define min_heap priority_queue<int,vector<int>,greater<int>>

const int mod=1e9+7;

const int N = 1e5 + 9, LG = 18, inf = 1e9 + 9;
vector<int>g[N];
int depth[N],par[N],sz[N];
int ft[N];
int val[N];
int n;
int gcd(int u, int v)
{
    if(!v) return (u > 0) ? u : -u;
    return gcd(v,u%v);
}
struct segtree{
    
    int size;
    vector<ll>tree;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size,0LL);
    }

    //change accordingly
    int merge(int u, int v)
    {
        return gcd(u,v);
    }

    void build(int x, int lx, int rx)
    {
        if(lx == rx)
        {
            tree[x] = val[ft[lx]] - val[ft[lx+1]];
            return;
        }
        int mid = (lx+rx)/2;
        build(2*x+1,lx,mid);
        build(2*x+2,mid+1,rx);
        tree[x] = merge(tree[2*x+1],tree[2*x+2]);
    }

    // void build(vector<int>&vec)
    // {
    //     build(0,0,n-1,vec);
    // }

   

    void update(int x, int lx, int rx, int i, int v)
    {
        if(lx == rx)
        {
           tree[x] += v;
           return;
        }
        int mid = (lx+rx)/2;
        if(i <= mid) update(2*x+1,lx,mid,i,v);
        else update(2*x+2,mid+1,rx,i,v);
        tree[x] = merge(tree[2*x+1], tree[2*x+2]);
    }

    

    int query(int l, int r, int x, int lx, int rx)
    {
        if(lx > r || rx < l) return 0; //change accordingly
        if(lx >= l && rx <= r) return tree[x];
        int mid = (lx+rx)/2;
        int s1 = query(l,r,2*x+1,lx,mid);
        int s2 = query(l,r,2*x+2,mid+1,rx);
        return merge(s1,s2);
    }

}t;

struct BIT{
    vector<int>tree;
    int size = 1;

    void init(int n)
    {
        size = n+1;
        tree.assign(size+5,0);
    }

    void update(int pos, int val)
    {
        while(pos <= size)
        {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
    void update(int l, int r, int val)
    {
        l++,r++;
        update(l,val);
        update(r+1,-val);
    }
    int query(int pos)
    {
        int ans = 0;
        pos++;
        while(pos > 0)
        {
            ans += tree[pos];
            pos -= (pos & -pos);
        }
        return ans;
    }
    
}bit;



void dfs(int u, int p = -1)
{
    if(p != -1) depth[u] = depth[p] + 1;
    par[u] = p;
    sz[u] = 1;
    
    if(p != -1) g[u].erase(find(g[u].begin(),g[u].end(),p));

    for(auto &v : g[u])
    {
        if(v == p) continue;
        dfs(v,u);
        sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(g[u][0],v);
    }
   
}

int head[N],in[N],out[N],T;
void dfs_hld(int u) {
  in[u] = T;
  ft[T] = u;
  T++;
  for (auto v : g[u]) {
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  out[u] = T;
}

int query(int u, int v) 
{
    int ans= 0;
    
    while(head[u] != head[v])
    {
        if(depth[head[u]] < depth[head[v]]) swap(u,v);
        int l = in[head[u]], r = in[u];
        ans = gcd(ans,t.query(l,r-1,0,0,n-1));
        int tmp = val[u] + bit.query(in[u]);
        ans = gcd(tmp,ans);
        u = par[head[u]];
        int nxt = u;
    }
    if(depth[u] > depth[v]) swap(u,v);
    int l = in[u], r = in[v];
    ans = gcd(ans,t.query(l,r-1,0,0,n-1));
    //debug(v,in[v],bit.query(in[v]));
    int tmp = val[v] + bit.query(in[v]);
    ans = gcd(tmp,ans);
    return ans;
}
void modify(int u, int v, int x)
{
    while(head[u] != head[v])
    {
        if(depth[head[u]] < depth[head[v]]) swap(u,v);
        int l = in[head[u]],r = in[u];
        if(r != n-1) t.update(0,0,n-1,r,x);
        if(l != 0) t.update(0,0,n-1,l-1,-x);
        bit.update(l,r,x);
        int nxt;
        u = par[head[u]];
        nxt =u;
    }
    if(depth[u] > depth[v]) swap(u,v);
    int l = in[u], r = in[v];
    t.update(0,0,n-1,r,x);
    if(l) t.update(0,0,n-1,l-1,-x);
    bit.update(l,r,x);
}
int32_t main()
{
    IOS;
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    for(int i = 0; i < n; i++) cin >> val[i];
    dfs(0);
    head[0] = 0;
    dfs_hld(0);
    t.init(n);
    t.build(0,0,n-1);
    bit.init(n);
  
    int q;
    cin >> q;
    while(q--)
    {
        char ch;
        cin >> ch;
        if(ch == 'F')
        {
            int u,v;
            cin >> u >> v;
            //debug(query(u,v));
            cout << query(u,v) << endl;
        }
        else
        {
            int u, v, x;
            cin >> u >> v >> x;
            modify(u,v,x);
        }
    }
    return 0;
}
