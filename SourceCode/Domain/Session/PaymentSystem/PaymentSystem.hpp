#pragma once


#include <any>
#include <string>
#include <vector>

#include "Domain/Session/PaymentSystem/PaymentSystemHandler.hpp"

namespace Domain::PaymentSystem
{
  // Library Package within the Domain Layer Abstract class
  class PaymentSystemBase : public PaymentSystemHandler

  {
  public:
    PaymentSystemBase();

    // Operations
    std::vector<std::string> getCommands();
    std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args );



    // Destructor
    // Pure virtual destructor helps force the class to be abstract, but must still be implemented
    ~PaymentSystemBase() noexcept = 0;

  protected:
  };

  struct TransactionSession : PaymentSystemBase
  {
    TransactionSession(PaymentCredentials & credentials );
  };


}    // namespace Domain::PaymentSystem
