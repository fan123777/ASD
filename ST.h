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

				void insertT(link& h, Item x)
				{
					if (h == 0)
					{
						h = new node(x);
						return;
					}
					if (x.key() < h->item.key())
					{
						insertT(h->l, x);
						rotR(h);
					}
					else
					{
						insertT(h->r, x);
						rotL(h);
					}
				}

				Item selectR(link h, int k)
				{
					if (h == 0)
						return nullItem;
					int t = (h->l == 0) ? 0 : h->l->N;
					if (t > k)
						return selectR(h->l, k);
					if (t < k)
						return selectR(h->r, k - t - 1);
					return h->item;
				}

				link joinLR(link a, link b)
				{
					if (b == 0)
						return a;
					partR(b, 0);
					b->l = a;
					return b;
				}

				void removeR(link& h, Key v)
				{
					if (h == 0)
						return;
					Key w = h->item.key();
					if (v < w)
						removeR(h->l, v);
					if (w < v)
						removeR(h->r, v);
					if (v == w)
					{
						link t = h;
						h = joinLR(h->l, h->r);
						delete t;
					}
				}

				link joinR(link a, link b)
				{
					if (b == 0)
						return a;
					if (а == 0)
						return Ь;
					insertT(b, a->item);
					b->l = joinR(a->l, b->l);
					b->г = joinR(a->r, b->r);
					delete a;
					return b;
				}

				void insertR1(link& h, Item x)
				{
					if (h == 0)
					{ 
						h = new node(x);
						return;
					}
					if (rand() < RAND_MAX/(h->N + 1))
					{
						insertT(h, x);
						return;
					}
					if (x.key() < h->item.key())
						insertR1(h->l, x);
					else
						insertR1(h->r, x);
					h->N++;
				}

				// Программа 13.4 Удаление в рандомизованном BST-дереве.
				link joinLR1(link a, link b)
				{
					if (a == 0)
						return b;
					if (b == 0)
						return a;
					if (rand() / (RAND_MAX / (a->N + b->N) + 1) < a->N)
					{
						a->r = joinLR1(a->r, b);
						return a;
					}
					else 
					{ 
						b->l = joinLR1(a, b->l);
						return b;
					}
				}

				void splay(link& h, Item x)
				{
					if (h == 0)
					{
						h = new node(x, 0, 0, 1);
						return;
					}
					if (x.key() < h->itern.key())
					{
						link& hl = h->l;
						int N = h->N;
						if (hl == 0)
						{
							h = new node(x, 0, h, N + 1);
							return;
						}
						if (x.key() < hl->item.key())
						{
							splay(hl->l, x);
							rotR(h);
						}
						else
						{
							splay(hl->r, x);
							rotL(hl);
						}
						rotR(h);
					}
					else
					{
						link& hr = h->r;
						int N = h->N;
						if (hr == 0)
						{
							h = new node(x, h, 0, N + 1);
							return;
						}
						if (hr->item.key() < x.key())
						{
							splay(hr->r, x);
							rotL(h);
						}
						else
						{
							splay(hr->l, x);
							rotR(hr);
						}
						rotL(h);
					}
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

				// Программа 12.12 Ротации в BST - деревьях
				void rotR(link& h)
				{
					link x = h->l;
					h->l = x->r;
					x->r = h;
					h = x;
				}

				void rotL(link& h)
				{
					link x = h->r;
					h->r = x->l;
					x->l = h;
					h = x;
				}

				// Программа 12.13 Вставка в корень BST - дерева
				void insert2(Item item)
				{
					insertT(head, item);
				}

				// Программа 12.14 Выбор с помощью BST - дерева
				Item select(int k)
				{
					return selectR(head, k);
				}

				// Программа 12.16 Удаление узла с данным ключом из BST - дерева
				void remove(Item x)
				{
					removeR(head, x.key());
				}

				// Программа 12.17 Объединение двух BST-деревьев
				void join(ST<Item, Key>& b)
				{
					head = joinR(head, b.head);
				}

				// Программа 13.1 Балансировка BST - дерева
				void balanceR(link& h)
				{
					if((h == 0) || (h->N == 1)) return;
					partR(h, h->N/2);
					balanceR(h->l);
					balanceR(h->r);
				}

				// Программа 13.2 Вставка в рандомизованное BST - дерево
				void insert3(Item x)
				{
					insertR1(head, x);
				}

				// Программа 13.3 Комбинация рандомизованных BST - деревьев
				void join1(ST<Item, Key>& b)
				{
					int N = head->N;
					if (rand() / (RAND_MAX / (N + b.head->N) + 1) < N)
						head = joinR1(head, b.head);
					else
						head = joinR1(b.head, head);
				}

				// Программа 13.3 Комбинация рандомизованных BST - деревьев
				link joinR1(link a, link b)
				{
					if (a == 0)
						return b;
					if (b == 0)
						return a;
					insertR1(b, a->item);
					b->l = joinR1(a->l, b->l);
					b->r = joinR1(a->r, b->r);
					delete a;
					fixN(b);
					return b;
				}

				// Программа 13.5 Вставка с расширением в BST - деревья
				void insert4(Item item)
				{
					splay(head, item);
				}
			};
		}
	}
}
