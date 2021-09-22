struct BIT{
    vector<int>tree;
    int size = 1;

    void init(int n)
    {
        size = n;
        tree.assign(size+1,0);
    }

    void update(int pos, int val)
    {
        while(pos <= size)
        {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }

    int pref(int pos)
    {
        int ans = 0;
        while(pos > 0)
        {
            ans += tree[pos];
            pos -= (pos & -pos);
        }
        return ans;
    }
    int rsum(int l, int r)
    {
        return pref(r) - pref(l-1);
    }
};
