/**
 * \file
 * \brief Definition of the event class.
 */

#ifndef __SCHOOL_EVENT_H__
#define __SCHOOL_EVENT_H__

#include "flavor.h"
#include "lorentzvector.h"

// Stdandard includes
#include <iostream>
#include <vector>

namespace school {

  // Structure for representing incoming and outgoing particles

  /** \brief Representation of a particle.
   * 
   * A particle has a flavor and a momentum.
   */
  struct particle {

    /** Flavor of the particle. */
    flavor_type   flavor;

    /** Momentum of the particle. */
    lorentzvector momentum;

  }; // end of struct particle

  /** \brief Representation of an event.
   *
   * An event is composed of 2 incoming particles and n outgoing particles.
   */
  class event {

  public:

    /** Bind our size_type to the particle vector's size_type. */
    typedef std::vector<particle>::size_type size_type;

    /** An element index can be negative, so we need a different type for it. */
    typedef long int index_type;

    /** Bind our iterator to the particle vector's iterator. */
    typedef std::vector<particle>::iterator iterator;

    /** Bind our const_iterator to the particle vector's const_iterator. */
    typedef std::vector<particle>::const_iterator const_iterator;

    /** Bind our value_type to lorentzvector's value_type. */
    typedef lorentzvector::value_type value_type;

    /** Momentum fraction of one incoming parton. */
    value_type xa;

    /** Momentum fraction of one incoming parton. */
    value_type xb;

  private:

    /** This will store the 2 incoming and n outgoing particles. */
    std::vector<particle> _M_array;

  public:

    /** Construct an event with n outgoing particles. */
    explicit event(size_type n = 1) : _M_array(n+2) {
    }

    // Copy
    event(const event &)               = default;
    event & operator = (const event &) = default;

    // Dectructor
    ~event() = default;

    /** \brief Element access (non-const).
     * 
     * Indexing starts from -1.
     * Elements -1 and 0 are the incoming particles.
     * Outgoing particles are indexed from 1 to n.
     */
    particle & operator [] (index_type k) {
      return _M_array[static_cast<size_type>(k+1)];
    }

    /** \brief Element access (const).
     * 
     * Indexing starts from -1.
     * Elements -1 and 0 are the incoming particles.
     * Outgoing particles are indexed from 1 to n.
     */
    const particle & operator [] (index_type k) const {
      return _M_array[static_cast<size_type>(k+1)];
    }

    iterator begin() {
      return _M_array.begin();
    }

    const_iterator begin() const {
      return _M_array.begin();
    }

    iterator end() {
      return _M_array.end();
    }

    const_iterator end() const {
      return _M_array.end();
    }

    /** Resize event to contain n outgoing particles. */
    void resize(size_type n) {
      _M_array.resize(n+2);
    }

    /** Query the number of outgoing particles. */
    size_type number_of_outgoings() const {
      return _M_array.size()-2;
    }

  }; // end of class event

  /** Generate the hadronic event. */
  event::value_type generate_event(event &, event::value_type);

} // end of namespace school

// I/O operators defined in the global namespace

std::ostream & operator << (std::ostream &, const school::event &);

#endif