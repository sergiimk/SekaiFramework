//////////////////////////////////////////////////////////////////////////
// class user_type
// {
//////////////////////////////////////////////////////////////////////////

friend class member_iterator;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// membere_iterator
//////////////////////////////////////////////////////////////////////////

/// bidirectional iterator over user type members
/** @ingroup reflection */
class member_iterator
{
public:
	member_iterator(const member_iterator& other)
		: m_type(other.m_type)
		, m_pos(other.m_pos)
		, m_offset(other.m_offset)
	{ }

	member_iterator& operator=(const member_iterator& rhs)
	{
		m_type = rhs.m_type;
		m_pos = rhs.m_pos;
		m_offset = rhs.m_offset;
	}

	const user_type& get_type() const { return *m_type; }

	template<class T>
	bool is() const { return (*this)->get_type() == T::member_id; }

	template<class T>
	T get() const
	{
		member* mem = m_type->_get_member(m_pos);
		ASSERT_STRICT(mem->get_type() == T::member_id);
		return T(*static_cast<T::member_type*>(mem), m_offset);		
	}

	member& operator*() const { return *m_type->_get_member(m_pos); }

	member* operator->() const { return m_type->_get_member(m_pos); }

	bool operator==(const member_iterator& rhs) const { return (m_type == rhs.m_type && m_pos == rhs.m_pos); }

	bool operator!=(const member_iterator& rhs) const { return !(*this == rhs); }

	bool operator<(const member_iterator& rhs) const { return m_pos < rhs.m_pos; }

	member_iterator& operator++()
	{
		ASSERT_STRICT(m_pos != m_type->_member_count());
		++m_pos;
		return *this;
	}

	member_iterator operator++(int)
	{
		member_iterator ret(*this);
		++*this;
		return ret;
	}

	member_iterator& operator--()
	{
		ASSERT_STRICT(m_pos != 0);
		--m_pos;
		return *this;
	}

	member_iterator operator--(int)
	{
		member_iterator ret(*this);
		--*this;
		return ret;
	}

private:
	friend class user_type;
	member_iterator(const user_type& t, size_t pos = 0, size_t offset = 0)
		: m_type(&t)
		, m_pos(pos)
		, m_offset(offset)
	{ }

	const user_type* m_type;
	size_t m_pos;
	size_t m_offset;
};

//////////////////////////////////////////////////////////////////////////

member_iterator members_begin() const { return member_iterator(*this); }
member_iterator members_end() const { return member_iterator(*this, _member_count()); }
member_iterator find_member(const char* name, bool search_base = false, size_t offset = 0) const;

//////////////////////////////////////////////////////////////////////////
// attribute_iterator
//////////////////////////////////////////////////////////////////////////

/// forward iterator over user type attributes
/** @ingroup reflection */
class attribute_iterator
{
public:
	attribute_iterator(const attribute_iterator& other)
		: m_type(other.m_type)
		, m_pos(other.m_pos)
	{ }

	attribute_iterator& operator=(const attribute_iterator& rhs)
	{
		m_type = rhs.m_type;
		m_pos = rhs.m_pos;
	}

	attribute& operator*() const
	{
		attribute* attr; member* mem;
		m_type->_get_attribute(attr, mem, m_pos);
		return *attr;
	}

	const user_type& get_type() const { return *m_type; }

	attribute* operator->() const { return &this->operator*(); }

	bool operator==(const attribute_iterator& rhs) const { return (m_type == rhs.m_type && m_pos == rhs.m_pos); }

	bool operator!=(const attribute_iterator& rhs) const { return !(*this == rhs); }

	bool operator<(const attribute_iterator& rhs) const { return m_pos < rhs.m_pos; }

	attribute_iterator& operator++()
	{
		ASSERT_STRICT(m_pos != m_type->_attribute_count());
		attribute* attr; member* mem;
		size_t size = m_type->_attribute_count();

		while(++m_pos != size)
		{
			m_type->_get_attribute(attr, mem, m_pos);
			if(!mem)
				break;
		}
		return *this;
	}

	attribute_iterator operator++(int)
	{
		attribute_iterator ret(*this);
		++*this;
		return ret;
	}

private:
	friend class user_type;
	attribute_iterator(const user_type& t, size_t pos = 0)
		: m_type(&t)
		, m_pos(pos)
	{ }

	const user_type* m_type;
	size_t m_pos;
};

//////////////////////////////////////////////////////////////////////////

attribute_iterator attributes_begin() const { return attribute_iterator(*this); }
attribute_iterator attributes_end() const { return attribute_iterator(*this, _attribute_count()); }

//////////////////////////////////////////////////////////////////////////
// hierarchy_traverser
//////////////////////////////////////////////////////////////////////////

/// Implement this interface to traverse hierarchy of types
/** Traversal starts from the node traverse was invoked on
  * and continues for all ancestors of that type
  * @ingroup reflection */
struct hierarchy_traverser
{
	/// called when entering a new type
	/** @param depth depth == 0 for a leaf node the traverse was invoked on
	  * @return return false if you don't want to traverse underlying branch */
	virtual bool EnterType(const user_type& t, size_t depth) = 0;

	/// called when leaving a type, not called if EnterType returned false
	/** @param depth depth == 0 for a leaf node the traverse was invoked on */
	virtual void LeaveType(const user_type& t, size_t depth) = 0;
};

void traverse_hierarchy(hierarchy_traverser& tr) const;

//////////////////////////////////////////////////////////////////////////
// };
//////////////////////////////////////////////////////////////////////////