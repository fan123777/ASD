#pragma once

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.4 Интерфейс абстрактного типа данных стека
		template <class Item>
		class Stack
		{
		public:
			Stack(int number);
			int empty() const;
			void push(Item item);
			Item pop();

		private:
			// программный код, зависящий от реализации 
		};

		// Программа 4.7 Реализация стека магазинного типа на базе массива
		namespace nsArrayStack
		{
			template <class Item>
			class Stack
			{
			private:
				Item *s;
				int N;

			public:
				Stack(int maxN)
				{
					s = new Item[maxN];
					N = 0;
				}

				~Stack()
				{
					delete[] s;
				}

				int empty() const
				{
					return N == 0;
				}

				void push(Item item)
				{
					s[N++] = item;
				}

				Item pop()
				{
					return s[--N];
				}
			};
		}

		// Программа 4.8 Реализация стека магазинного типа на базе связного списка
		namespace nsListStack
		{
			template <class Item>
			class Stack
			{
			private:
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

				link head;

			public:

				Stack()
				{
					head = 0;
				}

				int empty() const
				{
					return head == 0;
				}

				void push(Item x)
				{
					head = new node(x, head);
				}

				Item pop()
				{
					Item v = head->item;
					link t = head->next;
					delete head;
					head = t;
					return v;
				}
			};
		}
	}
}
