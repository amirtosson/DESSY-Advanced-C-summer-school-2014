/**
 * \file
 * \brief Implementation of event related operations.
 */

#include "event.h"
#include "school-rng.h"
#include "rambo.h"

namespace school {

  event::value_type generate_event(event & p, event::value_type Ecm) {

    // By default it will result random numbers in the range [0,1)
    std::uniform_real_distribution<event::value_type> rng;

    //----- generating the momentum fraction of the incoming parton -----
    p.xa = rng(_G_random_engine);
    p.xb = rng(_G_random_engine);

    //----- incoming parton -----
    p[-1].momentum = 0.5*p.xa*lorentzvector(0.0, 0.0, -Ecm, Ecm);
    p[ 0].momentum = 0.5*p.xb*lorentzvector(0.0, 0.0,  Ecm, Ecm);

    //----- generates the outgoings in partonic c.m. frame -----
    event::value_type weight = rambo(p.xa*p.xb*Ecm*Ecm, p.begin()+2, p.end());

    //----- boost to laboratory frame -----
    event::value_type bz = (p.xb-p.xa)/(p.xa+p.xb);

    if (bz != 0.0) {
      for (event::size_type i = 1; i <= p.number_of_outgoings(); i++)
        p[i].momentum.boost(0.0, 0.0, bz);
    }

    weight /= 2.0*p.xa*p.xb*Ecm*Ecm; // flux factor

    return weight;
  }

} // end of namespace school

std::ostream & operator << (std::ostream & os, const school::event & a) {

  school::lorentzvector itot, otot;

  os << "xa = " << a.xa << " xb = " << a.xb << "\n";
  os << "----------\n";

  // Print the incommings

  for (school::event::index_type i : {-1,0}) {
    itot += a[i].momentum;
    os << "incoming(" << i << "): " << a[i].flavor << ", "<< a[i].momentum << " " << a[i].momentum.mag2() << "\n";
  }

  // Print the outgoings

  for (school::event::size_type i = 1; i <= a.number_of_outgoings(); i++) {
    otot += a[i].momentum;
    os << "outgoing(" << i << "): "<< a[i].flavor << ", "<< a[i].momentum << " " << a[i].momentum.mag2() << "\n";
  }

  // Print momentum summary

  os << "Total incoming momentum: " << itot      << std::endl;
  os << "Total outgoing momentum: " << otot      << std::endl;
  os << "Momentum conservation:   " << itot-otot << std::endl;

  return os;
}
