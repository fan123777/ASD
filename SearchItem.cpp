#include "SearchItem.h"

namespace nsSearch
{
	namespace nsCharacterTablesAndBinarySearchTrees
	{
		namespace nsSearchItem
		{
			std::ostream& operator<<(std::ostream& os, Item& x)
			{
				x.show(os);
				return os;
			}
		}
	}
}
