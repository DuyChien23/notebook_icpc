#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> II;
const int N = 4e5 + 5, logN = 20;
const int MOD[2] = {998244353, 1000000007};

#define ms(s, n) memset(s, n, sizeof(s))
#define sz(a) (int) ((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())

inline ll sqr(int x) {return x * 1ll * x;}
inline int fpow(ll n, ll k, int p) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
inline void addmod(int& a, int val, int p) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p) {return (ll) a * b % p;}

struct suffix{
      int id, sL, sR;
      suffix(int _id = 0, int _sL = 0, int _sR = 0) : id(_id), sL(_sL), sR(_sR) {}
      bool operator < (const suffix& other) const{
            if(sL != other.sL) return sL < other.sL;
            return sR < other.sR;
      }
      bool operator == (const suffix& other) const{
            return sL == other.sL && sR == other.sR;
      }
};

int P[logN][N], cnt[N], Rank[N];

void radixSort(vector<suffix> &a, int n){
      vector<suffix> tmp(n);
      for(int i = 0; i < n; i ++) cnt[a[i].sR] ++;
      for(int i = 1; i < n; i ++) cnt[i] += cnt[i - 1];
      for(int i = n - 1; i >= 0; i --) tmp[-- cnt[a[i].sR]] = a[i];
 
      for(int i = 0; i < n; i ++) cnt[i] = 0;
      a = tmp;
 
      for(int i = 0; i < n; i ++) cnt[a[i].sL] ++;
      for(int i = 1; i < n; i ++) cnt[i] += cnt[i - 1];
      for(int i = n - 1; i >= 0; i --) tmp[-- cnt[a[i].sL]] = a[i];
 
      for(int i = 0; i < n; i ++) cnt[i] = 0;
      a = tmp;
}

vector<int> suffixArray(const string &s, int n){
      vector<char> ord(s.begin(), s.end());
      sort(all(ord));
      uni(ord);
      for(int i = 0; i < n; i ++){
          P[0][i] = lower_bound(all(ord), s[i]) - ord.begin();  
      }
      vector<int> sufA(n); 
      for(int i = 1; i < logN; i ++){
            vector<suffix> a;
            for(int j = 0; j < n; j ++) a.push_back( suffix(j, P[i - 1][j], P[i - 1][(j + (1 << i - 1)) % n]) );
            radixSort(a, n);
            int classes = 0;
            for(int j = 0; j < n; j ++){
                  if(j > 0 && a[j - 1] < a[j]) classes ++;
                  P[i][a[j].id] = classes;
            }
            for(int j = 0; j < n; j ++) sufA[j] = a[j].id;
      }
      return sufA;
}

vector<int> buildLCP(const vector<int>& sufA, const string& s, int n){
      vector<int> LCP(n - 1);
      for(int i = 0; i < n; i ++) Rank[sufA[i]] = i;
      int k = 0;
      for(int i = 0; i < n - 1; i ++){
            int j = sufA[Rank[i] - 1];
            while(i + k < n && j + k < n && s[i + k] == s[j + k]) k ++;
            LCP[Rank[i] - 1] = k;
            if(k > 0) k --;
      }
      return LCP;
}



void Lalisa(){
      string s, t;
      cin >> s >> t;
      string a = s + '#' + t + '$';
      int n = a.size(), S = s.size(), T = t.size();
      vector<int> suf = suffixArray(a, n);
      vector<int> lcp = buildLCP(suf, a, n);


}

int main(){
       //freopen("test.inp", "r", stdin);
       //freopen("test.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int nTest = 1;
    //cin >> nTest;
    while(nTest --) Lalisa();
    return 0;
}
