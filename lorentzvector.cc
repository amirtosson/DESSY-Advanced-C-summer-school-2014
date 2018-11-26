/**
 * \file
 * \brief Implementation of lorentzvector class members.
 */

#include "lorentzvector.h"

namespace school {

  void lorentzvector::boost(const value_type & bx, const value_type & by, const value_type & bz) {

    double b2     = bx*bx + by*by + bz*bz;
    double gamma  = 1.0/std::sqrt(1.0 - b2);
    double bp     = bx*_M_x + by*_M_y + bz*_M_z;
    double gamma2 = (b2 > 0.0 ? (gamma - 1.0)/b2 : 0.0);

    _M_x = _M_x + gamma2*bp*bx + gamma*bx*_M_t;
    _M_y = _M_y + gamma2*bp*by + gamma*by*_M_t;
    _M_z = _M_z + gamma2*bp*bz + gamma*bz*_M_t;
    _M_t = gamma*(_M_t + bp);
  }

} // end of namespace school
