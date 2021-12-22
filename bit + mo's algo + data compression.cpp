//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/sherlock-and-inversions/?fbclid=IwAR3HhstHEXJDa363rFydTMPnZur5j3Jllp2xb14xHaEuQ7vbDYT4JbIoF6Y
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
const int N=1e5+9;
int a[N];
ll ans[N];
int block = 300;
int mx;
struct BIT{
    vector<int>tree;
    int size = 1;

    void init(int n)
    {
        size = n;
        tree.assign(size+1,0);
    }

    void update(int pos, int val)
    {
        while(pos <= size)
        {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }

    ll pref(int pos)
    {
        int ans = 0;
        while(pos > 0)
        {
            ans += tree[pos];
            pos -= (pos & -pos);
        }
        return ans;
    }
    ll rsum(int l, int r)
    {
       if(r < l) return 0;
        return pref(r) - pref(l-1);
    }
};
struct item
{
    int l, r, id;
};
bool comp(item &x, item &y)
{
    if((x.l / block) != (y.l/block)) return x.l/block < y.l/block;
    return (x.r / block) < (y.r/block);
}
int last_l = 1, last_r = 0;
ll cnt = 0;
BIT bit;
void add_right(int pos)
{
    cnt += bit.rsum(a[pos]+1,mx);
    bit.update(a[pos],1);
}
void add_left(int pos)
{
    cnt += bit.rsum(1,a[pos]-1);
    bit.update(a[pos],1);
}
void remove_right(int pos)
{
    cnt -= bit.rsum(a[pos]+1,mx);
     bit.update(a[pos],-1);
}
void remove_left(int pos)
{
    cnt -= bit.rsum(1,a[pos]-1);
    bit.update(a[pos],-1);
}
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int>vec;
    for(int i = 1; i <= n; i++) 
    {
        int u; cin >> u; a[i] = u;
        vec.pb(u);
    }
    item query[q+1];
    
    for(int i = 1; i <= q; i++)
    {
        cin >> query[i].l >> query[i].r; 
        query[i].id = i;
    }
    sort(all(vec));
    vec.erase(unique(all(vec)),vec.end());
    sort(query+1,query+q+1,comp);
    mx = 0;
    for(int i = 1; i <= n; i++) a[i] = upper_bound(all(vec),a[i]) - vec.begin(), mx = max(mx,a[i]);
   // cout << "mx: " << mx << endl;
   // for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << endl;
    mx += 5;
    bit.init(mx+2);
    
    for(int i = 1; i <= q; i++)
    {
        while(last_l > query[i].l) last_l--, add_left(last_l);
        while(last_l <  query[i].l) remove_left(last_l), last_l++; 
        while(last_r > query[i].r) remove_right(last_r), last_r--;
        while(last_r < query[i].r) last_r++, add_right(last_r);
        ans[query[i].id] = cnt;
    }
    for(int i = 1; i <= q; i++) cout << ans[i] << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
