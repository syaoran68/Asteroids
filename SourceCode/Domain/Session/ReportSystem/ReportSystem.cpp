#include <any>
#include <string>
#include <vector>

#include "Domain/Session/ReportSystem/ReportSystem.hpp"
#include "Domain/Session/ReportSystem/DailyReports.hpp"


namespace Domain::ReportSystem
{
    using TechnicalServices::Persistence::ReportResponse;

    ReportSystemBase::ReportSystemBase()
  {
    //_logger << "Session successfully initialized";
  }

  std::vector<std::string> ReportSystemBase::getCommands()
  {
    std::vector<std::string> availableCommands;

    return availableCommands;
  }


  std::any ReportSystemBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    if( command == "Buy Game" )
    {
      ReportQuery reportRequest;

      ReportResponse dataReturned;

      return dataReturned;
    }



    return std::any();
  }

  ReportSystemBase::~ReportSystemBase() noexcept
  {
  }

}    // namespace Domain::ReportSystem