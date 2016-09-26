#include "AnalysisPrinciples.h"

namespace nsAnalysis
{
	namespace nsAnalysisPrinciples
	{
		void main()
		{

		}

		int program1(int a[], int v, int l, int r)
		{
			for (int i = l; i <= r; i++)
			if (v == a[i])
				return i;
			return -1;
		}

		int program2(int a[], int v, int l, int r)
		{
			while (r >= l)
			{
				int m = (l + r) / 2;
				if (v == a[m])
					return m;
				if (v < a[m])
					r = m - 1;
				else l = m + 1;
			}
			return -1;
		}
	}
}
