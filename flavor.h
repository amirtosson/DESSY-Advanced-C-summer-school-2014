/**
 * \file
 * \brief Definition of particle flavors.
 */

#ifndef __SCHOOL_FLAVOR_H__
#define __SCHOOL_FLAVOR_H__ 1

#include <iostream>

namespace school {

  /** \brief Particle flavors. */
  enum class flavor_type : int {
    nuebar     = -12, // -12
    positron        , // -11
    topbar     = -6 , //  -6
    bottombar       , //  -5
    charmbar        , //  -4
    strangebar      , //  -3
    upbar           , //  -2
    downbar         , //  -1
    gluon           , //   0
    up              , //   1
    down            , //   2
    strange         , //   3
    charm           , //   4
    bottom          , //   5
    top             , //   6
    electron   =  11, //  11
    nue               //  12
  }; // end of enum flavor_type

} // end of namespace school

inline school::flavor_type operator - (const school::flavor_type & f) {
  return static_cast<school::flavor_type>(-static_cast<int>(f));
}

// I/O operators defined in the global namespace

std::ostream & operator << (std::ostream &, const school::flavor_type &);

#endif