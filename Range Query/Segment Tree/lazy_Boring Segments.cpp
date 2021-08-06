//https://codeforces.com/contest/1555/problem/E

#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
// #define int long long
#define all(x) x.begin(),x.end()
const int mod=1e9+7;
const int inf = 1e9;
const int N=3e5+9;

struct item{
    int l, r, w;
};

int n, m;
struct segtree{
    
    int size;
    vector<ll>tree,lazy;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size,0LL);
        lazy.assign(2*size,0LL);
    }

    //change accordingly
    int merge(int u, int v)
    {
        return min(u,v);
    }

    void update(int x, int lx, int rx, int l, int r, int v)
    {
        if(lazy[x] != 0)
        {
            tree[x] += lazy[x];
            if(lx != rx)
            {
                lazy[2*x+1] += lazy[x];
                lazy[2*x+2] += lazy[x];
            }
            lazy[x] = 0;
        }
        if(lx > r || rx < l) return;
        if(lx >= l && rx <= r)
        {
            tree[x] += v;
            lazy[x] += v;
            if(lx != rx)
            {
                lazy[2*x+1] += lazy[x];
                lazy[2*x+2] += lazy[x];
            }
            lazy[x] = 0;
            return;
        }
        int mid = (lx+rx)/2;
        update(2*x+1,lx,mid,l,r,v);
        update(2*x+2,mid+1,rx,l,r,v);
        tree[x] = merge(tree[2*x+1], tree[2*x+2]);
    }

    void update(int l, int r, int v){
        update(0,0,n-1,l,r,v);     
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
        if(lazy[x] != 0)
        {
            tree[x] += lazy[x];
            if(lx != rx)
            {
                lazy[2*x+1] += lazy[x];
                lazy[2*x+2] += lazy[x];
            }
            lazy[x] = 0;
        }
        if(lx > r || rx < l) return 1; //change accordingly
        if(lx >= l && rx <= r) return tree[x];
        int mid = (lx+rx)/2;
        int s1 = query(l,r,2*x+1,lx,mid);
        int s2 = query(l,r,2*x+2,mid+1,rx);
        return merge(s1,s2);
    }

    ll query(int l, int r)
    {
        return query(l,r,0,0,n-1);
    }

};

bool comp(item &x, item &y)
{
    return x.w < y.w;
}

void solve()
{
    cin >> m >> n;
    vector<item>a(m);
    for(int i = 0; i < m; i++)
    {
        cin >> a[i].l >> a[i].r >> a[i].w;
        a[i].r--;
    }
    sort(all(a),comp);
    
    segtree st;
    st.init(n);
    int i = 0, j = 0, ans = inf;
    while(i < m)
    {
        while(j < m && st.query(1,n-1) == 0)
        {
            st.update(a[j].l,a[j].r,1);
            j++;
        }
        if(st.query(1,n-1) == 0) break;
        int tmp = a[j-1].w - a[i].w;
        ans = min(ans,a[j-1].w-a[i].w);
        st.update(a[i].l,a[i].r,-1);
        i++;
    }
    cout << ans << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
