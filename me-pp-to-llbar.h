/**
 * \file
 * \brief Definition of the me_pp_to_llbar class.
 */

#ifndef __SCHOOL_ME_PP_TO_LLBAR_H__
#define __SCHOOL_ME_PP_TO_LLBAR_H__ 1

#include "matrix-element.h"

namespace school {

  /** \brief A matrix element implementation.
   */
  struct me_pp_to_llbar : public matrix_element {

    /** \brief Calculate the matrix element.
     */
    value_type operator() (const event &) const;

    /** \brief Resize the event and generate the flavors.
     */
    void set_flavors(event &) const;

  }; // end of struct me_pp_to_llbar

} // end of namespace school

#endif