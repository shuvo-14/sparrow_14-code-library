//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/minimize-product-265ce7a0/

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
    int mn, mncnt, mx, mxcnt;
    item(int _mn = inf, int _mncnt = 0, int _mx = inf, int _mxcnt = 0)
    {
        mn = _mn, mx = _mx, mncnt = _mncnt, mxcnt = _mxcnt;
    }
};
int n;
struct segtree{
    
    int size;
    vector<item>tree;
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size,item());
        
    }
    //change accordingly
    item merge(item u, item v)
    {
      //  cout << "u: " << u.mn << " " << u.mncnt << " " << u.mx << " " << u.mxcnt << endl;
       // cout << "v: " << v.mn << " " << v.mncnt << " " << v.mx << " " <<v.mxcnt << endl;
       vector<pair<int,int>>vec;
       vec.pb({u.mn,u.mncnt});
       vec.pb({u.mx,u.mxcnt});
       vec.pb({v.mn,v.mncnt});
       vec.pb({v.mx,v.mxcnt});
       sort(all(vec));
       int now = vec[0].ff, cnt = vec[0].ss;
       int i = 1;
       for( ;i < 4; i++)
        {
            if(vec[i].ff != now) break;
            cnt += vec[i].ss;
        }
        item  res;
        if(i == 4)
        {
           // cout << "R: " << now << " " << cnt << " " << inf << " " << 0 << endl;
            return {now,cnt,inf,0};
        }
        int now1 = vec[i].ff, cnt1 = vec[i].ss;
        i++;
        for(; i < 4; i++)
        {
            if(vec[i].ff !=now1) break;
            cnt1 += vec[i].ss;
        }
        res = {now,cnt,now1,cnt1};
        cout << endl;
        return res;
    }
 
    void build(int x, int lx, int rx,vector<int>&vec)
    {
        if(lx == rx)
        {
            tree[x] = {vec[lx],1,inf,0};
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
            tree[x] = {v,1,inf,0};
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
        if(lx > r || rx < l) return {inf,0,inf,0}; //change accordingly
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
    int ans = 0;
   
    
    //cout << res.mn << " " << res.mncnt << " " << res.mx <<" " << res.mxcnt << endl;
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int i, v;
            cin >> i >> v;
            i--;
            st.update(i,v);
        }
        else
        {
            int l, r;
            cin >> l >> r; l--,r--;
            item now = st.query(l,r);
            
            if(now.mncnt > 1)
            {
                int x = now.mncnt;
                ans += ((x*(x-1)) / 2) % mod;
            }
            else if(now.mx != inf) ans += (now.mncnt * now.mxcnt) % mod;
            ans %= mod;
        }
    }
    // 5 2 3 3 3
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
