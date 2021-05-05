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
const int N=3e5+9;
ll a[N];
ll fre[N];
ll ff[N];
ll ans[N];
ll n, q, block;

struct query {
    ll l, r, i;
};
vector<query>v;

bool comp(query x, query y)
{
    if(x.l/block != y.l/block) return x.l/block < y.l/block;
    return x.r/block < y.r/block;
}
int last_l = 1, last_r = 0;
ll res = 0;
void add(ll x)
{
    ll preF = fre[a[x]];
    ll curF = preF+1;
    fre[a[x]]++;
    if(ff[preF]) ff[preF]--;
    ff[curF]++;
    res = max(res,curF);
}

void remove(ll x)
{
    ll preF = fre[a[x]];
    fre[a[x]]--;
    ll curF = fre[a[x]];
    ff[preF]--;
    ff[curF]++;
    if(curF < res)
    {
        if(ff[res]==0) res--;
    }
    
}
void solve()
{
    cin >> n >> q;
    block = sqrt(n);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        v.pb({l,r,i});
    }
    sort(all(v),comp);
    for(int i = 0; i < q; i++)
    {
        cout << endl;
        int l = v[i].l, r = v[i].r;
        //add
         while(r > last_r) last_r++, add(last_r);
         while(last_l > l) last_l--, add(last_l);
        //remove
        while(l > last_l) remove(last_l),last_l++;
        while(last_r > r) remove(last_r),last_r--;
        ans[v[i].i] = res;
    }
    for(int i = 1; i <= q; i++) cout << ans[i] << endl;
}

int main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
