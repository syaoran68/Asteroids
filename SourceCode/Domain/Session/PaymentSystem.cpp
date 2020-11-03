#include "PaymentSystem.hpp"


#include <string>
#include <any>
#include <vector>


namespace Domain::PaymentSystem
{
	PaymentSystemBase::PaymentSystemBase()
	{
          //_logger << "Session successfully initialized";
    }

    std::any PaymentSystemBase::executeCommands( const std::string & command, const std::vector<std::string> & args )
    {

        return std::any();
    }

    TransactionSession::TransactionSession( const PaymentCredentials & credentials ) : PaymentSystemBase( "Administrator", credentials )
    {
      _commandDispatch = {
          //{ "Play Game", playGame },
          //{ "Buy Game", buyGame },
          //{ "Run Reports", generateReport },

      };
    }



}