#include "secondary_indexer.hxx"
#include "car_owner.hxx"

#include <fstream>
#include <iterator>
#include <string>

// Build a secondary index given a list of structures in an input file.

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0]
		          << " <input_file> <key_table_file> <primary_key_file>"
		          << std::endl;
		return 1;
	}

	std::string input_file = argv[1];
	std::string key_table_file = argv[2];
	std::string primary_key_file = argv[3];

	// Open the input file for reading.
	std::ifstream input(input_file);

	// Generate a secondary key table from the input file.
	// Write the primary key table to "pk_file".
	// Use the "make" member in the car_owner struct as the secondary key.
	secondary_key_table<std::string> key_table =
		generate_secondary_index<std::string>(
			std::istream_iterator<car_owner>(input),
			std::istream_iterator<car_owner>(),
			primary_key_file,
			&car_owner::make
		);

	// Save the secondary key table to the "key_table" file for reading later.
	key_table.save(key_table_file);
}
