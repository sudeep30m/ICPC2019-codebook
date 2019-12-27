#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


#include "../../content/geometry/ConvexHull.h"
namespace old {
pair<vi, vi> ulHull(const vector<P>& S) {
	vi Q(sz(S)), U, L;
	iota(all(Q), 0);
	sort(all(Q), [&S](int a, int b){ return S[a] < S[b]; });
	trav(it, Q) {
#define ADDP(C, cmp) while (sz(C) > 1 && S[C[sz(C)-2]].cross(\
	S[it], S[C.back()]) cmp 0) C.pop_back(); C.push_back(it);
		ADDP(U, <=); ADDP(L, >=);
	}
	return {U, L};
}

vi convexHull(const vector<P>& S) {
	vi u, l; tie(u, l) = ulHull(S);
	if (sz(S) <= 1) return u;
	if (S[u[0]] == S[u[1]]) return {0};
	l.insert(l.end(), u.rbegin()+1, u.rend()-1);
	return l;
}
}
ostream &operator<<(ostream &os, P p) { return cout << "(" << p.x << "," << p.y << ")"; }
struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
int main() {
    const int SZ = 1e2;
    rep(t,0,100000) {
        const int GRID=1e3;
        vector<P> pts(SZ);
        rep(i,0,SZ) pts[i] = P(rand()%GRID, rand()%GRID);
        auto res = convexHull(pts);
        auto res2 = old::convexHull(pts);
        assert(sz(res) == sz(res2));
        rep(i,0,sz(res2)) {
            assert(pts[res2[i]] == res[i]);
        }
    }
    cout<<"Tests passed!"<<endl;
}
