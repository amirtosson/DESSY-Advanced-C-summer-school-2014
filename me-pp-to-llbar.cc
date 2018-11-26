/**
 * \file
 * \brief Implementation of me_pp_to_llbar members.
 */

#include "me-pp-to-llbar.h"
#include "school-rng.h"

#include <cfloat>

// This is for local use only
static inline
school::matrix_element::value_type
sqr(school::matrix_element::value_type x) {
  return x*x;
}

namespace school {

  matrix_element::value_type me_pp_to_llbar::operator () (const event & ev) const {

    // Boson mass
    const value_type mB = 270.0;

    // Boson width
    const value_type gB = 17.0;

    // alpha
    const value_type alpha = 1.0/129.0;

    // electron vector coupling
    const value_type vq = 2.65;

    // electorn axial coupling
    const value_type aq = 0.73;

    // quark vector coupling
    value_type vp = abs(static_cast<int>(ev[0].flavor))%2 == 0 ? 5.3 : -3.9;

    // quark axial coupling
    value_type ap = abs(static_cast<int>(ev[0].flavor))%2 == 0 ? 3.6 : -4.2;

    // anti-quark momentum
    const lorentzvector & pbar = static_cast<int>(ev[-1].flavor) < 0 ? ev[-1].momentum : ev[0].momentum;

    // quark momentum
    const lorentzvector & p = static_cast<int>(ev[-1].flavor) < 0 ? ev[0].momentum : ev[-1].momentum;

    // positron momentum
    const lorentzvector & qbar = ev[1].momentum;

    // electron momentum
    const lorentzvector & q = ev[2].momentum;

    // overall constants and propagator factor
    value_type Q2     = 2.*p*pbar;
    value_type bw     = 1./(sqr(Q2-sqr(mB))+sqr(mB*gB));
    value_type factor = 32.*3.0*sqr(4.*M_PI*alpha)*bw;

    // matrix element squared
    value_type me2 =
      factor * (
        ( sqr(vp*aq+vq*ap) + sqr(vp*vq+ap*aq) ) * (p*qbar) * (pbar*q) +
        ( sqr(vp*aq-vq*ap) + sqr(vp*vq-ap*aq) ) * (pbar*qbar) * (p*q)
      );

    // we need to avearge over spins and colors
    me2 /= 2.0*3.0*3.0;

    // we need to divide by the probabilities with which flavors and
    // beams have been selected
    me2 *= 2.0*5.0;

    return me2;
  }

  void me_pp_to_llbar::set_flavors(event & ev) const {

    ev.resize(2);

    ev[1].flavor = flavor_type::electron;
    ev[2].flavor = flavor_type::positron;

    int quark_flavor = std::uniform_int_distribution<int>(1,5)(_G_random_engine);

    ev[-1].flavor = static_cast<flavor_type>( quark_flavor);
    ev[ 0].flavor = static_cast<flavor_type>(-quark_flavor);

    int qbeam = std::uniform_int_distribution<int>(0,1)(_G_random_engine);

    if ( qbeam == 1 ) {
      std::swap(ev[-1].flavor, ev[0].flavor);
    }
  }

} // end of namespace school