#ifndef BINARY_FILE_HXX__
#define BINARY_FILE_HXX__

#include <iostream>
#include <fstream>
#include <string>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Provide an abstraction for reading, writing and modifying entries
// in a binary file.
template <typename FieldType>
class binary_file
{
public:
	binary_file() = default;

	binary_file(std::string fn, std::ios_base::openmode mode =
	            std::ios::binary | std::ios_base::in | std::ios_base::out)
		: _filename(fn), _file_handle(_filename, mode)
	{
	}

	template <typename... Args>
	void emplace_back(Args&&... args)
	{
		FieldType field(std::forward<Args>(args)...);
		_file_handle.seekp(0, std::ios_base::end);
		_file_handle.write(reinterpret_cast<char const*>(&field), sizeof(field));
	}

	template <typename Func>
	void operator() (std::size_t position, Func&& f)
	{
		FieldType field = (*this)[position];
		std::size_t file_pos = position * sizeof(field);

		f(field);

		_file_handle.seekp(file_pos);
		_file_handle.write(reinterpret_cast<char const*>(&field), sizeof(field));
	}

	FieldType operator [](std::size_t position)
	{
		FieldType field;
		std::size_t file_pos = position * sizeof(field);

		_file_handle.seekg(file_pos);
		_file_handle.read(reinterpret_cast<char*>(&field), sizeof(field));

		return field;
	}

private:
	std::string _filename;
	std::fstream _file_handle;
};


#endif // #ifndef BINARY_FILE_HXX__
