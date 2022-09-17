const int K = 26;

struct Vertex
{
    int leaf = 0;
    vector<int>next;
    Vertex()
    {
        next.assign(K,-1);
    }
};

vector<Vertex>Trie(1);

void add_string(string &s)
{
    int cur = 0;
    for(char ch : s)
    {
        int c = ch - 'a';
        if(Trie[cur].next[c] == -1)
        {
            Trie[cur].next[c] = Trie.size();
            Trie.emplace_back();
        }
        cur = Trie[cur].next[c];
    }
    Trie[cur].leaf++;
}
bool find(string &s)
{
    int cur = 0;
    for(char  ch : s)
    {
        int c = ch - 'a';
        if(Trie[cur].next[c] == -1) return 0;
        cur = Trie[cur].next[c];
    }
    return Trie[cur].leaf > 0;
}
void solve()
{
    for(int i = 0; i < 4; i++)
    {
        string s;
        cin >> s;
        add_string(s);
    }
    for(int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        cout << find(s) << endl;
    }
}
