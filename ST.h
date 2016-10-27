#pragma once

#include <iostream>

namespace nsSearch
{
	namespace nsCharacterTablesAndBinarySearchTrees
	{
		namespace nsST
		{
			// Программа 12.2 АТД таблицы символов
			template <class Item, class Key>
			class ST
			{
			private:
				// Код, зависящий от реализации 
			public:
				ST(int);
				int count();
				Item search(Key);
				void insert(Item);
				void remove(Item);
				Item select(int);
				void show(std::ostream&);
			};
		}

		namespace nsArrayST
		{
			// Программа 12.4 Таблица символов, основывающаяся на индексированном по ключам массиве
			template <class Item, class Key>
			class ST
			{
			public:
				ST(int maxN)
				{
					M = nullItem.key();
					st = new Item[M];
				}

				~ST()
				{
					delete[] st;
				}

				int count()
				{
					int N = 0;
					for (int i = 0; i < M; i++)
					if (!st[i].null())
						N++;
					return N;
				}

				void insert(Item x)
				{
					st[x.key()] = x;
				}

				Item search(Key v)
				{
					return st[v];
				}

				void remove(Item x)
				{
					st[x.key()] = nullItem;
				}

				Item select(int k)
				{
					for (int i = 0; i < M; i++)
						if (!st[i].null())
							if (k-- == 0)
								return st[i];
					return nullItem;
				}

				void show(std::ostream& os)
				{
					for (int i = 0; i < M; i++)
						if (!st[i].null())
							st[i].show(os);
				}

			private:
				Item nullItem, *st;
				int M;
			};
		}

		namespace nsSortedArrayST
		{
			// Программа 12.5 Таблица символов(упорядоченная) с использованием массива
			template <class Item, class Key>
			class ST
			{
			public:
				ST(int maxN)
				{
					st = new Item[maxN + 1];
					N = 0;
				}

				~ST()
				{
					delete[] st;
				}

				int count()
				{
					return N;
				}

				void insert(Item x)
				{
					int i = N++;
					Key v = x.key();
					while (i > 0 && v < st[i - 1].key())
					{
						st[i] = st[i - 1];
						i--;
					}
					st[i] = x;
				}

				// Программа 12.7 Бинарный поиск(в таблице символов, основанной на массиве)
				Item binarySearch(Key v)
				{
					return searchR(0, N - 1, v);
				}

				Item search(Key v)
				{
					int i = 0;
					for (i = 0; i < N; i++)
					if (!(st[i].key() < v))
						break;
					if (v == st[i].key())
						return st[i];
					return nullItem;
				}

				Item select(int k)
				{
					return st[k];
				}

				void show(std::ostream& os)
				{
					int i = 0;
					while (i < N)
						st[i++].show(os);
				}

			private:

				Item searchR(int l, int r, Key v)
				{
					if (l > r)
						return nullItem;
					int m = (l + r) / 2;
					if (v == st[m].key())
						return st[m];
					if (l == r)
						return nullItem;
					if (v < st[m].key())
						return searchR(l, m - 1, v);
					else
						return searchR(m + l, r, v);
				}

				Item nullItem, *st;
				int N;
			};
		}

		namespace nsListST
		{
			// Программа 12.6 Таблица символов(неупорядоченная) с использованием связного списка
			template <class Item, class Key>
			class ST
			{
			private:
				Item nullItem;
				struct node
				{
					Item item;
					node* next;
					node(Item x, node* t)
					{
						item = x;
						next = t;
					}
				};

				typedef node *link;
				int N;
				link head;
				Item searchR(link t, Key v)
				{
					if (t == 0)
						return nullItem;
					if (t->item.key() == v)
						return t->item;
					return searchR(t->next, v);
				}

			public:
				ST(int maxN)
				{
					head = 0;
					N = 0;
				}

				int count()
				{
					return N;
				}

				Item search(Key v)
				{
					return searchR(head, v);
				}

				void insert(Item x)
				{
					head = new node(x, head);
					N++;
				}
			};
		}

		namespace nsBSTST
		{
			// Программа 12.8 Таблица символов на базе дерева бинарного поиска
			template <class Item, class Key>
			class ST
			{
			private:
				struct node
				{
					Item item; node *l, *r;
					node(Item x)
					{
						item = x;
						l = 0;
						r = 0;
					}
				};

				typedef node *link;
				link head;
				Item nullItem;
				int N;

				Item searchR(link h, Key v)
				{
					if (h == 0)
						return nullItem;
					Key t = h->item.key();
					if (v == t)
						return h->item;
					if (v < t)
						return searchR(h->l, v);
					else
						return searchR(h->r, v);
				}

				void insertR(link& h, Item x)
				{
					if (h == 0)
					{
						h = new node(x);
						N++;
						return;
					}
					if (x.key() < h->item.key())
						insertR(h->l, x);
					else
						insertR(h->r, x);
				}

				void showR(link h, std::ostream& os)
				{
					if (h == 0)
						return;
					showR(h->l, os);
					h->item.show(os);
					showR(h->r, os);
				}

			public:
				ST(int maxN)
				{
					head = 0;
					N = 0;
				}

				int count()
				{
					return N;
				}

				Item search(Key v)
				{
					return searchR(head, v);
				}

				void insert(Item x)
				{
					insertR(head, x);
				}

				// Программа 12.10 Вставка в BST - дерево(нерекурсивная)
				void insert1(Item x)
				{
					Key v = х.key();
					if (head == 0)
					{
						head = new node(x);
						return;
					}
					link p = head;
					for (link q = p; q != 0; p = q ? q : p)
						q = (v < q->item.key()) ? q->l : q->r;
					if (v < p->item.key())
						р->l = new node(x);
					else
						p->r = new node(x);
				}

				// Программа 12.9 Сортировка с помощью BST-дерева
				void show(std::ostream& os)
				{
					showR(head, os);
				}
			};
		}
	}
}
