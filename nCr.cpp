  RECURSIVE
// ll mem[105][105];

// ll nCr(ll n, ll r)
// {
    
//     if(n == r) return 1;
//     if(r == 1) return n;
//     if(r == 0) return 1;
//     if(mem[n][r] != -1) return mem[n][r];
//     return mem[n][r] = nCr(n-1,r) + nCr(n-1,r-1);
// }
ITERATIVE

const int N=1e3+9;
int fac[N];
int invfac[N];

int Bigmod(int a, int n)
{
    if(n == 0) return 1;
    int x = Bigmod(a,n/2);
    x = (x*x) % mod;
    if(n&1) x = (x * a) % mod;
    return x;
}

int modInv(int a, int p)
{
    return Bigmod(a,p-2);
}

void precal()
{
    fac[0] = fac[1] = 1;
    for(int i = 2; i < N; i++) fac[i] = (fac[i-1] * i) % mod;
    invfac[N-1] = modInv(fac[N-1],mod);
    for(int i= N-2; i >= 0; i--) invfac[i] = (invfac[i+1] * (i+1)) % mod;
}

int nCr(int n, int r)
{
    if(r > n) return 0;
    int num = (fac[n] * invfac[r]) % mod;
    num = (num * invfac[n-r]) %mod;
    return num;
}
