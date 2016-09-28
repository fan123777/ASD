#pragma once

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.9 Интерфейс АТД "Отношения эквивалентности"
		class UnionFind
		{
		public:
			UnionFind(int);
			~UnionFind();
			int find(int, int);
			void unite(int, int);
		private:
			// программный код, зависящий от реализации 
		};
	}
}
