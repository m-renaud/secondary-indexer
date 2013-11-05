#ifndef SECONDARY_KEY_TABLE_HXX__
#define SECONDARY_KEY_TABLE_HXX__

#include "secondary_key_iterator.hxx"

#include <fstream>
#include <map>
#include <string>

template <typename SecondaryKeyType>
class secondary_key_table
{
public:
	using table_type = std::map<SecondaryKeyType, int>;
	using value_type = typename table_type::value_type;
	using key_type = typename table_type::key_type;
	using mapped_type = typename table_type::mapped_type;
	using iterator = typename table_type::iterator;
	using const_iterator = typename table_type::const_iterator;

	secondary_key_table() = default;
	secondary_key_table(secondary_key_table const&) = default;
	secondary_key_table(secondary_key_table&&) = default;

	secondary_key_table& operator =(secondary_key_table const&) = default;
	secondary_key_table& operator =(secondary_key_table&&) = default;

	~secondary_key_table() = default;

	secondary_key_table(table_type const& t, std::string const& pk_filename)
		: _table(t), _pk_filename(pk_filename)
	{
	}

	secondary_key_table(table_type&& t, std::string const& pk_filename)
		: _table(std::move(t)), _pk_filename(pk_filename)
	{
	}


	iterator begin() { return _table.begin(); }
	iterator end()   { return _table.end(); }

	const_iterator begin() const { return _table.begin(); }
	const_iterator end()   const { return _table.end(); }

	void load(std::string const& filename)
	{
		this->clear();

		std::ifstream input(filename);
		key_type key;
		mapped_type value;

		while (input >> key >> value)
		{
			_table.insert(std::make_pair(key,value));
		}
	}

	void save(std::string const& filename)
	{
		std::ofstream output(filename);
		for (value_type const& val : _table)
			output << val.first << ' ' << val.second << '\n';
	}

	void clear()
	{
		_table.clear();
	}

	void set_pk_filename(std::string const& fn)
	{
		_pk_filename = fn;
	}

	std::string get_pk_filename()
	{
		return _pk_filename;
	}

	template <typename Data>
	auto find(SecondaryKeyType const& key) const
		-> secondary_key_iterator<Data>
	{
		const_iterator i = _table.find(key);
		int rrn = -1;
		if (i != _table.end())
			rrn = i->second;

		return secondary_key_iterator<Data>(_pk_filename, rrn);
	}

private:
	table_type _table;
	std::string _pk_filename;
};

#endif // #ifndef SECONDARY_KEY_TABLE_HXX__
