https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

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
    int seg, pref,suf,sum;
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

    item single(int v)
    {
        if(v >= 0)
        {
            return {v,v,v,v};
        }
        else return {0,0,0,v};
    }

    item NEUTRAL_ELEMENT()
    {
        return {0,0,0,0};
    }

    //change accordingly
    item merge(item u, item v)
    {
        return
        {
            max({u.seg,v.seg,u.suf+v.pref}),
            max(u.pref,u.sum+v.pref),
            max(v.suf,v.sum+u.suf),
            u.sum + v.sum
        };
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

    void update(int x, int lx, int rx, int i, int v)
    {
        if(lx == rx)
        {
            tree[x] = single(v);
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

    item query(int l, int r, int x, int lx, int rx)
    {
        if(lx > r || rx < l) return NEUTRAL_ELEMENT(); //change accordingly
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
    for(auto &x: a) cin >> x;

    segtree st;
    st.init(n);
    st.build(a);

    cout << st.query(0,n-1).seg << endl;
    while(q--)
    {
        int i , v;
        cin >> i >> v;
        st.update(i,v);
        cout << st.query(0,n-1).seg << endl;
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
