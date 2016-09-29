﻿#pragma once

namespace nsDataStructures
{
	// Абстрактные типы данных
	namespace nsAbstractDataTypes
	{
		void main();

		// Программа 4.2 Программа-клиент для класса POINT (нахождение ближайшей точки)
		void program2();

		template <class Item>
		void exch(Item &x, Item &y);

		// Программа 4.5 Вычисление постфиксного выражения
		void program5();

		// Программа 4.6 Преобразование из инфиксной формы в постфиксную
		void program6();

		// Программа 4.10 Клиентская программа для АТД "Отношения эквивалентности"
		void program10(const int N, int a[][2]);

		// Для разработки нового уровня абстракции потребуется определить абстрактные объекты, с которыми необходимо манипулировать, и операции, которые должны выполняться над ними;
		// мы должны представить данные в некоторой структуре данных и реализовать операции;
		// Определение 4.1 Абстрактный тип данных (АТД) — это тип данных (набор значений и совокупность операций для этих значений), доступ к которому осуществляется только через интерфейс.
		// Программу, которая использует АТД, будем называть клиентом, а программу, в которой содержится спецификация этого типа данных - реализацией.
		// friend float distance(POINT, POINT);
		// Дружественная(friend) функция — это функция, которая, не будучи членом класса, имеет доступ к его приватным членам.
		// объявления общедоступных функций в классе образуют его интерфейс.
		
		// 4.1 Абстрактные объекты и коллекции объектов
		// Многие структуры данных и алгоритмы применяются для реализации фундаментальных АТД, представляющих собой коллекции абстрактных объектов и создаваемых на основе двух следующих операций:
		// - вставить новый объект в коллекцию
		// - удалить объект из коллекции
		// Такие АТД называются обобщенными очередями (generalized queues).
		// Как правило, для удобства в них также явно включаются следующие операции : создать(construct) структуру данных(конструкторы), подсчитать(count) количество объектов в структуре данных(или просто проверить, не пуста ли она).
		// Могут потребоваться и операции, наподобие уничтожить(destroy) структуру данных(деструкторы) и копировать(сору) структуру данных(конструкторы копирования);
		// В разделе 4.2 исследуется стек магазинного типа (pushdown stack), в котором для удаления объектов используется следующее правило : всегда удаляется объект, добавленный последним.
		
		// 4.2 АТД для стека магазинного типа
		// Определение 4.2 Стек магазинного типа — это АТД, который включает две основные операции : вставить, или затолкнуть(push) новый элемент и удалить, или вытолкнуть(pop) элемент, вставленный последним.
		// последним пришел, первым ушел (last-in, first-out, сокращенно LIFO).
		
		// 4.3 Примеры программ-клиентов, использующих ATD стека
		// 5*(((9 + 8)*D*6))+7)
		// Форма записи, обратная постфиксной, называется префиксной или Польской записью
		// 598 + 46**7 + * 
		// Преобразование из инфиксной формы в постфиксную.
		// Выражение обрабатывается слева направо : если встречается число, оно записывается в выходной поток; если встречается левая скобка, она игнорируется; если встречается знак операции, он заносится в стек; и если встречается правая скобка, то в выходной поток записывается знак операции, находящийся на верхушке стека.
		
		// 4.4 Реализации АТД стека 
		// Реализации на базе массива и связного списка.
		// Реализация на базе массива использует объем памяти, необходимый для размещения максимального числа элементов, которые может вместить стек в процессе вычислений;
		// реализация на базе списка использует объем памяти пропорционально количеству элементов, но при этом всегда расходует дополнительную память для одной связи на каждый элемент, а также дополнительное время на распределение памяти при каждой операции затолкнуть и освобождение памяти при каждой операции вытолкнуть.
		// Если требуется стек больших размеров, который обычно заполняется практически полностью, по - видимому, предпочтение стоит отдать реализации на базе массива.
		// Если же размер стека варьируется в широких пределах и присутствуют другие структуры данных, которым требуется память, не используемая во время, когда в стеке находится несколько элементов, предпочтение следует отдать реализации на базе связного списка.
		// Лемма 4.1 Используя либо массивы, либо связные списки, для АТД стека магазинного типа можно реализовать операции втолкнуть и вытолкнуть, имеющие постоянное время выполнения.
		
		// 4.5 Создание нового АТД
		// Подобный подход может породить следующие вопросы:
		// - какие базовые операции над доступными данными могут потребоваться клиентским программам?
		// - Какие операции можно реализовать эффективно?
		// разбиение программы на две части является более эффективным подходом, так как:
		// - позволяет отделять решение задачи высокого уровня (задачи связности) от решения задачи низкого уровня(задачи union - find) и решать эти две задачи независимо
		// - предоставляет естественный способ сравнения различных алгоритмов и структур данных, применяемых при решении этой задачи
		// - определяет с помощью интерфейса способ проверки ожидаемой работы программного обеспечения
		// - обеспечивает механизм, позволяющий совершенствовать представления (переходить к новым структурам данных и новым алгоритмам) без каких - либо изменений кода клиентских программ
		// - предоставляет абстракцию, которую можно использовать при построении других алгоритмов
		// К сожалению, при раздельной компиляции разные компиляторы налагают различные требования на реализацию шаблонов. Проблема заключается в том, что компилятор не может создать код для функции - члена, не зная типа параметра шаблона, который недоступен, так как определен в главной программе.
		// Определение функций - членов внутри объявлений классов позволяет избегать подобного рода головоломок, связанных с компиляцией.
		// Включение ключевого слова virtual в объявление функции - члена означает, что эта функция может быть переопределена в производном классе;
		// добавление последовательности символов = 0 в конце объявления функции - члена указывает на то, что данная функция является чистой виртуальной(pure virtual) функцией, которая должна быть переопределена в любом производном классе.
		// Абстрактный (abstract) класс — это класс, все члены которого являются чистыми виртуальными функциями. 
		// В любом классе, порожденном от абстрактного класса, должны быть определены все функции - члены и любые необходимые приватные данные - члены; таким образом, по нашей терминологии абстрактный класс является интерфейсом, а любой класс, порожденный от него, является реализацией.
		
		// 4.6 Очереди FIFO и обобщенные очереди
		// Очередь с дисциплиной FIFO (First-In, First-Out — Первым пришел, первым ушел) является еще одним фундаментальным АТД, который подобен стеку магазинного типа, но подчиняется противоположному правилу удаления элемента в операции удалить.
		// Из очереди удаляется не последний вставленный элемент, а наоборот — элемент, который был вставлен в очередь раньше всех остальных.
		// Определение 4.3 Очередь FIFO — это АТД, который содержит две базовых операции : вставить(put — занести) новый элемент и удалить(get — извлечь) элемент, который был вставлен раньше всех остальных.

		// Лемма 4.2 Для AТД "Очередь FIFO" имеется возможность реализовать операции get и put с постоянным временем выполнения, используя либо массивы, либо связные списки.
		// 164...
	}
}
