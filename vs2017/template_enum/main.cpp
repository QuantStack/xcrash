#include <iostream>

// This code compiles fine with VS 2015, gcc (from 4.9 to 7) and clang (from 3.6 to 6.0)
enum class layout_type
{
	row_major,
	column_major
};

template <class T, layout_type L>
struct xiterator
{
	using value_type = T;
	using const layout_type layout = L;
};

template <class T>
struct xconst_iterable
{
	template <layout_type L>
	using layout_iterator = xiterator<T, L>;
};

template <class T>
struct xiterable : private xconst_iterable<T>
{
	using base_type = xconst_iterable<T>;

	template <layout_type L>
	using layout_iterator = typename base_type::template layout_iterator<L>;
};

int main(int argc, char* argv[])
{
	using iter_type = xiterable<double>::layout_iterator<layout_type::row_major>;
	return 0;
}