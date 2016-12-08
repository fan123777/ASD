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
				auto edges = getEdges(G);
				for (auto& element : edges)
					std::cout << element.v << " - " << element.w << "\n";
			}

			template <typename Graph>
			void showAdjacencyMatrix(Graph& G)
			{
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

			// -----

			template <typename Graph>
			class IO
			{
			public:
				static void scan(Graph& G);
			};

			template <typename Impl>
			class CC
			{
			private:
				// Код, зависящий от реализации 
			public:
				CC(const Graph<Impl>& G);
				int count();
				bool connect(int, int);
			};
		}

		namespace nsChapter
		{

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
		}
	}
}
