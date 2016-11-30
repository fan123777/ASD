#pragma once

#include <vector>
#include <iostream>

namespace nsAlgorithmsOnGraphs
{
	namespace nsGraphPropertiesTypes
	{
		namespace nsGraph
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
	}
}
