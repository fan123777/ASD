#pragma once

#include <vector>
#include <iostream>
#include "Common.h"
#include <memory>
#include <random>

namespace nsAlgorithmsOnGraphs
{
	namespace nsGraphPropertiesTypes
	{
		namespace nsGraph
		{
			// Graph classes
			struct Edge
			{
				int v;
				int w;
				Edge(int v = -1, int w = -1)
					: v(v), w(w)
				{
				}
			};

			template<typename Impl>
			class Graph
			{
			public:
				Graph(int count, bool directed = false)
				{
					m_Pimpl.reset(new Impl(count, directed));
				}

				~Graph()
				{

				}

				int V() const
				{
					return m_Pimpl->V();
				}

				int E() const
				{
					return m_Pimpl->E();
				}

				bool directed() const
				{
					return m_Pimpl->directed();
				}

				void insert(Edge e)
				{
					m_Pimpl->insert(e);
				}

				void remove(Edge e)
				{
					m_Pimpl->remove(e);
				}

				bool edge(int v, int w)
				{
					return m_Pimpl->edge(v, w);
				}

				typename Impl::Iterator getIterator(int v) const
				{
					return m_Pimpl->getIterator(v);
				}

			private:
				std::shared_ptr<Impl> m_Pimpl;
			};

			class DenseImpl
			{
				int Vcnt, Ecnt; bool digraph;
				std::vector<std::vector<bool>> adj;

			public:
				DenseImpl(int V, bool digraph = false)
					:adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
				{
					for (int i = 0; i < V; i++)
						adj[i].assign(V, false);
				}

				int V() const
				{
					return Vcnt;
				}

				int E() const
				{
					return Ecnt;
				}

				bool directed() const
				{
					return digraph;
				}

				void insert(Edge e)
				{
					int v = e.v, w = e.w;
					if (adj[v][w] == false)
						Ecnt++;
					adj[v][w] = true;
					if (!digraph)
						adj[w][v] = true;
				}

				void remove(Edge e)
				{
					int v = e.v, w = e.w;
					if (adj[v][w] == true)
						Ecnt--;
					adj[v][w] = false;
					if (!digraph)
						adj[w][v] = false;
				}

				bool edge(int v, int w) const
				{
					return adj[v][w];
				}

				class Iterator
				{
					const DenseImpl& G;
					int i, v;
				public:
					Iterator(const DenseImpl &G, int v)
						:G(G), v(v), i(-1)
					{
					}

					int begin()
					{
						i = -1;
						return next();
					}

					int next()
					{
						for (i++; i < G.V(); i++)
						if (G.adj[v][i] == true)
							return i;
						return -1;
					}

					bool end()
					{
						return i >= G.V();
					}
				};

				Iterator getIterator(int v) const
				{
					return Iterator(*this, v);
				}
			};

			class SparseImpl
			{
				int Vcnt, Ecnt; bool digraph;

				struct node
				{
					int v;
					node* next;
					node(int x, node* t)
					{
						v = x;
						next = t;
					}
				};

				typedef node* link;
				std::vector <link> adj;

			public:
				SparseImpl(int V, bool digraph = false) :
					adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
				{
					adj.assign(V, 0);
				}

				int V() const
				{
					return Vcnt;
				}

				int E() const
				{
					return Ecnt;
				}

				bool directed() const
				{
					return digraph;
				}

				void insert(Edge e)
				{
					int v = e.v, w = e.w;
					adj[v] = new node(w, adj[v]);
					if (!digraph)
						adj[w] = new node(v, adj[w]);
					Ecnt++;
				}

				void remove(Edge e);

				bool edge(int v, int w) const;

				class Iterator
				{
					const SparseImpl &G;
					int v;
					link t;
				public:
					Iterator(const SparseImpl &G, int v)
						:G(G), v(v)
					{
						t = 0;
					}

					int begin()
					{
						t = G.adj[v];
						return t ? t->v : -1;
					}

					int next()
					{
						if (t) t = t->next;
						return t ? t->v : -1;
					}

					bool end()
					{
						return t == 0;
					}
				};

				Iterator getIterator(int v) const
				{
					return Iterator(*this, v);
				}
			};

			// Edge functions
			template <typename Graph>
			std::vector <Edge> getEdges(Graph& G)
			{
				int E = 0;
				std::vector <Edge> a(G.E());
				for (int v = 0; v < G.V(); v++)
				{
					auto A = G.getIterator(v);
					for (int w = A.begin(); !A.end(); w = A.next())
					if (G.directed() || v < w)
						a[E++] = Edge(v, w);
				}
				return a;
			}

			template <typename Graph>
			void addEdges(Graph& G, std::vector<Edge> edges)
			{
				for (auto& element : edges)
				{
					G.insert(element);
				}
			}

			// Show Graph
			template <typename Graph>
			void show(Graph& G)
			{
				std::cout << "Adjacency list :"<< std::endl;
				for (int v = 0; v < G.V(); v++)
				{
					std::cout.width(2);
					std::cout << v << ":";
					auto A = G.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
					{
						std::cout.width(2);
						std::cout << t << " ";
					}
					std::cout << endl;
				}
			}

			template <typename Graph>
			void showEdges(Graph& G)
			{
				std::cout << "Edges :" << std::endl;
				auto edges = getEdges(G);
				for (auto& element : edges)
					std::cout << element.v << " - " << element.w << "\n";
			}

			template <typename Graph>
			void showAdjacencyMatrix(Graph& G)
			{
				std::cout << "Adjacency matrix :" << std::endl;

				auto edges = getEdges(G);
				auto V = G.V();
				bool directed = G.directed();

				int** matrix = new int*[V];
				for (int i = 0; i < V; ++i)
					matrix[i] = new int[V];

				for (int i = 0; i < V; i++)
				for (int j = 0; j < V; j++)
					matrix[i][j] = 0;

				for (auto& element : edges)
				{
					matrix[element.v][element.w] = 1;
					if (!directed)
						matrix[element.w][element.v] = 1;
				}

				for (int i = 0; i < V; i++)
				{
					for (int j = 0; j < V; j++)
						std::cout << matrix[i][j] << " ";
					std::cout << "\n";
				}

				for (int i = 0; i < V; ++i)
					delete[] matrix[i];
				delete[] matrix;
			}

			template <typename Graph>
			void showAll(Graph& G)
			{
				showAdjacencyMatrix(G);
				show(G);
				showEdges(G);
			}

			// scan Graph
			template <typename Graph>
			void scanEZ(Graph& G)
			{
				int a, b;
				int v = G.V();
				while (true)
				{
					std::cin >> a;
					if (a < 0 || a >= v)
						break;
					std::cin >> b;
					if (b < 0 || b >= v)
						break;
					G.insert(Edge(a, b));
				}
			}

			// rand Graph
			template <class Graph>
			void randE(Graph& G, int E)
			{
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_int_distribution<int> dist(0, G.V() - 1);

				for (int i = 0; i < E;)
				{
					Edge e(dist(mt), dist(mt));
					if (e.v != e.w && !G.edge(e.v, e.w))
					{
						G.insert(e);
						i++;
					}
				}

			}

			// vertex degree
			template <class Graph>
			class Degree
			{
				const Graph &G;
				std::vector <int> degree;

			public:
				Degree(const Graph &G)
					: G(G), degree(G.V(), 0)
				{
					for (int v = 0; v < G.V(); v++)
					{
						auto A = G.getIterator(v);
						for (int w = A.begin(); !A.end(); w = A.next())
							degree[v]++;
					}
				}

				int operator [] (int v) const
				{
					return degree[v];
				}
			};

			// find path
			template <class Graph> class sPath
			{
				const Graph &G;
				std::vector <bool> visited;

				bool searchR(int v, int w)
				{
					if (v == w)
						return true;
					visited[v] = true;
					auto A = G.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (!visited[t])
					if (searchR(t, w))
						return true;
					return false;
				}

				bool searchR(int v, int w, int d)
				{
					if (v == w)
						return (d == 0);
					visited[v] = true;
					auto A = G.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (!visited[t])
					if (searchR(t, w, d - 1))
						return true;
					visited[v] = false;
					return false;
				}

			public:
				sPath(const Graph &G)
					:G(G), visited(G.V(), false)
				{
				}

				bool findSimplePath(int v, int w)
				{
					return searchR(v, w);
				}

				bool findHamiltonPath(int v, int w)
				{
					return searchR(v, w, G.V() - 1);
				}
			};

			// cycle exists
			template <class Graph> class ePath
			{
				Graph G;
				int v, w;
				bool found;
				nsCommon::Stack <int> S;

				int tour(int v)
				{
					while (true)
					{
						auto A = G.getIterator(v);
						int w = A.begin();
						if (A.end())
							break;
						S.push(v);
						G.remove(Edge(v, w));
						v = w;
					}
					return v;
				}

			public:
				ePath(const Graph &G, int v, int w)
					:G(G), v(v), w(w)
				{
					Degree<Graph> deg(G);
					int t = deg[v] + deg[w];
					if ((t % 2) != 0)
					{
						found = false;
						return;
					}
					for (t = 0; t < G.V(); t++)
					if ((t != v) && (t != w))
					if ((deg[t] % 2) != 0)
					{
						found = false;
						return;
					}
					found = true;
				}

				bool exists() const
				{
					return found;
				}

				void show()
				{
					if (!found)
						return;
					while (tour(v) == v && !S.empty())
					{
						v = S.pop();
						std::cout << "-" << v;
						std::cout << std::endl;
					}
				}
			};

			// search
			template <class Graph> class sDFS
			{
				int cnt;
				const Graph &G;
				std::vector <int> ord;

				void searchC(int v)
				{
					ord[v] = cnt++;
					auto A = G.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (ord[t] == -1)
						searchC(t);
				}

			public:
				sDFS(const Graph &G, int v = 0)
					:G(G), cnt(0), ord(G.V(), -1)
				{
					searchC(v);
				}

				int count() const
				{
					return cnt;
				}

				int operator[](int v) const
				{
					return ord[v];
				}

				void show() const
				{
					std::cout << "Number of visited vertex: " << cnt << std::endl;
					std::cout << "Order of visited vertex: " << std::endl;
					for (int i = 0; i < G.V(); i++)
						std::cout << ord[i] << " ";
					std::cout << endl;
				}
			};

			template <class Graph> class Search
			{
			protected:
				const Graph &G;
				int cnt;
				std::vector <int> ord;
				virtual void searchC(Edge) = 0;

				void search()
				{
					for (int v = 0; v < G.V(); v++)
					if (ord[v] == -1)
						searchC(Edge(v, v));
				}
			public:
				Search(const Graph &G)
					: G(G), ord(G.V(), -1), cnt(0)
				{

				}

				int operator[](int v) const { return ord[v]; }
			};

			template <class Graph>
			class DFS : public Search<Graph>
			{
				std::vector<int> st;

				void searchC(Edge e)
				{
					int w = e.w;
					ord[w] = cnt++;
					st[e.w] = e.v;
					auto A = G.getIterator(w);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (ord[t] == -1)
						searchC(Edge(w, t));
				}

			public:
				DFS(const Graph &G)
					: Search<Graph>(G), st(G.V(), -1)
				{
					search();
				}

				int ST(int v) const
				{
					return st[v];
				}

				void show() const
				{
					std::cout << "Number of visited vertex: " << cnt << std::endl;
					std::cout << "Order of visited vertex: " << std::endl;
					for (int i = 0; i < G.V(); i++)
						std::cout << ord[i] << " ";
					std::cout << endl;
					std::cout << "Parent vertex: " << std::endl;
					for (int i = 0; i < G.V(); i++)
						std::cout << st[i] << " ";
					std::cout << endl;
				}
			};

			template <class Graph>
			class Euler : public Search<Graph>
			{
			private:
				void searchC(Edge e)
				{
					int v = e.v, w = e.w;
					ord[w] = cnt++;
					std::cout << "-" << w;
					auto A = G.getIterator(w);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (ord[t] == -1) searchC(Edge(w, t));
					else if (ord[t] < ord[v])
						std::cout << "-" << t << "-" << w;
					if (v != w)
						std::cout << "-" << v;
					else
						std::cout << endl;
				}
			public:
				Euler(Graph &G)
					:Search<Graph>(G)
				{
					search();
				}
			};

			template <class Graph>
			class BFS : public Search<Graph>
			{
				std::vector<int> st;

				void searchC(Edge e)
				{
					nsCommon::Queue<Edge> Q;
					Q.put(e);
					ord[e.w] = cnt++;
					while (!Q.empty())
					{
						e = Q.get();
						st[e.w] = e.v;
						auto A = G.getIterator(e.w);
						for (int t = A.begin(); !A.end(); t = A.next())
						if (ord[t] == -1)
						{
							Q.put(Edge(e.w, t));
							ord[t] = cnt++;
						}
					}
				}

			public:
				BFS(Graph &G)
					: Search<Graph>(G), st(G.V(), -1)
				{
					search();
				}

				int ST(int v) const
				{
					return st[v];
				}
			};

			template <class Graph>
			class PFS : public Search<Graph>
			{
				std::vector<int> st;

				void searchC(Edge e)
				{
					GQ<Edge> Q(G.V());
					Q.put(e);
					ord[e.w] = cnt++;
					while (!Q.empty())
					{
						e = Q.get();
						st[e.w] = e.v;
						auto A = G.getIterator(e.w);
						for (int t = A.begin(); !A.end(); t = A.next())
						if (ord[t] == -1)
						{
							Q.put(Edge(e.w, t));
							ord[t] = cnt++;
						}
						else if (st[t] == -1)
							Q.update(Edge(e.w, t));
					}
				}
			public:
				PFS(Graph &G)
					:Search<Graph>(G), st(G.V(), -1)
				{
						search();
					}

				int ST(int v) const
				{
					return st[v];
				}
			};

			// Coherency
			template <typename Graph>
			class CC
			{
			private:
				const Graph & G;
				int ccnt;
				std::vector <int> id;

				void ccR(int w)
				{
					id[w] = ccnt;
					auto A = G.getIterator(w);
					for (int v = A.begin(); !A.end(); v = A.next())
					if (id[v] == -1)
						ccR(v);
				}

			public:
				CC(const Graph &G)
					:G(G), ccnt(0), id(G.V(), -1)
				{
					for (int v = 0; v < G.V(); v++)
					if (id[v] == -1)
					{
						ccR(v);
						ccnt++;
					}
				}

				int count() const
				{
					return ccnt;
				}

				bool connect(int s, int t) const
				{
					return id[s] == id[t];
				}
			};

			// Edge Coherency
			template <class Graph>
			class EC : public Search<Graph>
			{
				int bcnt;
				std::vector<int> low;

				void searchC(Edge e)
				{
					int w = e.w;
					ord[w] = cnt++;
					low[w] = ord[w];
					auto A = G.getIterator(w);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (ord[t] == -1)
					{
						searchC(Edge(w, t));
						if (low[w] > low[t])
							low[w] = low[t];
						if (low[t] == ord[t])
							bcnt++; // w-t является мостом 
					}
					else if
						(t != e.v)
					if (low[w] > ord[t])
						low[w] = ord[t];
				}

			public:
				EC(const Graph &G)
					:Search<Graph>(G), bcnt(0), low(G.V(), -1)
				{
					search();
				}

				int count() const
				{
					return bcnt + 1;
				}
			};

			// two colors
			template <class Graph> class BI
			{
				const Graph &G;
				bool OK;
				std::vector<int> vc;

				bool dfsR(int v, int c)
				{
					vc[v] = (c + 1) % 2;
					auto A = G.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (vc[t] == -1)
					{
						if (!dfsR(t, vc[v]))
							return false;
					}
					else if (vc[t] != c)
						return false;
					return true;
				}
			public:
				BI(const Graph &G) : G(G), OK(true), vc(G.V(), -1)
				{
					for (int v = 0; v < G.V(); v++)
					if (vc[v] == -1)
					if (!dfsR(v, 0))
					{
						OK = false;
						return;
					}
				}

				bool bipartite() const
				{
					return OK;
				}

				int color(int v) const
				{
					return vc[v];
				}
			};

			// get graph
			std::vector<Edge> getDFSGraphEdges(int& v);
			std::vector<Edge> getSearchGraphEdges(int& v);
			std::vector<Edge> getBridgeGraphEdges(int& v);
			std::vector<Edge> getBFSGraphEdges(int& v);
			std::vector<Edge> getDigraphEdges(int& v);
			std::vector<Edge> getDAGEdges(int& v);
			std::vector<Edge> getTransitiveClosureEdges(int& v);

			// reverse
			template <class inGraph, class outGraph>
			void reverse(const inGraph &G, outGraph &R)
			{

				for (int v = 0; v < G.V(); v++)
				{
					auto A = G.getIterator(v);
					for (int w = A.begin(); !A.end(); w = A.next())
						R.insert(Edge(w, v));
				}
			}

			// Программа 18.11.Реализация рандомизированной очереди
			template <class Item>
			class GQ
			{
			private:
				std::vector<Item> s;
				int N;

			public:
				GQ(int maxN) : s(maxN + 1), N(0)
				{
				}

				int empty() const
				{
					return N == 0;
				}

				void put(Item item)
				{
					s[N++] = item;
				}

				void update(Item x)
				{
				}

				Item get()
				{
					int i = int(N*rand() / (1.0 + RAND_MAX));
					Item t = s[i];
					s[i] = s[N - 1];
					s[N - 1] = t;
					return s[--N];
				}
			};

			// oriented DFS
			template <class Graph>
			class oDFS
			{
				const Graph &G;
				int depth, cnt, cntP;
				std::vector<int> pre, post;

				void show(char *s, Edge e)
				{
					for (int i = 0; i < depth; i++)
						std::cout << " ";
					std::cout << e.v << "-" << e.w << s << std::endl;
				}

				void dfsR(Edge e)
				{
					int w = e.w;
					show(" tree", e);
					pre[w] = cnt++;
					depth++;
					auto A = G.getIterator(w);
					for (int t = A.begin(); !A.end(); t = A.next())
					{
						Edge x(w, t);
						if (pre[t] == -1)
							dfsR(x);
						else if (post[t] == -1)
							show(" back", x);
						else if (pre[t] > pre[w])
							show(" down", x);
						else
							show(" cross", x);
					}
					post[w] = cntP++;
					depth--;
				}

			public:
				oDFS(const Graph &G)
					:G(G), cnt(0), cntP(0), pre(G.V(), -1), post(G.V(), -1)
				{
					for (int v = 0; v < G.V(); v++)
					if (pre[v] == -1)
						dfsR(Edge(v, v));
				}
			};

			// Transitive closure
			template <class tcGraph, class Graph>
			class TC
			{
				tcGraph T;

			public:
				TC(const Graph &G) : T(G)
				{
					for (int s = 0; s < T.V(); s++)
						T.insert(Edge(s, s));
					for (int i = 0; i < T.V(); i++)
						for (int s = 0; s < T.V(); s++)
							if (T.edge(s, i))
								for (int t = 0; t < T.V(); t++)
									if (T.edge(i, t))
										T.insert(Edge(s, t));
				}

				bool reachable(int s, int t) const
				{
					return T.edge(s, t);
				}
			};

			template <class Graph>
			class tc
			{
				Graph T;
				const Graph &G;

				void tcR(int v, int w)
				{
					T.insert(Edge(v, w));
					auto A = G.getIterator(w);
					for (int t = A.begin(); !A.end(); t = A.next())
						if (!T.edge(v, t))
							tcR(v, t);
				}

			public:

				tc(const Graph &G) : G(G), T(G.V(), true)
				{
					for (int v = 0; v < G.V(); v++)
						tcR(v, v);
				}

				bool reachable(int v, int w)
				{
					return T.edge(v, w);
				}
			};

			// traverse DAG
			template<typename Dag, typename Func>
			void traverseR(Dag D, int v, Func visit)
			{
				visit(v);
				auto a = D.getIterator(v);
				for (int t = A.begin(); !A.end(); t = A.next())
					traverseR(D, t);
			}

			// binary DAG
			// Программа 19.5.Представление бинарного дерева в виде двоичного графа DAG
			// int compressR(link h)
			// {
			// 	STx st;
			// 	if (h == NULL) return 0;
			// 	l = compressR(h->l);
			// 	r = compressR(h->r);
			// 	t = st.index(l, r);
			// 	adj[t].l = l; adj[t].r = r;
			// 	return t;
			// }

			// reverse topological sort
			// Программа 19.6. Обратная топологическая сортировка
			template <class Dag>
			class dagTS
			{
				const Dag &D;
				int cnt, tcnt;
				std::vector<int> pre, post, postI;

				void tsR(int v)
				{
					pre[v] = s cnt++;
					auto A = D.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
						if (pre[t] == -1)
							tsR(t);
					post[v] = tcnt;
					postI[tcnt++] = v;
				}

				// Программа 19.7.Топологическая сортировка
				void tsR1(int v)
				{
					pre[v] = cnt++;
					for (int w = 0; w < D.V(); w++)
						if (D.edge(w, v))
							if (pre[w] == -1)
								tsR1(w);
					post[v] = tcnt;
					postI[tcnt++] = v;
				}

			public:
				dagTS(const Dag &D)
					:D(D), tcnt(O), cnt(O),
					pre(D.V(), -1), post(D.V(), -1), postI(D.V(), -1)
				{
					for (int v = 0; v < D.V(); v++)
						if (pre[v] == -1) tsR(v);
				}

				int operator[](int v) const
				{
					return postI[v];
				}

				int relabel(int v) const
				{
					return post[v];
				}
			};

			// Программа 19.8.Топологическая сортировка, основанная на очереди истоков
			template <class Dag> class dagTS1
			{
				const Dag& D;
				std::vector<int> in, ts, tsI;

			public:
				dagTS1(const Dag &D) : D(D),
					in(D.V(), 0), ts(D.V(), -1), tsI(D.V(), -1)
				{
					nsCommon::Queue<int> Q;
					for (int v = 0; v < D.V(); v++)
					{
						auto A = D.getIterator(v);
						for (int t = A.begin(); !A.end(); t = A.next())
							in[t]++;
					}

					for (int v = 0; v < D.V(); v++)
					if (in[v] == 0)
						Q.put(v);
					for (int j = 0; !Q.empty(); j++)
					{
						ts[j] = Q.get();
						tsI[ts[j]] = j;
						auto A = D.getIterator(ts[j]);
						for (int t = A.begin(); !A.end(); t = A.next())
						if (--in[t] == 0)
							Q.put(t);
					}
				}

				int operator[] (int v) const
				{
					return ts[v];
				}

				int relabel(int v) const
				{
					return tsl[v];
				}
			};


		}

		namespace nsChapter
		{
			// Chapter 17
			// Программа 17.1.Интерфейс АТД графа
			struct Edge
			{
				int v;
				int w;
				Edge(int v = -1, int w = -1)
					: v(v), w(w)
				{
				}
			};

			namespace nsGraph
			{
				class Graph
				{
				private:
					// Код, зависящий от реализации 
				public:
					Graph(int count, bool oriented = false);
					~Graph();
					int V() const;
					int E() const;
					bool directed() const;
					int insert(Edge);
					int remove(Edge);
					bool edge(int, int);

					class adjIterator
					{
					public:
						adjIterator(const Graph &, int vertex);
						int begin();
						int next();
						bool end();
					};
				};

				// Программа 17.2.Пример клиентской функции обработки графов
				template <class Graph>
				std::vector <Edge> edges(Graph &G)
				{
					int E = 0;
					std::vector <Edge> a(G.E());
					for (int v = 0; v < G.V(); v++)
					{
						typename Graph::adjIterator A(G, v);
						for (int w = A.begin(); !A.end(); w = A.next())
						if (G.directed() || v < w)
							a[E++] = Edge(v, w);
					}
					return a;
				}

				// Программа 17.4.Интерфейс ввода/вывода для функций обработки графов
				template <class Graph>
				class IO
				{
				public:
					// Программа 17.3.Клиентская функция печати графа
					static void show(const Graph &G)
					{
						for (int s = 0; s < G.V(); s++)
						{
							std::cout.width(2);
							std::cout << s << ":";
							typename Graph::adjIterator A(G, s);
							for (int t = A.begin(); !A.end(); t = A.next())
							{
								std::cout.width(2);
								std::cout << t << " ";
							}
							std::cout << endl;
						}
					}

					static void scanEZ(Graph &);
					static void scan(Graph &);
				};

				// Программа 17.14.Построение графа из пар символов
				/*void IO<Graph>::scan(Graph &G)
				{
				string v, w;
				ST st;
				while (cin >> v >> w)
				G.insert(Edge(st.index(v), st.index(w)));
				}*/

				// Программа 17.5.Интерфейс связности
				template <class Graph>
				class CC
				{
				private:
					// Код, зависящий от реализации 
				public:
					CC(const Graph &);
					int count();
					bool connect(int, int);
				};
			}

			namespace nsDenseGraph
			{
				// Программа 17.7.Реализация АТД графа
				class Graph
				{
					int Vcnt, Ecnt; bool digraph;
					std::vector<std::vector<bool>> adj;

				public:
					Graph(int V, bool digraph = false)
						:adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
					{
						for (int i = 0; i < V; i++)
							adj[i].assign(V, false);
					}

					int V() const
					{
						return Vcnt;
					}

					int E() const
					{
						return Ecnt;
					}

					bool directed() const
					{
						return digraph;
					}

					void insert(Edge e)
					{
						int v = e.v, w = e.w;
						if (adj[v][w] == false)
							Ecnt++;
						adj[v][w] = true;
						if (!digraph)
							adj[w][v] = true;
					}
					void remove(Edge e)
					{
						int v = e.v, w = e.w;
						if (adj[v][w] == true)
							Ecnt--;
						adj[v][w] = false;
						if (!digraph)
							adj[w][v] = false;
					}

					bool edge(int v, int w) const
					{
						return adj[v][w];
					}

					class adjIterator;
					friend class adjIterator;
				};

				// Программа 17.8.Итератор для представления матрицы смежности
				class Graph::adjIterator
				{
					const Graph &G;
					int i, v;
				public:
					adjIterator(const Graph &G, int v)
						:G(G), v(v), i(-1)
					{
					}

					int begin()
					{
						i = -1;
						return next();
					}

					int next()
					{
						for (i++; i < G.V(); i++)
						if (G.adj[v][i] == true)
							return i;
						return -1;
					}

					bool end()
					{
						return i >= G.V();
					}
				};
			}

			class Graph
			{
				int Vcnt, Ecnt; bool digraph;

				struct node
				{
					int v;
					node* next;
					node(int x, node* t)
					{
						v = x;
						next = t;
					}
				};

				typedef node* link;
				std::vector <link> adj;

			public:
				Graph(int V, bool digraph = false) :
					adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
				{
					adj.assign(V, 0);
				}

				int V() const
				{
					return Vcnt;
				}

				int E() const
				{
					return Ecnt;
				}

				bool directed() const
				{
					return digraph;
				}

				void insert(Edge e)
				{
					int v = e.v, w = e.w;
					adj[v] = new node(w, adj[v]);
					if (!digraph)
						adj[w] = new node(v, adj[w]);
					Ecnt++;
				}

				void remove(Edge e);

				bool edge(int v, int w) const;

				// Программа 17.10.Итератор для представления графа в виде списка смежных вершин
				class adjlterator
				{
					const Graph &G;
					int v;
					link t;
				public:
					adjlterator(const Graph &G, int v) :
						G(G), v(v)
					{
						t = 0;
					}

					int beg()
					{
						t = G.adj[v];
						return t ? t->v : -1;
					}

					int nxt()
					{
						if (t) t = t->next;
						return t ? t->v : -1;
					}

					bool end()
					{
						return t == 0;
					}
				};
			};

			// Программа 17.11.Реализация класса, определяющего степени вершин
			template <class Graph> class Degree
			{
				const Graph &G;
				std::vector <int> degree;

			public:
				Degree(const Graph &G)
					: G(G), degree(G.V(), 0)
				{
					for (int v = 0; v < G.V(); v++)
					{
						typename Graph::adjIterator A(G, v);
						for (int w = A.begin(); !A.end(); w = A.next())
							degree[v]++;
					}
				}

				int operator [] (int v) const
				{
					return degree[v];
				}
			};

			// Программа 17.12.Генератор случайных графов (случайные ребра)
			void randE(Graph &G, int E);

			// Программа 17.13.Генератор случайных графов(случайный граф)
			void randG(Graph &G, int E);

			// Программа 17.15.Символьная индексация имен вершин
			class ST
			{
				int N, val;
				struct node
				{
					int v, d;
					node* l, *m, *r;
					node(int d)
						:v(-1), d(d), l(0), m(0), r(0)
					{
					}
				};

				typedef node* link;
				link head;

				link indexR(link h, const std::string &s, int w)
				{
					int i = s[w];
					if (h == 0)
						h = new node(i);
					if (i == 0)
					{
						if (h->v == -1)
							h->v = N++;
						val = h->v;
						return h;
					}
					if (i < h->d) h->l = indexR(h->l, s, w);
					if (i = h->d) h->m = indexR(h->m, s, w + 1);
					if (i > h->d) h->r = indexR(h->r, s, w);
					return h;
				}

			public:
				ST()
					:head(0), N(0)
				{
				}

				int index(const std::string &key)
				{
					head = indexR(head, key, 0);
					return val;
				}
			};

			// Программа 17.16.Поиск простого пути
			template <class Graph> class sPath
			{
				const Graph &G;
				std::vector <bool> visited;
				bool found;
				bool searchR(int v, int w)
				{
					if (v == w)
						return true;
					visited[v] = true;
					typename Graph::adjIterator A(G, v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (!visited[t])
					if (searchR(t, w))
						return true;
					return false;
				}

				// Программа 17.17.Гамильтонов путь
				bool searchR(int v, int w, int d)
				{
					if (v == w)
						return (d == 0);
					visited[v] = true;
					typename Graph::adjIterator A(G, v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (!visited[t])
					if (searchR(t, w, d - l))
						return true;
					visited[v] = false;
					return false;
				}

			public:
				sPath(const Graph &G, int v, int w)
					:G(G), visited(G.V(), false)
				{
					found = searchR(v, w);
				}

				bool exists() const
				{
					return found;
				}
			};

			// Программа 17.18.Существование эйлерова цикла
			template <class Graph> class ePath
			{
				Graph G;
				int v, w;
				bool found;
				nsCommon::Stack <int> S;

				// Программа 17.19.Поиск эйлерова пути с линейным временем выполнения
				int tour(int v)
				{
					while (true)
					{
						typename Graph::adjIterator A(G, v);
						int w = A.begin();
						if (A.end())
							break;
						S.push(v);
						G.remove(Edge(v, w));
						v = w;
					}
					return v;
				}

			public:
				ePath(const Graph &G, int v, int w)
					:G(G), v(v), w(w)
				{
					Degree<Graph> deg(G);
					int t = deg[v] + deg[w];
					if ((t % 2) != 0)
					{
						found = false;
						return;
					}
					for (t = 0; t < G.V(); t++)
					if ((t != v) && (t != w))
					if ((deg[t] % 2) != 0)
					{
						found = false;
						return;
					}
					found = true;
				}

				bool exists() const
				{
					return found;
				}

				void show()
				{
					if (!found)
						return;
					while (tour(v) == v && !S.empty())
					{
						v = S.pop();
						std::cout << "-" << v;
						std::cout << std::endl;
					}
				}
			};

			// Chapter 18
			// Программа 18.1.Поиск в глубину связной компоненты
			template <class Graph> class cDFS
			{
				int cnt;
				const Graph &G;
				std::vector <int> ord;

				void searchC(int v)
				{
					ord[v] = cnt++;
					auto A = G.getIterator(v);
					for (int t = A.begin(); !A.end(); t = A.next())
					if (ord[t] == -1)
						searchC(t);
				}

			public:
				cDFS(const Graph &G, int v = 0)
					:G(G), cnt(O), ord(G.V(), -1)
				{
					searchC(v);
				}

				int count() const
				{
					return cnt;
				}

				int operator[](int v) const
				{
					return ord[v];
				}
			};

			std::vector<Edge> getDFSGraphEdges(int& v);

			// Программа 18.2.Поиск на графе
			template <class Graph> class SEARCH
			{
			protected:
				const Graph &G;
				int cnt;
				std::vector <int> ord;
				virtual void searchC(Edge) = 0;

				void search()
				{
					for (int v = 0; v < G.V(); v++)
					if (ord[v] == -1)
						searchC(Edge(v, v));
				}

			public:
				SEARCH(const Graph &G)
					: G(G), ord(G.V(), -1), cnt(0)
				{
				}

				int operator[](int v) const { return ord[v]; }
			};
		}
	}
}
