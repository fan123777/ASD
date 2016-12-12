﻿#pragma once

namespace nsAlgorithmsOnGraphs
{
	// Орграфы и ориентированные ациклические графы 
	namespace nsDigraphsAndDirectedAcyclicGraph
	{
		void main();
		void test();

		// Если мы придаем значение, в каком порядке описываются две вершины каждого ребра графа, мы получаем совершенно другой комбинаторный объект, известный как ориентированный граф(directed graph), или орграф(digraph).
		// В орграфах обозначение s-t описывает ребро, которое ведет из вершины s в вершину t, но при этом оно не дает никакой информации о том, существует ли ребро, ведущее из t в s.
		// Имеется четыре вида отношений, в которых могут находиться две любые вершины орграфа:
		// связывающее их ребро отсутствует, ребро s - t, ведущее из s в t, ребро t - s, ведущее из t в s, и два ребра s - t и t - s, которые указывают на наличие связи в обоих направлениях.
		// работа с орграфами существенно отличается от работы с неориентированными графами.
		// В этом заключается суть проблемы, известной как задача составления расписаний (scheduling problem).
		// Она не имеет смысла, если в орграфе имеется цикл, в подобного рода ситуациях мы работаем с графами DAG(directed acyclic graph — ориентированный ациклический граф).
		
		// 19.1. Глоссарий и правила игры 
		// Определение 19.1. Ориентированный граф (или орграф) представляет собой некоторый набор вершин плюс некоторый набор ориентированных ребер, которые соединяют упорядоченные пары вершин(при этом дублированные ребра отсутствуют).
		// Мы говорим, что ребро направлено из первой вершины во вторую вершину.
		// Определение 19.2. Ориентированный путь (directed path) в орграфе есть список вершин, в котором имеется(ориентированное) ребро орграфа, соединяющее каждую вершину списка со следующим элементом этого списка.
		// Мы говорим, что вершина t достижима (reachable) из вершины s, если существует ориентированный путь из s в t.
		// Мы принимаем соглашение, согласно которому каждая вершина достижима сама из себя, и обычно реализуем это свойство за счет того, что в представление нашего орграфа включаем петли.
		// Что более важно, для орфафов и графов характерны существенные структурные различия.
		// Например, тот факт, что вершина t достижима из вершины s в орграфе, ничего не говорит о том, достижима ли s из t.
		// Полустепень захода (indegree) вершины орграфа есть число ориентированных ребер, которые ведут в эту вершину.
		// Полустепень исхода (outdegree) вершины орграфа есть число ориентированных ребер, которые исходят из этой вершины.
		// Ни одна из вершин орграфа не достижима из вершины с полустепенью исхода 0, эта вершина получила название сток(sink);
		// вершина с полустепенью захода 0 получила название исток(source), она не достижима ни из одной другой вершины орграфа.
		// Орграфы, в которых допускается существование петель и в которых каждая вершина обладает полустепенью исхода, равной 1, называется картой(mар) (отображение самого на себя множества целых чисел в диапазоне от 0 до V - 1).
		// Обращение (reverse) орграфа - это орграф, который мы получаем, поменяв ориентацию всех ребер орграфа на обратную.
		// Обратите внимание на тот факт, что путь s-t-s есть цикл длиной 2 в орграфе, в то время как цикл в неориентированном графе должен проходить через три различных вершины.
		// Определение 19.3. Ориентированный ациклический граф (directed acyclic graph), или граф DAG, — это орграф, не содержащий направленных циклов.
		// Неориентированный граф связен, если существует путь из каждой его вершины в любую другую вершину;
		// что касается орграфов, то мы модифицируем данное выше определение следующим образом:
		// Определение 19.4. Орграф называется сильно связным(strongly connected), если каждая его вершина достижима из любой другой вершины.
		// ...165 -> add getDagGraph.
	}
}
