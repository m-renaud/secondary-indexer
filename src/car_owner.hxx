#ifndef CAR_OWNER_HXX__
#define CAR_OWNER_HXX__

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

// A struct to represent the owners of a variety of cars.
struct car_owner
{
	car_owner() = default;
	car_owner(std::string const& o, std::string const& m)
	{
		std::strncpy(owner, o.c_str(), 20);
		std::strncpy(make, m.c_str(), 20);
	}

	char owner[20];
	char make[20];
};

// Allow car_owner's to be written to an ostream.
std::ostream& operator <<(std::ostream& os, car_owner const& co)
{
	return os << "  Owner: " << std::string(co.owner) << "\n"
	          << "  Make: " << std::string(co.make);
}

// Allow car_owner's to be read from an istream.
std::istream& operator >>(std::istream& is, car_owner& co)
{
	std::string o, m;
	is >> o >> m;
	std::strncpy(co.owner, o.c_str(), 20);
	std::strncpy(co.make, m.c_str(), 20);
	return is;
}


#endif // #ifndef CAR_OWNER_HXX__
