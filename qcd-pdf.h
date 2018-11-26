/**
 * \file
 * \brief Definition of the qcd_hadron and qcd_antihadron classes.
 */

#ifndef __SCHOOL_QCD_PDF_H__
#define __SCHOOL_QCD_PDF_H__ 1

#include "flavor.h"

namespace school {

  typedef double value_type;

  /** \brief Abstract base class for hadron implementations.
   *
   * Actual hadron implementations are usually written by someone else, but they
   * all need to implement methods in this class so that we can use them in our
   * project.
   */
  struct qcd_hadron_base {

    /** \brief The pdf function.
     */
    virtual value_type parton(flavor_type, value_type, value_type) const = 0;

    /** \brief Lower bound for the pdf evolution range.
     */
    virtual value_type q2min() const = 0;

    /** \brief Upper bound for the pdf evolution range.
     */
    virtual value_type q2max() const = 0;

    /** \brief The smallest x value.
     */
    virtual value_type xmin() const = 0;

    virtual ~qcd_hadron_base() {
    }

  }; // end of struct qcd_hadron_base

  /** \brief The standard hadron implementation.
   *
   * This is an extremely simplified model.
   */
  struct qcd_hadron : public qcd_hadron_base {

    /** \brief The pdf function.
     */
    virtual value_type parton(flavor_type, value_type, value_type) const {
      return 1.0;
    }

    /** \brief Lower bound for the pdf evolution range.
     */
    virtual value_type q2min() const {
      return 1.0;
    }

    /** \brief Upper bound for the pdf evolution range.
     */
    virtual value_type q2max() const {
      return 1e+20;
    }

    /** \brief The smallest x value.
     */
    virtual value_type xmin() const {
      return 1e-8;
    }

    virtual ~qcd_hadron() {
    }

  }; // end of struct qcd_hadron

  /** \brief Anti-hadron adaptor class.
   *
   * It turns a hadron pdf to an antihadron pdf.
   * Be careful though, for the scope of this antihadron is limited to the
   * scope of its hadron pair. After the original hadron instance is destroyed,
   * its antihadron pair becomes unusable.
   */
  class qcd_antihadron : public qcd_hadron_base {

  private:

    /** \brief The original hadron.
     */
    const qcd_hadron_base & _M_pdf;

  public:

    // It is impossible to create an antihadron without having an actual hadron.
    qcd_antihadron() = delete;

    /** \brief Constructing an antihadron from an existing hadron.
     */
    explicit qcd_antihadron(const qcd_hadron_base & pdf) : _M_pdf(pdf) {
    }

    qcd_antihadron(const qcd_antihadron &) = default;

    qcd_antihadron & operator = (const qcd_antihadron &) = delete;

    //----- destructor -----
    virtual ~qcd_antihadron() {
    }

    /** \brief The pdf function.
     */
    virtual value_type parton(flavor_type fl, value_type x, value_type q2) const {
      //return _M_pdf.parton(static_cast<flavor_type>(-static_cast<int>(fl)), x, q2);
      return _M_pdf.parton(-fl, x, q2);
    }

    /** \brief Lower bound for the pdf evolution range.
     */
    virtual value_type q2min() const {
      return _M_pdf.q2min();
    }

    /** \brief Upper bound for the pdf evolution range.
     */
    virtual value_type q2max() const {
      return _M_pdf.q2max();
    }

    /** \brief The smallest x value.
     */
    virtual value_type xmin() const {
      return _M_pdf.xmin();
    }

  }; // end of class qcd_antihadron

} // end of namespace school

#endif