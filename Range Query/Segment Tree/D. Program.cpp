//https://codeforces.com/contest/1473/problem/D

#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
// #define ll long long
#define pb push_back
#define ff first
#define ss second
#define int long long
#define all(x) x.begin(),x.end()
const int mod=1e9+7;
const int inf = 1e9;
const int N=3e5+9;
struct item{
    int lo, hi, total;
};
int n;
struct segtree{
    
    int size;
    vector<item>tree;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.resize(2*size);
    }

    //change accordingly
    item merge(item u, item v)
    {
        int one = min(u.lo,v.lo+u.total);
        int two = max(u.hi,v.hi+u.total);
        int three = u.total+v.total;

        return {one,two,three};
    }

    item single(int v)
    {
        if(v >= 0)
        {
            return {0,v,v};
        }
        return {v,0,v};
    }

    void build(int x, int lx, int rx,vector<int>&vec)
    {
        if(lx == rx)
        {
            tree[x] = single(vec[lx]);
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


    item query(int l, int r, int x, int lx, int rx)
    {
        if(lx > r || rx < l) return {0,0,0}; //change accordingly
        if(lx >= l && rx <= r) return tree[x];
        int mid = (lx+rx)/2;
        item s1 = query(l,r,2*x+1,lx,mid);
        item s2 = query(l,r,2*x+2,mid+1,rx);
        return merge(s1,s2);
    }

    item query(int l, int r)
    {
        return query(l,r,0,0,n-1);
    }

};

void solve()
{
    int q;
    cin >> n >> q;
    vector<int>a(n);
    for(int i= 0; i < n;i++)
    {
        char x; cin >> x;
        if(x == '+') a[i] = 1;
        else a[i] = -1;
    }
    segtree st;
    st.init(n);
    st.build(a);
    while(q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        item x, y;
        if(l == 0) x = {0,0,0};
        else x = st.query(0,l-1);
        if(r == n-1) y = {0,0,0};
        else y = st.query(r+1,n-1);
        item ans = st.merge(x,y);
    
        cout << ans.hi - ans.lo + 1 << endl;
    }
}

int32_t main()
{
    IOS;
    int t = 1;
    cin >> t;
    while(t--) solve();

    return 0;
}
