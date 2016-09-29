#pragma once

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.13 Интерфейс АТД "Очередь FIFO"
		template <class Item>
		class Queue
		{
		private:
			// программный код, зависящий от реализации 
		public:
			Queue(int);
			int empty();
			void put(Item);
			Item get();
		};

		namespace nsListQueue
		{
			// Программа 4.14 Реализация очереди FIFO на базе связного списка
			template <class Item>
			class Queue
			{
			public:
				Queue()
				{
					head = 0;
				}

				~Queue();

				int empty() const
				{
					return head == 0;
				}

				void put(Item x)
				{
					link t = tail;
					tail = new node(x);
					if (head == 0)
						head = tail;
					else
						t->next = tail;
				}

				Item get()
				{
					Item v = head->item;
					link t = head->next;
					delete head;
					head = t;
					return v;
				}

			private:
				struct node
				{
					Item item;
					node* next;
					node(Item x)
					{
						item = x;
						next = 0;
					}
				};

				typedef node *link;

				link head;
				link tail;
			};
		}

		namespace nsArrayQueue
		{
			// Программа 4.15 Реализация очереди FIFO на базе массива
			template <class Item>
			class Queue
			{
			private:
				Item *q;
				int N, head, tail;

			public:
				Queue(int maxN)
				{
					q = new Item[maxN + 1];
					N = maxN + 1;
					head = N;
					tail = 0;
				}

				int empty() const
				{
					return head % N == tail;
				}

				void put(Item item)
				{
					q[tail++] = item;
					tail = tail % N;
				}

				Item get()
				{
					head = head % N;
					return q[head++];
				}
			};
		}
	}
}
