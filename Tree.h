#pragma once

#include "Stack.h"
#include "Queue.h"
#include <iostream>

namespace nsDataStructures
{
	namespace nsRecursionAndTrees
	{
		template<typename Item>
		class Tree
		{ 
		public:
			// Программа 5.14 Рекурсивный обход дерева

			Tree(Item x)
			{
				item = x;
				l = 0;
				r = 0;
			}

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

		// Программа 5.17 Вычисление параметров дерева
		template<typename Item>
		int count(Tree<Item>* h)
		{
			if (h == 0)
				return 0;
			return count(h->l) + count(h->r) + 1;
		}

		template<typename Item>
		int height(Tree<Item>* h)
		{
			if (h == 0)
				return -1;
			int u = height(h->l), v = height(h->r);
			if (u > v) 
				return u + 1;
			else
				return v + 1;
		}

		// Программа 5.18 Функция быстрого вывода дерева
		template<typename Item>
		void printnode(Item x, int h)
		{
			for (int i = 0; i < h; i++)
				std::cout << " ";
			std::cout << x << std::endl;
		}

		template<typename Item>
		void show(Tree<Item>* t, int h)
		{
			if (t == 0)
			{
				printnode('*', h);
				return;
			}
			show(t->r, h + 1);
			printnode(t->item, h);
			show(t->l, h + 1);
		}

		// Программа 5.19 Конструирование турнира
		template<typename Item>
		Tree<Item>* max1(Item a[], int l, int r)
		{
			int m = (l + r) / 2;
			Tree<Item>* x = new Tree<Item>(a[m]);
			if (l == r)
				return x;
			x->l = max1(a, l, m);
			x->r = max1(a, m + 1, r);
			Item u = x->l->item, v = x->r->item;
			if (u > v)
				x->item = u;
			else
				x->item = v;
			return x;
		}

		// Программа 5.20 Создание дерева синтаксического анализа
		template<typename Item>
		Tree<Item>* parse(char *a, int i)
		{
			char t = a[i++];
			Tree<Item>* x = new Tree<Item>(t);
			if ((t == ' + ') || (t == '*'))
			{
				x->l = parse(a, i);
				x->r = parse(a, i);
			}
			return x;
		}

		// Программа 5.21 Поиск в глубину
		struct MyGNode
		{
			int v;
			MyGNode* next;

			MyGNode(int x, MyGNode* t)
			{
				v = x;
				next = t;
			}
		};

		typedef MyGNode* MyGlink;

		void MyTraverseG(int k, void visit(int), int visited[], MyGlink adj[]);

		// Программа 5.22 Поиск в ширину
		void widthTraverseG(int k, void visit(int), int visited[], MyGlink adj[]);
	}
}
