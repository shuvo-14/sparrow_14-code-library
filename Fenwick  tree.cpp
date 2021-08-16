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
const int N=1e4+9;
int tree[N];

void update(int pos, int v, int n)
{
    while(pos <= n)
    {   
        tree[pos] += v;
        pos += (pos & -pos);
    }
}
int query(int pos)
{
    int sum = 0;
    while(pos > 0)
    {
        sum += tree[pos];
        pos -= (pos & -pos);
    }
    return sum;
}
void solve()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
    {
        int v;
        cin >> v;
        update(i,v,n);
    }
    while(q--)
    {
        char ch;
        cin >> ch;
        if(ch == 's')
        {
            int l, r, m;
            cin >> l >> r >> m;
            int ans = query(r) - query(l-1);
            cout << ans % m << endl;
        }
        else if(ch == '+')
        {
            int i, v;
            cin >> i >> v;
            update(i,v,n);
        }
        else
        {
            int i, v;
            cin >> i >> v;
            update(i,-v,n);
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
