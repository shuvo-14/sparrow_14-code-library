array<int,3> exgcd(int a, int b)
{
    if(!b) return {a,1LL,0LL};
    auto [g,x,y] = exgcd(b,a%b);
    return {g,y,x-(a/b)*y};
}
