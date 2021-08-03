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
const int N=2e5+9;
int a[N],b[N], m[N][18];
int n;
int query(int l, int r)
{
    int len = r - l + 1;
    len = log2(len);
    int x = m[l][len];
    int y = m[r-(1<<len)+1][len];
    return __gcd(x,y);
}
void solve()
{
    cin >> n;
    for(int i =  1; i <= n; i++) cin >> a[i];
    for(int i = 1; i < n; i++) b[i] = abs(a[i+1]-a[i]), m[i][0] = b[i];
    n--;
    for(int j = 1; j < 20; j++)
    {
        for(int i = 1;  i + (1<<j)-1 <= n; i++) m[i][j] = __gcd(m[i][j-1],m[i+(1<<(j-1))][j-1]);
    }
    int ans=1;
    for(int i = 1; i <= n; i++)
    {
        int lo = i, hi = n;
        int ok = 0, now = 0;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (query(i, mid) > 1LL)
            {
                ok = 1;
                now = mid - i + 1;
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }

        ans = max(ans, now + 1);
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
