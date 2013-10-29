#ifndef SECONDARY_KEY_ITERATOR_HXX__
#define SECONDARY_KEY_ITERATOR_HXX__

#include "binary_file.hxx"
#include "primary_key_entry.hxx"

#include <string>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Iterator to go through data based on secondary key index.
//
// Type Parameters:
//   Data: The data type being indexed.
//   SecondaryKeyType: The type being used as the secondary key.
//
// An instance of this class will usually be returned by the
// secondary_key_table.find() method. The instance of that class will
// have the appropriate information to properly initialize an
// iterator.
template <typename Data = int>
class secondary_key_iterator
{
public:
	secondary_key_iterator()
		: _current(-1)
	{
	}

	secondary_key_iterator(secondary_key_iterator const& ski)
		: _filename(ski._filename), _pk_file(ski._filename),
		  _pke(_pk_file[ski._current]), _current(ski._current)
	{
	}

	secondary_key_iterator(std::string const& filename, int rrn)
		: _filename(filename), _pk_file(_filename), _current(rrn)
	{
		_pke = _pk_file[_current];
	}

	Data const& operator *()
	{
		return _pke.get_data();
	}

	int current_rrn() const	{ return _current; }

	secondary_key_iterator& operator ++()
	{
		if (_current == -1)
			return *this;

		_current = _pke.get_next_RRN();

		if (_current != -1)
			_pke = _pk_file[_current];

		return *this;
	}

	template <typename D>
	bool operator ==(secondary_key_iterator<D> const& rhs) const
	{
		return _current == rhs.current_rrn();
	}

	template <typename D>
	bool operator !=(secondary_key_iterator<D> const& rhs) const
	{
		return ! (*this == rhs);
	}

private:
	std::string _filename;
	binary_file< primary_key_entry<Data> > _pk_file;
	primary_key_entry<Data> _pke;
	int _current;
};


#endif // #ifndef SECONDARY_KEY_ITERATOR_HXX__
