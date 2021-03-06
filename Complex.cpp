﻿#include "Complex.h"

using namespace std;

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		Complex::Complex(float x, float y)
		{
			re = x;
			im = y;
		}

		float Complex::Re() const
		{
			return re;
		}

		float Complex::Im() const
		{
			return im;
		}

		Complex& Complex::operator*=(const Complex& rhs)
		{
			float t = Re();
			re = Re()*rhs.Re() - Im() *rhs.Im();
			im = t*rhs.Im() + Im() *rhs.Re();
			return *this;
		}

		ostream& operator<<(ostream& t, const Complex& c)
		{
			t << c.Re() << " " << c.Im(); return t;
		}
	}
}
