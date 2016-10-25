#include "Sorting.h"
#include "ElementarySortingMethods.h"
#include "QuickSort.h"
#include "MergeAndMergeSort.h"
#include "PriorityQueueAndHeapSort.h"
#include "BitwiseSort.h"
#include "SpecialPurposeSortingMethods.h"

namespace nsSorting
{
	void main()
	{
		nsElementarySortingMethods::main();
		nsQuickSort::main();
		nsMergeAndMergeSort::main();
		nsPriorityQueueAndHeapSort::main();
		nsBitwiseSort::main();
		nsSpecialPurposeSortingMethods::main();
	}
}
