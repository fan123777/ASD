#pragma once

#include "Stack.h"
#include "Queue.h"

namespace nsDataStructures
{
	namespace nsRecursionAndTrees
	{
		template<typename Item>
		class Tree
		{ 
		public:
			// Программа 5.14 Рекурсивный обход дерева
			void traverse(void visit(Tree<Item>*))
			{
				visit(this);
				traverse(l, visit);
				traverse(r, visit);
			}

			Item getItem() const
			{
				return item;
			}

		// private:
			void traverse(Tree<Item>* h, void visit(Tree<Item>*))
			{
				if (h == 0)
					return;

				visit(h);
				traverse(h->l, visit);
				traverse(h->r, visit);
			}

			Item item;
			Tree *l, *r;
		};

		// Программа 5.15 Прямой обход(нерекурсивная реализация)
		template<typename Item>
		void traverse(Tree<Item>* h, void visit(Tree<Item>*))
		{
			nsAbstractDataTypes::nsListStack::Stack<Tree<Item>*> s;
			s.push(h);
			while (!s.empty())
			{
				visit(h = s.pop());
				if (h->r != 0)
					s.push(h->r);
				if (h->l != 0)
					s.push(h->l);
			}
		}

		// Программа 5.16 Обход по уровням
		template<typename Item>
		void traverse1(Tree<Item>* h, void visit(Tree<Item>*))
		{
			nsAbstractDataTypes::nsListQueue::Queue<Tree<Item>*> q;
			q.put(h);
			while (!q.empty())
			{
				visit(h = q.get());
				if (h->l != 0)
					q.put(h->l);
				if (h->r != 0)
					q.put(h->r);
			}
		}
	}
}
