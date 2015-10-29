#ifndef DEFAULTMETRICS_H
#define DEFAULTMETRICS_H

#include "trigTypes.h"
#include "recoTypes.h"

struct MatchMetrics{
  double distance(const typeA& reco, const trigA& trig) const {
    std::cout << "default A-type metric reco: " << reco.etaA() << " trig: " << trig.eta() << std::endl;
    return reco.etaA()-trig.eta();
  }
  double distance(const typeB& reco, const trigB& trig) const {
    std::cout << "default B-type metric reco: " << reco.etaB() << " trig: " << trig.eta() << std::endl;
    return reco.etaB()-trig.eta();
  }
  double distance(const typeC& reco, const trigC& trig) const {
    std::cout << "default C-type metric reco: " << reco.etaC() << " trig: " << trig.eta() << std::endl;
    return reco.etaC()-trig.eta();
  }
};
#endif