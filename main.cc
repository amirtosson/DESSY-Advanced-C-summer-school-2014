

#include "mc-integral.h"
#include "me-pp-to-llbar.h"

#include <iostream>

using namespace school;
using namespace std;

int main()
{
  qcd_hadron       pdf1;       // incoming hadron
  qcd_antihadron   pdf2(pdf1); // incoming antihadron
  me_pp_to_llbar   me;         // matrix element

  // MC integral
  mc_integral xsec(14000.0, &pdf1, &pdf2, &me);

  // analysers
  total_xsection tot1, tot2;
  pT_dist        pT;

  // Generate event and calculate the cross section.
  for (unsigned long k = 0; k < 1000000; ++k ) { // zawed events bra7tk ba2a!!
    xsec({&tot1, &tot2, &pT});
  }

  // Print the results.
  tot1.print(std::cout);
  tot2.print(std::cout);
  pT.print  (std::cout);

  return 0;
}
