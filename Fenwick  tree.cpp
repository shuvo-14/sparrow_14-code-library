struct BIT{
    int size = 1;
    vector<int>tree;
    void init(int n)
    {
        size = n + 1;
        tree.assign(size,0);
    }
    int query(int pos)
    {
        int ans = 0;
        while(pos > 0)
        {
            ans += tree[pos];
            pos -= (pos & -pos);
        }
        return ans;
    }
    int query(int l, int r)
    {
        return query(r) - query(l-1);
    }
    void update(int pos, int val)
    {
        while(pos < size)
        {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};
