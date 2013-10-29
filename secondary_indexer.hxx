#ifndef SECONDARY_INDEXER_HXX__
#define SECONDARY_INDEXER_HXX__

#include "key_entry.hxx"
#include "secondary_key_table.hxx"
#include "binary_file.hxx"

#include <vector>
#include <map>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Generate a secondary key table and primary key file given two input
// iterators and the field to use for indexing.
//
// The field to use for indexing is given as a pointer to member.
//
// Input:  - [begin, end) iterator range.
//         - Filename to save the primary key to.
//         - Field to use for the secondary key.
//
// Output: - Secondary key table :: secondary_key_table<
//
template <
	typename InterpretedSKT,
	typename Iter,
	typename SecondaryKeyType,
	typename Data = typename Iter::value_type
>
auto generate_secondary_index(
	Iter begin, Iter end,
	std::string filename,
	SecondaryKeyType Data::*sk_field)
	-> secondary_key_table<InterpretedSKT>
{
	std::map<InterpretedSKT, int> secondary_index;
	std::map<InterpretedSKT, int> last_position;
	binary_file< key_entry<Data> > pk_file(
		filename,
		std::ios_base::binary | std::ios_base::in
		| std::ios_base::out | std::ios_base::trunc
	);

	int current_RRN = 0;

	for (; begin != end; ++begin)
	{
		std::cout << *begin << std::endl;
		auto skt_iter = secondary_index.find(InterpretedSKT((*begin).*sk_field));
		if (skt_iter == secondary_index.end())
			secondary_index[(*begin).*sk_field] = current_RRN;

		pk_file.emplace_back((*begin), -1);

		auto lpi = last_position.find((*begin).*sk_field);
		if (lpi != last_position.end())
		{
			pk_file(
				lpi->second,
				[&](key_entry<Data>& field)
				{
					field.set_next_RRN(current_RRN);
				}
			);
		}

		last_position[(*begin).*sk_field] = current_RRN;

		++current_RRN;
	}

	return secondary_key_table<InterpretedSKT>(std::move(secondary_index), filename);
}

#endif // #ifndef SECONDARY_INDEXER_HXX__
