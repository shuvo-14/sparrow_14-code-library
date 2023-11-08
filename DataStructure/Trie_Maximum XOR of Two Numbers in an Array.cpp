struct Node{
    Node* link[2];
    bool containsKey(int bit)
    {
        return (link[bit] != NULL);
    }
    void put(int bit, Node* node)
    {
        link[bit] = node;
    }
    Node* get(int bit)
    {
        return link[bit];
    }
};
class Trie{
private: Node* root;
public:
    Trie()
    {
        root = new Node();
    }
    void insert(int val)
    {
        Node* node = root;
        for(int i = 31; i >= 0; i--)
        {
            int bit = (val>>i)&1;
            if(!node->containsKey(bit))
            {
                node->put(bit,new Node());
            }
            node = node->get(bit);
        }
    }
    int getMax(int val)
    {
        Node* node = root;
        int curMx = 0;
        for(int i = 31; i >= 0; i--)
        {
            int bit = (val>>i)&1;
            if(node->containsKey(1-bit))
            {
                curMx |= (1<<i);
                node = node->get(1-bit);
            }
            else node = node->get(bit);
        }
        return curMx;
    }
};

class Solution {
public:
    Trie trie;
    int findMaximumXOR(vector<int>& nums) {
        for(int cur : nums) trie.insert(cur);
        int max_ans = 0;
        for(int cur : nums)
        {
            int cur_mx = trie.getMax(cur);
            if(cur_mx > max_ans) max_ans = cur_mx;
        }
        return max_ans;
    }
};
