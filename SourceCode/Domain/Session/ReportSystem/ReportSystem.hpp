#pragma once


#include <any>
#include <string>
#include <vector>

#include "Domain/Session/ReportSystem/ReportSystemHandler.hpp"

namespace Domain::ReportSystem
{
  // Library Package within the Domain Layer Abstract class
  class ReportSystemBase : public ReportSystemHandler

  {
  public:
    ReportSystemBase(const std::string description, const ReportQuery & report);

    // Operations
    std::vector<std::string> getCommands()                                                                          override;
    std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args )   override;



    // Destructor
    // Pure virtual destructor helps force the class to be abstract, but must still be implemented
    ~ReportSystemBase() noexcept override = 0;

  protected:

   public:
    using DispatchTable = std::map<std::string, std::any (*)( Domain::ReportSystem::ReportSystemBase &, const std::vector<std::string> & )>;
    DispatchTable _commandDispatch;
  };

  struct ReportSession : ReportSystemBase{ ReportSession( const ReportQuery & report );};

}    // namespace Domain::PaymentSystem
