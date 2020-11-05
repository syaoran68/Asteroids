#include "Domain/Session/PaymentSystem/PaymentSystemHandler.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace Domain::PaymentSystem
{
  using TechnicalServices::Persistence::PaymentCredentials;
  using TechnicalServices::Persistence::PaymentTransaction;

  PaymentSystemHandler::~PaymentSystemHandler() noexcept = default;

std::unique_ptr<PaymentSystemHandler> PaymentSystemHandler::createSession( const PaymentCredentials & paymentInfo )
  {

    return std::unique_ptr<PaymentSystemHandler>();
  }

}    // namespace Domain::PaymentSystem