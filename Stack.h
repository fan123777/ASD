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

		// Программа 4.16 Стек индексных элементов, в котором запрещены повторяющиеся элементы
		namespace nsUniqueStack
		{
			template <class Item>
			class Stack
			{
			public:
				Stack(int maxN)
				{
					N = 0;
					s = new Item[maxN];
					t = new Item[maxN];
					for (int i = 0; i < maxN; i++)
						t[i] = 0;
				}

				~Stack()
				{
					delete[] s;
					delete[] t;
				}

				bool empty() const
				{
					return N == 0;
				}

				void push(Item item)
				{
					if (t[item] == 1)
						return;
					s[N++] = item;
					t[item] = 1;
				}

				Item pop()
				{
					t[s[--N]] = 0;
					return s[N];
				}

			private:
				Item *s, *t;
				int N;
			};
		}
	}
}
