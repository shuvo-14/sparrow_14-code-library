//https://toph.co/p/just-another-range-query?fbclid=IwAR2fhcegIDNGGN6Y6sXABu3IodzKlRULWg3YxVLuYhYMwRz0C_hg-YyReYM

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
const int N=1e5+9;
const int logn = 35;

int n;
int tree[N*logn],lazy[N*logn],L[N*logn],R[N*logn];
int cnt = 1;
struct segtree{
    
    int merge(int u, int v)
    {
        return u + v;
    }

    int create(int &x)
    {
        if(!x)
        {
            x = ++cnt;
        }
        return x;
    }

    void propagate(int x, int lx, int rx)
    {
        if(lazy[x])
        {
            tree[x] += (rx-lx+1) * lazy[x];
            if(lx != rx)
            {
                lazy[create(L[x])] += lazy[x];
                lazy[create(R[x])] += lazy[x];
            }
            lazy[x] = 0;
        }
    }

    void update(int x, int lx, int rx, int l, int r, int v)
    {
        propagate(x,lx,rx);
        if(lx > r || rx < l) return;
        if(lx >= l && rx <= r)
        {
            tree[x] += (rx-lx+1) * v * 1LL;
            lazy[x] += v;
            if(lx != rx)
            {
                lazy[create(L[x])] += lazy[x];
                lazy[create(R[x])] += lazy[x];
            }
            lazy[x] = 0;
            return;
        }
        int mid = (lx+rx)/2;
        update(create(L[x]),lx,mid,l,r,v);
        update(create(R[x]),mid+1,rx,l,r,v);
        tree[x] = merge(tree[L[x]],tree[R[x]]);
    }

    void update(int l, int r, int v){
        update(1,1,n,l,r,v);     
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
        propagate(x,lx,rx);
        if(lx > r || rx < l) return 0LL; //change accordingly
        if(lx >= l && rx <= r) return tree[x];
        int mid = (lx+rx)/2;
        int s1 = query(l,r,L[x],lx,mid);
        int s2 = query(l,r,R[x],mid+1,rx);
        return merge(s1,s2);
    }

    ll query(int l, int r)
    {
        return query(l,r,1,1,n);
    }

};
int get(int l, int r)
{
    return  (r-l+1) * (r+l) / 2;
}
void solve()
{
    int q;
    cin >> n >> q;
  
    segtree st;
    
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;
            st.update(l,r,v);
        }
         if(op == 2)
        {
            int l, r;
            cin >> l >> r;
            cout << "query: " << st.query(l,r) << endl;
            cout << get(l,r) - st.query(l,r) << endl;
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
