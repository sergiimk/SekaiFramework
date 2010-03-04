/*========================================================
* pnt2_aos.h
* @author Sergey Mikhtonyuk
* @date 26 April 2009
=========================================================*/

#ifndef _PNT2_AOS_H__
#define _PNT2_AOS_H__

namespace VML {

/// A 2-D point (not optimized, because __m64 is not supported on x64 machines)
/** @ingroup VML */
class Point2
{
	float mX;
	float mY;

public:
	/// Default constructor; does no initialization 
	inline Point2( ) { };

	/// Copy a 3-D point
	inline Point2( const Point2 & pnt );

	/// Construct a 3-D point from x, y, and z elements
	inline Point2( float x, float y );

	/// Set all elements of a 2-D point to the same scalar value
	explicit inline Point2( float scalar );

	/// Initializes point with minimal float value
	explicit inline Point2( _t_min );

	/// Initializes point with maximal float value
	explicit inline Point2( _t_max );

	/// Assign one 2-D point to another
	inline Point2 & operator =( const Point2 & pnt );

	/// Set the x element of a 2-D point
	inline Point2 & setX( float x );

	/// Set the y element of a 2-D point
	inline Point2 & setY( float y );

	/// Get the x element of a 2-D point
	inline float getX( ) const;

	/// Get the y element of a 2-D point
	inline float getY( ) const;

	/// Set an x or y element of a 2-D point by index
	inline Point2 & setElem( int idx, float value );

	/// Get an x or y element of a 3-D point by index
	inline float getElem( int idx ) const;

	/// Subscripting operator to set or get an element
	inline float & operator []( int idx );

	/// Subscripting operator to get an element
	inline float operator []( int idx ) const;

	/// Subtract a 2-D point from another 2-D point
	inline const Point2 operator -( const Point2 & pnt ) const;

	/// Add a 2-D point to another 2-D point
	inline const Point2 operator +( const Point2 & pnt ) const;

	/// Perform compound assignment and addition with a 2-D point
	inline Point2 & operator +=( const Point2 & pnt );

	/// Perform compound assignment and subtraction by a 2-D point
	inline Point2 & operator -=( const Point2 & pnt );

	/// Maximum element of a 2-D point
	inline float maxElem( ) const;

	/// Minimum element of a 2-D point
	inline float minElem( ) const;

	/// Compute the sum of all elements of a 2-D point
	inline float sum( ) const;

	/// Compute the square of the distance of a 2-D point from the coordinate-system origin
	inline float distSqrFromOrigin( ) const;

	/// Compute the distance of a 2-D point from the coordinate-system origin
	inline float distFromOrigin( ) const;
};

/** @addtogroup VML_Scalar */
/** @{ */

/// Multiply two 2-D points per element
inline const Point2 mulPerElem( const Point2 & pnt0, const Point2 & pnt1 );

/// Divide two 2-D points per element
/** Floating-point behavior matches standard library function divf4 */
inline const Point2 divPerElem( const Point2 & pnt0, const Point2 & pnt1 );

/// Compute the reciprocal of a 2-D point per element
/** Floating-point behavior matches standard library function recipf4 */
inline const Point2 recipPerElem( const Point2 & pnt );

/// Compute the square root of a 2-D point per element
/** Floating-point behavior matches standard library function sqrtf4 */
inline const Point2 sqrtPerElem( const Point2 & pnt );

/// Compute the reciprocal square root of a 2-D point per element
/** Floating-point behavior matches standard library function rsqrtf4 */
inline const Point2 rsqrtPerElem( const Point2 & pnt );

/// Compute the absolute value of a 2-D point per element
inline const Point2 absPerElem( const Point2 & pnt );

/// Copy sign from one 2-D point to another, per element
inline const Point2 copySignPerElem( const Point2 & pnt0, const Point2 & pnt1 );

/// Maximum of two 3-D points per element
inline const Point2 maxPerElem( const Point2 & pnt0, const Point2 & pnt1 );

/// Minimum of two 3-D points per element
inline const Point2 minPerElem( const Point2 & pnt0, const Point2 & pnt1 );

/// Apply uniform scale to a 2-D point
inline const Point2 scale( const Point2 & pnt, float scaleVal );

/// Compute the square of the distance between two 2-D points
inline float distSqr( const Point2 & pnt0, const Point2 & pnt1 );

/// Compute the distance between two 2-D points
inline float dist( const Point2 & pnt0, const Point2 & pnt1 );

/// Linear interpolation between two 2-D points
/** Does not clamp t between 0 and 1 */
inline const Point2 lerp( float t, const Point2 & pnt0, const Point2 & pnt1 );

/// Conditionally select between two 2-D points
inline const Point2 select( const Point2 & pnt0, const Point2 & pnt1, bool select1 );

/// Compares points with given epsilon
inline bool equivalent( const Point2 & pnt0, const Point2 & pnt1, float epsilon = EQ_EPSILON);

/// Compares matrices with relative precision
/** Precision 1.0 is 100% means both values must be within x2 from each other
*  Example equivalentRelative(0.001f, 0.002f, 1.0f) - 100%
*  relative distance from v1 to v2 is 100%, and from v2 to v1 is 50%
*  both fall into desired range so result is true */
inline bool equivalentRelative( const Point2 & pnt0, const Point2 & pnt1, float precision);

/** @} */





/////////////////////////////////////////////////////////////////////////////////





inline Point2::Point2( const Point2 & pnt )
:	mX(pnt.mX),
	mY(pnt.mY)
{
}

inline Point2::Point2( float _x, float _y )
:	mX(_x),
	mY(_y)
{
}

inline Point2::Point2( float scalar )
:	mX(scalar),
	mY(scalar)
{
}

inline Point2::Point2( _t_min )
:	mX((std::numeric_limits<float>::min)()),
	mY((std::numeric_limits<float>::min)())
{
}

inline Point2::Point2( _t_max )
:	mX((std::numeric_limits<float>::max)()),
	mY((std::numeric_limits<float>::max)())
{
}

inline const Point2 lerp( float t, const Point2 & pnt0, const Point2 & pnt1 )
{
	return pnt0 + scale( pnt1 - pnt0, t );
}

inline Point2 & Point2::operator =( const Point2 & pnt )
{
	mX = pnt.mX;
	mY = pnt.mY;
	return *this;
}

inline Point2 & Point2::setX( float _x )
{
	mX = _x;
	return *this;
}

inline float Point2::getX( ) const
{
	return mX;
}

inline Point2 & Point2::setY( float _y )
{
	mY = _y;
	return *this;
}

inline float Point2::getY( ) const
{
	return mY;
}

inline Point2 & Point2::setElem( int idx, float value )
{
	*(&mX + idx) = value;
	return *this;
}

inline float Point2::getElem( int idx ) const
{
	return *(&mX + idx);
}

inline float & Point2::operator []( int idx )
{
	return *(&mX + idx);
}

inline float Point2::operator []( int idx ) const
{
	return *(&mX + idx);
}

inline const Point2 Point2::operator -( const Point2 & pnt ) const
{
	return Point2( ( mX - pnt.mX ), ( mY - pnt.mY ) );
}

inline const Point2 Point2::operator +( const Point2 & pnt ) const
{
	return Point2( ( mX + pnt.mX ), ( mY + pnt.mY ) );
}

inline Point2 & Point2::operator +=( const Point2 & pnt )
{
	mX += pnt.mX;
	mY += pnt.mY;
	return *this;
}

inline Point2 & Point2::operator -=( const Point2 & pnt )
{
	mX -= pnt.mX;
	mY -= pnt.mY;
	return *this;
}

inline float Point2::maxElem( ) const
{
	return (mX > mY)? mX : mY;
}

inline float Point2::minElem( ) const
{
	return (mX < mY)? mX : mY;
}

inline float Point2::sum( ) const
{
	return mX + mY;
}

inline float Point2::distSqrFromOrigin( ) const
{
	return mX * mX + mY * mY;
}

inline float Point2::distFromOrigin( ) const
{
	return sqrtf(distSqrFromOrigin());
}

inline const Point2 mulPerElem( const Point2 & pnt0, const Point2 & pnt1 )
{
	return Point2( ( pnt0.getX() * pnt1.getX() ), ( pnt0.getY() * pnt1.getY() ) );
}

inline const Point2 divPerElem( const Point2 & pnt0, const Point2 & pnt1 )
{
	return Point2( ( pnt0.getX() / pnt1.getX() ), ( pnt0.getY() / pnt1.getY() ) );
}

inline const Point2 recipPerElem( const Point2 & pnt )
{
	return Point2( ( 1.0f / pnt.getX() ), ( 1.0f / pnt.getY() ) );
}

inline const Point2 sqrtPerElem( const Point2 & pnt )
{
	return Point2( sqrtf( pnt.getX() ), sqrtf( pnt.getY() ) );
}

inline const Point2 rsqrtPerElem( const Point2 & pnt )
{
	return Point2( ( 1.0f / sqrtf( pnt.getX() ) ), ( 1.0f / sqrtf( pnt.getY() ) ) );
}

inline const Point2 absPerElem( const Point2 & pnt )
{
	return Point2( fabsf( pnt.getX() ), fabsf( pnt.getY() ) );
}

inline const Point2 copySignPerElem( const Point2 & pnt0, const Point2 & pnt1 )
{
	return Point2(
		( pnt1.getX() < 0.0f )? -fabsf( pnt0.getX() ) : fabsf( pnt0.getX() ),
		( pnt1.getY() < 0.0f )? -fabsf( pnt0.getY() ) : fabsf( pnt0.getY() )
		);
}

inline const Point2 maxPerElem( const Point2 & pnt0, const Point2 & pnt1 )
{
	return Point2(
		(pnt0.getX() > pnt1.getX())? pnt0.getX() : pnt1.getX(),
		(pnt0.getY() > pnt1.getY())? pnt0.getY() : pnt1.getY()
		);
}

inline const Point2 minPerElem( const Point2 & pnt0, const Point2 & pnt1 )
{
	return Point2(
		(pnt0.getX() < pnt1.getX())? pnt0.getX() : pnt1.getX(),
		(pnt0.getY() < pnt1.getY())? pnt0.getY() : pnt1.getY()
		);
}

inline const Point2 scale( const Point2 & pnt, float scaleVal )
{
	return mulPerElem( pnt, Point2( scaleVal ) );
}

inline float distSqr( const Point2 & pnt0, const Point2 & pnt1 )
{
	return ( pnt1 - pnt0 ).distSqrFromOrigin();
}

inline float dist( const Point2 & pnt0, const Point2 & pnt1 )
{
	return ( pnt1 - pnt0 ).distFromOrigin();
}

inline const Point2 select( const Point2 & pnt0, const Point2 & pnt1, bool select1 )
{
	return Point2(
		( select1 )? pnt1.getX() : pnt0.getX(),
		( select1 )? pnt1.getY() : pnt0.getY()
		);
}

inline bool equivalent ( const Point2 & pnt0, const Point2 & pnt1, float epsilon)
{
	return (
		(fabsf(pnt0.getX() - pnt1.getX()) <= epsilon) && 
		(fabsf(pnt0.getY() - pnt1.getY()) <= epsilon)
		);
}

inline bool equivalentRelative( const Point2 & pnt0, const Point2 & pnt1, float precision )
{
	return (
		float_cmp_rel(pnt0.getX(), pnt1.getX(), precision) && 
		float_cmp_rel(pnt0.getY(), pnt1.getY(), precision)
		);
}

} // namespace VML


#endif // _PNT2_AOS_H__