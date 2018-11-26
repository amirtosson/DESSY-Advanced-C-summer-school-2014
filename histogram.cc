/**
 * \file
 * \brief Implementation of histogram class methods.
 */

#include "histogram.h"

#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>

namespace school {

  std::ostream & histogram::print(std::ostream & os, size_type npoints) const {

    // print the name
    os << "#   " << _M_name << std::endl;

    // print the bins
    auto p    = _M_bins.begin();
    auto next = p;
    ++next;

    while (next != _M_end) {
      const bin & b  = p->second;
      value_type  dx = next->first - p->first;
      os << p->first                    << "  "
         << next->first                 << "  "
         << b.sum_of_weights/npoints/dx << "  "
         << std::sqrt((b.sum_of_squared_weights - b.sum_of_weights * b.sum_of_weights / npoints) / npoints) / dx
         << std::endl;
      ++next;
      ++p;
    }

    return os;
  }

  std::vector<histogram::value_type> histogram::regular_bin_edges(
    value_type lower,
    value_type upper,
    size_type  n_bins
  ) {

    std::vector<value_type> res;
    value_type              step = (upper - lower) / n_bins;

    for (size_type k = 0; k <= n_bins; ++k) {
      res.push_back(lower + k*step);
    }

    return res;
  }

  std::vector<histogram::value_type> histogram::log_bin_edges(
    value_type lower,
    value_type upper,
    size_type  n_bins
  ) {

    std::vector<value_type> res;
    value_type              step = log10(upper/lower) / n_bins;

    for (size_type k = 0; k <= n_bins; ++k) {
      res.push_back(lower*pow(10.0,k*step));
    }

    return res;
  }

} // end of namespace school
