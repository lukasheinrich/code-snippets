#ifndef DUMMYFEATURES
#define DUMMYFEATURES

template<typename REQUESTED, typename STORED, typename CONTAINER>
struct FeatureGetter;

// these are just some dummy methods that get the features

//element feature case
template<typename REQUESTED, typename CONTAINER>
struct FeatureGetter<REQUESTED,REQUESTED,CONTAINER>{
  static std::vector<Feature<REQUESTED> > getFeatures(EventStore* evtStore){

    auto cont = evtStore->getContainer();

    ElementLink<CONTAINER>* the_link = new ElementLink<CONTAINER>(*cont,0);
    LinkHolder_with_Link<REQUESTED,CONTAINER>*  holder_with_link = new LinkHolder_with_Link<REQUESTED,CONTAINER>(the_link);

    Feature<REQUESTED> feature(holder_with_link->getlink()->operator->(),holder_with_link);
    
    std::vector<Feature<REQUESTED> > result;
    result.push_back(feature);
    return result;
  }
};

//container feature case
template<typename CONTAINER>
struct FeatureGetter<CONTAINER,CONTAINER,CONTAINER>{
  static std::vector<Feature<CONTAINER> > getFeatures(EventStore* evtStore){


    auto cont = evtStore->getContainer();

    CONTAINER* viewcont = new CONTAINER;
    
    for(int i = 0;i<cont->size();++i){
      viewcont->push_back(cont->at(i));
    }


    auto the_link = new DataLink<CONTAINER>(*cont);
    auto holder_with_link = new LinkHolder_with_Link<CONTAINER,CONTAINER>(the_link);

    Feature<CONTAINER> feature(holder_with_link->getlink()->operator->(),holder_with_link);
    
    std::vector<Feature<CONTAINER> > result;
    result.push_back(feature);
    return result;
  }
};


//flattened case
template<typename REQUESTED, typename CONTAINER>
struct FeatureGetter<REQUESTED,CONTAINER,CONTAINER>{
  static std::vector<Feature<REQUESTED> > getFeatures(EventStore* evtStore){

    auto cont = evtStore->getContainer();

    CONTAINER* viewcont = new CONTAINER;
    
    for(int i = 0;i<cont->size();++i){
      viewcont->push_back(cont->at(i));
    }

    std::vector<Feature<REQUESTED> > result;

    for(int i = 0;i<viewcont->size();++i){
      ElementLink<CONTAINER>* the_link = new ElementLink<CONTAINER>(*viewcont,i);
      LinkHolder_with_Link<REQUESTED,CONTAINER>*  holder_with_link = new LinkHolder_with_Link<REQUESTED,CONTAINER>(the_link);
      Feature<REQUESTED> feature(holder_with_link->getlink()->operator->(),holder_with_link);
      result.push_back(feature);
    }

    return result;
  }
};

#endif