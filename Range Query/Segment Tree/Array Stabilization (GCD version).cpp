//https://codeforces.com/contest/1547/problem/F

#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
//#define int long long
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
        return __gcd(u,v);
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
        build(0,0,2*n-1,vec);
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
        return query(l,r,0,0,2*n-1);
    }

};
void solve()
{
    cin >> n;
    vector<int>a(2*n);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i+n] = a[i];
    }
    segtree st;
    st.init(2*n);
    st.build(a);
    int ans = n-1, lo = 0, hi = n-1;
    while(lo <= hi)
    {
        int mid = (lo+hi)/2;
        int ok = 1, g = -1;
       // cout << "mid: " << mid << endl;
        for(int i = 0; i < n; i++)
        {
            int x = st.query(i,i+mid);
           // cout << "x: " << x << endl;
            if(g == -1) g = x;
            else if(g != x)
            {
                ok = 0;
                break;
            }
        }
        if(ok)
        {
            ans = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }
    cout << ans << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
    cin >> t;
    while(t--) solve();

    return 0;
}
