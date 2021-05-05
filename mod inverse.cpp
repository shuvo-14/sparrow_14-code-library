// Calculates a^b
// for mod inverse of a % m, we need to calculate bigmod(a,m-2);
ll BigMod(ll a, ll b)
  {
      if(b==0) return 1;
      ll x = BigMod(a,b/2);
      x = (x * x) % mod;
      if(b%2) x = (x*a) % mod;
      return x;
  }
