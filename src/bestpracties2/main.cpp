#include <iostream>
#include <memory>
#include <vector>
//#include "BenchMarkTest.h"

class CMoveClass
{
public:
	CMoveClass(const std::vector<int>&d):data(d){
		std::cout << "Contructor\n";
	}
	~CMoveClass(){}

	CMoveClass(const CMoveClass& source) {
		std::cout << "copy Contructor\n";
		data = source.data;
	}

	CMoveClass(CMoveClass&& source)noexcept :data(std::move(source.data)) {
		std::cout << "Move Contructor\n";
	}

	std::vector<int> data;
};

int main()
{
#ifdef TEST_MOVESEMANTIC_PERFORMANCE
	std::cout << std::endl;

	{
		std::array<int, SIZE / 1000> myArray;
		measurePerformance(myArray, "std::array<int,SIZE/1000>");
	}

	{
		std::vector<int> myVec(SIZE);
		measurePerformance(myVec, "std::vector<int>(SIZE)");
	}

	{
		std::deque<int>myDec(SIZE);
		measurePerformance(myDec, "std::deque<int>(SIZE)");
	}

	{
		std::list<int>myList(SIZE);
		measurePerformance(myList, "std::list<int>(SIZE)");
	}

	{
		std::forward_list<int>myForwardList(SIZE);
		measurePerformance(myForwardList, "std::forward_list<int>(SIZE)");
	}

	{
		std::string myString(SIZE, ' ');
		measurePerformance(myString, "std::string(SIZE,' ')");
	}

	std::vector<int> tmpVec(SIZE);
	std::iota(tmpVec.begin(), tmpVec.end(), 0);

	{
		std::set<int>mySet(tmpVec.begin(), tmpVec.end());
		measurePerformance(mySet, "std::set<int>");
	}

	{
		std::unordered_set<int>myUnorderedSet(tmpVec.begin(), tmpVec.end());
		measurePerformance(myUnorderedSet, "std::unordered_set<int>");
	}

	{
		std::map<int, int>myMap;
		for (auto i = 0; i <= SIZE; ++i) myMap[i] = i;
		measurePerformance(myMap, "std::map<int,int>");
	}

	{
		std::unordered_map<int, int>myUnorderedMap;
		for (auto i = 0; i <= SIZE; ++i) myUnorderedMap[i] = i;
		measurePerformance(myUnorderedMap, "std::unordered_map<int,int>");
	}

#endif // TEST_MOVESEMANTIC_PERFORMANCE

	std::vector<int> test(10000,0);
	CMoveClass test1(test);

	auto test2 = std::move(test1);

	system("Pause");
	return 0;
}
