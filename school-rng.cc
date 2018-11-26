/**
 * \file
 * \brief Definition of our global random number generator.
 */

#include "school-rng.h"

namespace school {

  /** \brief Our global random number generator.
   * 
   *  We need a random number generator. In C++11 there are many
   *  random number generators available. We want to have a global
   *  generator that every routine can use so that we don't have to always
   *  pass through this information. We use mt19937_64 as defult generator in
   *  the school namespace. This can be changed if it is needed...
   */
  std::mt19937_64 _G_random_engine;

} // end of namespace school