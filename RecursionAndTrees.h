﻿#pragma once

namespace nsDataStructures
{
	// Рекурсия и деревья
	namespace nsRecursionAndTrees
	{
		void main();

		// Программа 5.1 Функция вычисления факториала(рекурсивная реализация)
		int factorial1(int N);
		int factorial2(int N);

		// Программа 5.2 Сомнительная рекурсивная программа
		int puzzle(int N);

		// Программа 5.3 Алгоритм Эвклида
		int gcd(int m, int n);

		// Программа 5.4 Рекурсивная программа для оценки префиксных выражений
		int eval();

		// Программа 5.6 Применение алгоритма "разделяй и властвуй" для отыскания максимума
		template<typename Item>
		Item max(Item a[], int l, int r)
		{
			if (l == r)
				return a[l];
			int m = (l + r) / 2;
			Item u = max(a, l, m);
			Item v = max(a, m + 1, r);
			If(u > v) return u;
			else return v;
		}

		// Программа 5.7 Решение задачи о ханойских башнях
		void hanoi(int N, int d);

		// Программа 5.8 Применение алгоритма "разделяй и властвуй" для рисования линейки
		void rule(int l, int r, int h);

		// Программа 5.9 Не рекурсивная программа для рисования линейки
		void rule1(int l, int r, int h);

		// Программа 5.10 Числа фибоначчи(рекурсивная реализация)
		int F(int i);

		// В языках программирования рекурсивной программой называют программу, которая обращается к самой себе(подобно тому, как в математике рекурсивной функцией называют функцию, которая определена через понятия самой этой функции).
		// Следовательно, вторая важная особенность рекурсивной программы — наличие условия завершения, позволяющего программе прекратить вызывать себя.
		
		// 5.1 Рекурсивные алгоритмы
		// Рекурсивный алгоритм — это алгоритм, решающий задачу путем решения одного или нескольких более узких вариантов той же задачи.
		// Желательно использовать рекурсивные программы, которые всегда вызывают себя с меньшими значениями аргументов.
		// базовые особенности рекурсивной программы : она вызывает саму себя(с меньшими значениями аргументов) и содержит условие завершения, при выполнении которого непосредственно вычисляет свое результирующее значение.
		// Дабы убедиться в правильности работы программы, можно применить метод математической индукции:
		// - Программа вычисляет 0! (исходное значение)
		// - Если допустить, что программа вычисляет k! для k < N(индуктивное предположение), то она вычисляет и N!.
		// В частности, если следовать правилам математической индукции, необходимо удостовериться, что создаваемые рекурсивные функции удовлетворяют двум основным условиям :
		// - Они должны явно решать задачу для исходного значения.
		// - В каждом рекурсивном вызове должны использоваться меньшие значения аргументов.
		// Программа 5.3 — компактная реализация алгоритма Евклида для отыскания наибольшего общего делителя для двух целых чисел.
		// Число t делит и х и у тогда, и только тогда, когда оно делит и у и х mod у(х по модулю у), поскольку x равно х mod у плюс число, кратное у.
		// В принципе, любой цикл for можно заменить эквивалентной рекурсивной программой.
		
		// 5.2 Разделяй и властвуй
		// Во множестве рассматриваемых в книге программ используется два рекурсивных вызова, каждый из которых работает приблизительно с половиной входных данных.
		// Эта рекурсивная схема - вероятно, наиболее важный случай хорошо известного метода "разделяй и властвуй" разработки алгоритмов, который служит основой для важнейших алгоритмов.
		// Как обычно, сам код предполагает проверку правильности вычисления методом индукции :
		// - Он явно и немедленно отыскивает максимальный элемент массива, размер которого равен 1.
		// - Для N > 1 код разделяет массив на два, размер каждого из которых меньше N, исходя из индуктивного предложения, находит максимальные элементы в обеих частях и возвращает большее из этих двух значений, которое должно быть максимальным значением для всего массива.
		// Лемма 5.1 Рекурсивная функция, которая разделяет задачу размерности N на две независимые(непустые) решающие ее части, рекурсивно вызывает себя менее N раз.
		// Лемма 5.2 Рекурсивный алгоритм "разделяй и властвуй" решения задачи о ханойских башнях дает решение, приводящее к 2N — 1 перемещениям.
		// Рекурсивно определенные геометрические узоры иногда называют фракталами.
		
		// 5.3 Динамическое программирование
		// Рекуррентное соотношение — это рекурсивная функция с целочисленными значениями.
		// Рассуждения, приведенные в предыдущем абзаце, подсказывают, что любую такую функцию можно приближенно вычислить, вычисляя все значения функции, начиная с наименьшего, используя на каждом шаге ранее вычисленные значения для подсчета текущего значения.
		// Эта технология называется восходящим динамическим программированием (battom-up dynamic programming).
		// 
	}
}
