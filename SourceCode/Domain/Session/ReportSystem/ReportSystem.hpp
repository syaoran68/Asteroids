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
    ReportSystemBase();

    // Operations
    std::vector<std::string> getCommands();
    std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args );



    // Destructor
    // Pure virtual destructor helps force the class to be abstract, but must still be implemented
    ~ReportSystemBase() noexcept = 0;

  protected:
  };



}    // namespace Domain::PaymentSystem
