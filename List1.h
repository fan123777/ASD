#pragma once

namespace nsDataStructures
{
	namespace nsElementaryDataStructures
	{
		namespace nsList
		{
			// Программа 3.12 Интерфейс обработки списков
			typedef int Item;

			struct node
			{
				Item item;
				node *next;
			};

			typedef node *link;
			typedef link Node;

			void construct(int);
			Node newNode(int);
			void deleteNode(Node);
			void insert(Node, Node);
			Node remove(Node);
			Node next(Node);
			Item item(Node);

			// Программа 5.5 Примеры рекурсивных функций для связных списков
			int count(link x);
			void traverse(link h, void visit(link));
			void traverseR(link h, void visit(link));
			void remove(link x, Item v);

		}
	}
}
