/**
 * \file
 * \brief Definition of the lorentzvector class and related operations.
 */

#ifndef __SCHOOL_LORENTZVECTOR_H__
#define __SCHOOL_LORENTZVECTOR_H__

#include "threevector.h"

namespace school {

  /** \brief Representation of a Lorentz vector.
   *
   * A Lorentz vector consist of 3 space-like components and one time-like
   * component. That's why we use a threevector as the base class for a Lorentz
   * vector.
   */
  class lorentzvector : public threevector {

  public:

    /** \brief The scalar type of lorentzvector's time-like component.
     *
     * We bind this to the underlying threevector's value_type, so if we change
     * the floating point type there it will be automatically changed here, too.
     */
    typedef threevector::value_type value_type;

  protected:

    // We add a time-like component to the three space-like components defined
    // in threevector.

    value_type _M_t; ///< Time-like component t.

  public:

    /** \brief The empty constructor sets every data member to zero.
     *
     * Space-like components are handled by the underlying threevector
     * constructor. If we don't state it otherwise, threevector's empty
     * constructor will be called before running lorentzvector's constructor.
     */
    lorentzvector() :
    _M_t(0.0) {
    }

    // We don't want a simple double value treated as a lorentzvector. Never.
    // So we allow only explicit conversion to a lorentzvector using this constructor.

    /** \brief Contructor with 1 parameter.
     * 
     * We don't want a single floating point value treated as a lorentzvector.
     * Never. So we allow only explicit conversion to a lorentzvector using this
     * constructor. To prevent implicit conversion from a floating point value
     * to a lorentzvector we use the keyword "explicit" in the constructor.
     */
    explicit lorentzvector(const value_type & x) :
    threevector(x),
    _M_t(0.0) {
    }

    /** \brief This constructor can be used with 2, 3 or 4 parameters.
     */
    lorentzvector(const value_type & x, const value_type & y, const value_type & z = 0, const value_type & t = 0) :
    threevector(x, y, z),
    _M_t(t) {
    }

    /** \brief Convert a threevector and optionally a time-like value to a lorentzvector.
     */
    lorentzvector(const threevector & v, const value_type & t = 0) :
    threevector(v),
    _M_t(t) {
    }

    /** \brief The copy constructor.
     *
     * Makes a lorentzvector out of another already existing lorentzvector. We
     * are satisfied with the default implementation so we use the keyword
     * "default" here.
     */
    lorentzvector(const lorentzvector &) = default;

    /** \brief The assignment operator.
     *
     * It is similar to the copy constructor, but in this case data members
     * already exist and have to be assigned a new value.
     */
    lorentzvector & operator = (const lorentzvector &) = default;

    /** \brief The destructor of lorentzvector.
     */
    ~lorentzvector() = default;

    // Element access. We need to define these only for the time-like component,
    // for the space-like components are already defined in threevector.

    /** \brief Return time-like component t as a constant reference.
     */
    const value_type & T() const {
      return _M_t;
    }

    /** \brief Return time-like component t as a reference.
     */
    value_type & T() {
      return _M_t;
    }

    // Computed assignments (a+=b; a-=b; a*=b; a/=b;).
    // We can reuse the computed assignments already defined in threevector.

    lorentzvector & operator += (const lorentzvector & b) {
      threevector::operator+=(b);
      _M_t += b._M_t;
      return *this;
    }

    lorentzvector & operator -= (const lorentzvector & b) {
      threevector::operator-=(b);
      _M_t -= b._M_t;
      return *this;
    }

    lorentzvector & operator *= (const value_type & b) {
      threevector::operator*=(b);
      _M_t *= b;
      return *this;
    }

    lorentzvector & operator /= (const value_type & b) {
      threevector::operator/=(b);
      _M_t /= b;
      return *this;
    }

    // Other member functions.

    value_type plus      () const { return _M_t + _M_z;                      }
    value_type minus     () const { return _M_t - _M_z;                      }
    value_type rapidity  () const { return 0.5*std::log(plus()/minus());     }
    value_type prapidity () const { return -std::log(std::tan(0.5*theta())); }
    value_type mag2      () const { return _M_t*_M_t - threevector::mag2();  }

    threevector boostVector() const {
      return threevector(*this) /= _M_t;
    }

    // Lorentz boost

    void boost(const value_type &, const value_type &, const value_type &); // This is defined in lorentzvector.cc.
    void boost(const threevector & a) { boost(a.X(), a.Y(), a.Z()); }

  }; // end of class lorentzvector

  /** Dot product */
  inline lorentzvector::value_type dot(const lorentzvector & a, const lorentzvector & b) {
    return a.T()*b.T() - a.X()*b.X() - a.Y()*b.Y() - a.Z()*b.Z();
  }

} // end of namespace school

// Operators are declared in the global namespace.

// Unary operators

inline school::lorentzvector operator + (const school::lorentzvector & a) {
  return a;
}

inline school::lorentzvector operator - (const school::lorentzvector & a) {
  return school::lorentzvector(-a.X(), -a.Y(), -a.Z(), -a.T());
}

// Other operators

inline school::lorentzvector operator + (const school::lorentzvector & a, const school::lorentzvector & b) {
  return school::lorentzvector(a) += b;
}

inline school::lorentzvector operator - (const school::lorentzvector & a, const school::lorentzvector & b) {
  return school::lorentzvector(a) -= b;
}

inline school::lorentzvector operator * (const school::lorentzvector & a, const school::lorentzvector::value_type & b) {
  return school::lorentzvector(a) *= b;
}

inline school::lorentzvector operator * (const school::lorentzvector::value_type & b, const school::lorentzvector & a) {
  return school::lorentzvector(a) *= b;
}

inline school::lorentzvector operator / (const school::lorentzvector & a, const school::lorentzvector::value_type & b) {
  return school::lorentzvector(a) /= b;
}

/** Dot product */
inline school::lorentzvector::value_type operator * (const school::lorentzvector & a, const school::lorentzvector & b) {
  return a.T()*b.T() - a.X()*b.X() - a.Y()*b.Y() - a.Z()*b.Z();
}

inline bool operator == (const school::lorentzvector & a, const school::lorentzvector & b) {
  return a.X() == b.X() && a.Y() == b.Y() && a.Z()== b.Z() && a.T()== b.T();
}

inline bool operator != (const school::lorentzvector & a, const school::lorentzvector & b) {
  return a.X() != b.X() || a.Y() != b.Y() || a.Z() != b.Z() || a.T() != b.T();
}

// I/O operators

inline std::ostream & operator << (std::ostream & os, const school::lorentzvector & q) {
  return os << "(" << q.X() << ", " << q.Y() << ", " << q.Z() << "; " << q.T() << ")";
}

/*
inline std::ostream & operator << (std::ostream & os, const school::lorentzvector & q) {
  return os << "(" << static_cast<const school::threevector &>(q) << "; " << q.T() << ")";
}
*/

#endif
