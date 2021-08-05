// https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A

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

int n;
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

    void update(int x, int lx, int rx, int i, int v)
    {
        if(lx == rx)
        {
            tree[x] = v;
            return;
        }
        int mid = (lx+rx)/2;
        if(i <= mid) update(2*x+1,lx,mid,i,v);
        else update(2*x+2,mid+1,rx,i,v);
        tree[x] = merge(tree[2*x+1], tree[2*x+2]);
    }

    void update(int i, int v){
        update(0,0,n-1,i,v);     
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
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
    cin >> n;
    vector<int>a(n,0);
    segtree st;
    st.init(n);
    st.build(a);
    for(int i = 0; i < n; i++)
    {
       int x;
       cin >> x;
       cout << st.query(x,n-1) << " ";
       st.update(x-1,1);
    }
}

int32_t main()
{
    IOS;
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
