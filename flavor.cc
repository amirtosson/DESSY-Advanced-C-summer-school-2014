#include <iostream>

#include "flavor.h"

std::ostream & operator << (std::ostream & os, const school::flavor_type & f) {

  switch (f) {
    case school::flavor_type::nuebar:
      os << "nuebar";
      break;
    case school::flavor_type::positron:
      os << "positron";
      break;
    case school::flavor_type::topbar:
      os << "topbar";
      break;
    case school::flavor_type::bottombar:
      os << "bottombar";
      break;
    case school::flavor_type::charmbar:
      os << "charmbar";
      break;
    case school::flavor_type::strangebar:
      os << "strangebar";
      break;
    case school::flavor_type::upbar:
      os << "upbar";
      break;
    case school::flavor_type::downbar:
      os << "downbar";
      break;
    case school::flavor_type::gluon:
      os << "gluon";
      break;
    case school::flavor_type::up:
      os << "up";
      break;
    case school::flavor_type::down:
      os << "down";
      break;
    case school::flavor_type::strange:
      os << "strange";
      break;
    case school::flavor_type::charm:
      os << "charm";
      break;
    case school::flavor_type::bottom:
      os << "bottom";
      break;
    case school::flavor_type::top:
      os << "top";
      break;
    case school::flavor_type::electron:
      os << "electron";
      break;
    case school::flavor_type::nue:
      os << "nue";
      break;
    default:
      break;
  }

  return os;
}