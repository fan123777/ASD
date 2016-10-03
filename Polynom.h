#pragma once

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.24 Интерфейс АТД "Полином"
		// Программа 4.25 Реализация АТД "Полином" на базе массива
		template <class Number>
		class Polynom
		{
		public:
			Polynom(Number c, int N)
			{
				a = new Number[N + 1];
				n = N + 1;
				a[N] = c;
				for (int i = 0; i < N; i++)
					a[i] = 0;
			}

			~Polynom()
			{
				delete[] a;
			}

			float eval(float x) const
			{
				double t = 0.0;
				for (int i = n - 1; i >= 0; i--)
					t = t*x + a[i];
				return t;
			}

			friend Polynom operator+(Polynom& p, Polynom& q)
			{
				Polynom t(0, p.n > q.n ? p.n - 1 : q.n - 1);
				for (int i = 0; i < p.n; i++)
					t.a[i] += p.a[i];
				for (int j = 0; j < q.n; j++)
					t.a[j] += q.a[j];
					return t;
			}

			friend Polynom operator*(Polynom& p, Polynom& q)
			{
				Polynom t(0, (p.n - 1) + (q.n - 1));
				for (int i = 0; i < p.n; i++)
					for (int j = 0; j < q.n; j++)
						t.a[i + j] += p.a[i] * q.a[j];
				return t;
			}

		private:
			int n;
			Number *a;
		};
	}
}
