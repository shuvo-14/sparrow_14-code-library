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
const int N=3e5+9;
void counting_sort(vector<int>&p,vector<int>&c)
{
    int n = p.size();
    vector<int>cnt(n),pos(n);
    for(auto x: c) cnt[x]++;
    for(int i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];
    vector<int>p_new(n);
    for(auto x: p)
    {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}
void solve()
{
    string s;
    cin >> s;
    s += '$';
    int n = s.size();
    vector<int>p(n),c(n);
    vector<pair<char,int>>a(n);
    for(int i = 0; i < n; i++) a[i] = {s[i],i};
    sort(all(a));
    for(int i = 0; i < n; i++) p[i] = a[i].ss;
    c[p[0]] = 0;
    for(int i = 1; i < n; i++)
    {
        if(a[i].ff == a[i-1].ff)  c[p[i]] = c[p[i-1]];
        else c[p[i]] = c[p[i-1]] + 1;
    } 
    int k = 0;
    while((1<<k) < n)
    {
        for(int i = 0; i < n; i++) p[i] = (p[i] - (1<<k)+n) % n;
        counting_sort(p,c);
        vector<int>c_new(n);
        c_new[p[0]] = 0;
        for(int i = 1; i < n; i++)
        {
            pair<int,int>cur,prev;
            prev = {c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
            cur = {c[p[i]],c[(p[i]+(1<<k))%n]};
            if(cur == prev) c_new[p[i]] = c_new[p[i-1]];
            else c_new[p[i]] = c_new[p[i-1]] + 1;
        }
        k++;
        c = c_new;
    }
   // for(int i = 0; i < n; i++) cout << p[i] << " " << s.substr(p[i],n-p[i]) << endl;; cout << endl;
    vector<int>lcp(n);
    k = 0;
    for(int i = 0; i + 1 < n; i++)
    {
        int x = c[i];
        int j = p[x-1];
        while(s[i+k] == s[j+k]) k++;
        lcp[x-1] = k;
        k = max(k-1,0); 
    }
    for(int i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
    for(int i = 0; i + 1 < n; i++) cout << lcp[i] <<" "; cout << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
