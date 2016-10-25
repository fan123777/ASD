#pragma once

#include <iostream>

namespace nsSearch
{
	namespace nsCharacterTablesAndBinarySearchTrees
	{
		namespace nsST
		{
			// Программа 12.2 АТД таблицы символов
			template <class Item, class Key>
			class ST
			{
			private:
				// Код, зависящий от реализации 
			public:
				ST(int);
				int count();
				Item search(Key);
				void insert(Item);
				void remove(Item);
				Item select(int);
				void show(std::ostream&);
			};
		}
	}
}
