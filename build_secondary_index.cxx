#include "secondary_indexer.hxx"
#include "car_owner.hxx"

#include <fstream>
#include <iterator>

// Build a secondary index given a list of structures in an input file.

int main()
{
	// Open the input file for reading.
	std::ifstream input("input.txt");

	// Generate a secondary key table from the input file.
	// Write the primary key table to "pk_file".
	// Use the "make" member in the car_owner struct as the secondary key.
	secondary_key_table<std::string> key_table =
		generate_secondary_index<std::string>(
			std::istream_iterator<car_owner>(input),
			std::istream_iterator<car_owner>(),
			"pk_file",
			&car_owner::make
		);

	// Save the secondary key table to the "key_table" file for reading later.
	key_table.save("key_table");
}
