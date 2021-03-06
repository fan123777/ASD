﻿#pragma once

namespace nsSorting
{
	// Элементарные методы сортировки
	namespace nsElementarySortingMethods
	{
		void main();
		void testSort();

		// Программа 6.1.Пример сортировки массива с помощью управляющей программы
		template <class Item>
		void exch(Item& a, Item& b)
		{
			Item t = a; a = b; b = t;
		}

		template <class Item>
		void compexch(Item& a, Item& b)
		{
			if (b < a)
				exch(a, b);
		}

		template <class Item>
		void sort(Item a[], int l, int r)
		{
			for (int i = 1 + 1; i <= r; i++)
				for (int j = i; j > l; j--)
					compexch(a[j - 1], a[j]);
		}

		// Программа 6.2.Сортировка выбором
		template <class Item>
		void selection(Item a[], int l, int r)
		{
			for (int i = l; i < r; i++)
			{
				int min = i;
				for (int j = i + 1; j <= r; j++)
					if (a[j] < a[min])
						min = j;
					exch(a[i], a[min]);
			}
		}

		// Программа 6.3.Сортировка вставками
		template <class Item>
		void insertion(Item a[], int l, int r)
		{
			int i;
			for (i = r; i > l; i--)
				compexch(a[i - 1], a[i]);
			for (i = l + 2; i <= r; i++)
			{
				int j = i;
				Item v = a[i];
				while (v < a[j - 1])
				{
					a[j] = a[j - 1];
					j--;
				}
				a[j] = v;
			}
		}

		// Программа 6.4.Пузырьковая сортировка
		template <class Item>
		void bubble(Item a[], int l, int r)
		{
			for (int i = l; i < r; i++)
				for (int j = r; j > i; j--)
					compexch(a[j - 1], a[j]);
		}

		// Программа 6.5.Сортировка методом Шелла
		template <class Item>
		void shellsort(Item a[], int l, int r)
		{
			int h;
			for (h = 1; h <= (r - l)/9; h = 3*h + 1);
			for (; h > 0; h /= 3)
				for (int i = l + h; i <= r; i++)
				{
					int j = i;
					Item v = a[i];
					while (j >= l + h && v < a[j - h])
					{
						a[j] = a[j - h];
						j -= h;
					}
					a[j] = v;
				}
		}

		// Программа 6.6.Драйвер сортировки массивов
		void program6();

		template<typename Item>
		int MyCompare(void *i, void *j)
		{
			return strcmp(*(Item *)i, *(Item *)j);
		}

		template<typename Item>
		void MySort(Item a[], int l, int r)
		{
			qsort(a, r - l + 1, sizeof(Item), MyCompare);
		}

		// Программа 6.14.Обменная сортировка
		template <class Item, class Index>
		void insitu(Item data[], Index a[], int N)
		{
			for (int i = 0; i < N; i++)
			{
				Item v = data[i];
				int j, k;
				for (k = i; a[k] != i; k = a[j], a[j] = j)
				{
					j = k;
					data[k] = data[a[k]];
				}
				data[k] = v; a[k] = k;
			}
		}

		void sortList();

		// Программа 6.17.Распределяющий подсчет
		void distcount(int a[], int l, int r);


		// Мы подробно рассмотрим реализацию трех элементарных методов : сортировки выбором, сортировки вставками и пузырьковой сортировки.
		
		// 6.1. Правила игры 
		// Мы будем рассматривать методы сортировки файлов элементов, обладающих ключами.
		// Цель метода сортировки заключается в переупорядочении элементов таким образом, чтобы их ключи следовали в соответствии с четко определенными правилами(обычно это цифровой или алфавитный порядок).
		// Если сортируемый файл полностью помещается в оперативной памяти, то используемый в этом случае метод сортировки называется внутренним.
		// Сортировка файлов, хранящихся на магнитной ленте или диске, называется внешней.
		// Пример функции сортировки, представленный программой 6.1, является одним из вариантов сортировки вставками(insertion sort).
		// Так как в нем используются только операции сравнения и обмена, то его можно считать примером неадаптивной(nonadaptive) сортировки:
		// последовательность операций, которые она выполняет, не зависит от порядка следования данных.
		// И наоборот, адаптивная (adaptive) сортировка выполняет различные последовательности операций в зависимости от результата сравнения(вызов операции operator<).
		// Для выполнения сортировки N элементов методом выбора, методом вставок и пузырьковым методом требуется время,пропорциональное N^2.
		// Более совершенные методы могут выполнить сортировку N элементов за время, пропорциональное NlogN.
		// Метод Шелла(N^3/2)
		// Аналитические результаты, изложенные в предыдущем параграфе, получены на основе подсчета базовых операций(сравнение и обмен значениями), которые выполняет алгоритм.
		// В общем, наилучший способ уменьшения стоимости приложения — это переключение на более эффективный алгоритм;
		// Другой способ предусматривает минимизацию внутренних циклов по числу команд.
		// Дополнительный объем оперативной памяти, используемый алгоритмом сортировки, является вторым по важности фактором, который также будет рассматриваться.
		// Методы можно разбить на три категории:
		// - те, которые выполняют сортировку на месте и не нуждаются в дополнительной памяти, за исключением, возможно, небольшого стека или таблицы;
		// - те, которые используют представление в виде связного списка или каким - то другим способом получает доступ к данным,используя для этой цели указатели или индексы массивов, в связи с чем необходима дополнительная память для размещения TV указателей или индексов, 
		// - и те, которые требуют дополнительной памяти для размещения еще одной копии массива, подвергаемого сортировке.
		// Определение 6.1: Говорят, что метод сортировки устойчив, если он сохраняет относительный порядок размещения элементов в файле, который содержит дублированные ключи.
		// Использование устойчивого алгоритма сортировки гораздо предпочтительней.
		// Если сортируемые элементы имеют большие размеры, не имеет смысла перемещать их в памяти, целесообразнее выполнять непрямую(indirect) сортировку:
		// переупорядочиваются не сами элементы, а, скорее, массив указателей(индексов) так, что первый указатель указывает на наименьший элемент, следующий — на наименьший из оставшихся и т.д.
		
		// 6.2. Сортировка выбором
		// Сначала отыскивается наименьший элемент массива, затем он меняется местами с элементом, стоящим первым в сортируемом массиве.
		// Далее, находится второй наименьший элемент и меняется местами с элементом, стоящим вторым в исходном массиве.
		// Этот процесс продолжается до тех пор, пока весь массив не будет отсортирован.
		// Изложенный метод называется сортировкой выбором, поскольку он работает по принципу выбора наимень шего элемента из числа неотсортированных.
		// Этому методу сортировки файлов отдается предпочтение в тех случаях, когда записи файла огромны, а ключи занимают незначительное пространство.
		// В подобного рода приложениях затраты ресурсов на перемещения записей намного превосходят стоимость операций сравнения, а что касается перемещения данных, то никакой алгоритм не способен выполнить сортировку файла с меньшим числом перемещений данных, нежели метод выбора.
		
		// 6.3. Сортировка вставками
		// Функция sort из программы 6.1 является программной реализацией этого метода, получившего название сортировки вставками(insertion sort).
		// - Прежде всего, можно отказаться от выполнения операций compexch, если встречается ключ, который не больше ключа вставляемого элемента, поскольку подмассив, находящийся слева, уже отсортирован.
		// быстродействие программы, повышается примерно в два раза.
		// - Менее очевидное улучшение реализации следует из того факта, что проверка условия у > l обычно оказывается излишней.
		// Третье улучшение, которое сейчас будет рассматриваться, также касается удаления лишних команд из внутреннего цикла.
		// Оно следует из того факта, что последовательные обмены значениями с одним и тем же элементом не эффективны.
		// Если производятся два или большее число обменов значениями, то мы имеем:
		// t = a[j]; a[j] = a[j-l] ; a[j-l] = t;
		// за которым следует
		// t = a[j-l]; a[j-l] = a[j-2] ; a[j-2] = t
		// и т.д.
		// было бы правильно назвать функцию sort из программы 6.1 неадаптивной сортировкой вставками (nonadaptive insertion sort).
		// В отличие от сортировки выбором, время выполнения сортировки вставками зависит главным образом от исходного порядка ключей при вводе.
		// Например, если файл большой, а ключи записей уже упорядочены(или почти упорядочены), то сортировка вставками выполняется быстро, а сортировка выбором протекает медленно.
		
		// 6.4. Пузырьковая сортировка
		// Метод пузырьковой сортировкой (bubble sort), в рамках которой выполняются следующие действия:
		// Проход по файлу с обменом местами соседних элементов, нарушающих заданный порядок, до тех пор, пока файл не будет окончательно отсортирован.
		
		// 6.5. Характеристики производительности элементарных методов сортировки
		// В общем случае время выполнения алгоритма сортировки пропорционально количеству операций сравнения, выполняемых этим алгоритмом, количеству перемещений или перемен местами элементов, а, возможно, и обоим сразу.
		// Лемма 6.1. Сортировка выбором производит примерно (N^2)/2 операций сравнения и N операций обмена элементов местами.
		// единственный показатель сортировки выбором, зависящий от характера входных данных — это число операций присваивания переменной min новых значений. O(NlogN)
		// Лемма 6.2. Сортировка вставками производит в среднем приблизительно (N^2)/4 операций сравнения и (N^2)/4 операций полуобмена элементов местами(перемещений) и в два раза больше операций в наихудшем случае.
		// Лемма 6.3. Пузырьковая сортировка производит в среднем примерно (N^2)/2 операций сравнения и (N^2)/2 операций обмена как в среднем, так и в наихудшем случаях.
		// Определение 6.2. Инверсией называется пара ключей, которые нарушают порядок в файле.
		// Лемма 6.4. Методы вставок и пузырьковой сортировки выполняют линейно зависимое от N число операций сравнения и обмена при сортировке файлов с не более чем постоянным числом инверсий, приходящихся на каждый элемент.
		// Лемма 6.5. Сортировка вставками использует линейно зависимое (от N) число операций сравнения и обмена для файлов с не более чем постоянным количеством элементов, которые имеют более чем постоянное число соответствующих инверсий.
		// Лемма 6.6. Время выполнения сортировки выбором линейно зависит от размеров файлов с большими элементами и малыми ключами.
		
		// б.б. Сортировка методом Шелла
		// Сортировка методом Шелла представляет собой простейшее расширение метода вставок, быстродействие которого выше за счет обеспечения возможности обмена местами элементов, которые находятся далеко один от другого.
		// Идея заключается в переупорядочении файла таким образом, чтобы придать ему следующее свойство:
		// совокупность h - ых элементов исходного файла(начиная с любого) образует отсортированный файл.
		// В таком случае говорят, что файл h - упорядочен(h - sorted).
		// Использование такого рода процедуры для любой последовательности значений h, которая заканчивается единицей, завершается получением упорядоченного файла:
		// именно в этом и заключается суть сортировки методом Шелла.
		// Добавление внешнего цикла, изменяющего значение шага, позволяет получить компактную программную реализацию сортировки методом Шелла, в которой используется последовательность шагов 1 4 13 40 121 364 1093 3280 9841.
		// N((logN)^2) 
		// Лемма 6.7.Результатом h- сортировки k- упорядоченного файла есть h- и k- упорядоченный файл.
		// Лемма 6.8. Сортировка методом Шелла выполняет менее N(h — 1)(k — 1)/g операций сравнения при g- сортировке h- и k- упорядоченного файла при условии, что h и к взаимно просты.
		// Лемма 6.9. Сортировка методом Шелла выполняет менее О (N^(3/2)) операций сравнения для последовательности шагов 1 4 13 40 121 364 1093 3280 9841...
		// Лемма 6.10. Сортировка методом Шелла выполняет менее O(N^(4/3)) операций сравнения для последовательности шагов 1 8 23 77 281 1073 4193 16577...
		// Лемма 6.11. Сортировка методом Шелла выполняет менее О (N (logN)^2) операций сравнения для последовательности шагов 1 2 3 4 6 9 8 12 18 27 16 24 36 54 81...
		
		// 6.7. Сортировка других типов данных
		// В частности, будут рассматриваться интерфейсы для:
		// - элементов или обобщенных объектов, подлежащих сортировке
		// - массивов элементов.

		// 6.8 Сортировка по индексам и указателям
		// Для индексной сортировки характерно следующее:
		// если а есть массив указателей на ключи, то результатом вызова функции sort будет переупорядочение указателей таким образом, что последовательный доступ к ним означает доступ к ключам в соответствующем порядке.
		// Мы выполняем операции сравнения, следуя указателям; мы реализуем операции обмена за счет перемены местами указателей.
		// Функция qsort из стандартной библиотеки С представляет собой сортировку по указателям.
		// Можно "сортировать" файл даже в том случае, когда к нему разрешен доступ "только для чтения".
		// Более того, используя несколько индексных массивов или массивов указателей, можно сортировать один и тот же файл по многим ключам.
		// Этот процесс называется перестановкой по месту (in situ) или обменное упорядочение файла.
		// Непрямая сортировка требует дополнительного пространства памяти для размещения массива индексов или массива указателей и дополнительного времени для выполнения операций непрямого сравнения.
		// Во многих приложениях эти затраты являются вполне оправданной ценой за гибкость и возможность вообще не затрагивать записи.
		
		// 6.9. Сортировка связных списков
		// Возможность того, что ссылки на узлы будут осуществляться через указатели, управление которыми реализуется за пределами сортировки, означает, что наши программы должны менять только связи в узлах и не должны менять ключей или какой - либо другой информации.
		
		// 6.10. Метод распределяющего подсчета 
		// выполнить сортировку файла, состоящего из N элементов, ключи которого принимают целые значения в диапазоне от 0 до М - 1.
		// идея состоит в том, чтобы подсчитать количество ключей с каждым конкретным значением, а затем использовать счетчики при перемещении в соответствующие позиции во время второго прохода по сортируемому файлу.
		// Лемма 6.12. Метод распределяющего подсчета представляет собой сортировку с линейно зависимым временем выполнения при условии, что диапазон изменения значений ключей пропорционален размеру файла.
	}
}
