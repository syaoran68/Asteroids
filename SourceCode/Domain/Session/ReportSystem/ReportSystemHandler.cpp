#include "Domain/Session/ReportSystem/ReportSystem.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace Domain::ReportSystem
{
  using TechnicalServices::Persistence::ReportQuery;

  std::unique_ptr<ReportSystemHandler> ReportSystemHandler::createSession( const ReportQuery & paymentInfo )
  {
    return std::unique_ptr<ReportSystemHandler>();
  }

  ReportSystemHandler::~ReportSystemHandler() noexcept = default;

  

}    // namespace Domain::PaymentSystem