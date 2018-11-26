/**
 * \file
 * \brief Definition of the matrix_element abstract base class.
 */

#ifndef __MATRIX_ELEMENT_H__
#define __MATRIX_ELEMENT_H__ 1

#include "event.h"

namespace school {

  // The matrix_element will be an abstract base class with 2 abstract methods
  // and a virtual destructor.

  /** \brief Abstract base class for a matrix element.
   */
  struct matrix_element {

    typedef event::value_type value_type;

    // We need a virtual destructor for this data structure.
    virtual ~matrix_element() {}

    // ME me; me(p); me.operator()(p);
    /** \brief Calculate the matrix element.
     */
    virtual value_type operator () (const event &) const = 0;

    /** \brief Resize the event and generate the flavors.
     */
    virtual void set_flavors(event &) const = 0;

  }; // end of struct matrix_element

} // end of namespace school

#endif