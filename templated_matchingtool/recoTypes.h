#ifndef RECOTYPES_H
#define RECOTYPES_H

struct typeA {
  typeA(double pt = 0,double eta = 0,double phi = 0) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double ptA()const{return m_pt;}
  double etaA()const{return m_eta;}
  double phiA()const{return m_phi;}
  void print(){std::cout << "typeA pt: " << ptA() << " eta: " << etaA() << " phi: " << phiA()<< std::endl;}
  double m_pt;
  double m_eta;
  double m_phi;
};
struct typeB {
  typeB(double pt = 0,double eta = 0,double phi = 0) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double ptB()const{return m_pt;}
  double etaB()const{return m_eta;}
  double phiB()const{return m_phi;}
  void print(){std::cout << "typeB pt: " << ptB() << " eta: " << etaB() << " phi: " << phiB()<< std::endl;}
  double m_pt;
  double m_eta;
  double m_phi;
};
struct typeC {
  typeC(double pt = 0,double eta = 0,double phi = 0) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double ptC()const{return m_pt;}
  double etaC()const{return m_eta;}
  double phiC()const{return m_phi;}
  void print(){std::cout << "typeC pt: " << ptC() << " eta: " << etaC() << " phi: " << phiC()<< std::endl;}
  double m_pt;
  double m_eta;
  double m_phi;
};
struct typeD {
  typeD(double pt = 0,double eta = 0,double phi = 0) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double ptD()const{return m_pt;}
  double etaD()const{return m_eta;}
  double phiD()const{return m_phi;}
  void print(){std::cout << "typeD pt: " << ptD() << " eta: " << etaD() << " phi: " << phiD()<< std::endl;}
  double m_pt;
  double m_eta;
  double m_phi;
};

#endif