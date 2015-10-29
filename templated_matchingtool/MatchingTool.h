#ifndef MATCHINGTOOL_H
#define MATCHINGTOOL_H

#include "DefaultMetrics.h"
#include "RecoCombo.h"
#include "recoToTrigMap.h"
#include "MetricOverride.h"

struct MatchingTool{
  typedef MatchMetrics DefaultMetrics;

  //general purpose signature for multi-types
  template<typename... TYPES, typename METRICS = DefaultMetrics>
  void matchReco(const RecoCombo<TYPES...>& rcombo,const std::string& chain, METRICS metrics = METRICS()){
    matchTypes(rcombo,metrics);
  }
  
  //convenience function for a single type
  template<typename T, typename METRICS = DefaultMetrics>
  void matchReco(const std::initializer_list<T>& initlist,const std::string& chain, METRICS metrics = METRICS()){
    matchTypes(make_reco(initlist),metrics);
  }

private:
  template<typename T, typename METRICS>
  void matchTypes(const Storage<T>& recos, METRICS metrics){
    std::cout << "processing individual reco type: " << typeid(T).name() << std::endl;
    std::cout << "recos size is: " << recos.size() << std::endl;

    typedef typename Registry::typeMap<T>::type trigType;
    std::cout << "trigger type is: " << typeid(trigType).name() << std::endl;

    std::vector<trigType> triggerObjs(recos.size());
    auto distance_matrix = makeDistanceMatrix(recos,triggerObjs,metrics); 
  }

  template<typename FIRST, typename... REST, typename METRICS>
  typename std::enable_if<(sizeof...(REST)>0)>::type matchTypes(const RecoCombo<FIRST,REST...>& rcombo, METRICS metrics){
    matchTypes<FIRST>(rcombo.template get<FIRST>(),metrics);
    const RecoCombo<REST...>& restcomb = rcombo;
    matchTypes<REST...>(restcomb,metrics);
  }

  template<typename RECO,typename TRIGGER, typename METRICS>
  std::vector<std::vector<double> > makeDistanceMatrix(const std::vector<RECO> recs,
                                                       const std::vector<TRIGGER>& trigs,
                                                       METRICS m){
    std::cout << "making distance matrix" << std::endl;
    std::cout << "size of recos: " << recs.size() << std::endl;
    std::cout << "size of trigs: " << trigs.size() << std::endl;

    DefaultMetrics dmetrics;
    auto oride = make_override(m,dmetrics);
    for(auto r : recs){
      for(auto t : trigs){
        std::cout << "distance is: " << oride.distance(r,t) << std::endl;
      }
    }
    std::vector<std::vector<double> > matrix;
    return matrix;
  }
};
#endif