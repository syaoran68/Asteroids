#include <any>
#include <string>
#include <vector>

#include "Domain/Session/ReportSystem/ReportSystem.hpp"
#include "Domain/Session/ReportSystem/DailyReports.hpp"

namespace
{
    #define STUB( functionName )                                                                               \
  std::any functionName( Domain::ReportSystem::ReportSystemBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
  {                                                                                                        \
    return {};                                                                                             \
  }

  STUB(Daily)
  STUB(Monthly)
}


namespace Domain::ReportSystem
{
    using TechnicalServices::Persistence::ReportResponse;

    ReportSystemBase::ReportSystemBase( const std::string description, const ReportQuery & report )
  {
    //_logger << "Session successfully initialized";
  }

    ReportSystemBase::~ReportSystemBase()
  {

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



  ReportSession::ReportSession(const ReportQuery & report) : ReportSystemBase("Report", report)
  {
    _commandDispatch = {
        { "Daily Reports", Daily },
        { "Monthly Reports", Monthly }

    };

  }

}    // namespace Domain::ReportSystem