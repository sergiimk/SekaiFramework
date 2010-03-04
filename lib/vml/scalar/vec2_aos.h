/*========================================================
* vec2_aos.h
* @author Sergey Mikhtonyuk
* @date 20 July 2009
=========================================================*/
#ifndef _VEC2_AOS_H__
#define _VEC2_AOS_H__

namespace VML
{

	/// A 2-D vector in array-of-structures format
	/** @ingroup VML_Scalar */
	class Vector2
	{
		float mX;
		float mY;

	public:

		/// Default constructor; does no initialization
		inline Vector2( ) { };

		/// Copy a 2-D vector
		inline Vector2( const Vector2 & vec );

		/// Construct a 2-D vector from x, y elements 
		inline Vector2( float x, float y);

		/// Copy elements from a 2-D point into a 2-D vector
		explicit inline Vector2( const Point2 & pnt );

		/// Set all elements of a 2-D vector to the same scalar value
		explicit inline Vector2( float scalar );

		/// Initializes vector with minimal float value
		explicit inline Vector2( _t_min );

		/// Initializes vector with maximal float value
		explicit inline Vector2( _t_max );

		/// Assign one 2-D vector to another 
		inline Vector2 & operator =( const Vector2 & vec );

		/// Set the x element of a 2-D vector
		inline Vector2 & setX( float x );

		/// Set the y element of a 2-D vector
		inline Vector2 & setY( float y );

		/// Get the x element of a 2-D vector
		inline float getX( ) const;

		/// Get the y element of a 2-D vector
		inline float getY( ) const;

		/// Set an x or y element of a 2-D vector by index
		inline Vector2 & setElem( int idx, float value );

		/// Get an x or y element of a 2-D vector by index
		inline float getElem( int idx ) const;

		/// Subscripting operator to set or get an element
		inline float & operator []( int idx );

		/// Subscripting operator to get an element
		inline float operator []( int idx ) const;

		/// Add two 2-D vectors
		inline const Vector2 operator +( const Vector2 & vec ) const;

		/// Subtract a 2-D vector from another 2-D vector 
		inline const Vector2 operator -( const Vector2 & vec ) const;

		/// Add a 2-D vector to a 2-D point
		inline const Point2 operator +( const Point2 & pnt ) const;

		/// Multiply a 2-D vector by a scalar
		inline const Vector2 operator *( float scalar ) const;

		/// Divide a 2-D vector by a scalar 
		inline const Vector2 operator /( float scalar ) const;

		/// Perform compound assignment and addition with a 2-D vector
		inline Vector2 & operator +=( const Vector2 & vec );

		/// Perform compound assignment and subtraction by a 2-D vector
		inline Vector2 & operator -=( const Vector2 & vec );

		/// Perform compound assignment and multiplication by a scalar
		inline Vector2 & operator *=( float scalar );

		/// Perform compound assignment and division by a scalar
		inline Vector2 & operator /=( float scalar );

		/// Negate all elements of a 2-D vector
		inline const Vector2 operator -( ) const;

		/// Returns true if all components of vector are less than corresponding in vec
		inline bool operator < ( const Vector2 & vec ) const;

		/// Returns true if all components of vector are less or equal than corresponding in vec
		inline bool operator <= ( const Vector2 & vec ) const;

		/// Returns true if all components of vector are greater than corresponding in vec
		inline bool operator > ( const Vector2 & vec ) const;

		/// Returns true if all components of vector are greater or equal than corresponding in vec
		inline bool operator >= ( const Vector2 & vec ) const;

		/// Maximum element of a 2-D vector
		inline float maxElem( ) const;

		/// Minimum element of a 2-D vector
		inline float minElem( ) const;

		/// Compute the sum of all elements of a 2-D vector 
		inline float sum( ) const;

		/// Compute the square of the length of a 2-D vector
		inline float lengthSqr( ) const;

		/// Compute the length of a 2-D vector
		inline float length( ) const;

		/// Clamps to maximum length
		inline void clampLength( float max_len );

		/// Sets length and preserves direction
		/** The result is unpredictable when all elements of vec are at or near zero */
		inline void setLength( float len );

		/// Normalize a 2-D vector
		/** The result is unpredictable when all elements of vec are at or near zero */
		inline void normalize( );

		/// Construct x axis
		static inline const Vector2 xAxis( );

		/// Construct y axis
		static inline const Vector2 yAxis( );

	};


	/** @addtogroup VML_Scalar */
	/** @{ */

	/// Multiply a 2-D vector by a scalar 
	inline const Vector2 operator *( float scalar, const Vector2 & vec );

	/// Multiply two 2-D vectors per element
	inline const Vector2 mulPerElem( const Vector2 & vec0, const Vector2 & vec1 );

	/// Divide two 2-D vectors per element
	/** Floating-point behavior matches standard library function divf4 */
	inline const Vector2 divPerElem( const Vector2 & vec0, const Vector2 & vec1 );

	/// Compute the reciprocal of a 2-D vector per element
	/** Floating-point behavior matches standard library function recipf4 */
	inline const Vector2 recipPerElem( const Vector2 & vec );

	/// Compute the square root of a 2-D vector per element
	/** Floating-point behavior matches standard library function sqrtf4 */
	inline const Vector2 sqrtPerElem( const Vector2 & vec );

	/// Compute the reciprocal square root of a 2-D vector per element
	/** Floating-point behavior matches standard library function rsqrtf4 */
	inline const Vector2 rsqrtPerElem( const Vector2 & vec );

	/// Compute the absolute value of a 2-D vector per element
	inline const Vector2 absPerElem( const Vector2 & vec );

	/// Copy sign from one 2-D vector to another, per element
	inline const Vector2 copySignPerElem( const Vector2 & vec0, const Vector2 & vec1 );

	/// Maximum of two 2-D vectors per element 
	inline const Vector2 maxPerElem( const Vector2 & vec0, const Vector2 & vec1 );

	/// Minimum of two 2-D vectors per element
	inline const Vector2 minPerElem( const Vector2 & vec0, const Vector2 & vec1 );

	/// Compute the dot product of two 2-D vectors
	inline float dot( const Vector2 & vec0, const Vector2 & vec1 );

	/// Clamps to maximum length
	inline const Vector2 clampLength( const Vector2& vec, float max_len );

	/// Sets length and preserves direction
	/** The result is unpredictable when all elements of vec are at or near zero */
	inline const Vector2 setLength( const Vector2& vec, float len );

	/// Normalize a 2-D vector
	/** The result is unpredictable when all elements of vec are at or near zero */
	inline const Vector2 normalize( const Vector2 & vec );

	/// Linear interpolation between two 2-D vectors
	/** Does not clamp t between 0 and 1 */
	inline const Vector2 lerp( float t, const Vector2 & vec0, const Vector2 & vec1 );

	/// Compares vectors with given epsilon
	inline bool equivalent( const Vector2 & vec0, const Vector2 & vec1, float epsilon = EQ_EPSILON);

	/// Compares matrices with relative precision
	/** Precision 1.0 is 100% means both values must be within x2 from each other
	*  Example equivalentRelative(0.001f, 0.002f, 1.0f) - 100%
	*  relative distance from v1 to v2 is 100%, and from v2 to v1 is 50%
	*  both fall into desired range so result is true */
	inline bool equivalentRelative( const Vector2 & vec0, const Vector2 & vec1, float precision);

	/** @} */


	inline Vector2::Vector2( const Vector2 & vec )
		:	mX(vec.mX),
			mY(vec.mY)
	{
	}

	inline Vector2::Vector2( float _x, float _y )
		:	mX(_x),
			mY(_y)
	{
	}

	inline Vector2::Vector2( const Point2 & pnt )
		:	mX(pnt.getX()),
			mY(pnt.getY())
	{
	}

	inline Vector2::Vector2( float scalar )
		:	mX(scalar),
			mY(scalar)
	{
	}

	inline Vector2::Vector2( _t_min )
		:	mX((std::numeric_limits<float>::min)()),
			mY((std::numeric_limits<float>::min)())
	{
	}

	inline Vector2::Vector2( _t_max )
		:	mX((std::numeric_limits<float>::max)()),
			mY((std::numeric_limits<float>::max)())
	{
	}

	inline const Vector2 Vector2::xAxis( )
	{
		return Vector2( 1.0f, 0.0f );
	}

	inline const Vector2 Vector2::yAxis( )
	{
		return Vector2( 0.0f, 1.0f );
	}

	inline const Vector2 lerp( float t, const Vector2 & vec0, const Vector2 & vec1 )
	{
		return ( vec0 + ( ( vec1 - vec0 ) * t ) );
	}

	inline Vector2 & Vector2::operator =( const Vector2 & vec )
	{
		mX = vec.mX;
		mY = vec.mY;
		return *this;
	}

	inline Vector2 & Vector2::setX( float _x )
	{
		mX = _x;
		return *this;
	}

	inline float Vector2::getX( ) const
	{
		return mX;
	}

	inline Vector2 & Vector2::setY( float _y )
	{
		mY = _y;
		return *this;
	}

	inline float Vector2::getY( ) const
	{
		return mY;
	}

	inline Vector2 & Vector2::setElem( int idx, float value )
	{
		*(&mX + idx) = value;
		return *this;
	}

	inline float Vector2::getElem( int idx ) const
	{
		return *(&mX + idx);
	}

	inline float & Vector2::operator []( int idx )
	{
		return *(&mX + idx);
	}

	inline float Vector2::operator []( int idx ) const
	{
		return *(&mX + idx);
	}

	inline const Vector2 Vector2::operator +( const Vector2 & vec ) const
	{
		Vector2 ret(*this);
		return ret += vec;
	}

	inline const Vector2 Vector2::operator -( const Vector2 & vec ) const
	{
		Vector2 ret(*this);
		return ret -= vec;
	}

	inline const Point2 Vector2::operator +( const Point2 & pnt ) const
	{
		return Point2(
			( mX + pnt.getX() ),
			( mY + pnt.getY() )
			);
	}

	inline const Vector2 Vector2::operator *( float scalar ) const
	{
		Vector2 ret(*this);
		return ret *= scalar;
	}

	inline Vector2 & Vector2::operator +=( const Vector2 & vec )
	{
		mX += vec.mX;
		mY += vec.mY;
		return *this;
	}

	inline Vector2 & Vector2::operator -=( const Vector2 & vec )
	{
		mX -= vec.mX;
		mY -= vec.mY;
		return *this;
	}

	inline Vector2 & Vector2::operator *=( float scalar )
	{
		mX *= scalar;
		mY *= scalar;
		return *this;
	}

	inline const Vector2 Vector2::operator /( float scalar ) const
	{
		Vector2 ret(*this);
		return ret /= scalar;
	}

	inline Vector2 & Vector2::operator /=( float scalar )
	{
		mX /= scalar;
		mY /= scalar;
		return *this;
	}

	inline const Vector2 Vector2::operator -( ) const
	{
		return Vector2(-mX, -mY);
	}

	inline bool Vector2::operator < ( const Vector2 & vec ) const
	{
		return (mX < vec.mX) && (mY < vec.mY);
	}

	inline bool Vector2::operator <= ( const Vector2 & vec ) const
	{
		return (mX <= vec.mX) && (mY <= vec.mY);
	}

	inline bool Vector2::operator > ( const Vector2 & vec ) const
	{
		return (mX > vec.mX) && (mY > vec.mY);
	}

	inline bool Vector2::operator >= ( const Vector2 & vec ) const
	{
		return (mX >= vec.mX) && (mY >= vec.mY);
	}

	inline float Vector2::maxElem( ) const
	{
		return (mX > mY) ? mX : mY;
	}

	inline float Vector2::minElem( ) const
	{
		return (mX < mY) ? mX : mY;
	}

	inline float Vector2::sum( ) const
	{
		return mX + mY;
	}

	inline float Vector2::lengthSqr( ) const
	{
		return mX * mX + mY * mY;
	}

	inline float Vector2::length( ) const
	{
		return sqrtf( lengthSqr( ) );
	}

	inline void Vector2::clampLength( float max_len )
	{
		float lens = lengthSqr( );
		if(lens > max_len * max_len)
		{
			float scale = max_len / sqrtf( lens );
			mX *= scale;
			mY *= scale;
		}
	}

	inline void Vector2::setLength( float len )
	{
		float lens = lengthSqr( );
		if(lens < EQ_EPSILON * EQ_EPSILON) return;
		float scale = len / sqrtf( lens );
		mX *= scale;
		mY *= scale;
	}

	inline void Vector2::normalize( )
	{
		float lenInv;
		lenInv = ( 1.0f / length() );
		mX *= lenInv;
		mY *= lenInv;
	}

	inline const Vector2 operator *( float scalar, const Vector2 & vec )
	{
		return vec * scalar;
	}

	inline const Vector2 mulPerElem( const Vector2 & vec0, const Vector2 & vec1 )
	{
		return Vector2(
			( vec0.getX() * vec1.getX() ),
			( vec0.getY() * vec1.getY() )
			);
	}

	inline const Vector2 divPerElem( const Vector2 & vec0, const Vector2 & vec1 )
	{
		return Vector2(
			( vec0.getX() / vec1.getX() ),
			( vec0.getY() / vec1.getY() )
			);
	}

	inline const Vector2 recipPerElem( const Vector2 & vec )
	{
		return Vector2(
			( 1.0f / vec.getX() ),
			( 1.0f / vec.getY() )
			);
	}

	inline const Vector2 sqrtPerElem( const Vector2 & vec )
	{
		return Vector2(
			sqrtf( vec.getX() ),
			sqrtf( vec.getY() )
			);
	}

	inline const Vector2 rsqrtPerElem( const Vector2 & vec )
	{
		return Vector2(
			( 1.0f / sqrtf( vec.getX() ) ),
			( 1.0f / sqrtf( vec.getY() ) )
			);
	}

	inline const Vector2 absPerElem( const Vector2 & vec )
	{
		return Vector2(
			fabsf( vec.getX() ),
			fabsf( vec.getY() )
			);
	}

	inline const Vector2 copySignPerElem( const Vector2 & vec0, const Vector2 & vec1 )
	{
		return Vector2(
			( vec1.getX() < 0.0f )? -fabsf( vec0.getX() ) : fabsf( vec0.getX() ),
			( vec1.getY() < 0.0f )? -fabsf( vec0.getY() ) : fabsf( vec0.getY() )
			);
	}

	inline const Vector2 maxPerElem( const Vector2 & vec0, const Vector2 & vec1 )
	{
		return Vector2(
			(vec0.getX() > vec1.getX())? vec0.getX() : vec1.getX(),
			(vec0.getY() > vec1.getY())? vec0.getY() : vec1.getY()
			);
	}

	inline const Vector2 minPerElem( const Vector2 & vec0, const Vector2 & vec1 )
	{
		return Vector2(
			(vec0.getX() < vec1.getX())? vec0.getX() : vec1.getX(),
			(vec0.getY() < vec1.getY())? vec0.getY() : vec1.getY()
			);
	}

	inline float dot( const Vector2 & vec0, const Vector2 & vec1 )
	{
		float result;
		result = ( vec0.getX() * vec1.getX() );
		result += ( vec0.getY() * vec1.getY() );
		return result;
	}

	inline const Vector2 clampLength(const Vector2& vec, float max_len)
	{
		Vector2 ret(vec);
		ret.clampLength(max_len);
		return ret;
	}

	inline const Vector2 setLength(const Vector2& vec, float len)
	{
		Vector2 ret(vec);
		ret.setLength(len);
		return ret;
	}

	inline const Vector2 normalize( const Vector2 & vec )
	{
		float lenInv = ( 1.0f / vec.length( ) );
		return Vector2(
			( vec.getX() * lenInv ),
			( vec.getY() * lenInv )
			);
	}

	inline bool equivalent (const Vector2 & vec0, const Vector2 & vec1, float epsilon)
	{
		return (
			(fabsf(vec0.getX() - vec1.getX()) <= epsilon) && 
			(fabsf(vec0.getY() - vec1.getY()) <= epsilon)
			);
	}

	inline bool equivalentRelative(const Vector2 & vec0, const Vector2 & vec1, float precision)
	{
		return (
			float_cmp_rel(vec0.getX(), vec1.getX(), precision) &&
			float_cmp_rel(vec0.getY(), vec1.getY(), precision)
			);
	}

} // namespace

#endif // _VEC2_AOS_H__