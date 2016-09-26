﻿#pragma once

namespace nsDataStructures
{
	// Элементарные структуры данных
	namespace nsElementaryDataStructures
	{
		void main();

		// Программа 3.1 Описание функций
		void program1();
		int lg(int);

		// Программа 3.2 Типы чисел
		void program2();
		typedef int Number;
		Number randNum();

		// Программа 3.3 Интерфейс типа данных point
		struct point
		{
			float x;
			float у;
		};
		float distance(point, point);

		void polar(float x, float у, float *r, float *theta);

		// Программа 3.5 Решето Эратосфена
		void program5();

		// Программа 3.7 Имитация подбрасываний монеты
		void program7();
		int heads();

		// Программа 3.8 Вычисление ближайшей точки
		void program8();
		float randFloat();

		template<typename Item>
		struct node
		{ 
			Item item;
			node *next;

			node(Item x, node* t)
			{
				item = x;
				next = t;
			}
		};
		template<typename T>
		using link = node<T>*;
		
		void testList();

		// Программа 3.9 Пример циклического списка(задача Иосифа)
		void program9();

		// Программа 3.10 Обращение порядка следования элементов списка
		link<int> program10(link<int> x);

		// Программа 3.11 Сортировка методом вставки в список
		void program11();

		// Программа 3.13 Организация списка для задачи Иосифа
		void program13();

		// Программа 3.15 Поиск строки
		void program15();

		// Массивы, строки, связные списки и деревья служат базовыми элементами большинства алгоритмов.
		
		// 3.1 Строительные блоки
		// Определение 3.1 Тип данных — это множество значений и набор операций с ними.
		// Третий метод рекомендован и широко распространен в программировании на С, C++ и других языках.Он предусматривает разбиение программы на три файла:
		// - Интерфейс, где определяется структура данных и объявляются функции, используемые для управления этой структурой
		// - Реализация функций, объявленных в интерфейсе
		// - Клиентская программа, которая использует функции, объявленные в интерфейсе, для реализации более высокого уровня абстракции
		// Простейшим механизмом группировки данных в C++ являются массивы(arrays) и структуры(structures).
		
		// 3.2 Массивы 

		// 3.3 Связные списки
		// Основное преимущество связных списков перед массивами заключается в возможности эффективного изменения расположения элементов. 
		// За эту гибкость приходится жертвовать скоростью доступа к произвольному элементу списка, поскольку единственный способ получения элемента состоит в отслеживании связей от начала списка.
		// Определение 3.2 Связный список — это набор элементов, причем каждый из них является частью узла(node), который также содержит ссылку(link) на узел.
		// Чаще всего приходится иметь дело со списками, соответствующими простому последовательному расположению элементов, принимая одно из следующих соглашений для ссылки последнего узла:
		// - Это пустая (null) ссылка, не указывающая на какой-либо узел.
		// - Ссылка указывает на фиктивный узел (dummy node), который не содержит элементов.
		// - Ссылка указывает на первый узел, что делает список циклическим.

		// 3.4 Обработка простых списков
		// Определение 3.3 Связный список содержит либо null-ссылки, либо ссылки на узлы, которые содержат элемент и ссылку на связный список.
		// обход списка (traverse).
		// for (link t = х; t •= 0; t = t->next) visit(t->item);
		// Главная причина использования ведущего узла становится понятной, если рассмотреть процесс добавления первого узла к сортированному списку.
		// Этот узел имеет наименьший элемент в списке ввода и может находиться в любом месте списка.
		// Существуют три возможности :
		// - Дублировать цикл for, который обнаруживает наименьший элемент и создает список из одного узла таким же образом, как в программе 3.9.
		// - Перед каждой вставкой узла проверять, не является ли список вывода пустым.
		// - Использовать фиктивный ведущий узел, ссылка которого указывает на первый узел списка, как в данном примере.

		// 3.5 Распределение памяти под списки
		// Динамическое распределение памяти(dynamic memory allocation) — это процесс управления памятью и ответных действий на вызов операторов new и delete из клиентских программ.

		// 3.6 Строки
		
		// 3.7 Составные структуры данных 
		// 116...


		// !!!
		// Порешать задачки из 3.4, 3.5!!!
	}
}
