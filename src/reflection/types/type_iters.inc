//////////////////////////////////////////////////////////////////////////
// class type
// {
//////////////////////////////////////////////////////////////////////////

friend class attribute_iterator;

//////////////////////////////////////////////////////////////////////////
// attribute_iterator
//////////////////////////////////////////////////////////////////////////

/// forward iterator over user type attributes
/** @ingroup reflection */
class attribute_iterator
{
public:

	typedef std::forward_iterator_tag iterator_category;
	typedef attribute value_type;
	typedef ptrdiff_t difference_type;
	typedef attribute* pointer;
	typedef attribute& reference;

	attribute_iterator(const attribute_iterator& other)
		: m_type(other.m_type)
		, m_pos(other.m_pos)
	{ }

	attribute_iterator& operator=(const attribute_iterator& rhs)
	{
		m_type = rhs.m_type;
		m_pos = rhs.m_pos;
		return *this;
	}

	const attribute& operator*() const
	{
		return *m_type->_get_attribute(m_pos);
	}

	const type& get_type() const { return *m_type; }

	const attribute* operator->() const { return &this->operator*(); }

	bool operator==(const attribute_iterator& rhs) const { return (m_type == rhs.m_type && m_pos == rhs.m_pos); }

	bool operator!=(const attribute_iterator& rhs) const { return !(*this == rhs); }

	attribute_iterator& operator++()
	{
		ASSERT_STRICT(m_pos != m_type->_attribute_count());
		++m_pos;
		return *this;
	}

	attribute_iterator operator++(int)
	{
		attribute_iterator ret(*this);
		++*this;
		return ret;
	}

private:
	friend class type;
	attribute_iterator(const type& t, size_t pos = 0)
		: m_type(&t)
		, m_pos(pos)
	{ }

	const type* m_type;
	size_t m_pos;
};

//////////////////////////////////////////////////////////////////////////

attribute_iterator attributes_begin() const { return attribute_iterator(*this); }
attribute_iterator attributes_end() const { return attribute_iterator(*this, _attribute_count()); }

//////////////////////////////////////////////////////////////////////////
// };
//////////////////////////////////////////////////////////////////////////