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
const int N=200005;
pair<int,pair<int,int>> nodes[3*N];
string s;
void build(int n, int l, int r)
{
   // cout << "build\n";
    if(l == r){
        if(s[l] == '+') nodes[n] = {1,{0,1}};
        else nodes[n] = {-1,{-1,0}};
       // cout << l + 1 << " " << r + 1 << " " << nodes[n].ff << " " << nodes[n].ss.ff << " " << nodes[n].ss.ss << endl;
        return;
    }
    int mid = (l+r)/2, left = 2 * n, right = 2 * n + 1;
    build(left,l,mid);
    build(right,mid+1,r);
    pair<int,pair<int,int>>x,y;
    x = nodes[left];
    y = nodes[right];
    int ft = x.ff + y.ff;
    int sc = min(x.ff+y.ss.ff,x.ss.ff);
    int tr = max(x.ff+y.ss.ss,x.ss.ss);
    nodes[n] = {ft,{sc,tr}};
    //cout << l + 1 << " " << r + 1 << " " << nodes[n].ff << " " << nodes[n].ss.ff << " " << nodes[n].ss.ss << endl;
}

pair<int,pair<int,int>> query(int n, int l, int r, int i, int j)
{
    if(l > j || r < i) return {0,{0,0}}; 
    if(l >= i && r <= j) return nodes[n];
    int mid = (l+r)/2, left = 2 * n, right = 2 * n + 1;
    pair<int,pair<int,int>> x,y;
    x = query(left,l,mid,i,j);
    y = query(right,mid+1,r,i,j);
    int fr = x.ff + y.ff;
    int sc = min(x.ff + y.ss.ff,x.ss.ff);
    int tr = max(x.ff+y.ss.ss,x.ss.ss);
    return {fr,{sc,tr}};
}

void solve()
{
    int n, m;
    cin >> n >> m;
    cin >> s;
    build(1,0,n-1);
    while(m--)
    {
        int l, r;
        cin >> l >>  r;
        pair<int,pair<int,int>>x,y;
        if(l == 1)  x = {0,{0,0}};
        else x = query(1,0,n-1,0,l-2);
        if(r != n)  y = query(1,0,n-1,r,n-1);
        else y = {0,{0,0}};
        // cout << x.ff << " " << x.ss.ff << " " << x.ss.ss << endl;
        // cout << y.ff << " " << y.ss.ff << " " << y.ss.ss << endl;
        int mn = min(x.ff+y.ss.ff,x.ss.ff);
        int mx = max(x.ff+y.ss.ss,x.ss.ss);
        cout << mx - mn + 1 << endl;
    }
}

int main()
{
    IOS;
    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}
