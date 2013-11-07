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
	car_owner(std::string const& o, std::string const& mk, std::string const& md)
	{
		std::strncpy(owner, o.c_str(), 20);
		std::strncpy(make, mk.c_str(), 20);
		std::strncpy(model, md.c_str(), 20);
	}

	char owner[20];
	char make[20];
	char model[20];
};

// Allow car_owner's to be written to an ostream.
std::ostream& operator <<(std::ostream& os, car_owner const& co)
{
	return os << "  Owner: " << std::string(co.owner) << "\n"
	          << "  Make:  " << std::string(co.make) << "\n"
	          << "  Model: " << std::string(co.model);
}

// Allow car_owner's to be read from an istream.
std::istream& operator >>(std::istream& is, car_owner& co)
{
	std::string o, mk, md;
	is >> o >> mk >> md;
	std::strncpy(co.owner, o.c_str(), 20);
	std::strncpy(co.make, mk.c_str(), 20);
	std::strncpy(co.model, md.c_str(), 20);
	return is;
}


#endif // #ifndef CAR_OWNER_HXX__
