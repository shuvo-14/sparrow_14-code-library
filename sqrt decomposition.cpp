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
const int N=1e5+9;
int a[N];
int F[N];
int block;
// must be 0 based index
int get_min(int l, int r)
{
    int LB = l / block;
    int RB = r / block;
    int mn = INT_MAX;
    if(LB == RB)
    {
        for(int i = l; i <= r; i++) mn = min(mn,a[i]);
        return mn;
    }
    for(int i = l; i < (LB+1) * block; i++) mn = min(mn,a[i]);
    for(int i = LB+1; i < RB; i++) mn = min(mn,F[i]);
    for(int i = (RB)*block; i <= r; i++) mn = min(mn,a[i]);
    return mn;
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    block = sqrt(n);
    int r = n / block;
    for(int i = 0; i < r; i++)
    {
        int mn = INT_MAX;
        for(int j = block * i ; j < (i+1)*block; j++)
        {
            mn = min(mn,a[j]);
        }
       
        F[i] = mn;
        // cout << "i: " << i << " " <<  F[i] << endl;
    }
    if(n%block)
    {
        int mn = INT_MAX;
        for(int j = r * block; j < n; j++) mn = min(mn,a[j]);
        F[r] = mn;
    }
    int q;
    cin >> q;
    while(q--)
    {
        int l, r;
        cin >> l >> r;
        cout << get_min(l,r) << endl;
    }
}

int main()
{
    IOS;
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
