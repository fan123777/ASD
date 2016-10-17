﻿#pragma once

namespace nsSorting
{
	// Слияние и сортировкаслиянием
	namespace nsMergeAndMergeSort
	{
		void main();

		// Программа 8.1.Слияние
		template <class Item>
		void mergeAB(Item c[], Item a[], int N, Item b[], int M)
		{
			for (int i = 0, j = 0, k = 0; k < N + M; k++)
			{
				if (i == N)
				{
					c[k] = b[j++];
					continue;
				}
				if (j == M)
				{
					c[k] = a[i++];
					continue;
				}
				c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
			}
		}


		// Слияние является основой для простого алгоритма сортировки типа "разделяй и властвуй" а также для его двойника - алгоритма восходящей(снизу - вверх) сортировки слиянием, при этом оба из них достаточно просто реализуются.
		// В этой главе рассматривается сортировка слиянием (mergesort), которая является дополнением быстрой сортировки в том, что она состоит из двух рекурсивных вызовов с последующей процедурой слияния.
		// Одним из наиболее привлекательных свойств сортировки слиянием является тот факт, что она сортирует файл, состоящий из N элементов, за время, пропорциональное NlogN, независимо от характера входных данных.
		// Основной недостаток сортировки слиянием заключается в том, что прямолинейные реализации этого алгоритма требуют дополнительного пространства памяти, пропорционального N.
		// Cортировка методом слияния достойна того, чтобы к ней проявить внимание в случае, когда на первый план выходят такие показатели как быстродействие, необходимость избегать наихудших случаев, возможность использования дополнительного пространства памяти.
		// Сортировка слиянием - это устойчивая сортировка, и данное обстоятельство склоняет чашу весов в ее пользу в тех приложениях, в которых устойчивость имеет важное значение.
		// Другое свойство сортировки слиянием, которое приобретает важное значение в некоторых ситуациях, является тот факт, что сортировка слиянием обычно реализуется таким образом, что она осуществляет, в основном, последовательный доступ к данным(один элемент за другим).
		// Например, сортировка слиянием — именно тот метод, который можно применить к связным спискам, для которых из всех методов доступа применим только метод последовательного доступа.
		// Слияние часто используется в качестве основы для сортировки на специализированных и высокопроизводительных машинах, поскольку именно последовательный доступ к данным в подобного рода системах обработки данных является самым быстрым.
		
		// 8.1. Двухпутевое слияние
		// 332
	}
}
