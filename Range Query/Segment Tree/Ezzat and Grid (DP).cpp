// https://codeforces.com/contest/1557/problem/D

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
const int N=3e5+9;
const pair<int,int>NIL = {0,-1};
int sz;
struct segtree{
    
    int size;
    vector<pair<int,int>>tree,lazy;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size,NIL);
        lazy.assign(2*size,NIL);
    }

    //change accordingly
    pair<int,int> merge(pair<int,int> u, pair<int,int> v)
    {
        return max(u,v);
    }


    void propagate(int x, int lx, int rx)
    {
        if(lazy[x] != NIL)
        {
            tree[x] = max(tree[x],lazy[x]);
            if(lx != rx)
            {
                lazy[2*x] = max(lazy[2*x],lazy[x]);
                lazy[2*x+1] = max(lazy[2*x+1],lazy[x]);
            }
            lazy[x] = NIL;
        }
    }

    void update(int x, int lx, int rx, int l, int r, pair<int,int> v)
    {
        propagate(x,lx,rx);
        if(lx > r || rx < l) return;
        if(lx >= l && rx <= r)
        {
            tree[x] = max(tree[x],v);
            lazy[x] = max(lazy[x],v);
            if(lx != rx)
            {
                lazy[2*x] = max(lazy[2*x],lazy[x]);
                lazy[2*x+1] = max(lazy[2*x+1],lazy[x]);
            }
            lazy[x] = NIL;
            return;
        }
        int mid = (lx+rx)/2;
        update(2*x,lx,mid,l,r,v);
        update(2*x+1,mid+1,rx,l,r,v);
        tree[x] = merge(tree[2*x], tree[2*x+1]);
    }

    void update(int l, int r, pair<int,int> v){
        update(1,1,sz,l,r,v);     
    }

    pair<int,int> query(int l, int r, int x, int lx, int rx)
    {
        propagate(x,lx,rx);
        if(lx > r || rx < l) return NIL; //change accordingly
        if(lx >= l && rx <= r) return tree[x];
        int mid = (lx+rx)/2;
        pair<int,int> s1 = query(l,r,2*x,lx,mid);
        pair<int,int> s2 = query(l,r,2*x+1,mid+1,rx);
        return merge(s1,s2);
    }

    pair<int,int> query(int l, int r)
    {
        return query(l,r,1,1,sz);
    }

};

void solve()
{
   int n, m;
   cin >> n >> m;
   vector<pair<int,int>>v[n];
   vector<int>id;
   while(m--)
   {
       int i, l, r;
       cin >> i >> l >> r;
       v[i-1].pb({l,r});
       id.pb(l);
       id.pb(r);
   }
   sort(all(id));
   id.erase(unique(all(id)),id.end());
   for(int i = 0; i < n; i++)
   {
       for(auto &c: v[i])
       {
           c.ff = upper_bound(all(id),c.ff)-id.begin();
           c.ss = upper_bound(all(id),c.ss)- id.begin();
       }
   }
   sz = id.size();
   segtree st;
   st.init(sz);
   vector<int>prev(n,-1);
   for(int i = 0; i < n;i++)
   {
       pair<int,int>mx = NIL;
       for(auto &c : v[i])
           mx = max(mx,st.query(c.ff,c.ss));
       mx.ff++;
       prev[i] = mx.ss;
       mx.ss = i;
       for(auto &c: v[i])
          st.update(c.ff,c.ss,mx);
   }
   pair<int,int> mx = st.query(1,sz);
   int cur = mx.ss;
   vector<int>vis(n);
   while(cur != -1)
   {
       vis[cur] = 1;
       cur = prev[cur];
   }
   cout << n - mx.ff << endl;
   for(int i = 0; i < n; i++)
        if(!vis[i]) cout << i + 1 << " "; cout << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
