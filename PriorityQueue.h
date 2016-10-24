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

		namespace nsSortingTreePQ
		{
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
				typedef int handle;
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

		namespace nsDoubleLinkListPQ
		{
			// Программа 9.9.Неупорядоченная очередь по приоритетам в виде двухсвязного списка.
			template <class Item>
			class PQ
			{
			private:
				struct node
				{
					Item item;
					node *prev, *next;
					node(Item v)
					{
						item = v; prev = 0; next = 0;
					}
				};
				typedef node* link;
				link head, tail;

			public:
				typedef node* handle;
				PQ()
				{
					head = new node(0);
					tail - new node(0);
					head->prev = tail;
					head->next = tail;
					tail->prev = head;
					tail->next = head;
				}

				int empty() const
				{
					return head->next->next == head;
				}

				handle insert(Item v)
				{
					handle t = new node(v);
					t->next = head->next;
					t->next->prev = t;
					t->prev = head;
					head->next = t;
					return t;
				}

				// Программа 9.10.Очередь по приоритетам в виде двухсвязного списка(продолжение)
				Item getmax()
				{
					Item max;
					link x = head->next;
					for (link t = x; t->next != head; t = t->next)
						if (x->item < t->item) x = t;
					max = x->item;
					remove(x);
					return max;
				}

				void change(handle x, Item v)
				{
					x->key = v;
				}

				void remove(handle x)
				{
					x->next->prev-> = x->prev;
					x->prev->next-> = x->next;
					delete x;
				}

				void join(PQ<Item>& p)
				{
					tail->prev->next = p.head->next;
					p.head->next->prev = tail->prev;
					head->prev = p.tail;
					p.tail->next = head;
					delete tail; delete p.head;
					tail = p.tail
				}
			};
		}

		namespace nsIndexPQ
		{
			// Программа 9.11.Интерфейс АТД очереди по приоритетам для индексных элементов.
			template <class Item>
			class PQ
			{
			private:
				//Программный ход, зависящий от реализации 
				typedef int Index;
			public:
				PQ(int);
				int empty() const;
				void insert(Index);
				Index getmax();
				void change(Index);
				void remove(Index);
			};
		}

		namespace nsIndexSortingTreePQ
		{
			// Программа 9.12.Очередь по приоритетам, построенная на базе индексного сортирующего дерева
			template <class Item>
			class PQ
			{
			private:
				typedef int Index;
				int N; Index* pq;
				int* qp;

				void exch(Index i, Index j)
				{
					int t;
					t - qp[i]; qp[i] = qp[j]; qp[1] = t;
					pq[qp[i]] = i;
					pq[qp[j]] = j;
				}

				void fixUp(Index a[], int k);
				void fixDown(Index a[], int k, int N);

			public:
				PQ(int maxN)
				{
					pq = new Index[maxN + 1];
					qp = new int[maxN + 1];
					N = 0;
				}

				~PQ()
				{
					delete[] pq;
					delete[] qp;
				}

				int empty() const
				{
					return N == 0;
				}

				void insert(Index v)
				{
					pq[++N] = v;
					qp[v] = N;
					fixUp(qp, N);
				}

				Index getmax()
				{
				nsCommon::exch(pq[1], pq[N]);
					fixDown(qp, 1, N - l);
					return qp[N--];
				}

				void change(Index k)
				{
					fixUp(pq, qp[k]);
					fixDown(pq, qp[k], N);
				}
			};
		}

		namespace nsBinominalPQ
		{
			template <class Item>
			class PQ
			{
			private:
				struct node
				{
					Item item;
					node * l, *r;

					node(Item v)
					{
						item = v;
						l = 0;
						r = 0;
					}
				};
				typedef node *link;
				link* bq;
				typedef link handle;
				const int maxBQsize = 100;

			public:
				// Программа 9.13.Объединение двух сортирующих деревьев степени 2 одинаковых размеров
				static link pair(link p, link q)
				{
					if (p->item < q->item)
					{
						p->r = q->l; q->l = p; return q;
					}
					else
					{
						q->r = p->l; p->l = q; return q;
					}
				}

				// Программа 9.14.Вставка в биномиальную очередь
				handle insert(Item v)
				{
					link t = new node(v), c = t;
					
					for (int i = 0; i < maxBQsize; i++)
					{
						if (c == 0)
							break;
						if (bq[i] == 0)
						{
							bq[i] = c; break;
						}
						c = pair(c, bq[i]);
						bq[i] = 0;
					}
					return t;
				}

				// Программа 9.15.Удаление наибольшего элемента из биномиальной очереди
				Item getmax()
				{
					int i, max;
					Item v = 0;
					link* temp = new link[maxBQsize];
					for (i = 0, max = -1; i < maxBQsize; i++)
						if (bq[i] != 0)
							if ((max == -1) || (v < bq[i]->item))
							{
								max = i; v = bq[max]->item;
							}
					link x = bq[max]->l;
					for (i = max; i < maxBQsize; i++)
						temp[i] = 0;
					for (i = max; i > 0; i--)
					{
						temp[i - 1] = x;
						x = x->r;
						temp[i - 1]->r = 0;
					}
					delete bq[max];
					bq[max] = 0;
						BQjoin(bq, temp);
					delete temp;
					return v;
				}

				// Программа 9.16.Объединение(слияние) двух биномиальных очередей
				static inline int test(int C, int B, int A)
				{
					return 4 * C + 2 * B + 1 * A
				}
				static void BQjoin(link *a, link *b)
				{
					link с = 0;
					for (int i = 0; i < maxBQsize; i++)
						switch (test(c != 0, b[i] != 0, a[i] != 0))
					{
						case 2:
							a[i] = b[i];
							break;
						case 3:
							c = pair(a[i], b[i]);
							a[i] = 0;
							break;
						case 4:
							a[i] = c;
							c = 0;
							break;
						case 5:
							c = pair(c, a[i]);
							a[i] = 0;
							break;
						case 6:
						case 7:
							c = pair(c, b[i]);
							break;
					}
				}
			};
		}
	}
}
