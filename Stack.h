#pragma once

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.4 Интерфейс абстрактного типа данных стека
		template <class Item>
		class Stack
		{
		public:
			Stack(int);
			int empty() const;
			void push(Item item);
			Item pop();

		private:
			// программный код, зависящий от реализации 
		};
	}
}
