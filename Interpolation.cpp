#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> II;
const int N = 1e6 + 5, logN = 20;
const int MOD = 1e9 + 7;
const int block = 500;
const ll inf  = 1e9 + 1;
const ll INF = 1e18;
#define ms(s, n) memset(s, n, sizeof(s))
#define sz(a) (int) ((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
#define point II
#define X first
#define Y second
inline ll sqr(int x) {return x * 1ll * x;}
inline int fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

inline int inverse(int x){
       return fpow(x, MOD - 2);
}

int f[N], n, k, ft[N];

int F(int x){
       if(x <= k + 1) return f[x];
       int fact = 1;
       for(int i = 0; i <= k + 1; i ++) fact = mult(fact, x - i);
       int ans = 0;
       for(int i = 0; i <= k + 1; i ++){
             int num = mult( f[i], mult( fact, inverse(x - i) ) ); // num
             int dem = mult(ft[i], ft[k + 1 - i]);
             if((k - i + 1) % 2 == 1) dem = (MOD - dem) % MOD; // mult with pow(-1, k - i + 1);
             addmod( ans, mult(num, inverse(dem)) ); 
       }
       return ans;
}
void Lalisa(){
       cin >> n >> k;
       ft[0] = 1;
       for(int i = 1; i <= k + 1; i ++){
           f[i] = (f[i - 1] + fpow(i, k)) % MOD;
           ft[i] = mult(ft[i - 1], i);
       }
       cout << F(n) << "\n";
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