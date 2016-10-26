#include "CharacterTablesAndBinarySearchTrees.h"
#include "SearchItem.h"
#include "ST.h"
#include <iostream>

using namespace std;

namespace nsSearch
{
	namespace nsCharacterTablesAndBinarySearchTrees
	{
		void main()
		{
			program3();
		}

		using namespace nsSearchItem;

		// using namespace nsArrayST;
		using namespace nsSortedArrayST;
		// using namespace nsListST;

		void program3()
		{
			int N, maxN = maxKey, sw = 1;
			ST<Item, Key> st(maxN);
			for (N = 0; N < maxN; N++)
			{
				Item v;
				if (sw)
					v.rand();
				else
					v.scan();
				if (!(st.search(v.key())).null())
					continue;
				st.insert(v);
			}
			st.show(std::cout);
			std::cout << endl;
			std::cout << N << " keys" << endl;
			std::cout << st.count() << " distinct keys" << std::endl;
		}
	}
}
