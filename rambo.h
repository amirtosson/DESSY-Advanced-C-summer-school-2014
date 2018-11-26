/**
 * \file
 * \brief Declaration of the rambo() function.
 */

#ifndef __SCHOOL_RAMBO_H__
#define __SCHOOL_RAMBO_H__

#include "event.h"
#include "school-rng.h"

namespace school {

  event::value_type rambo(
    event::value_type s,
    event::iterator   first,
    event::iterator   last
  );

} // end of namespace school

#endif
