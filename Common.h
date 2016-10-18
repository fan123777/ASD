#pragma once

namespace nsCommon
{
	template <class Item>
	void exch(Item& a, Item& b)
	{
		Item t = a; a = b; b = t;
	}

	template <class Item>
	void compexch(Item& a, Item& b)
	{
		if (b < a)
			exch(a, b);
	}

	template <class Item>
	void insertion(Item a[], int l, int r)
	{
		int i;
		for (i = r; i > l; i--)
			compexch(a[i - 1], a[i]);
		for (i = l + 2; i <= r; i++)
		{
			int j = i;
			Item v = a[i];
			while (v < a[j - 1])
			{
				a[j] = a[j - 1];
				j--;
			}
			a[j] = v;
		}
	}

	template<typename Item>
	struct node
	{
		node(Item x, node*t = nullptr)
		{
			item = x;
			next = t;
		}

		Item item;
		node *next;
	};

	template<typename T>
	using link = node<T>*;

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
