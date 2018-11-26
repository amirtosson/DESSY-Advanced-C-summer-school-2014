

#ifndef __SCHOOL_MC_INTEGRAL_H__
#define __SCHOOL_MC_INTEGRAL_H__

#include "event.h"
#include "matrix-element.h"
#include "qcd-pdf.h"
#include "analyser.h"

#include <initializer_list> //to use of initializer list syntax to initialize types
#include <utility>

namespace school {// the used name space !!
  class mc_integral {

  public:

    typedef event::value_type value_type;

  private:

    value_type _M_Ecm;
    const qcd_hadron_base *_M_pdf1;
    const qcd_hadron_base *_M_pdf2;
    const matrix_element *_M_me;
    mutable event  _TMP_p; // allow to be changed inside the const methods
    mutable value_type _TMP_weight;

  public:
    mc_integral(
      value_type             Ecm ,
      const qcd_hadron_base *pdf1,
      const qcd_hadron_base *pdf2,
      const matrix_element  *me
    ) :
    _M_Ecm  (Ecm ),
    _M_pdf1 (pdf1),
    _M_pdf2 (pdf2),
    _M_me   (me  ) {
    }


    void operator () ();// mogoda fy el cc

    //Returns the last event.

    std::pair<value_type, const event &> last_event() const {
      return {_TMP_weight, _TMP_p};
    }
    
    
    //  Generate one event and analyse it.

    void operator () (std::initializer_list<analyser*> ah) {
      this->operator()();
      for(auto iter : ah) {
        iter->operator()(_TMP_p, _TMP_weight);
      }
    }

  };

}

#endif
