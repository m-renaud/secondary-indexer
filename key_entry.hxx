#ifndef KEY_ENTRY_HXX__
#define KEY_ENTRY_HXX__

#include <utility>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Class to hold a primary key entry for the primary key file.
// Aggregate of the primary key and data associated with it as well as
// a field for the next relative record number.
template <typename T>
class key_entry
{
public:
	using value_type = T;

	key_entry() = default;
	key_entry(key_entry const&) = default;
	key_entry(key_entry&&) = default;

	key_entry& operator =(key_entry const&) = default;
	key_entry& operator =(key_entry&&) = default;

	~key_entry() = default;

	key_entry(T const& data, std::size_t nRRN)
		: _data(data), _nextRRN(nRRN)
	{
	}

	value_type const& get_data() const { return _data; }
	void set_data(T const& data) { _data = data; };
	void set_data(T&& data)      { _data = std::move(data); };

	int get_next_RRN() const { return _nextRRN; }
	void set_next_RRN(int rrn) { _nextRRN = rrn; }

private:
	value_type _data;
	int _nextRRN;
};

#endif // #ifndef KEY_ENTRY_HXX__
