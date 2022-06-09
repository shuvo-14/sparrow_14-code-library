int a[N];

struct segtree 
{
    int sz = 1;
    vector<int>tree;
    void init(int n)
    {
        while(sz < n) sz *= 2;
        tree.assign(2*sz+1,0);
    }
    int merge(int lft, int rgt)
    {
        return min(lft,rgt);
    }
    void build(int x, int lx, int rx)
    {
        if(lx == rx)
        {
            tree[x] = a[lx];
            return;
        }
        int mid = (lx+rx)/2;
        build(2*x,lx,mid);
        build(2*x+1,mid+1,rx);
        tree[x] = merge(tree[2*x],tree[2*x+1]);
    }
    void update(int x, int lx, int rx, int i, int val)
    {
        if(lx == rx)
        {
            tree[x] = val;
            return;
        }
        int mid = (lx+rx)/2;
        if(i <= mid) update(2*x,lx,mid,i,val);
        else update(2*x+1,mid+1,rx,i,val);
        tree[x] = merge(tree[2*x],tree[2*x+1]);
    }
    int query(int x, int lx, int rx, int l, int r)
    {
        if(lx >= l and rx <= r) return tree[x];
        if(lx > r or rx < l) return inf;
        int mid = (lx+rx)/2;
        int q1 = query(2*x,lx,mid,l,r);
        int q2 = query(2*x+1,mid+1,rx,l,r);
        return merge(q1,q2);
    }
};
