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
	}
}
