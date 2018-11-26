/**
 * \file
 * \brief Implementation of threevector class members.
 */

#include "threevector.h"

namespace school {

  void threevector::rotateX(const value_type & psi) {

    value_type sp = std::sin(psi);
    value_type cp = std::cos(psi);
    value_type py = _M_y;
    value_type pz = _M_z;

    _M_y = cp*py - sp*pz;
    _M_z = sp*py + cp*pz;
  }

  void threevector::rotateY(const value_type & th) {

    value_type st = std::sin(th);
    value_type ct = std::cos(th);
    value_type px = _M_x;
    value_type pz = _M_z;

    _M_x =  ct*px + st*pz;
    _M_z = -st*px + ct*pz;
  }

  void threevector::rotateZ(const value_type & ph) {

    value_type cp = std::cos(ph);
    value_type sp = std::sin(ph);
    value_type px = _M_x;
    value_type py = _M_y;

    _M_x = cp*px - sp*py;
    _M_y = sp*px + cp*py;
  }

} // end of namespace school
