#include "Point.h"

using namespace std;

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		Point::Point()
		{
			x = 1.0 * rand() / RAND_MAX;
			y = 1.0 * rand() / RAND_MAX;
		}

		float Point::distance(Point a) const
		{
			float dx = x - a.x, dy = y - a.y;
			return sqrt(dx*dx + dy*dy);
		}

		float Point::distance(Point b, Point a)
		{
			float dx = a.x- b.x, dy = a.y - b.y;
			return sqrt(dx*dx + dy*dy);
		}

		float Point::X() const
		{
			return x;
		}

		float Point::Y() const
		{
			return y;
		}

		int Point::operator == (Point a)
		{
			return distance(a, *this) < .001;
		}

		std::ostream& operator<<(std::ostream& t, Point p)
		{
			cout << "(" << p.X() << "," << p.Y() << ")";
			return t;
		}
	}
}
