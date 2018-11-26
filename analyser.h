
#ifndef __SCHOOL_ANALYSER_H__
#define __SCHOOL_ANALYSER_H__ 1

#include <iostream>
#include "event.h"
#include "histogram.h"

namespace school {

  /** \brief Simple analyser base class.
   */
  struct analyser
  {
    typedef event::size_type  size_type;
    typedef event::value_type value_type;

    /** \brief Counter for the number of events.
     */
    size_type _M_number_of_events;

    /** \brief The default constructor sets the number of events to zero.
     */
    analyser() : _M_number_of_events(0) {
    }

    // destructor
    virtual ~analyser() {
    }

    /** \brief Analyze an event.
     */
    virtual void analyze(const event & ev, value_type weight) = 0;

    /** \brief Analyze an event and increment the counter.
     */
    void operator () (const event & ev, value_type weight)  {
      this->analyze(ev, weight);
      ++_M_number_of_events;
    }

    /** \brief Print the result.
     *
     * This will be a virtual function, so we need to create only one print
     * operator for the base class. The actual printing is done by the print
     * method in the derived class.
     */
    virtual std::ostream & print(std::ostream &) const = 0;

  }; // end of struct analyser

  /**  \brief Analyser for the total cross section.
   */
  struct total_xsection : analyser {

    /** \brief The sum of weights.
     */
    value_type _M_weight_sum;

    /** \brief The sum of weight squares to calculate statistical error.
     */
    value_type _M_weight2_sum;

    total_xsection() : _M_weight_sum (0.0), _M_weight2_sum(0.0) {
    }

    total_xsection(const total_xsection &) = default;

    virtual ~total_xsection() {
    }

    total_xsection & operator = (const total_xsection &) = default;

    /** \brief Analyze an event.
     */
    void analyze(const event & ev, value_type weight) {
      _M_weight_sum  += weight;
      _M_weight2_sum += weight*weight;
    }

    /** \brief Print the result.
     */
    std::ostream & print(std::ostream & os) const {
      return os
        << "Total cross section is "
        << _M_weight_sum/_M_number_of_events
        << " +/- "
        << std::sqrt(
             (_M_weight2_sum -
              _M_weight_sum * _M_weight_sum / _M_number_of_events
             ) / _M_number_of_events
           )
        << std::endl;
    }

  }; // end of struct total_xsection

  struct pT_dist : analyser {

    /** \brief The histogram.
     */
    histogram _M_hist;

    // default constructor
    pT_dist() : _M_hist(
      "lepton pT distribution",
      histogram::regular_bin_edges(0.0, 400, 20)
    ) {
    }

    pT_dist(const pT_dist &) = default;

    virtual ~pT_dist() {
    }

    pT_dist & operator = (const pT_dist &) = default;

    /** \brief Analyze an event.
     */
    void analyze(const event & p, value_type weight) {
      value_type pT = p[1].momentum.perp();
      _M_hist.accumulate(pT, weight);
    }
    
    /** \brief Print the result.
     */
    std::ostream & print(std::ostream & os) const {
      return _M_hist.print(os, _M_number_of_events);
    }

  }; // end of struct pT_dist

} // end of namespace school

/** \brief Print operator for all analyser descendants.
 *
 * This stream insertion operator will work for all derived class instances by
 * calling the proper virtual print() method.
 */
inline std::ostream & operator << (std::ostream & os, const school::analyser & ana) {
  return ana.print(os);
}

#endif
