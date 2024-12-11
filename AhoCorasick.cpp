const int ALP = 26;

struct Node{
       Node *link;
       Node *next[ALP];
       int cnt = 0;
};

struct AhoCorasick{
       Node* root;
       AhoCorasick() {
              root = new Node();
              root->link = root;
       }
       void addWord(string s) {
              Node* cur = root;
              for(char c : s) {
                     int id = c - 'a';
                     if(cur->next[id] == nullptr) {
                            cur->next[id] = new Node();
                     }
                     cur = cur->next[id];
              }
              cur->cnt ++;
       }
       void buildSuffix() {
              queue<Node*> qu;
              for(int i = 0; i < ALP; i ++) {
                     if(root->next[i] == nullptr) {
                            root->next[i] = root;
                            continue;
                     }
                     root->next[i]->link = root;
                     qu.push(root->next[i]);
              }
              while(!qu.empty()){
                     Node* u = qu.front();
                     qu.pop();
                     for(int i = 0; i < ALP; i ++) {
                            Node* v = u->next[i];
                            if(v != nullptr) {
                                   Node* p = u->link;
                                   while(p != root && p->next[i] == nullptr) p = p->link;
                                   v->link = p->next[i];
                                   v->cnt += v->link->cnt;
                                   qu.push(v);
                            } else {
                                   Node* p = u->link;
                                   while(p != root && p->next[i] == nullptr) p = p->link;
                                   u->next[i] = p->next[i];
                            }
                     }
              }
       }
};

string t, s[N];
int n, m, pref[N], suf[N];

void Lalisa(){
       cin >> t >> m;
       n = t.size();
       t = " " + t + " ";
       AhoCorasick* AC = new AhoCorasick();
       for(int i = 1; i <= m; i ++) cin >> s[i], AC->addWord(s[i]);
       AC->buildSuffix();
       Node* cur = AC->root;
       for(int i = 1; i <= n; i ++) {
              cur = cur->next[ t[i] - 'a' ];
              pref[i] = cur->cnt;
       }
       delete AC;
       AC = new AhoCorasick();
       for(int i = 1; i <= m; i ++) {
              reverse(s[i].begin(), s[i].end());
              AC->addWord(s[i]);
       }
       AC->buildSuffix();
       cur = AC->root;
       for(int i = n; i >= 1; i --) {
              cur = cur->next[t[i] - 'a'];
              suf[i] = cur->cnt;
       }
       ll res = 0;
       for(int i = 1; i < n; i ++) res += pref[i] * 1ll * suf[i + 1];
       cout << res << "\n";
}
