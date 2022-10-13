#include "pch.h"

TEST(heapTest, heapTest) {
	//Use heap to be able to get the maximum value of the collection in not much time (the front).
	std::vector<float> heap = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	EXPECT_FALSE(std::is_heap(begin(heap), end(heap)));
	std::make_heap(begin(heap), end(heap));
	EXPECT_TRUE(std::is_heap(begin(heap), end(heap)));

	EXPECT_EQ(heap, std::vector<float>({ 9, 8, 6, 7, 4, 5, 2, 0, 3, 1 }));

	std::vector<float> heap2 = heap;
	heap2.push_back(8.88);
	std::push_heap(begin(heap2), end(heap2));

	EXPECT_EQ(heap2, std::vector<float>({ 9, 8.88, 6, 7, 8, 5, 2, 0, 3, 1, 4 }));

	std::vector<float> heap3 = heap;
	std::pop_heap(begin(heap3), end(heap3));
	heap3.pop_back();
	EXPECT_EQ(heap3, std::vector<float>({ 8, 7, 6, 3, 4, 5, 2, 0, 1 }));

	std::vector<float> heap4 = heap;
	std::sort_heap(begin(heap4), end(heap4));
	EXPECT_EQ(heap4, std::vector<float>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));
	//is_heap_until
}


struct MockClass
{
	int x;
	int y;  // Does not participate in comparisons
};

bool operator<(const MockClass& lhs, const MockClass& rhs)
{
	return lhs.x < rhs.x;
}


// Shore of sorting
TEST(sortTest, sortTest) {
	std::vector<float> unsorted = { 8, 4, 5, 2, 6, 7, 1, 0, 3, 9 };
	EXPECT_EQ(std::is_sorted_until(begin(unsorted), end(unsorted)), begin(unsorted)+1);
	std::sort(begin(unsorted), end(unsorted));
	EXPECT_EQ(unsorted, std::vector<float>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

	EXPECT_EQ(std::is_sorted_until(begin(unsorted), end(unsorted)), end(unsorted));

	std::vector<float> unsorted2 = { 8, 4, 5, 2, 6, 7, 1, 0, 3, 9 };
	std::partial_sort(begin(unsorted2), begin(unsorted2)+5, end(unsorted2));
	if (unsorted2.size() >= 5) {
		unsorted2.resize(unsorted2.size() - 5);
	}
	EXPECT_EQ(std::is_sorted_until(begin(unsorted2), end(unsorted2)), begin(unsorted2) + 5);

	EXPECT_EQ(unsorted2, std::vector<float>({ 0, 1, 2, 3, 4 }));

	std::vector<float> unsorted3 = { 8, 4, 5, 2, 6, 7, 1, 0, 3, 9 };
	std::nth_element(begin(unsorted3), begin(unsorted3) + 5, end(unsorted3));
	EXPECT_EQ(*(begin(unsorted3) + 5), 5);
	
	std::vector<float> unsorted4 = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };
	std::inplace_merge(begin(unsorted4), begin(unsorted4) + 5, end(unsorted4));
	EXPECT_EQ(unsorted4, std::vector<float>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

	// Runes: modifications of algorithms
	std::vector<MockClass> mockVector = {
		{8,3},
		{0,3},
		{4,7},
		{0,2},
		{2,5},
		{0,1}
	};

	EXPECT_FALSE(std::is_sorted(begin(mockVector), end(mockVector)));
	std::stable_sort(begin(mockVector), end(mockVector));
	EXPECT_EQ(mockVector[0].y, 3);
	EXPECT_EQ(mockVector[1].y, 2);
	EXPECT_EQ(mockVector[2].y, 1);
	EXPECT_TRUE(std::is_sorted(begin(mockVector), end(mockVector)));
}

// Partitioning
TEST(partitionTest, partitionTest) {
	//to partition a collection is to look at it through a predicate (something that returns a boolean).
	std::vector<int> unpartitioned = { 2, 0, 3, 0, 0, 4, 0, 5, 0 };
	std::partition(begin(unpartitioned), end(unpartitioned), [](int i) {return i == 0; });
	std::vector<int> unpartitionedslice(begin(unpartitioned), begin(unpartitioned) + 5);
	EXPECT_EQ(unpartitionedslice, std::vector<int>({0,0,0,0,0}));

	std::vector<int>::iterator partitionPoint = std::partition_point(begin(unpartitioned), end(unpartitioned), [](int i) {return i == 0; });

	EXPECT_EQ(partitionPoint, begin(unpartitioned) + 5);

	std::vector<int> unpartitioned2{ 0, 0, 3, -1, 2, 4, 5, 0, 7 };
	EXPECT_FALSE(std::is_partitioned(begin(unpartitioned2), end(unpartitioned2), [](int n) {return n <= 0; }));
	std::stable_partition(begin(unpartitioned2), end(unpartitioned2), [](int n) {return n <= 0; });
	EXPECT_TRUE(std::is_partitioned(begin(unpartitioned2), end(unpartitioned2), [](int n) {return n <= 0; }));

	EXPECT_EQ(unpartitioned2, std::vector<int>({ 0, 0, -1, 0, 3, 2, 4, 5, 7 }));
	//is_partitioned_until
}

//Lands of permutation
#include <random>
TEST(permutationTest, permutationTest) {
	std::vector<int> unpermuted = { 8, 4, 5, 2, 6, 7, 1, 0, 3, 9 };
	std::rotate(begin(unpermuted), begin(unpermuted) + 1, end(unpermuted));
	EXPECT_EQ(unpermuted, std::vector<int>({ 4, 5, 2, 6, 7, 1, 0, 3, 9, 8 }));
	std::rotate(rbegin(unpermuted), rbegin(unpermuted) + 2, rend(unpermuted));
	EXPECT_EQ(unpermuted, std::vector<int>({ 9, 8, 4, 5, 2, 6, 7, 1, 0, 3 }));
	std::rotate(begin(unpermuted), begin(unpermuted) + 1, end(unpermuted));

	std::shuffle(begin(unpermuted), end(unpermuted), std::default_random_engine(0));
	EXPECT_EQ(unpermuted, std::vector<int>({ 6, 3, 1, 0, 5, 2, 4, 9, 7, 8 }));

	std::sort(begin(unpermuted), end(unpermuted));

	// Interesting if you'd like to do something for every possible arrangement of a collection
	std::next_permutation(begin(unpermuted), end(unpermuted));
	EXPECT_EQ(unpermuted, std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 9, 8 }));
	std::prev_permutation(begin(unpermuted), end(unpermuted));
	EXPECT_EQ(unpermuted, std::vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));
	std::reverse(begin(unpermuted), end(unpermuted));
	EXPECT_EQ(unpermuted, std::vector<int>({ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }));
}

//Numerical algorithms
#include <numeric>
TEST(numericalTest, numericalTest) {
	std::vector<int> numericals = { 0, 0, 3, -1, 2, 4, 5, 0, 7 };
	EXPECT_EQ(std::count(begin(numericals), end(numericals), 0), 3);
	// If left to type inference, op operates on values of the same type as init which can result in
	//unwanted casting of the iterator elements. For example, std::accumulate(v.begin(), v.end(), 0)
	//likely does not give the result one wishes for when v is std::vector<double>.
	EXPECT_EQ(std::accumulate(begin(numericals), end(numericals),0), 20);
	EXPECT_EQ(std::transform_reduce(begin(numericals), end(numericals), 0, std::plus{}, [](auto val) { return ++val; }), 29);
	std::partial_sum(begin(numericals), end(numericals), begin(numericals));
	EXPECT_EQ(numericals, std::vector<int>({ 0, 0, 3, 2, 4, 8, 13, 13, 20 }));
	std::exclusive_scan(begin(numericals), end(numericals), begin(numericals),1);
	EXPECT_EQ(numericals, std::vector<int>({ 1, 1, 1, 4, 6, 10, 18, 31, 44 }));

	std::vector<int> otherNumericals = { 2, 4, 6, 8, 10, 12, 14, 16, 18 };
	
	EXPECT_EQ(std::inner_product(begin(numericals), end(numericals), begin(otherNumericals), 0), 1764);

}

