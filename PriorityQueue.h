#pragma once

#include "Common.h"

namespace nsSorting
{
	namespace nsPriorityQueue
	{
		// Программа 9.1.Базовый тип абстрактных данных очереди по приоритетам
		template <class Item>
		class PQ
		{
		public:
			PQ(int);
			int empty() const;
			void insert(Item);
			Item getmax();
		private:
			// Программный код, который зависит от реализации 
		};

		namespace nsArrayPQ
		{
			// Программа 9.2.Реализация очереди по приоритетам с использованием массивов
			template <class Item>
			class PQ
			{
			public:
				PQ(int maxN)
				{
					pq = new Item[maxN];
					N = 0;
				}

				~PQ()
				{
					delete[] pq;
				}

				int empty() const
				{
					return N = 0;
				}

				void insert(Item item)
				{
					pq[N++] = item;
				}

				Item getmax()
				{
					int max = 0;
					for (int j = 1; j < N; j++)
						if (pq[max] < pq[j])
							max = j;
					nsCommon::exch(pq[max], pq[N - 1]);
					return pq[--N];
				}

			private:
				Item *pq;
				int N;
			};
		}

		namespace nsSortingTreePQ
		{
			// Программа 9.3.Восходящая установка структуры сортирующего дерева
			template <class Item>
			void fixUp(Item a[], int k)
			{
				while (k > 1 && a[k / 2] < a[k])
				{
					nsCommon::exch(a[k], a[k / 2]);
					k = k / 2;
				}
			}

			// Программа 9.4.Нисходящая установка структуры сортирующего дерева
			template <class Item>
			void fixDown(Item a[], int k, int N)
			{
				while (2 * k <= N)
				{
					int j = 2 * k;
					if (j < N && a[j] < a[j + 1])
						j++;
					if (!(a[k] < a[j]))
						break;
					nsCommon::exch(a[k], a[j]);
					k = j;
				}
			}

			// Программа 9.5.Очередь по приоритетам на базе сортирующего дерева
			template <class Item>
			class PQ
			{
			public:
				PQ(int maxN)
				{
					pq = new Item[maxN + 1];
					N = 0;
				}

				~PQ()
				{
					delete[] pq;
				}

				int empty() const
				{
					return N == 0;
				}

				void insert(Item item)
				{
					pq[++N] = item;
					fixUp(pq, N);
				}

				Item getmax()
				{
					nsCommon::exch(pq[1], pq[N]);
					fixDown(pq, 1, N - l);
					return pq[N--];
				}

			private:
				Item *pq;
				int N;
			};
		}

		namespace nsFullPQ
		{
			// Программа 9.8.Полный АТД очереди по приоритетам
			template <class Item>
			class PQ
			{
			public:
				//Определение дескриптора в зависимости от реализации 
				PQ(int);
				int empty() const;
				handle insert(Item);
				Item getmax();
				void change(handle, Item);
				void remove(handle);
				void join(PQ<Item>&);
			private:
				//Программный код, зависящий от реализации 
			};
		}
	}
}
