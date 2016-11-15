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

				Item searchR1(link t, Key v, int k)
				{
					if (t == 0)
						return nullItem;
					if (v == t->item.key())
						return t->item;
					link x = t->next[k];
					if ((x == 0) || (v < x->item.key()))
					{
						if (k == 0)
							return nullItem;
						return searchR1(t, v, k - 1);
					}
					return searchR1(x, v, k);
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

				// Программа 13.7 Поиск в списках пропусков
				Item search1(Key v)
				{
					return searchR1(head, v, lgN);
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
				int red;

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
					if (rand() < RAND_MAX / (h->N + 1))
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

				int Red(link x)
				{
					if (x == 0)
						return 0;
					return x->red;
				}

				void RBinsert(link& h, Item x, int sw)
				{
					if (h == 0)
					{
						h = new node(x);
						return;
					}

					if (Red(h->l) && Red(h->r))
					{
						h->red = 1;
						h->l->red = 0;
						h->r->red = 0;
					}
					if (x.key() < h->item.key())
					{
						RBinsert(h->l, x, 0);
						if (Red(h) && Red(h->l) && sw)
							rotR(h);
						if (Red(h->l) && Red(h->l->l))
						{
							rotR(h);
							h->red = 0;
							h->r->red = 1;
						}
					}
					else
					{
						RBinsert(h->r, x, 1);
						if (Red(h) && Red(h->r) && !sw)
							rotL(h);
						if (Red(h->r) && Red(h->r->r))
						{
							rotL(h);
							h->red = 0;
							h->l->red = 1;
						}
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

				// Программа 13.6 Вставка в RB-деревья бинарного поиска 
				void insert5(Item x)
				{
					RBinsert(head, x, 0);
					head->red = 0;
				}
			};
		}

		namespace nsPassList
		{
			// Программа 13.8 Структуры данных и конструктор списка пропусков
			template <class Item, class Key>
			class ST
			{
			private:
				struct node
				{
					Item item;
					node **next;
					int sz;
					node(Item x, int k)
					{
						item = x;
						sz = k;
						next = new node*[k];
						for (int i = 0; i < k; i++)
							next[i] = 0;
					}
				};

				typedef node *link;
				link head;
				Item nullItem;
				int lgN;
				static const int lgNmax = 10;
				link* heads;
				int N, M;

				int randX()
				{
					int i, j, t = rand();
					for (i = 1, j = 2; i < lgNmax; i++, j += j)
					if (t > RAND_MAX / j)
						break;
					if (i > lgN)
						lgN = i;
					return i;
				}

				void insertR(link t, link x, int k)
				{
					Key v = x->item.key();
					link tk = t->next[k];
					if ((tk == 0) || (v < tk->item.key()))
					{
						if (k < x->sz)
						{
							x->next[k] = tk;
							t->next[k] = x;
						}
						if (k = 0)
							return;
						insertR(t, x, k - 1); return;
					}
					insertR(tk, x, k);
				}

				void removeR(link t, Key v, int k)
				{
					link x = t->next[k];
					if (!(x->item.key() < v))
					{
						if (v == x->item.key())
						{
							t->next[k] = x->next[k];
						}
						if (k == 0)
						{ 
							delete x;
							return;
						}
						removeR(t, v, k - 1); return;
					}
					removeR(t->next[k], v, k);
				}

				Item searchR1(link t, Key v)
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
					N = 0; M = maxN / 5;
					heads = new link[M];
					for (int i = 0; i < M; i++)
						heads[i] = 0;

					head = new node(nullItem, lgNmax);
					lgN = 0;
				}

				~ST()
				{
					delete[] heads;
				}

				// Программа 13.9 Вставка в список пропусков
				void insert(Item v)
				{
					insertR(head, new node(v, randX()), lgN);
				}

				// Программа 13.10 Удаление в списках пропусков
				void remove(Item x)
				{
					removeR(head, x.key(), lgN);
				}

				// Программа 14.3 Хеширование с помощью раздельного связывания
				Item search(Key v)
				{
					return searchR1(heads[hash(v, M)], v);
				}

				void insert1(Item item)
				{
					int i = hash(item, key(), M);
					heads[i] = new node(item, heads[i]);
					N++;
				}
			};
		}

		namespace nsLinearProbing
		{
			// Программа 14.4 Линейное зондирование
			template <class Item, class Key>
			class ST
			{
			private:
				struct node
				{
					Item item;
					node **next;
					int sz;
					node(Item x, int k)
					{
						item = x;
						sz = k;
						next = new node*[k];
						for (int i = 0; i < k; i++)
							next[i] = 0;
					}
				};

				Item *st;
				int N, M;
				Item nullItem;

				void expand()
				{
					Item *t = st;
					init(M + M);
					for (int i = 0; i < M / 2; i++)
					if (!t[i].null()) insert2(t[i]);
					delete[] t;
				}

			public:
				ST(int maxN)
				{
					N = 0; M = 2 * maxN;
					st = new Item[M];
					for (int i = 0; i < M; i++)
						st[i] = nullItem;
				}

				~ST()
				{
					delete[] st;
				}

				int count() const
				{
					return N;
				}

				void insert(Item item)
				{
					int i = hash(item.key(), M);
					while (!st[i].null())
						i = (i + 1) % M;
					st[i] = item;
					N++;
				}

				Item search(Key v)
				{
					int i = hash(v, M);
					while (!st[i].null())
					if (v == st[i].key())
						return st[i];
					else
						i = (i + 1) % M;
					return nullItem;
				}

				// Программа 14.5 Удаление из хеш - таблицы, использующей линейное зондирование
				void remove(Item x)
				{
					int i = hash(x.key(), M), j;
					while (!st[i].null())
						if (x.key() == st[i].key())
							break;
						else
							i = (i + 1) % M;
					if (st[i].null())
						return;
					st[i] = nullItem;
					N--;
					for (j = i + 1; !st[j].null(); j = (j + 1) % M, N--)
					{
						Item v = st[j];
						st[j] = nullltem;
						insert(v);
					}
				}

				// Программа 14.6 Двойное хеширование 
				void insert1(Item item)
				{
					Key v = item.key();
					int i = hash(v, M), k = hashtwo(v, M);
					while (!st[i].null())
						i = (i + k) % M;
					st[i] = item;
					N++;
				}

				Item search1(Key v)
				{
					int i = hash(v, M), k = hashtwo(v, M);
					while (!st[i].null())
					if (v = st[i].key())
						return st[i];
					else
						i = (i + k) % M;
					return nullItem;
				}

				// Программа 14.7 Динамическая вставка в хеш-таблицу (для линейного зондирования)
				// ST(int maxN)
				// {
				// 	init(4);
				// }

				void insert2(Item item)
				{
					int i = hash(item.key(), M);
					while (!st[i].null())
						i = (i + 1) % M;
					st[i] = item;
					if (N++ >= M / 2)
						expand();
				}
			};
		}

		namespace nsDST
		{
			// Программа 15.1 Бинарное DST - дерево
			template <class Item, class Key>
			class ST
			{
			private:
				struct node
				{
					Item item;
					node * l, *r;

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

				Item searchR(link h, Key v, int d)
				{
					if (h == 0)
						return nullItem;
					if (h->l == 0 && h->r == 0)
					{
						Key w = h->item.key();
						return (v == w) ? h->item : nullItem;
					}
					if (digit(v, d) == 0)
						return searchR(h->l, v, d + 1);
					else
						return searchR(h->r, v, d + 1);
				}

				void insertR(link& h, Item x)
				{
					if (h == 0)
					{ 
						h = new node(x);
						return;
					}

					if (x.key() < h->item.key())
						insertR(h->l, x);
					else
						insertR(h->r, x);
				}

				link split(link p, link q, int d)
				{
					link t = new node(nullItem);
					t->N = 2;
					Key v = p->item.key();
					Key w = q->item.key();
					switch (digit(v, d) * 2 + digit(w, d))
					{
					case 0: t->l = split(p, q, d + 1); break;
					case 1: t->l = p; t->r = q; break;
					case 2: t->r = p; t->l = q; break;
					case 3: t->r = split(p, q, d + 1); break;
					}
					return t;
				}

				void insertR1(link& h, Item x, int d)
				{
					if (h == 0)
					{ 
						h = new node(x);
						return;
					}
					if (h->l == 0 && h->r == 0)
					{
						h = split(new node(x), h, d);
						return;
					}
					if (digit(x.key(), d) == 0)
						insertR1(h->l, x, d + 1);
					else
						insertR1(h->r, x, d + 1);
				}

			public:
				ST(int maxN)
				{
					head = 0;
				}

				// Программа 15.2 Поиск в trie-дереве
				Item search(Key v)
				{
					return searchR(head, v, 0);
				}

				void insert(Item x)
				{
					insertR(head, x);
				}

				// Программа 15.3 Вставка в trie-дерево
				void insert1(Item item)
				{
					insertR1(head, item, 0);
				}
			};
		}

		namespace nsPatricia
		{
			template <class Item, class Key>
			class ST
			{
			private:
				struct node
				{
					Item item;
					node * l, *r;
					int bit;

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

				Item searchR(link h, Key v, int d)
				{
					if (h->bit <= d)
						return h->item;
					if (digit(v, h->bit) == 0)
						return searchR(h->l, v, h->bit);
					else
						return searchR(h->r, v, h->bit);
				}

				link insertR(link h, Item x, int d, link p)
				{
					Key v = x.key();
					if ((h->bit >= d) || (h->bit <= p->bit))
					{
						link t = new node(x); t->bit = d;
						t->l = (digit(v, t->bit) ? h : t);
						t->r = (digit(v, t->bit) ? t : h);
						return t;
					}
					if (digit(v, h->bit) == 0)
						h->l = insertR(h->l, x, d, h);
					else
						h->r = insertR(h->r, x, d, h);
					return h;
				}

				void showR(link h, std::ostream& os, int d)
				{
					if (h->bit <= d)
					{
						h->item.show(os);
						return;
					}
					showR(h->l, os, h->bit);
					showR(h->r, os, h->bit);
				}

			public:
				// Программа 15.4 Поиск в patricia - дереве
				Item search(Key v)
				{
					Item t = searchR(head, v, -1);
					return (v == t.key()) ? t : nullItem;
				}

				// Программа 15.5 Вставка в patricia - дерево
				ST(int maxN)
				{
					head = new node(nullItem);
					head->l = head->r = head;
				}

				void insert(Item x)
				{
					Key v = x.key();
					int i;
					Key w = searchR(head->l, v, -1).key();
					if (v == w)
						return;
					for (i = 0; digit(v, i) == digit(w, i); i++);
						head->l = insertR(head->l, x, i, head);
				}

				// Программа 15.6 Сортировка в patricia - дереве
				void show(std::ostream& os)
				{
					showR(head->l, os, -1);
				}

			};
		}

		namespace nsTrie
		{
			template <class Item, class Key>
			class ST
			{
			private:
				struct node
				{
					node **next;
					node()
					{
						next = new node*[R];
						for (int i = 0; i < R; i++)
							next[i] = 0;
					}
				};

				typedef node *link;
				link head;

				Item searchR(link h, Key v, int d)
				{
					int i = digit(v, d);
					if (h == 0)
						return nullItem;
					if (i — NULLdigit)
					{
						Item dummy(v);
						return dummy;
					}
					return searchR(h->next[i], v, d + 1);
				}

				void insertR(link& h, Item x, int d)
				{
					int i = digit(x.key(), d);
					if (h == 0)
						h = new node;
					if (i == NULLdigit)
						return;
					insertR(h->next[i], x, d + 1);
				}

			public:
				ST(int maxN)
				{
					head = 0;
				}

				Item search(Key v)
				{
					return searchR(head, v, 0);
				}

				void insert(Item x)
				{
					insertR(head, x, 0);
				}
			};
		}

		namespace nsTST
		{
			// Программа 15.8 Поиск и вставка в TST - дерево существования
			template <class Item, class Key>
			class ST
			{

			};
		}
	}
}
