/**
 * \file
 * \brief Definition of the histogram class.
 */

#ifndef __SCHOOL_HISTOGRAM_H__
#define __SCHOOL_HISTOGRAM_H__ 1

#include <map>
#include <string>
#include <iostream>
#include <vector>

namespace school {

  /** \brief Histogram class.
   */
  class histogram {

  public:

    typedef size_t size_type;
    typedef double value_type;

    /** \brief A histogram bin.
     */
    struct bin {

      value_type sum_of_weights;
      value_type sum_of_squared_weights;

      /** \brief Default constructor.
       */
      bin() :
      sum_of_weights        (0.0),
      sum_of_squared_weights(0.0) {
      }

      bin(const bin &)               = default;
     ~bin()                          = default;
      bin & operator = (const bin &) = default;

      /** \brief Add a new weight to the histogram bin.
       */
      void count(value_type weight) {
        sum_of_weights         += weight;
        sum_of_squared_weights += weight*weight;
      }
    }; // end of struct bin

  private:

    /** \brief Name of the analysis.
     */
    std::string _M_name;

    /** \brief Content of the histogram.
     */
    std::map<value_type,bin> _M_bins;

    /** \brief The last bin (this defines the upper bound).
     */
    std::map<value_type,bin>::const_iterator _M_end;

  public:

    /** The default constructor is disabled.
     * There is no analysis without a name and a binning. */
    histogram() = delete;

    histogram(const histogram &)               = default;
    ~histogram()                               = default;
    histogram & operator = (const histogram &) = default;

    /** Construct giving name and bin boundaries. */
    histogram(const std::string & name, const std::vector<value_type> & edges) :
    _M_name(name) {
      for (auto e = edges.begin() + 1; e != edges.end(); e++) {
        _M_bins[*e] = bin();
      }
      _M_end = _M_bins.end(); // the last+1 bin
      _M_end--;               // this is the last bin
    }

    /** \brief Accumulate weights into the histogram.
     */
    void accumulate(value_type observable, value_type weight) {

      // do nothing if observable is smaller than xmin
      if (observable < _M_bins.begin()->first) { return; }

      // get the right bin
      std::map<value_type,bin>::iterator b = _M_bins.upper_bound(observable);

      // do nothing if the observable is bigger than xmax
      if (b == _M_bins.end()) { return; }

      // otherwise fill the weight
      b->second.count(weight);
    }

    /** \brief Print histogram.
     */
    std::ostream & print(std::ostream &, unsigned long) const;

    /** \brief Helper to calculate bin boundaries.
     */
    static std::vector<value_type> regular_bin_edges(
      value_type lower,
      value_type upper,
      size_type  n_bins
    );

    /** \brief Helper to calculate bin boundaries.
     */
    static std::vector<value_type> log_bin_edges(
      value_type lower,
      value_type upper,
      size_type  n_bins
    );

  }; // end of class histogram

} // end of namespace school

#endif