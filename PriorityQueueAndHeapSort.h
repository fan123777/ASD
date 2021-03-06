﻿#pragma once

#include "PriorityQueue.h"
#include "Common.h"

namespace nsSorting
{
	namespace nsArrayPQ = nsPriorityQueue::nsArrayPQ;
	namespace nsSortingPQ = nsPriorityQueue::nsSortingTreePQ;

	// Очереди по приоритетам и пирамидальная сортировка
	namespace nsPriorityQueueAndHeapSort
	{
		void main();

		// Программа 9.6.Сортировка с использованием очереди по приоритетам
		template <class Item>
		void PQsort(Item a[], int l, int r)
		{
			int k;
			nsSortingPQ::PQ<Item> pq(r - l + l);
			for (k = l; k <= r; k++)
				pq.insert(a[k]);
			for (k = r; k >= l; k--)
				a[k] = pq.getmax();
		}

		// Программа 9.7.Пирамидальная сортировка
		template <class Item>
		void heapsort(Item a[], int l, int r)
		{
			int k, N = r - l + 1;
			Item *pq = a + l - 1;
			for (k = N/2; k >= 1; k--)
				nsSortingPQ::fixDown(pq, k, N);
			while (N > 1)
			{
				nsCommon::exch(pq[1l], pq[N]);
				nsSortingPQ::fixDown(pq, 1, --N);
			}
		}

		// Часто мы накапливаем некоторый набор записей, после чего обрабатываем запись с максимальным значением ключа, затем, возможно, накопление записей продолжается, потом обрабатывается запись с наибольшим текущим ключом и т.д.
		// Соответствующая структура данных в подобного рода средах поддерживает операции вставки нового элемента и удаления наибольшего элемента.
		// Такая структура данных называется очередью по приоритетам.
		// Определение 9.1. Очередь по приоритетам представляет собой структуру элементов с ключами, которая поддерживает две основные операции : вставку нового элемента и удаление элемента с наибольшим значением ключа.
		// Необходимо построить и поддерживать структуры данных, содержащие записи с числовыми ключами(приоритетами), которые поддерживают некоторые из следующих операций:
		// - Создать (construct) очередь по приоритетам из N заданных элементов
		// - Вставить (insert) новый элемент
		// - Удалить наибольший (remove the maximum) элемент
		// - Изменить приоритет (change the priority) произвольно выбранного элемента
		// - Удалить (remove) произвольно выбранный элемент
		// - Объединить (join) две очереди но приоритетам в одну
		// Как и в случае других структур данных, в этот набор потребуется добавить стандартные операции создать, проверить наличие элементов и, возможно, операции уничтожить и копировать.
		// Например, у некоторых клиентских программ часто возникает необходимость найти наибольший(find the maximum) элемент в очереди по приоритетам без его удаления из очереди.
		// Или же понадобится операция заменить наибольший (replace the maximum) элемент новым элементом.
		// Мы можем реализовать подобного рода операции за счет использования в качестве строительных блоков две базовых операции:
		// - операцию найти наибольший можно представить через операцию удалить наибольший и следующую за ней операцию вставить
		// - а операцию заменить наибольший можно представить либо через операцию вставить и следующую за ней удалить наибольший, либо через операцию удалить наибольший и следующую за ней вставить.
		// для очередей по приоритетам наиболее характерными являются операции удалить наибольший(remove - the - maximum) и вставить(insert), поэтому им и будет уделяться основное внимание.
		// Мы почти приблизимся к идеалу в смысле возможности выполнить операцию удалить наибольший за время, которое находится в логарифмической зависимости от числа элементов в очереди, а все остальные операции - за постоянное время.
		// в разделах 9.2—9.4 внимание сосредоточивается на рассмотрении классической структуры данных, получившей название сортирующее дерево(heap), которая обеспечивает эффективную реализацию всех операций, кроме операции объединить.
		// в разделе 9.7 рассматриваются более сложные структуры данных, получившие название биномиальных очередей(binomial queue), которые используются для реализации всех операций(в том числе и операции объединить) в наихудшем случае логарифмической зависимости времени выполнения.

		// 9.1. Элементарные реализации
		// Программа 9.2 демонстрирует реализацию, которая в качестве базовой структуры данных использует неупорядоченный массив.
		// Операция найти наибольший элемент реализуется следующей последовательностью действий : сначала производится просмотр массива с целью обнаружения наибольшего элемента, затем осуществляется замена наибольшего элемента на последний элемент с последующим уменьшением размера очереди на единицу.
		// Выбор в пользу того, оставить элементы неотсортированными или разместить их в определенном порядке, определяется тем, что упорядоченная совокупность элементов позволяет выполнить операции удалить наибольший или найти наибольший за постоянное время, но это также означает необходимость прохода по всему списку, чтобы выполнить операцию вставить.
		// Неупорядоченная последовательность элементов позволяет выполнить операцию вставить за постоянное время, а для операции удалить наибольший или найти наибольший потребуется просмотреть весь список.
		// Неупорядоченность представляет собой прототипный "ленивый" подход к решению проблемы, в рамках которого выполнение работы откладывается до тех пор, пока это не станет необходимым(в данном случае, поиск наибольшего элемента);
		// упорядоченная последовательность представляет собой прототипный "энергичный" подход к решению проблемы, когда заранее выполняется максимально возможный объем работы(поддержка списка отсортированным на случай выполнения операции вставка), дабы обеспечить максимальную эффективность последующих операций.
		// Реализация, работающая с неупорядоченными списками, может оказаться приемлемой в приложениях, в которых выполняются лишь немногие операции удалить наибольший и в то же время очень большое количество вставок, тогда как упорядоченный список лучше подходит в тех случаях, когда выполняется большое число операций найти наибольший либо когда вставляемые элементы преимущественно больше уже находящихся в очереди по приоритетам.

		// 9.2. Пирамидальная структура данных 
		// Основной темой настоящей главы является простая структура данных, получившая название сортирующего дерева(heap), которая может эффективно поддерживать основные операции в очереди по приоритетам.
		// В сортирующем дереве записи хранятся в виде массива таким образом, что каждый ключ обязательно принимает значение большее, чем значения двух других ключей, занимающих относительно него строго определенные положения.
		// Определение 9.2. Дерево называется пирамидально упорядоченным(heap - ordered), если ключ в каждом его узле больше или равен ключам всех потомков этого узла(если таковые имеются).
		// Эквивалентная формулировка : ключ в каждом узле пирамидально упорядоченного дерева меньше или равен ключу узла, который является родителем данного узла.
		// Лемма 9.1. Ни один из узлов пирамидально упорядоченного дерева не может иметь ключа, большего чем ключ корня дерева.
		// Однако особенно удобно пользоваться полным бинарным деревом(complete binary tree).
		// Определение 9.3. Сортирующее дерево есть совокупность узлов с ключами, образующих полное пирамидально упорядоченное бинарное дерево, представленное в виде массива.
		// Родителя узла, находящегося в позиции i, необходимо искать в позиции |_i/2_| и, соответственно, два потомка узла в позиции / находятся в позициях 2i и 2i + 1.
		
		// 9.3. Алгоритмы для сортирующих деревьев 
		// Все алгоритмы очередей по приоритетам для сортирующих деревьев работают таким образом, что сначала вносят простое изменение, способное нарушить структуру пирамиды, затем выполняют проход вдоль пирамиды, внося при этом в сортирующее дерево такие изменения, которые гарантируют, что структура сортирующего дерева сохраняется везде.
		// Этот процесс иногда называют установлением пирамидального порядка(heapifying).
		// Если свойства сортирующего дерева нарушены из-за того, что ключ некоторого узла становится больше ключа родительского узла, можно сделать шаг в направлении исправления этого нарушения, обменяв местами этот узел с его родителем.
		// Нисходящая установка структуры сортирующего дерева:
		// Обратите внимание на то обстоятельство, что если N есть четное число и к равно N / 2, то узел в позиции к имеет только одного потомка — этот случай требует особого подхода!
		// Если очередь по приоритетам представлена как пирамидально упорядоченный массив, использование операции вставить (insert) равносильно добавлению нового элемента в конец массива и перемещение этого элемента по массиву с целью восстановления структуры сортирующего дерева;
		// операция удалить наибольший(remove the maximum) равносильна удалению наибольшего элемента из вершины дерева с последующим размещением элемента, находящегося в конце дерева, в его вершине и перемещением его вниз вдоль массива с целью восстановления структуры сортирующего дерева.
		// Лемма 9.2. Операции вставить (insert) и удалить наибольший(remove the maximum) для абстрактного типа данных могут быть реализованы на пирамидально упорядоченных деревьях таким образом, что операция вставить требует для своего выполнения на очереди, состоящей из N элементов, не более lg(N) сравнений, а операция удалить наибольший — не более 2*lg(N) сравнений.
		// Базовые процедуры fixUp и fixDown из программ 9.3 и 9.4 позволяют получить прямую реализацию операций изменить приоритет(change priority) и удалить (remove).
		// Лемма 9.3. Операции изменить приоритет (change priority), удалить(remove) и изменить приоритет (change priority) для АТД очередь по приоритетам могут быть реализованы через сортирующие деревья, такие, что для любой из указанных выше операций требуется выполнение не более чем 2lg(N) операций сравнения на очереди из N элементов.
		// Специально обращаем внимание на тот факт, что в этот список не включена операция объединить(join).
		// любую очередь по приоритетам можно использовать для построения еще одного метода сортировки.
		// Мы просто вставляем все подлежащие сортировке ключи в очередь по приоритетам, а затем многократно используем операцию удалить наибольший, чтобы удалять их в порядке убывания приоритетов.
		// Такое использования очереди по приоритетам, представленной в виде неупорядоченного списка, соответствует выполнению сортировки выбором, а применение упорядоченного списка соответ ствует выполнению сортировки вставками.
		
		// 9.4. Пирамидальная сортировка
		// Лемма 9.4. Для построения сортирующего дерева снизу вверх требуется линейно зависимое время.
		// Лемма 9.5. Пирамидальная сортировка использует менее 2*N*lg(N) сравнений для сортировки N элементов.
		// Достижение такой гарантированной эффективности для худшего случая требует уплаты своей цены:
		// например, внутренний цикл рассматриваемого алгоритма(стоимость выражается количеством операций сравнения) выполняет больше базовых операций, чем внутренний цикл быстрой сортировки, таким образом, пирамидальная сортировка, по - видимому, работает медленнее быстрой сортировки как на обычных файлах, так и на файлах с произвольной организацией.
		// Сортирующие деревья можно успешно использовать для решения проблемы выборки k максимальных элементов из N элементов(см.главу 7), особенно в случаях, когда k мало.
		// Лемма 9.6. Выборка на базе пирамидальной сортировки позволяет отыскать k-й наибольший элемент из N элементов за время, пропорциональное N, когда k мало или близко по величине к N, либо за время, пропорциональное N*log(N), во всех других случаях.
		// Одна из идей, развитая Флойдом, состоит в использовании того обстоятельства, что элемент, повторно вставляемый в процессе нисходящей сортировки, проделывает весь путь на нижний уровень, так что мы можем сэкономить время, затрачиваемое на проверку достижения таким элементом своей позиции, просто продвигая больший из двух потомков до тех пор, пока не будет достигнут нижний уровень с последующим продвижением вверх по сортирующему дереву в соответствующую позицию.
		// Этот метод требует дополнительных вычислений и может оказаться полезным на практике только в ситуациях, когда расходы на операции сравнения сравнительно велики.
		// Другая идея заключается в том, чтобы построить сортирующие деревья, опираясь на представление полных пирамидально упорядоченных троичных деревьев в виде массивов, при этом узел в позиции к больше или равен узлам в позициях Зk — 1, Зk и 3k + 1 и меньше или равен узлам в позициях |_(k+1)/3_| для всех позиций между 1 и N в массиве из N элементов.
		// Естественно, не может не интересовать проблема, какой метод сортировки выбрать для конкретного приложения:
		// пирамидальную сортировку, быструю сортировку или сортировку слиянием.
		
		// 9.5. Абстрактный тип данных очереди по приоритетам
		// Мы не рассматриваем операции уничтожить (destroy) или копировать(сору), а выбрали один из нескольких возможных вариантов операции объединить(join).
		// гораздо труднее разработать такую реализацию, в рамках которой гарантируется логарифмическая производительность для всех видов операций.
		// В тех приложениях, в которых очереди по приоритетам не достигают больших размеров или в которых смесь операций вставить и удалить наибольший обладает рядом специальных свойств, предпочтительным может оказаться полностью гибкий интерфейс.
		// При необходимости можно добавить в программы деструктор, конструктор копирования и перегруженный оператор присваивания для дальнейшего совершенствования этого приложения с целью получения АТД первого класса.
		
		// 9.6. Очередь по приоритетам для индексных элементов
		// Будем называть структуру данных, построенную этой программой, индексным сортирующим деревом(index heap).
		
		// 9.7. Биномиальные очереди 
		// Ни одна из рассмотренных выше реализаций не может обеспечить высокоэффективное выполнение в наихудшем случае сразу всех операций объединить, удалить наибольший и вставить.
		// Неупорядоченные связные списки позволяют быстро выполнять операции объединить и вставить, но на них медленно выполняется операция удалить наибольший;
		// упорядоченные связные списки позволяют быстро выполнять операции удалить наибольший, но на них медленно выполняются операции объединить и вставить;
		// на сортирующем дереве быстро выполняются вставить и удалить наибольший, но медленно - операция объединить и т.д.
		// Основная трудность сопряжена с такими динамическими операциями как вставить, объединить и удалить наибольший, которые требуют модификации древовидных структур.
		// Вначале следует отметить, что операция объединить (join) тривиальна для одного специального типа дерева с ослабленным требованием необходимости быть пирамидально упорядоченным.
		// Определение 9.4. Бинарное дерево, содержащее узлы с ключами, называется левосторонним пирамидально упорядоченным(left heap ordered), если ключ каждого узла больше или равен всем ключам левого поддерева этого ключа(если таковое имеется).
		// Определение 9.5. Сортирующее дерево степени 2 есть левостороннее пирамидально упорядоченное дерево, состоящее из корневого узла с пустым правым поддеревом и полным левым поддеревом.
		// В дереве, соответствующем сортирующему дереву степени 2 по левому потомку, соответствие правому потомку называется биномиальным деревом (binomial tree).
		// В частности, мы ощущаем свою зависимость от следующих факторов, являющихся прямым следствием приведенных определений:
		// - Количество узлов сортирующего дерева степени 2 есть степень числа 2.
		// - Ни один из узлов не обладает ключом, который превосходит по значению ключ корня.
		// - Биномиальные деревья пирамидально упорядочены.
		// Корневой узел с большим значением ключа становится корнем результирующего дерева(другой исходный корень при этом становится потомком корня результирующего дерева), а его левое поддерево становится правым поддеревом другого корневого узла.
		// Если задано связное представление деревьев, то операция объединения выполняется за постоянное время : мы всего лишь устанавливаем две связи в вершине.
		// Определение 9.6. Биномиальная очередь представляет собой набор сортирующих деревьев степени 2, ни одно из которых не совпадает с остальными по размеру.
		// Структура биномиальной очереди определяется числом узлов этой очереди в соответствии с двоичным представлением целых чисел.
		// В биномиальной очереди размера N содержатся максимум lg(N) сортирующих деревьев степени 2, высота которых не превосходит значения lg(N).
		// Начнем с рассмотрения операции вставить (insert).
		// чтобы добавить в биномиальную очередь новый элемент, мы продвигаемся справа налево, выполняя слияние сортирующих деревьев, соответствующих битам 1 с переносимым сортирующим деревом, пока не найдем самую правую пустую позицию, в которую и помещаем переносимое дерево.
		// Как мы вскоре убедимся, реализация операции объединить соответствует реализации операции сложения двоичных чисел.
		// Можно также реализовать операцию удалить наибольший (remove the maximum) путем одного вызова операции объединить.
		// Столь непосредственная аналогия с операциями двоичной арифметики вплотную подводит к естественной реализации операции объединить.
		// Лемма 9.7. Все операции на очереди по приоритетам как на абстрактном типе данных могут быть реализованы на биномиальной очереди таким образом, что для выполнения любой из них на очереди из N элементов требуется O(lg(N)) шагов.
		// Лемма 9.8. Построение биномиальной очереди с выполнением N операций вставок в первоначально пустую очередь требует выполнения O(N) сравнений в наихудшем случае.
	}
}
