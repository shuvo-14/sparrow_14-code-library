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
struct item{
    //Use required attributes
    int mn, mncnt, mx, mxcnt;

    //Default Values
    item(int _mn = inf, int _mncnt = 0, int _mx = inf, int _mxcnt = 0)
    {
        mn = _mn, mx = _mx, mncnt = _mncnt, mxcnt = _mxcnt;
    }
};
int n;
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
        return u + v;
    }

    void build(int x, int lx, int rx,vector<int>&vec)
    {
        if(lx == rx)
        {
            tree[x] = vec[lx];
            return;
        }
        int mid = (lx+rx)/2;
        build(2*x+1,lx,mid,vec);
        build(2*x+2,mid+1,rx,vec);
        tree[x] = merge(tree[2*x+1],tree[2*x+2]);
    }

    void build(vector<int>&vec)
    {
        build(0,0,n-1,vec);
    }

    void update(int x, int lx, int rx, int l, int r, int v)
    {
        if(lazy[x] != 0)
        {
            tree[x] += (rx-lx+1) * lazy[x];
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
            tree[x] += (rx-lx+1) * v;
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
            tree[x] += (rx-lx+1) * lazy[x];
            if(lx != rx)
            {
                lazy[2*x+1] += lazy[x];
                lazy[2*x+2] += lazy[x];
            }
            lazy[x] = 0;
        }
        if(lx > r || rx < l) return 0LL; //change accordingly
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

void solve()
{
    int q;
    cin >> n >> q;
    vector<int>a(n);
    for(auto &x: a) cin >> x;
    segtree st;
    st.init(n);
    st.build(a);

    //cout << st.query(0,n-1) << endl;
    
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;
            l--,r--;
            st.update(l,r,v);
        }
         if(op == 3)
        {
            int l, r;
            cin >> l >> r;
            l--,r--;
            cout << st.query(l,r) << endl;
        }
    }
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
