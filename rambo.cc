/**
 * \file
 * \brief Implementation of the rambo() function.
 */

#include "rambo.h"

namespace school {

  static lorentzvector __rambo_helper_random_momentum() {

    std::uniform_real_distribution<event::value_type> rng;

    event::value_type E   = -std::log(rng(_G_random_engine)*rng(_G_random_engine));
    event::value_type pz  = E*(2.0*rng(_G_random_engine) - 1.0);
    event::value_type pt  = std::sqrt(E*E - pz*pz);
    event::value_type phi = 6.28318530717958647692*rng(_G_random_engine);

    return lorentzvector(pt*std::cos(phi), pt*std::sin(phi), pz, E);
  }

  /** This function calculates the phase space weights for the RAMBO events.
   * The proper 2pi factors are included in the phase space definition.
   */
  static event::value_type __rambo_helper_weight(
    event::size_type  n,
    event::value_type s
  ) {

    constexpr event::value_type __8PI   =  25.13274122871834590768;
    constexpr event::value_type __16PI2 = 157.91367041742973790108;

    //----- fact[n] = exp(log(Gamma[n]*Gamma[n-1])/(n-2)) -----

    static const event::value_type fact[] = {
      1.000000000000000000000, 1.000000000000000000000,
      1.000000000000000000000, 2.000000000000000000000,
      3.464101615137754587050, 5.241482788417793214280,
      7.325683002969412729490, 9.711867496604076595340,
      12.39635026120588892703, 15.37624008321082805550,

      18.64921022211253121271, 22.21334732883035904420,
      26.06704940665039454817, 30.20895473052848875326,
      34.63789090520187258023, 39.35283742689448285515,
      44.35289755618292354658, 49.63727677424801864857,
      55.20526599889455311234, 61.05622831083046240725,

      67.189588314900381553350, 73.604823510775700955150,
      80.301457218028968401580, 87.279052719104399855340,
      94.537208367699191038680, 102.07555347055500771508,
      109.89374479486319958781, 117.99146358623666580202,
      126.36841300677002588944, 135.02431592135521673949,

      143.95891297472152603605, 153.17196091274811705250,
      162.66323111025862674191, 172.43250827433702043364,
      182.47958929763210591531, 192.80428224046477961708,
      203.40640542405709375678, 214.28578662004717056856,
      225.44226232377745474056, 236.87567710075244487879
    };

    return std::pow(s/(__16PI2*fact[n]), (static_cast<int>(n)-2)/__8PI);
  }

  event::value_type rambo(
    event::value_type s,
    event::iterator   first,
    event::iterator   last
  ) {

    lorentzvector psum;

    for (auto iter = first; iter < last; iter++) {
      psum += (iter->momentum = __rambo_helper_random_momentum());
    }

    //----- parameters of the conform transformation -----

    event::value_type x    = std::sqrt(s)/std::sqrt(psum.mag2());
    threevector       bVec = -psum.boostVector();

    //----- do the conform transformation -----

    for (auto iter = first; iter < last; iter++) {
      iter->momentum.boost(bVec);
      iter->momentum *= x;
    }

    return __rambo_helper_weight(static_cast<event::size_type>(last-first), s);
  }

} // end of namespace school