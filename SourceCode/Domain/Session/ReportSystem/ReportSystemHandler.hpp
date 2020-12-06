
#pragma once

#include <any>
#include <memory>       // unique_ptr
#include <stdexcept>    // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::ReportSystem
{
  // might use the persistence layer to hold the credit card information
  using TechnicalServices::Persistence::ReportQuery;

  class ReportSystemHandler
  {
  public:
    // Exceptions
    struct SessionException : std::runtime_error
    {
      using runtime_error ::runtime_error;
    };
    struct BadCommand : SessionException
    {
      using SessionException::SessionException;
    };

    //creating the external link session
    static std::unique_ptr<ReportSystemHandler> createSession( const ReportQuery & paymentInfo );

    // virtual function operations
    virtual std::vector<std::string> getCommands()                                                                        = 0;    // retrieves the list of actions (commands)
    virtual std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) = 0;    // Throws BadCommand

    //Destructor
    virtual ~ReportSystemHandler() noexcept = 0;

  protected:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    ReportSystemHandler & operator=( const ReportSystemHandler & rhs ) = default;    // copy assignment
    ReportSystemHandler & operator=( ReportSystemHandler && rhs ) = default;         // move assignment
  };
}    // namespace Domain::PaymentSystem