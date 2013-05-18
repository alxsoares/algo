#define th(x) this->x = x
int rmq[2 * maxn];
struct ST {
	int mm[2 * maxn];
	int best[20][2 * maxn];

	void init(int n) {
		int i, j, a, b;
		mm[0] = -1;
		for (i = 1; i <= n; i++) {
			mm[i] = ((i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1]);
			best[0][i] = i;
		}
		for (i = 1; i <= mm[n]; i++) {
			for (j = 1; j <= n + 1 - (1 << i); j++) {
				a = best[i - 1][j];
				b = best[i - 1][j + (1 << (i - 1))];
				best[i][j] = rmq[a] < rmq[b] ? a : b;
			}
		}
	}

	int query(int a, int b) {
		if (a >  b) swap(a, b);
		int t;
		t = mm[b - a + 1];
		a = best[t][a];
		b = best[t][b - (1 << t) + 1];
		return rmq[a] < rmq[b] ? a : b;
	}
};
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		th(b); th(nxt);
	}
};
/**
	lcaת��Ϊrmq����
	ע��: 
		1.maxnΪ���ڵ���, ST�������F��bufҪ����Ϊ2*maxn!!!!!
		2.ST��Ϊ1��ʼ��������ȻΪ0��ʼ!
		3.F��ŷ������,rmq���������,Pĳ����ŷ�������е�һ�γ��ֵ�λ��
*/
struct LCA2RMQ {
	int n;							//�ڵ����
	Nod buf[2*maxn]; int len; int E[maxn];	//Tree	��Դ
	int V[2*maxn], route[maxn];				//·����Ȩ������ĳ���·����
	bool vis[maxn];						//0û�з��ʣ�Ҽ���ڷ���
	
	ST st;							//Spare-Table...
	int F[2*maxn], P[maxn], cnt;	//��������,cntΪ������,levΪdfsʱ����(���ٵݹ�ջ��С)
	
	void init(int n) {
		th(n);
		len = 0;
		memset(E, 255, sizeof(E));
	}
	
	void addEdge(int a, int b, int v) {
		buf[len].init(b, E[a]); V[len] = v; E[a] = len ++;
		buf[len].init(a, E[b]);	V[len] = v;	E[b] = len ++;
	}
	
	int query(int a, int b) {				//���������ڵ㣬��������lca�ڵ���
		return F[st.query(P[a], P[b])];
	}
	
	//1.���ݹ�桿
	void dfs(int a, int lev) {
		vis[a] = 1;		
		++cnt;
		F[cnt] = a;
		rmq[cnt] = lev;
		P[a] = cnt;
		for(int i = E[a]; i != -1; i = buf[i].nxt) {
			if(vis[buf[i].b]) continue;
			route[buf[i].b] = route[a] + V[i];
			dfs(buf[i].b, lev + 1);
			++cnt;
			F[cnt] = a;
			rmq[cnt] = lev;
		}
	}
	void solve(int root) {
		memset(vis, 0, sizeof(vis));
		route[root] = cnt = 0;
		dfs(root, 0);
		st.init(2 * n - 1);
	}
	
	//2.���ǵݹ�桿
	/*void solve(int root) {
		static Nod stk[maxn];
		memset(vis, 0, sizeof(vis));
		
		stk[0].init(root, E[root]);
		int len = Ҽ;
		int lev = 0;
		cnt = 0;
		route[root] = 0;										//update route!
		
		while(Ҽ) {
			Nod & cur = stk[len-Ҽ];
//here, b means current Nod, nxt means nxt's pointer(as buf.nxt)!
			if(false == vis[cur.b]) {
				vis[cur.b] = Ҽ;
				F[++ cnt] = cur.b;
				rmq[cnt] = lev;
				P[cur.b] = cnt;
			} else if(cur.nxt == -Ҽ) {
				if(--len == 0)	break;
				F[++ cnt] = stk[len-Ҽ].b;
				rmq[cnt] = -- lev;
			} else {
				int & i = cur.nxt;
				if(!vis[buf[i].b]) {
					route[buf[i].b] = route[cur.b] + V[i];		
//update route!
					lev ++;
					stk[len ++].init(buf[i].b, E[buf[i].b]);
				}
				i = buf[i].nxt;
			}
		}
		st.init(2 * n - 1);
		}*/
} lca;