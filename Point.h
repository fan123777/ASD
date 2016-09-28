#pragma once
#include <iostream>

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.1 Реализация класса Point
		class Point
		{
		public:
			Point();
			float distance(Point a) const;
			static float distance(Point a, Point b);
			float X() const;
			float Y() const;
			int operator == (Point a);

		private:
			float x, y;
		};

		std::ostream& operator<<(std::ostream& t, Point p);
	}
}
