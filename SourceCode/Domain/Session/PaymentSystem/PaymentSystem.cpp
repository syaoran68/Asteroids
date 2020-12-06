#include "Domain/Session/PaymentSystem/PaymentSystem.hpp"


#include <string>
#include <any>
#include <vector>


namespace Domain::PaymentSystem
{
  PaymentSystemBase::PaymentSystemBase()
  {
    //_logger << "Session successfully initialized";
  }

  std::vector<std::string> PaymentSystemBase::getCommands()
  {
    std::vector<std::string> availableCommands;

    return availableCommands;
  }


  std::any PaymentSystemBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    if( command == "Buy Game" )
    {
      PaymentTransaction paymentDetails;
      return paymentDetails;

      
    }



    return std::any();
  }

  PaymentSystemBase::~PaymentSystemBase() noexcept
  {

  }

  TransactionSession::TransactionSession( PaymentCredentials & credentials )
  {

  }

}    // namespace Domain::PaymentSystem