#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long LL;

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d: ", cas);
		string s;
		cin >> s;
		int n = s.size();
		if (n < 4) {
			cout << s << "nanodesu" << endl;
		}else if (s.substr(n - 4, 4) == "desu") {
			cout << s.substr(0, n - 4) << "nanodesu" << endl;
		} else {
			cout << s << "nanodesu" << endl;
		}
	}
	return 0;
}
