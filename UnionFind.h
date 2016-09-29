#pragma once

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.12 Абстрактный класс для АТД отношения эквивалетности
		class uf
		{
		public:
			uf(int);
			virtual int find(int, int) = 0;
			virtual void unite(int, int) = 0;
		};

		// Программа 4.9 Интерфейс АТД "Отношения эквивалентности"
		class UnionFind
		{
		public:
			UnionFind(int N);
			~UnionFind();
			int find(int p, int q);
			void unite(int p, int q);

		private:
			int *id, *sz;
			int find(int x);
		};
	}
}
