/**
 * \file
 * \brief Definition of the threevector class and related operations.
 */

#ifndef __SCHOOL_THREEVECTOR_H__
#define __SCHOOL_THREEVECTOR_H__

// Standard includes

#include <cmath>
#include <iostream>

/** \brief Namespace "school" contains most of our project code.
 *
 * The school namespace can be extended with arbitrary names just by opening
 * a new school namespace block and placing new names (functions, variables,
 * etc.) inside the block. Operators are an exception, for we want them to be
 * defined in the global namespace.
 */
namespace school {

  /** \brief Threevector implementation.
   */
  class threevector {

  public:

    // It is a good practise to name our types according to their role in the code.

    /** \brief The scalar type of threevector's space-like components.
     *
     * It is always a good idea to name the types used in a class according to
     * their role in the code. Using this method it is very easy to change the
     * underlying type. Suppose we want to increase precision. We only need to
     * replace double to long double in this single typedef instead of replacing
     * every double occurance in the code.
     */
    typedef double value_type;

  protected:

    // Data members are protected. We want to access them from derived classes
    // so we do not make them private.

    value_type _M_x; ///< Space-like component x
    value_type _M_y; ///< Space-like component y
    value_type _M_z; ///< Space-like component z

  public:

    /** \brief The empty constructor sets every data member to zero.
     */
    threevector() :
    _M_x(0.0),
    _M_y(0.0),
    _M_z(0.0) {
    }

    /** \brief Contructor with 1 parameter.
     * 
     * We don't want a single floating point value treated as a threevector.
     * Never. So we allow only explicit conversion to a threevector using this
     * constructor. To prevent implicit conversion from a floating point value
     * to a threevector we use the keyword "explicit" in the constructor.
     * We use a constant reference parameter to be more general, although in
     * this case it is not strictly necessary, because the underlying type
     * (a double) can be passed by value without problem.
     */
    explicit threevector(const value_type & x) :
    _M_x(x),
    _M_y(0.0),
    _M_z(0.0) {
    }

    /** \brief Constructor with either 2 or 3 parameters.
     */
    threevector(const value_type & x, const value_type & y, const value_type & z = 0) :
    _M_x(x),
    _M_y(y),
    _M_z(z) {
    }

    /** \brief Copy constructor.
     *
     * The copy constructor makes a threevector out of another already existing
     * threevector. We are satisfied with the default implementation so we use
     * the keyword "default" here.
     */
    threevector(const threevector &) = default;

    /** \brief Assignment operator.
     *
     * The assignment operator is similar to the copy constructor, but in this
     * case data members already exist and have to be assigned a new value.
     */
    threevector & operator = (const threevector &) = default;

    /** \brief Destructor.
     *
     * We are satisfied with the default destructor.
     */
    ~threevector() = default;

    // When their value must not be changed, we access elements as constant references.

    /** \brief Return space-like component x as a constant reference.
     */
    const value_type & X() const { return _M_x; }

    /** \brief Return space-like component y as a constant reference.
     */
    const value_type & Y() const { return _M_y; }

    /** \brief Return space-like component z as a constant reference.
     */
    const value_type & Z() const { return _M_z; }

    // When their value can be changed, we access elements as simple references.

    /** \brief Return space-like component x as a reference.
     */
    value_type & X() { return _M_x; }

    /** \brief Return space-like component y as a reference.
     */
    value_type & Y() { return _M_y; }

    /** \brief Return space-like component z as a reference.
     */
    value_type & Z() { return _M_z; }

    // Computed assignments (a+=b; a-=b; a*=b; a/=b;).
    // The left side of the operator is always *this.
    // The right side is the parameter of the method.
    // We can rewrite these as a.operator+=(b); a.operator-=(b);
    // a.operator*=(b); a.operator/=(b); respectively.

    /** \brief Computed assignment with addition.
     */
    threevector & operator += (const threevector & b) {
      _M_x += b._M_x;
      _M_y += b._M_y;
      _M_z += b._M_z;
      return *this;
    }

    /** \brief Computed assignment with subtraction.
     */
    threevector & operator -= (const threevector & b) {
      _M_x -= b._M_x;
      _M_y -= b._M_y;
      _M_z -= b._M_z;
      return *this;
    }

    /** \brief Computed assignment with multiplication by a simple value.
     */
    threevector & operator *= (const value_type & b) {
      _M_x *= b;
      _M_y *= b;
      _M_z *= b;
      return *this;
    }

    /** \brief Computed assignment with division by a simple value.
     */
    threevector & operator /= (const value_type & b) {
      _M_x /= b;
      _M_y /= b;
      _M_z /= b;
      return *this ;
    }

    /** \brief Magnitude squared.
     */
    value_type mag2() const {
      return _M_x*_M_x + _M_y*_M_y + _M_z*_M_z;
    }

    /** \brief Transverse component squared.
     */
    value_type perp2() const {
      return _M_x*_M_x + _M_y*_M_y;
    }

    /** \brief Magnitude.
     */
    value_type mag() const {
      return std::sqrt(mag2());
    }

    /** \brief Transverse component.
     */
    value_type perp() const {
      return std::sqrt(perp2());
    }

    /** \brief Azimuth.
     */
    value_type phi() const {
      return (_M_x == 0.0 && _M_y == 0.0) ? 0.0 : std::atan2(_M_y,_M_x);
    }

    /** \brief Polar angle.
     */
    value_type theta() const {
      value_type p = perp();
      return (p == 0.0 && _M_z == 0.0) ? 0.0 : std::atan2(p, _M_z);
    }

    // The following methods have only their declarations here.
    // The definitions are in the separate source file threevector.cc.

    /** \brief Rotate around axis x.
     */
    void rotateX(const value_type & psi);

    /** \brief Rotate around axis y.
     */
    void rotateY(const value_type & th);

    /** \brief Rotate around axis z.
     */
    void rotateZ(const value_type & ph);

  }; // end of class threevector

  /** \brief Dot product.
   */
  inline threevector::value_type dot(const threevector & a, const threevector & b) {
    return a.X()*b.X() + a.Y()*b.Y() + a.Z()*b.Z();
  }

  /** \brief Cross product.
   */
  inline threevector cross(const threevector & a, const threevector & b) {
    return
      threevector(
        a.Y()*b.Z() - a.Z()*b.Y(),
        a.Z()*b.X() - a.X()*b.Z(),
        a.X()*b.Y() - a.Y()*b.X()
      );
  }

  // Specializations

  inline threevector::value_type cosAngle(const threevector & a, const threevector & b) {
    threevector::value_type ptot2 = a.mag2() * b.mag2();
    return ptot2 <= 0.0 ? 1.0 : dot(a, b) / std::sqrt(ptot2);
  }

  inline threevector::value_type angle(const threevector & a, const threevector & b) {
    threevector::value_type ptot2 = a.mag2() * b.mag2();
    return ptot2 <= 0.0 ? 0.0 : std::acos(dot(a, b) / std::sqrt(ptot2));
  }

} // end of namespace school

// Operators are declared in the global namespace, because we need
// ::operator+(a,b) rather than school::operator+(a,b).
// However when using the operator notation a+b, the compiler (at least g++) can
// handle the situation, but using the function-like notation operator+(a,b)
// there will be problems for sure.

// Unary operations are defined as external functions.

/** \brief Unary plus.
 */
inline school::threevector operator + (const school::threevector & x) {
  return x;
}

/** \brief Unary minus.
 */
inline school::threevector operator - (const school::threevector & x) {
  return school::threevector(-x.X(), -x.Y(), -x.Z());
}

// Other operators which are also defined as external functions.

/** \brief Addition.
 */
inline school::threevector operator + (const school::threevector & a, const school::threevector & b) {
  return school::threevector(a) += b;
}

/** \brief Subtraction.
 */
inline school::threevector operator - (const school::threevector & a, const school::threevector & b) {
  return school::threevector(a) -= b;
}

/** \brief Multiplication of a vector by a value (vector comes first).
 */
inline school::threevector operator * (const school::threevector & a, const school::threevector::value_type & b) {
  return school::threevector(a) *= b;
}

/** \brief Multiplication of a vector by a value (value comes first).
 */
inline school::threevector operator * (const school::threevector::value_type & a, const school::threevector & b) {
  return school::threevector(b) *= a;
}

/** \brief Division of a vector by a value.
 */
inline school::threevector operator / (const school::threevector & a, const school::threevector::value_type & b) {
  return school::threevector(a) /= b;
}

/** \brief Multiplication of two vectors resulting a value (dot product).
 */
inline school::threevector::value_type operator * (const school::threevector & a, const school::threevector & b) {
  return a.X()*b.X() + a.Y()*b.Y() + a.Z()*b.Z();
}

/** \brief Check equality of two vectors.
 */
inline bool operator == (const school::threevector & a, const school::threevector & b) {
  return a.X() == b.X() && a.Y() == b.Y() && a.Z() == b.Z();
}

/** \brief Check inequality of two vectors.
 */
inline bool operator != (const school::threevector & a, const school::threevector & b) {
  return a.X() != b.X() || a.Y() != b.Y() || a.Z() != b.Z();
}

// I/O operations

/** \brief Print a vector into a stream.
 */
inline std::ostream & operator << (std::ostream & os, const school::threevector & q) {
  return os << "(" << q.X() << "," << q.Y() << "," << q.Z() << ")";
}

#endif
