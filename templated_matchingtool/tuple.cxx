#include <iostream>
#include <vector>
#include <utility>

#include "MatchingTool.h"
#include "recoTypes.h"
#include "trigTypes.h"
#include "lambda_init_metric.h"
#include "RecoCombo.h"

int main(){
  typeA a(50,51,52); 
  typeA a2(57,58,59);
  typeB b(60,61,62); 
  typeB b2(67,68,69);
  typeC c(70,71,72); 
  typeD d(80,81,82); 
  

  MatchingTool t;
  std::cout << "----------- MATCH SINGLE TYPE (DEFAULT METRICS) ------------ " << std::endl;
  t.matchReco({a,a2},"HLT_one_two");


  std::cout << "----------- MATCH TWO TYPES (DEFAULT METRICS) ------------ " << std::endl;
  t.matchReco(make_reco({a,a2},{b}),"HLT_one_two");


  std::cout << "----------- MATCH THREE TYPES (DEFAULT METRICS) ------------ " << std::endl;
  t.matchReco(make_reco({a,a2},{b},{c}),"HLT_one_two");


  std::cout << "----------- MATCH OVERRIDE METRICS ------------ " << std::endl;
  //override two of the thee metric definitions
  auto override = make_metric(
    [](const typeA& reco, const trigA trig) {
      std::cout << "overridden A, reco ptA " << reco.ptA() << " trig pt: " << trig.pt()  << std::endl;
      return reco.ptA()-trig.pt();},
    [](const typeB& reco, const trigB trig) {
      std::cout << "overridden B, reco phiA " << reco.phiB() << " trig phi: " << trig.phi()  << std::endl;
      return reco.phiB()-trig.phi();
    }
  );
  t.matchReco(make_reco({a,a2},{b,b2},{c}),"HLT_one_two",override);


  std::cout << "----------- MATCH OVERRIDE METRICS (IN-CALL DEFINITION) ------------ " << std::endl;
  //override type A, and type B metrics, use default metric for C
  t.matchReco(make_reco({a,a2},{b},{c}),"HLT_one_two",make_metric([](const typeA& reco, const trigA& trig){return 110.0;},
                                                                  [](const typeB& reco, const trigB& trig){return 120.0;}));

  std::cout << "--------------------------------- " << std::endl;
};