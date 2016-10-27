#include "CharacterTablesAndBinarySearchTrees.h"
#include "SearchItem.h"
#include "ST.h"
#include <iostream>
#include <fstream>

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
		// using namespace nsSortedArrayST;
		// using namespace nsListST;
		using namespace nsBSTST;


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

		void program11()
		{
			/*const int maxN = 100;
			const int maxQ = 100;
			static char text[maxN];
			int N = 0; char t;
			ifstream corpus;
			corpus.open("filename");
			while (N < maxN && corpus.get(t))
				text[N++] = t;
			text[N] = 0;
			ST<Item, Key> st(maxN);
			for (int i = 0; i < N; i++)
				st.insert(&text[i]);
			char query[maxQ];
			Item x, v(query);
			while (cin.getline(query, maxQ))
			if ((x == st.search(v.key())).null())
				cout << "not found: " << query << endl;
			else
				cout << x->text << ": " << query << endl;*/
		}
	}
}
