#include <iostream>
#include <fstream>

#include "car_owner.hxx"
#include "secondary_key_table.hxx"

// Read the contents of the primary key file and allow iteration based
// on secondary key selected.
int main(int argc, char* argv[])
{
	// Check command line arguments.
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <seconary_key_file> <primary_key_file>\n";
		return 1;
	}

	// Construct a key table and load the secondary key file.
	secondary_key_table<std::string> key_table;

	key_table.load(std::string(argv[1]));
	key_table.set_pk_filename(std::string(argv[2]));

	// Display greeting.
	std::cout << "Welcome to secondary file query processor.\n"
	          << "  Key Table: " << argv[1] << "\n"
	          << "  Key File:  " << argv[2] << "\n\n";

	// Read a secondary key and print all records with that as the secondary key.
	std::string key;
	std::cout << "Query> ";

	while (std::cin >> key)
	{
		secondary_key_iterator<car_owner> i = key_table.find<car_owner>(key);
		secondary_key_iterator<car_owner> end;
		if (i == end)
			std::cout << "No entries with secondary key " << key << ".\n";
		else
			for (; i != secondary_key_iterator<>(); ++i)
				std::cout << "  --------\n" << *i << std::endl;

		std::cout << "\nQuery> ";
	}
}
