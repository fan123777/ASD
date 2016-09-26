#include "ElementaryDataStructures.h"
#include <iostream>
#include "List1.h"

using namespace std;

namespace nsDataStructures
{
	namespace nsElementaryDataStructures
	{
		void main()
		{
			// program1();
			// program2();
			// program5();
			// program7();
			// program8();
			// testList();
			// program9();
			// program11();
			// program13();
			program15();
		}

		void program1()
		{
			for (int N = 1000; N <= 1000000000; N *= 10)
				cout << lg(N) << " " << N << endl;
		}

		int lg(int N)
		{
			int i;
			for (i = 0; N > 0; i++, N /= 2);
			return i;
		}

		void program2()
		{
			int N = 100;
			float ml = 0.0, m2 = 0.0;
			for (int i = 0; i < N; i++)
			{
				Number x = randNum();
				ml += ((float)x) / N;
				m2 += ((float)x*x) / N;
			}
			cout << " Avg. : " << ml << endl;
			cout << "Std. dev.: " << sqrt(m2 - ml*ml) << endl;
		}

		Number randNum()
		{
			return rand();
		}

		float distance(point a, point b)
		{
			float dx = a.x - b.x, dy = a.у - b.у;
			return sqrt(dx*dx + dy*dy);
		}

		void polar(float x, float y, float *r, float *theta)
		{
			*r = sqrt(x*x + y*y);
			*theta = atan2(y, x);
		}

		void program5()
		{
			const int N = 1000;
			int i, a[N];

			for (i = 2; i < N; i++)
				a[i] = 1;

			for (i = 2; i < N; i++)
				if (a[i])
					for (int j = i; j*i < N; j++)
						a[i*j] = 0;

			for (i = 2; i < N; i++)
			if (a[i])
				cout << " " << i;
			cout << endl;
		}

		void program7()
		{
			int i, j, cnt;
			int N = 32, M = 1000;
			int *f = new int[N + 1];

			for (j = 0; j <= N; j++)
				f[j] = 0;

			for (i = 0; i < M; i++, f[cnt]++)
				for (cnt = 0, j = 0; j <= N; j++)
					if (heads())
						cnt++;

			for (j = 0; j <= N; j++)
			{
				if (f[j] == 0)
					cout << ".";
				for (i = 0; i < f[j]; i += 10)
					cout << "*";
				cout << endl;
			}
			delete[] f;
		}

		int heads()
		{
			return rand() < RAND_MAX / 2;
		}

		void program8()
		{
			float d = 0.1;
			int i, cnt = 0, N = 100;

			point *a = new point[N];

			for (i = 0; i < N; i++)
			{
				a[i].x = randFloat();
				a[i].у = randFloat();
			}

			for (i = 0; i < N; i++)
				for (int j = i + 1; j < N; j++)
					if (distance(a[i], a[j]) < d)
						cnt++;
			cout << cnt << " pairs within " << d << endl;

			delete[] a;
		}

		float randFloat()
		{
			return 1.0* rand() / RAND_MAX;
		}

		void testList()
		{
			link<int> x = new node<int>(5, nullptr);
			link<int> t = new node<int>(10, x);
		}

		void program9()
		{
			int i, N = 9, M = 5;
			link<int> t = new node<int>(1, 0);
			t->next = t;
			link<int> x = t;
			for (i = 2; i <= N; i++)
				x = (x->next = new node<int>(i, t));
			while (x != x->next)
			{
				for (i = 1; i < M; i++)
					x = x->next;
				t = x->next;
				cout << t->item << endl;
				x->next = x->next->next;
				delete t;
			}
		}

		link<int> program10(link<int> x)
		{
			link<int> t, y = x, r = 0;
			while (y != 0)
			{
				t = y->next; y->next = r; r = y;
				y = t;
			}
			return r;
		}

		void program11()
		{
			int N = 1000;
			node<int> heada(0, nullptr);
			link<int> a = &heada, t = a;

			for (int i = 0; i < N; i++)
				t = (t->next = new node<int>(rand() % 1000, 0));

			node<int> headb(0, nullptr);
			link<int> u, x, b = &headb;

			for (t = a->next; t != 0; t = u)
			{
				u = t->next;
				for (x = b; x->next != 0; x = x->next)
					if (x->next->item > t->item)
						break;
				t->next = x->next; x->next = t;
			}
		}

		void program13()
		{
			int i, N = 9, M = 5;
			nsList::Node t, x;
			nsList::construct(N);

			for (i = 2, x = nsList::newNode(1); i <= N; i++)
			{
				t = nsList::newNode(i);
				insert(x, t);
				x = t;
			}

			while (x != next(x))
			{
				for (i = 1; i < M; i++)
					x = next(x);
				nsList::deleteNode(nsList::remove(x));
			}

			cout << item(x) << endl;
		}

		void program15()
		{
			const int N = 10;
			int i; char t;
			char a[N], *p = "test";

			for (i = 0; i < N - 1; a[i] = t, i++)
				if (!cin.get(t))
					break;

			a[i] = 0;

			for (i = 0; a[i] != 0; i++)
			{
				int j;
				for (j = 0; p[j] != 0; j++)
					if (a[i + j] != p[j])
						break;
					if (p[j] == 0)
						cout << i << " ";
			}

			cout << endl;
		}
	}
}
