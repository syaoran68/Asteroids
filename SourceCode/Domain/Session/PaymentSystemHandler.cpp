#include "Domain/Session/PaymentSystemHandler.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace Domain::PaymentSystem
{
    using TechnicalServices::Persistence::PaymentTransaction;
    using TechnicalServices::Persistence::PaymentCredentials;

  PaymentTransaction Domain::PaymentSystem::PaymentSystemHandler::createSession( const PaymentCredentials & paymentInfo )
  {
      //STUB for external payment system linking
    std::string tempTransactionID = "135123612346";
      return std::make_unique<PaymentTransaction>;
  }


}

