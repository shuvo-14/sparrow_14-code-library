string kmp(string s)
{
    // longest pref subsequence which is common
    vector<int>lps(s.size(),0);
    for(int i = 1; i < s.size(); i++)
    {
        int pre_idx = lps[i-1];
        while(pre_idx > 0 && s[pre_idx] != s[i]) 
        {
            pre_idx = lps[pre_idx-1];
        }
        lps[i] = pre_idx + (s[pre_idx] == s[i] ? 1 : 0);
    }
    int l = lps[s.size()-1];
    return s.substr(0,l);
}
