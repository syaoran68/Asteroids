#include "Domain/Session/ReportSystem/ReportSystemHandler.hpp"
#include "Domain/Session/ReportSystem/DailyReports.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace Domain::ReportSystem
{
  using TechnicalServices::Persistence::ReportQuery;

  ReportSystemHandler::~ReportSystemHandler() noexcept = default;

  std::unique_ptr<ReportSystemHandler> ReportSystemHandler::createSession( const ReportQuery & reportRequest )
  {

     if(reportRequest.reportType == "Daily")
     {
        return std::unique_ptr<DailyReports>();
     }

    return std::unique_ptr<DailyReports>();
  }

}    // namespace Domain::PaymentSystem