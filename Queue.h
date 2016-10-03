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

				Queue(const Queue& rhs)
				{
					head = 0;
					*this = rhs;
				}

				Queue& operator=(const Queue& rhs)
				{
					if (this == &rhs)
						return *this;
					deletelist();
					link t = rhs.head;
					while (t != 0)
					{
						put(t->item);
						t = t->next;
					}
					return *this;
				}

				~Queue()
				{
					deletelist();
				}

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
				void deletelist()
				{
					for (link t = head; t != 0; head = t)
					{
						t = head->next;
						delete head;
					}
				}

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

		namespace nsFirstClassQueue
		{
			// Программа 4.21 Интерфейс АТД первого класса "Очередь"
			// Программа 4.22 Реализация очереди первого класса на базе связного списка

			template <class Item>
			class Queue
			{
			private:
				// Implementation-dependent code 
			public:
				Queue(int);
				Queue(const Queue&);
				Queue& operator=(const Queue&);
				~Queue();
				int empty() const;
				void put(Item);
				Item get();
			};
		}
	}
}
