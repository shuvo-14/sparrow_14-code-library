vector<ll>prime;
int vis[N];
void sieve()
{
    prime.pb(2);
    for(ll i = 3; i < N; i+=2)
    {
        if(vis[i]) continue;
        prime.pb(i);
        for(ll j = i * i; j < N; j+=2*i) vis[j] = 1;
    }
}
