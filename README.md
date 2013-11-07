# Secondary Indexer

This repository contains code to perform automatic secondary indexing
on any POD with a simple and easy to use interface.

# Requirements

- CMake
- C++11 Compiler

# Usage

To use the secondary indexer, the only thing that needs to be done is
create a structure to represent a tuple, define an input (<<) and
output (>>) operator for the structure, and call the
`generate_secondary_index` function.

## Defining the Data Structure

We will use the *car owner* example for demonstration here.

```cpp
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
```

Notice that we simply defined a default constructor and a constructor
that initializes all the `char[]` elements with `std::strncpy`.


### Defining the Input Operator

```cpp
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
```

### Defining the Output Operator

```cpp
    // Allow car_owner's to be written to an ostream.
    std::ostream& operator <<(std::ostream& os, car_owner const& co)
    {
    	return os << "  Owner: " << std::string(co.owner) << "\n"
    	          << "  Make:  " << std::string(co.make) << "\n"
    	          << "  Model: " << std::string(co.model);
    }
```

## Building the Secondary Index

See `build_car_owner_index.cxx`.

## Query the Secondary Index

See `query_car_owner_index.cxx`.
