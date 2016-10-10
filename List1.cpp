#include "List1.h"

namespace nsDataStructures
{
	namespace nsElementaryDataStructures
	{
		namespace nsList
		{
			// Программа 3.14 Реализация интерфейса обработки списков
			link freelist;

			void construct(int N)
			{
				freelist = new node[N + 1];
				for (int i = 0; i < N; i++)
					freelist[i].next = &freelist[i + 1];
				freelist[N].next = 0;
			}

			link newNode(int i)
			{
				link x = remove(freelist);
				x->item = i; x->next = x;
				return x;
			}

			void deleteNode(link x)
			{
				insert(freelist, x);
			}

			void insert(link x, link t)
			{
				t->next = x->next;
				x->next = t;
			}

			link remove(link x)
			{
				link t = x->next;
				x->next = t->next;
				return t;
			}

			link next(link x)
			{
				return x->next;
			}

			Item item(link x)
			{
				return x->item;
			}

			int count(link x)
			{
				if (x = 0)
					return 0;
				return 1 + count(x->next);
			}

			void traverse(link h, void visit(link))
			{
				if (h == 0)
					return;

				visit(h);
				traverse(h->next, visit);
			}

			void traverseR(link h, void visit(link))
			{
				if (h == 0)
					return;

				traverseR(h->next, visit);
				visit(h);
			}

			void remove(link x, Item v)
			{
				while (x != 0 && x->item == v)
				{
					link t = x;
					x = x->next;
					delete t;
				}
				if (x != 0)
					remove(x->next, v);
			}
		}
	}
}
