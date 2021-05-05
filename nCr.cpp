ll mem[105][105];

ll nCr(ll n, ll r)
{
    
    if(n == r) return 1;
    if(r == 1) return n;
    if(r == 0) return 1;
    if(mem[n][r] != -1) return mem[n][r];
    return mem[n][r] = nCr(n-1,r) + nCr(n-1,r-1);
}
