#pragma once

#include <iostream>

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.18 Интерфейс АТД первого класса для комплексных чисел
		// Программа 4.18 АТД первого класса для комплексных чисел
		class Complex
		{
		public:
			Complex(float x, float y);
			float Re() const;
			float Im() const;
			Complex& operator*=(const Complex&);

		private:
			float re, im;
		};

		std::ostream& operator<<(std::ostream& t, const Complex& c);

	}
}
