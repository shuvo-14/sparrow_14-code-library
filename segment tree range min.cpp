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
const int inf = 1e9;
int ara[N];
int tree[4*N];
//int sum[2*N];
void build(int si, int ss, int se)
{
    if(ss == se){
         tree[si] = ara[ss];
        return;
    }
    int mid = (ss + se) / 2;
    build(2*si,ss,mid);
    build(2*si+1,mid+1,se);
    tree[si] = min( tree[2*si], tree[2*si+1]); 
   // return;
}
 
int query(int si, int ss, int se, int qs, int qe)
{
    if(ss > qe || se < qs) return inf;
    if(ss >= qs && se <= qe) return tree[si];
    int mid = (ss+se)/2;
    int l = query(2*si,ss,mid,qs,qe);
    int r = query(2*si+1,mid+1,se,qs,qe);
    return min(l,r);
}
 
void solve()
{
    int n, m;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> ara[i];
    build(1,1,n);
    cin >> m;
    while(m--)
    {
        int l, r;
        cin >> l >> r;
        cout << query(1,1,n,l+1,r+1) << endl;
    }
}
 
int main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();
 
    return 0;
} 
