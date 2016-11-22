﻿#pragma once

namespace nsSearch
{
	// Поразрядный поиск 
	namespace nsBitwiseSearch
	{
		void main();

		// В нескольких методах поиска обработка ведется за счет исследования ключей поиска по небольшим фрагментам за раз вместо того, чтобы на каждом шаге сравнивать полные значения ключей.
		// Эти методы носят название поразрядного поиска(radix - search) и работают аналогично методам поразрядной сортировки, которые рассматривались в главе 10.
		// Они удобны, когда фрагменты ключей поискалегкодоступны, и могут обеспечить эффективные решения для множества реальных применений поиска.
		// В данном случае применяется та же абстрактная модель, которая использовалась в главе 10:
		// в зависимости от контекста ключ может быть словом(последовательностью байтов фиксированной длины) или строкой(последовательностью байтов переменной длины).
		// Принципиальные преимущества методов поразрядного поиска заключается в следующем:
		// они обеспечивают приемлемую производительность для худшего случая без сложностей, присущих сбалансированным деревьям;
		// они обеспечивают простой способ обработки ключей переменной длины;
		// некоторые из них позволяют экономить память, сохраняя часть ключа внутри поисковой структуры;
		// они могут обеспечить быстрый доступ к данным, конкурируя как с деревьями бинарного поиска (BST-деревьями), так и с хешированием.
		
		// 15.1 Деревья цифрового поиска 
		// Простейший метод поразрядного поиска основан на использовании деревьев цифрового поиска(digital search trees — DST), на которые в дальнейшем будем ссылаться как на DST - деревья.
		// Алгоритмы поиска и вставки аналогичны поиску в бинарном дереве, за исключением одного различия:
		// ветвление в дереве выполняется не в соответствии с результатом сравнения полных ключей, а в соответствии с выбранными разрядами ключа.
		// На первом уровне используется ведущий разряд;
		// на втором уровне используется разряд, следующий за ведущим, и т.д., пока не встретится внешний узел.
		// DST-деревья характеризуются тем, что каждый ключ размещается где - то вдоль пути, определенного разрядами ключа(следующими слева направо).
		// Этого свойства достаточно, чтобы реализации операций search и insert в программе 15.1 работали правильно.
		// Лемма 15.1 Для выполнения поиска или вставки в DST-дереве, построенном из N случайных ключей, требуется около lg(N) сравнений в среднем и около 2*lg(N) сравнений вхудшем случае.
		// Количество сравнений никогда не превышает количество разрядов в ключе поиска.
		
		// 15.2 Trie-деревья 
		// Основная идея заключается в хранении ключей только в нижней части дерева, в листьях.
		// повсеместно используется термин trie-дерево и все его понимают.
		// В trie-дереве ключи хранятся в листьях бинарного дерева.
		// Вспомните из раздела 5.4, что лист в дереве — это узел, не имеющий дочерних узлов, что отличает его от внешнего узла, который интерпретируется как нулевой дочерний узел.
		// Определение 15.1 Под trie-деревом понимается бинарное дерево, имеющее ключи, связанные с каждым из его листьев, и рекурсивно определенное следующим образом.
		// Trie-дерево, состоящее из пустого набора ключей, представляет собой нулевую связь.
		// Trie-дерево, состоящее из единственного ключа — это лист, содержащий данный ключ.
		// И, наконец, trie - дерево, содержащее намного больше одного ключа — это внутренний узел, левая связь которого ссылается на trie - дерево с ключами, начинающимися с 0 разряда, а правая — на trie - дерево с ключами, начинающимися с 1 разряда, причем для конструирования поддеревьев ведущий разряд такого дерева должен быть удален.
		// Лемма 15.2 Структура trie-дерева не зависит от порядка вставки ключей : для каждого данного набора различных ключей существует уникальное trie-дерево.
		// Лемма 15.3. Для выполнения вставки или поиска случайного ключа в trie-дереве, построенном из N случайных(различных) строк разрядов, требуется в среднем около lgN сравнений разрядов.
		// В худшем случае количество сравнений разрядов не превышает количество разрядов в искомом ключе.
		// Исследование самого рекуррентного соотношения позволяет понять, почему trie - деревья лучше сбалансированы, чем BST - деревья:
		// вероятность того, что разделение произойдет вблизи середины дерева, гораздо выше, чем в любом другом месте.
		// Лемма 15.4 Trie-дерево, построенное из N случайных w-разрядных ключей, содержит в среднем около N / ln(2) = 1.44 N узлов.
		
		// 15.3 patricia-деревья 
		// Начиная со структуры данных стандартного trie - дерева, мы избегаем однонаправленного ветвления благодаря применению простого приема:
		// в каждый узел помещается индекс разряда, который должен проверяться с целью выбора пути из этого узла.
		// Более того, внешние узлы исключаются при помощи еще одного простого приема:
		// данные хранятся во внутренних узлах, а связи с внешними узлами заменяются связями, которые указывают в обратном направлении вверх на требуемый внутренний узел в trie - дереве.
		// Программа 15.4 содержит реализацию алгоритма поиска в patricia-дереве.
		// Используемый метод отличается от поиска в trie - дереве в трех отношениях:
		// - не существует никаких явных нулевых связей,
		// - в ключе проверяется не следующий разряд, а указанный,
		// - поиск завершается сравнением ключа в точке, в которой выполняется перемещение по дереву вверх.
		// Со временем встречается связь, указывающая вверх: каждая направленная вверх связь указывает на уникальный ключ в дереве, содержащий разряды, которые могли бы направить поиск вдоль этой связи.
		// Таким образом, если ключ в узле, указанный первой направленной вверх связью, равен искомому ключу, поиск является успешным; в противном случае он будет безуспешным.
		// Лемма 15.5 Вставка или поиск случайного ключа в patricia-дереве, построенном из N случайных строк разрядов, требует приблизительно lgN сравнений разрядов в среднем и приблизительно 2 lgN сравнений разрядов в худшем случае.
		// Количество сравнений разрядов никогда не превышает длины ключа.
		// patricia-метод (или поиск с использованием trie-дерева, из которого удалены однонаправленные ветвления) — наиболее предпочтительный метод поиска при наличии длинных ключей.
		// При использовании patricia-деревьев можно надеяться, что количество проверок разрядов, необходимых для поиска среди N записей, даже с очень длинными ключами, будет приблизительно пропорциональным lgN.

		// 15.4 Многопутевые trie-деревья и TST-деревья
		// Было установлено, что производительность поразрядной сортировки можно существенно увеличить, рассматривая одновременно более одного разряда.
		// То же самоесправедливо и в отношении поразрядного поиска : исследуя одновременно по r разрядов, скорость поиска можно увеличить в r раз.
		// Прежде чем создавать реализацию полной таблицы символов с несколькими типами узлов, давайте начнем изучение многопутевых деревьев с задачи таблицы существования, в которой хранятся только ключи(без каких - либо записей и связанной с ними информации).
		// Определение 15.2 trie-дерево существования, соответствующее набору ключей, рекурсивно определяется следующим образом:
		// trie - дерево для пустого набора ключей — нулевая связь;
		// trie - дерево для непустого набора ключей — внутренний узел, содержащий связи, ссыпающиеся на trie - дерево для каждой возможной цифры ключа, причем при построении поддеревьев ведущая цифра должна удаляться.
		// Определение 15.3 Многопутевое trie-дерево — это многопутевое дерево, имеющее связанные с каждым из его листьев ключи, которое рекурсивно определяется следующим образом:
		// - trie - дерево для пустого набора ключей представляет собой нулевую связь;
		// - trie -дерево для единственного ключа — лист, содержащий этот ключ;
		// - trie - дерево для набора ключей, количество которых значительно превышает 1 - внутренний узел со связями, ссылающимися на trie - деревья для ключей с каждым из возможных значений цифр, причем для конструирования поддеревьев ведущая цифра должна удаляться.
		// Лемма 15.6. Для выполнения поиска или вставки в стандартном R - арном trie - дереве в среднем требуется выполнение приблизительно log_R(N) сравнений байтов в дереве, построенном из N случайных строк байтов.
		// Количество связей в R - арном trie - дереве, построенном из N случайных ключей, приблизительно равно R*N /(ln(R)).
		// Количество сравнений байтов, необходимое для выполнения поиска или сравнения, не превышает количества байтов в искомом ключе.
		// В остальной части этого раздела рассматривается альтернативное представление trie - деревьев, построенных программой 15.7:
		// trie - дерево тернарного поиска(ternary search trie — TST), или просто TST-дерево.
		// Продолжая использовать соответствие между деревьями поиска и алгоритмами сортировки, мы видим, что TST - деревья соответствуют трехпутевой сортировке, точно так же как BST - деревья соответствуют быстрой сортировке, trie - деревья — бинарной быстрой сортировке, а М - путевые trie - деревья — М - путевой сортировке.
		// Это код реализует те же алгоритмы абстрактного trie-дерева, что и в программе 15.7, но каждый узел содержит одну цифру и три связи:
		// по одной для ключей, следующая цифра которых меньше, равна и больше соответствующей цифры в искомом ключе.
		// Лемма 15.7 Для выполнения поиска или вставки в полное TST - дерево требуется время, пропорциональное длине ключа.
		// Количество связей в TST - дереве превышает количество символов во всех ключах не более чем в три раза.
		// Главное достоинство использования TST-деревьев заключается в том, что они легко приспосабливаются к неоднородностям в ключах, возникновение которых весьма вероятно в реальных приложениях.
		// Это является следствием двух основных эффектов.
		// Во-первых, ключи в реальных приложениях образуются из больших наборов символов, а использование конкретных символов в наборах далеко от однородного - например, в конкретном наборе строк, скорее всего, будет использоваться только небольшая часть возможных символов.
		// Во-вторых, ключи в практических приложениях часто имеют  структурированный формат, различающийся от приложения к приложению, когда в одной части ключа используются только буквы, в другой - только цифры, а специальные символы служат разделителями.
		// Второе практическое преимущество поиска, основанного на TST-деревьях, по сравнению со множеством других алгоритмов заключается в том, что обнаружение промахов при поиске, скорее всего, будет исключительно эффективным даже при длинных ключах.
		// Третья причина привлекательности TST-деревьев заключается в том, что они поддерживают более общие операции, нежели рассмотренные операции таблиц символов.
		// Еще одно простое усовершенствование поиска, основанного на использовании TST-деревьев, - использование большого явного многопутевого узла в корне.
		// Для этого проще всего хранить таблицу R TST - деревьев: по одному для каждого возможного значения первой буквы в ключах.
		// Лемма 15.8 Для выполнения поиска или вставки в TST-дереве, содержащем элементы в листьях(т.е., не имеющем ни одной однопутевой ветви в нижней части дерева) и R^t - путевые ветви в корне, требуется приблизительно ln(N) — t*ln(R) обращений к байтам для N ключей, которые являются случайными строками байтов.
		// При этом количество требуемых связей равно R^t (для корневого узла) плюс небольшое постоянное число, кратное N.
		// Причины, по которым при использовании строковых ключей TST - деревья предпочтительнее стандартных BST - деревьев, таковы:
		// - они обеспечивают быстрое обнаружение промаха при поиске;
		// - они непосредственно приспособлены для многопутевого ветвления в корне;
		// - и (что наиболее важно) они хорошо подходят для ключей в виде строк байтов, не являющихся случайными, поэтому длина поиска не превышает длину ключа в TST - дереве.
		// Вероятно, наиболее важное свойство trie - деревьев или TST - деревьев с записями в листьях заключается в том, что их характеристики производительности не зависят от длины ключа.
		// Следовательно, их можно использовать для ключей произвольной длины.

		// 15.5 Алгоритмы индексирования текстовых строк
		// Дерево поиска, которое построено из ключей, определенных строковыми указателями внутри текстовой строки, называется деревом суффиксов.
		// Чтобы использовать TST-деревья для построения строкового индекса, необходимо удалить код, обрабатывающий конечные части ключей в структуре данных, поскольку ни одна строка не является префиксом другой и, следовательно, никогда не придется сравнивать строки вплоть до их конечных символов.
		// Эта модификация включает в себя изменение определения operator== в интерфейсе типа элемента, чтобы две строки считались равными, если одна из них - префикс другой, как это было сделано в разделе 12.7, поскольку мы будем сравнивать ключ поиска(короткий) с текстовой строкой(длинной), начиная с некоторой позиции текстовой строки.
		// Третье удобное изменение — хранение в каждом узле строковых указателей, а не символов, чтобы каждый узел в дереве ссылался на позицию в текстовой строке(позицию, следующую за первым вхождением строки, определенной символами в равных ветвях от корня до этого узла).
		// Несмотря на все описанные преимущества, имеется одно важное обстоятельство, которым мы пренебрегли при рассмотрении использования BST - деревьев, patricia - деревьев или TST - деревьев для типичных приложений индексирования текста:
		// сам по себе текст фиксирован, поэтому нет необходимости поддерживать динамические операции insert, как мы привыкли это делать.
		// Базовый алгоритм, подходящий в данной ситуации — бинарный поиск с использованием строковых указателей
		// Индекс — это набор строковых указателей; построение индекса — это сортировка строковых указателей.
		// Основное преимущество использования бинарного поиска по сравнению с динамическими структурами данных заключается в экономии используемого объема памяти.
	}
}