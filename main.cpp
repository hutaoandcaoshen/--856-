//方法一（改后）
//把每一对括号看成一个节点，就会明白那是多个分插的树，之前计算时直接压成了全是兄弟节点，导致发生错误
//之前思路有问题，现在是改后的
class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        for(int i=0;i<s.size();i++)
        {
            char ch=s[i];
            if(ch=='(')
            {
                st.push(0);
            }
            else
            {
                int m=st.top();
                st.pop();
                if(m==0)
                {
                    m+=1;
                }
                else{
                    m*=2;
                }
                st.top()+=m;
            }
        }
        return st.top();
    }
};


//方法二：深度计数
// 方法二：深度计数
class Solution {
public:
    int scoreOfParentheses(string s) {
        int ans = 0;
        int depth = 0;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                ++depth;
            } else {
                --depth;
                if (s[i - 1] == '(') {
                    ans += (1 << depth);
                }
            }
        }
        return ans;
    }
};

//方法三：区间dp
class Solution {
public:
    int scoreOfParentheses(string s) {
        int n = s.size();
        vector<int> match(n, -1);
        stack<int> st;
        
        // 预处理匹配括号
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                int j = st.top(); st.pop();
                match[i] = j;
                match[j] = i;
            }
        }
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // 按长度枚举
        for (int len = 2; len <= n; len += 2) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                
                // 只处理 s[i..j] 是有效括号串的情况
                if (s[i] != '(') continue;
                int k = match[i];
                if (k > j) continue;      // s[i] 的匹配位置在 j 之外
                
                if (k == j) {
                    // 情况一：整体是 (A)
                    if (i + 1 == j) {
                        dp[i][j] = 1;                  // ()
                    } else {
                        dp[i][j] = 2 * dp[i + 1][j - 1]; // (A)
                    }
                } else {
                    // 情况二：A B，其中 A = s[i..k]
                    // 只有 s[k+1..j] 也可能有效时才转移，避免越界
                    if (k + 1 <= j) {
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                    }
                }
            }
        }
        
        return dp[0][n - 1];
    }
};