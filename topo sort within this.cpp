#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
const int N = 100005;
vector<int>v[N];
int vis[N];
vector<int>t_sort;

bool dfs_sort(int u)
{
    vis[u] = 2;
    for(auto c: v[u]){
        if(vis[c] == 2) return true;
        if(vis[c] == 0 && dfs_sort(c)) return true;
    }
    vis[u] = 1;
    t_sort.pb(u);
    return false;
}

bool topo_sort(int n)
{
    for(int i = 1; i <= n; i++) vis[i] = 0;
    for(int i = 1; i <= n; i++){
        if(vis[i] == 0){
            if(dfs_sort(i)){
                return false;
            }
        }
    }
    reverse(all(t_sort));
    return true;
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<string>a(N);
    map<string,int>mp;

    
    for(int i = 1; i <= n; i++){
        string s;
        cin >> s;
        a[i] = s;
        
        mp[a[i]] = i;
    }
    for(int i = 1; i <= m; i++)
    {
        
        string s;
        int mt;
        bool ok = false;
        cin >> s >> mt;
        vector<int>x;
        for(int j = 0; j < (1 << k); j++)
        {
            string t = s;
            for(int l = 0; l < 4; l++){
               // cout << "j: " << j << " " << (1<<l) << " " << (j & (1 << l)) << endl;
               // cout << "j: " << j << " l: " << l << " 1<<l: " << (1<<l) <<  " " << (j & (1 << l)) << endl;
                if((j & (1 << l))) t[l] = '_';
            }
            //cout << t << endl;
            if(mp.count(t)){
                x.pb(mp[t]);
            }
            if(t == a[mt]) ok = true;
        }
        if(!ok){cout << "NO\n"; return;}
        for(int c: x){
            if(c == mt) continue;
            v[mt].pb(c);
        }
    }
    //cout << "top: " << endl;
    if(topo_sort(n)){
        cout << "YES\n";
        for(auto c: t_sort) cout << c << " ";
    }
    else cout << "NO\n";
    
}

int main()
{
    IOS;
    int t = 1;
   // cin >> t;
    while(t--) solve();

    return 0;
}
