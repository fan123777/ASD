﻿#pragma once

namespace nsSearch
{
	// Хеширование
	namespace nsHashing
	{
		void main();

		// Программа 14.1 Хеш - функция для дроковых ключей
		int hash(char *v, int M);

		// Программа 14.2 Универсальная хеш - функция(для строковых ключей)
		int hashU(char *v, int M);


		// В этой главе мы рассмотрим хеширование(hashing) — расширенный вариант поиска с использованием индексирования по ключу, применяемый в более типовых приложениях поиска, в которых не приходится рассчитывать на наличие ключей со столь удобными свойствами.
		// Алгоритмы поиска, которые используют хеширование, состоят из двух отдельных частей.Первый шаг — вычисление хеш - функции, которая преобразует ключ поиска в адрес в таблице.
		// В идеале различные ключи должны были бы отображаться на различные адреса, но часто два и более различных ключа могут преобразовываться в один и тот же адрес в таблице.
		// Поэтому вторая часть поиска методом хеширования — процесс разрешения конфликтов, который обрабатывает такие ключи.
		// Хеширование — хороший пример компромисса между временем и объемом памяти.
		// Это ожидаемое постоянное время выполнения — теоретический оптимум производительности для любой реализации таблицы символов, но хеширование не является панацеей по двум основным причинам.
		// Во - первых, время выполнения зависит от длины ключа, которая может быть значительной в реальных приложениях, использующих длинные ключи.
		// Во - вторых, хеширование не обеспечивает эффективные реализации для других операций, таких как select или sort, с таблицами символов.

		// 14.1 Хеш-функции
		// При наличии таблицы, которая может содержать М элементов, нам требуется функция, которая преобразует ключи в целые числа в диапазоне[О, М— 1].
		// Идеальную хешфункцию легко вычислить и аппроксимировать случайной функцией: для любого вводимого значения в определенном смысле выводимое значение должно быть равновероятным.
		// Строго говоря, для каждого вида ключей, который может использоваться, требуется отдельная хеш - функция.
		// Вероятно, простейшей является ситуация, когда ключами являются числа с плавающей точкой, заведомо относящиеся к фиксированному диапазону.
		// Например, если ключи — числа, которые больше 0 и меньше 1, их можно просто умножить на М, округлить до ближайшего целого числа и получить адрес в диапазоне между 0 и М— 1;
		// Если ключи больше s и меньше t, их можно масштабировать, вычтя s и разделив на t — s, в результате чего они попадут в диапазон значений между 0 и 1, а затем умножить на М для получения адреса в таблице.
		// Такие функции бесполезны для хеширования, если только ключи не распределены по диапазону равномерно, поскольку хешзначение определяется только ведущими цифрами ключа.
		// Более простой и эффективный метод для w-разрядных целых чисел — один из, вероятно, наиболее часто используемых методов хеширования — выбор в качестве размера М таблицы простого числа и вычисление остатка от деления k на M, или h(k) = k mod M для любого целочисленного ключа k.
		// Такая функция называется модульной хеш - функцией.
		// Модульное хеширование применяется во всех случаях, когда имеется доступ к разрядам, образующим ключи, независимо от того, являются ли они целыми числами, представленными машинным словом, последовательностью символов, упакованных в машинное слово, или представлены одним из множества других возможных вариантов.
		// Модульное хеширование весьма просто реализовать, за исключением того, что размер таблицы необходимо определить простым числом.
		// Возможность ценой небольших затрат придать реальным ключам случайный вид приводит к рассмотрению рандомизованных алгоритмов хеширования — нам требуются хеш - функции, которые создают случайные индексы таблицы независимо от существующих ключей.
		// Еще более эффективный подход использование случайных значений коэффициентов в вычислении и другого случайного значения для каждой цифры ключа.
		// Такой подход дает рандомизованный алгоритм, называемый универсальным хешированием.
		// Теоретически идеальная универсальная хеш-функция — это функция, для которой вероятность конфликта между двумя различными ключами в таблице размером М равна в точности 1/M.
		// Подведем итоги : чтобы использовать хеширование для реализации абстрактной таблицы символов, в качестве первого шага необходимо расширить интерфейс абстрактного типа, включив в него операции hash, которая отображает ключи на неотрицательные целые числа, меньше размера таблицы М.
		// ---
		// inline int hash (Key v, int M) 
		// { return (int)M*(v - s) / (t - s); }
		// ---
		// (int) (.616161 * (float) v) % М
		// ---
		// (6161 * (unsigned) v) % М 
		// Все эти функции, включая программу 14.1, работающую со строковыми ключами, проверены временем; они равномерно распределяют ключи и служат программистам в течение многих лет.
		// Универсальный метод, предртавленный в программе 14.2 — заметное усовершенствование для строковых ключей, которое обеспечивает случайные хеш - значения при небольших затратах; аналогичные рандомизованные методы можно применить к целочисленным ключам.
		// Несмотря на очевидные преимущества рассмотренных методов, их реализация требует внимания по двум причинам.
		// Во-первых, необходимо быть внимательным во избежание ошибок при преобразовании типов и использовании арифметических функций применительно к различным машинным представлениям ключей.
		// Во-вторых, весьма вероятно, что во многих приложениях вычисление хеш - функции будет выполняться во внутреннем цикле и время ее выполнения может в значительной степени определять общее время выполнения.
		// Наиболее быстрый метод для многих компьютеров — сделать М степенью 2 и воспользоваться хеш - функцией
		// inline int hash(Key v, int M)
		// {
		//	 return v & (M - l);
		// }

		// 14.2 Раздельное связывание
		// второй компонент алгоритма хеширования — определения способа обработки случая, когда два ключа представляются одним и тем же адресом.
		// Самый прямой метод — построить для каждого адреса таблицы связный список элементов, ключи которых отображаются на этот адрес.
		// Лемма 14.1 Раздельное связывание уменьшает количество выполняемых при последовательном поиске сравнений в М раз(в среднем) при использовании дополнительного объема памяти для М связей.
		// Лемма 14.2 В хеш-таблице, использующей раздельное связывание, содержащей М списков и N ключей, вероятность того, что количество ключей в каждом списке незначительно отличается от N / M, очень близка к 1.
		// Приведенный анализ — пример классической задачи занятости, при которой рассматривается N мячей, произвольно забрасываемых в одну из М корзин, и анализируется распределение мячей по корзинам.
		// Когда объем памяти не является критичным, значение М может быть выбрано достаточно большим, чтобы время поиска было постоянным; когда же объем памяти критичен, все же можно повысить производительность в М раз, выбрав значение М максимально допустимым.
		// В общем случае хеширование не подходит для использования в приложениях, в которых требуются реализации операций sort и select для АТД.
		// Однако хеширование часто используется в типовых ситуациях, когда необходимо использовать таблицу символов с потенциально большим количеством операций search, insert и remove с последующим однократным выводом элементов в порядке их ключей.
		
		// 14.3 Линейное зондирование 
		// Существует несколько методов хранения N элементов в таблице размером М > N, при которых разрешение конфликтов основывается на наличии пустых мест в таблице.
		// Такие методы называются методами хеширования с открытой адресацией.
		// Простейший метод открытой адресации называется линейным зондированием (linear probing):
		// при наличии конфликта(когда хеширование выполняется в место таблицы, которое уже занято элементом с ключом, не совпадающим с ключом поиска) мы просто проверяем следующую позицию в таблице.
		// Обычно подобную проверку(определяющую, содержит ли данная позиция таблицы элемент с ключом, равным ключу поиска) называют зондированием(probe).
		// Линейное зондирование характеризуется выявлением одного из трех возможных исходов зондирования:
		// если позиция таблицы содержит элемент, ключ которого совпадает с искомым, имеет место попадание при поиске; в противном случае(если позиция таблицы содержит элемент, ключ которого не совпадает с искомым) мы просто зондируем позицию таблицы со следующим по величине индексом, продолжая этот процесс(возвращаясь к началу таблицы при достижении ее конца) до тех пор, пока не будет найден искомый ключ или пустая позиция таблицы.
		// Если содержащий искомый ключ элемент должен быть вставлен вслед за неудачным поиском, он помещается в пустую область таблицы, в которой поиск был завершен.
		// Как и в случае раздельного связывания, производительность методов с открытой адресацией зависит от коэффициента а = N / M, но при этом он интерпретируется иначе.
		// Иногда а называют коэффициентом загрузки хеш - таблицы.
		// При использовании линейного зондирования размер таблицы больше, чем при раздельном связывании, поэтому необходимо, чтобы М > N, но общий используемый объем памяти может быть меньше, поскольку никаких связей не используется.
		// Средние затраты на выполнение линейного зондирования зависят от способа объединения элементов в непрерывные группы занятых ячеек таблицы, называемые кластерами(clusters), при их вставке.
		// Лемма 14.3 При разрешении конфликтов с помощью линейного зондирования среднее количество зондирований, требуемых для поиска в хеш - таблице размером М, которая содержит N = аМ ключей, приблизительно равно
		// 1/2 * (1 + 1 / (1-a)) и 1/2 * (1 + 1/((1-a)^2))
		// для попаданий и промахов, соответственно.
		// А как удалить ключ из таблицы, построенной с помощью линейного зондирования?
		
		// 14.4 Двойное хеширование 
		// Хуже того, вставка ключа с одним хеш - значением может существенно увеличить время поиска ключей с другими хеш - значениями:
		// вставка ключа М приводит к увеличению времени поиска. Это явление называется кластеризацией, поскольку оно связано с процессом образования кластеров.
		// Оно может значительно замедлять линейное зондирование для почти заполненных таблиц.
		// К счастью, существует простой способ избежать возникновения проблемы кластеризации — двойное хеширование.
		// Основная стратегия остается той же, что и при выполнении линейного зондирования.
		// Единственное различие состоит в том, что вместо исследования каждой позиции таблицы, следующей за конфликтной, мы используем вторую хеш - функцию для получения постоянного шага, который будет использоваться для последовательности зондирования.
		// Лемма 14.4 При разрешении конфликтов с помощью двойного хеширования среднее количество зондирований, необходимых для выполнения поиска в хеш - таблице размером М, содержащей N = аМ ключей, равно
		// (1/a)*ln(1/(1 - a)) и 1/(1-a)
		// для обнаружения попаданий и промахов, соответственно. 
		// Лемма 14.5 Сохраняя коэффициент загрузки меньшим, чем 1 - 1/sqrt(t) для линейного зондирования, и меньшим, чем 1 - 1/t для двойного хеширования, можно обеспе чить, чтобы в среднем для выполнения всех поисков требовалось менее t зондирований.
		// Подобно линейному зондированию, двойное хеширование — неподходящее основание для реализации полнофункционального АТД таблицы символов, в котором необходимо поддерживать операции sort или select.

		// Динамические хеш-таблицы
		// Один из способов обеспечения роста в хеш-таблицах — удвоение размера таблицы, когда она начинает заполняться.
		// При каждом удвоении размера таблицы для всех ключей выполняется повторное хеширование и повторная вставка.
		// Все вставки выполняются в разреженные таблицы(менее чем на одну четверть для повторной вставки и от одной четверти до одной второй в остальных случаях), поэтому возникает мало конфликтов.
		// Эту же концепцию можно выразить, говоря, что затраты на одну вставку меньше четырех зондирований.
		// Если требуется поддерживать операцию remove абстрактного типа данных, может иметь смысл сужать таблицу, вдвое уменьшая ее размер при уменьшении количества ее ключей.
		// Но это требует одной оговорки: порог сужения должен отличаться от порога увеличения, поскольку в противном случае небольшое количество операций insert и remove могло бы приводить к последовательности операций удвоения и уменьшения размера вдвое даже для очень больших таблиц.
		// Лемма 14.6 Последовательность операций search, insert и delete в таблицах символов может быть выполнена за время, которое пропорционально t, и при использовании объема памяти, не превышающего числа ключей в таблице, умноженного на постоянный коэффициент.
		// Этот метод подходит для использования в реализации таблицы символов, предназначенной для библиотеки общего назначения, когда последовательности применения операций непредсказуемы, поскольку позволяет приемлемым образом обрабатывать таблицы любых размеров.
		// Основной его недостаток — затраты на повторное хеширование и распределение памяти при расширении и сжатии таблицы.
		// В типичном случае, когда основными выполняемыми операциями являются операции поиска, гарантия малого заполнения таблицы обеспечивает прекрасную производительность.
		
		// 14.6 Перспективы
		// Обобщая, можно охарактеризовать три основных метода (линейное зондирование, двойное хеширование и раздельное связывание) следующим образом:
		// Линейное зондирование является самым быстрым из этих трех методов(при наличии достаточного объема памяти, чтобы таблица была разреженной), двойное хеширование позволяет наиболее эффективно использовать память(но требует дополнительных затрат времени для вычисления второй хеш - функции), а раздельное связывание проще всего реализовать и применять(при условии наличия хорошего средства распределения памяти).
		// Один класс методов перемещает элементы во время вставки при двойном хешировании, делая успешный поиск более эффективным.
		// Так, Брент(Brent) разработал метод, при использовании которого среднее время успешного поиска может ограничиваться константой даже в заполненной таблице.
		// Такой метод может быть удобным в приложениях, в которых попадания при поиске — основная операция.
		// Другой метод, называемый упорядоченным хешированием (ordered hashing), использует упорядочение для уменьшения затрат на безрезультатный поиск при использовании линейного зондирования, приближая их к затратам на успешный поиск.
		// Этот метод предназначен для приложений, в которых преобладают промахи при поиске.
		// Таблица символов, в которой быстро происходит обнаружение промахов при поиске и несколько медленнее — попаданий при поиске, может использоваться для реализации словаря исключений(exception dictionary).
		// В качестве реализации таблиц символов хеширование предпочтительней структур бинарных деревьев, рассмотренных в главах 12 и 13, поскольку оно несколько проще и может обеспечить оптимальное(постоянное) время поиска, если ключи относятся к стандартному типу или достаточно просты, чтобы можно было быть уверенным в разработке хорошей хеш - функции для них.
		// Преимущества структур бинарных деревьев по сравнению с хешированием заключается в том, что
		// - деревья основываются на более простом абстрактном интерфейсе(разработка хеш-функции не требуется);
		// - деревья являются динамическими (никакая предварительная информация о количестве вставок не требуется);
		// - деревья могут обеспечить гарантированную производительность в худшем случае(все элементы могут быть помещены в одну и ту же позицию даже при использовании наилучшего метода хеширования);
		// - деревья поддерживают более широкий диапазон операций(самое главное, операции sort и select).
		// Когда эти факторы не имеют значения, безусловно следует выбирать хеширование, только с одной важной оговоркой : когда ключи представляют собой длинные строки, их можно встроить в структуры данных, которые могут обеспечить методы поиска, работающие еще быстрее хеширования.
	}
}
