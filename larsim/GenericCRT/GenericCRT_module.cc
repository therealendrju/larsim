////////////////////////////////////////////////////////////////////////
// Class:       GenericCRT
// Plugin Type: producer (art v3_05_01)
// File:        GenericCRT_module.cc
//
// Generated at Wed Oct 28 07:07:35 2020 by Andrzej Szelc using cetskelgen
// from cetlib version v3_10_00.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "GenericCRT.h"


#include <memory>

namespace sim {
  class GenericCRT;
}


class sim::GenericCRT : public art::EDProducer {
public:
  explicit GenericCRT(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  GenericCRT(GenericCRT const&) = delete;
  GenericCRT(GenericCRT&&) = delete;
  GenericCRT& operator=(GenericCRT const&) = delete;
  GenericCRT& operator=(GenericCRT&&) = delete;

  // Required functions.
  void produce(art::Event& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:

  std::string fLArG4Label;  
  
  // Declare member data here.

};


sim::GenericCRT::GenericCRT(fhicl::ParameterSet const& p)
  : EDProducer{p}  // 
  , fLArG4Label(p.get< std::string >("LArG4Label"))
  // More initializers here.
{
  produces< std::vector<sim::AuxDetSimChannel> >();  
  // Call appropriate produces<>() functions here.
  // Call appropriate consumes<>() for any products to be retrieved by this module.
}

void sim::GenericCRT::produce(art::Event& e)
{
  // Implementation of required member function here.
  //std::unique_ptr< std::vector< sim::AuxDetSimChannel > > adCol (new  std::vector<sim::AuxDetSimChannel> );  
  auto adCol = std::make_unique<std::vector<sim::AuxDetSimChannel>>();
  
  art::Handle< std::vector<sim::AuxDetHit> > input_AuxDetHitCol;
  e.getByLabel(fLArG4Label,input_AuxDetHitCol);
  std::vector<sim::AuxDetHit> const& input_AuxDetHitColVector(*input_AuxDetHitCol);
  
  const sim::AuxDetSimChannel adsc = sim::GenericCRTUtility::GetAuxDetSimChannelByNumber(input_AuxDetHitColVector,1);
       //GenericCRTUtility::FillAuxDetSimChannels(input_AuxDetHitColVector,adCol.get());
  adCol->push_back(adsc);      
        
  e.put(std::move(adCol));   
    
}

void sim::GenericCRT::beginJob()
{
  // Implementation of optional member function here.
}

void sim::GenericCRT::endJob()
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(sim::GenericCRT)
