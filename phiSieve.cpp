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
int phi[N];
bitset<N>vis;
void phiSieve()
{
    for(int i = 1; i < N; i++) phi[i] = i;
    vis[1] = 1;
    for(int i = 2; i < N; i++)
    {
        if(!vis[i])
        {
            for(int j = i; j < N; j += i)
            {
                vis[j] = 1;
                phi[j] -= phi[j]/i;
            }
        }
    }
}
void solve()
{
    int n;
    cin >> n;
    cout << phi[n] << endl;
}

int main()
{
    IOS;
    int t;
    phiSieve();
    cin >> t;
    while(t--) solve();

    return 0;
}
