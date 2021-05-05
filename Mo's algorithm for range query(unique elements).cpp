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
const int N=1e6+9;
int fre[1000005];
int ans[200005];
int a[30005];
int len, cnt = 0;
struct query
{
    int l, r, id;
};
query ask[2*N];
 
bool comp(query x, query y)
{
    if(x.l/len != y.l/len) return x.l/len < y.l/len;
    return x.r/len < y.r/len;
}
int last_l = 1, last_r = 0;
 
void add(int i)
{
    if(fre[a[i]] == 0) cnt++;
    fre[a[i]]++;
}
void remove(int i)
{
    fre[a[i]]--;
    if(fre[a[i]] == 0) cnt--;
}
 
void solve()
{
    int n;
    cin >> n;
    len = sqrt(n);
    for(int i = 1; i <= n; i++) cin >> a[i];
    int m;
    cin >> m;
    for(int i = 1; i <= m; i++)
    {
        int l, r;
        cin >> ask[i].l >> ask[i].r; ask[i].id = i;
    }
    sort(ask+1,ask+m+1,comp);
    
    for(int i = 1; i <= m; i++)
    {
        int l, r;
        l = ask[i].l, r = ask[i].r;
        while(last_l > l) last_l--, add(last_l);
        while(last_l < l) remove(last_l), last_l++;
        while(last_r > r)  remove(last_r), last_r--;
        while(last_r < r) last_r++, add(last_r);
        ans[ask[i].id] = cnt;
    }
    for(int i = 1; i <= m; i++) cout << ans[i] << endl;
}
 
int main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();
 
    return 0;
} 
