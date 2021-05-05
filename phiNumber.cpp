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
vector<int>prime;
bitset<N>isComposite;
int phi[N];
void sievePhi()
{
    for(int i = 2; i < N; i++)
    {
        if(!isComposite[i])
        {
            prime.pb(i);
            phi[i] = i - 1;
        }
        for(int j = 0; j < prime.size() && i * prime[j] < N; j++)
        {
            isComposite[i*prime[j]] = 1;
            if(i%prime[j] == 0)
            {
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            else phi[i*prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}
void solve()
{
    int n;
    cin >> n;
    cout  << phi[n] << endl;
}

int main()
{
    IOS;
    int t;
    sievePhi();
    cin >> t;
    while(t--) solve();

    return 0;
}
