

#include "mc-integral.h"

using namespace std;

namespace school {

  void mc_integral::operator () () {

    // Setting the flavours, this resizes _TMP_p
    _M_me->set_flavors(_TMP_p);

    // Generate the momenta.
    _TMP_weight = generate_event(_TMP_p, _M_Ecm);

    // For factorization scale we use shat.
    value_type shat = (_TMP_p[-1].momentum+_TMP_p[0].momentum).mag2();

    // Calculate the pdfs.
    _TMP_weight *= _M_pdf1 -> parton(_TMP_p[-1].flavor, _TMP_p.xa, shat);
    _TMP_weight *= _M_pdf2 -> parton(_TMP_p[ 0].flavor, _TMP_p.xb, shat);

    // Calculate the matrix element.
    _TMP_weight *= _M_me -> operator()(_TMP_p);
  }

} // end of namespace school
