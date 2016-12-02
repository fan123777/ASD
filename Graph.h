#pragma once

#include <vector>
#include <iostream>

namespace nsAlgorithmsOnGraphs
{
	namespace nsGraphPropertiesTypes
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
				Graph(int, bool b = false);
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
					adjIterator(const Graph &, int);
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
				static void show(const Graph &);
				static void scanEZ(Graph &);
				static void scan(Graph &);
			};

			// Программа 17.3.Клиентская функция печати графа
			template <class Graph>
			void IO<Graph>::show(const Graph &G)
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

		namespace nsSparseMultiGraph
		{
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
		}
	}
}
