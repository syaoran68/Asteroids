
#include "Domain/Session/User.hpp"
#include "Domain/Session/ReportSystem/ReportSystemHandler.hpp"
#include "Domain/Session/PaymentSystem/PaymentSystemHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::User::UserBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  STUB(generateReport)
  STUB(playGame)
  STUB(buyGame)

  std::any checkoutBook( Domain::User::UserBase & User, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a book and the mark the book as being checked out by user
    std::string results = "Title \"" + args[0] + "\" checkout by \"" + User._credentials.userName + '"';
    User._logger << "checkoutBook:  " + results;
    return {results};
  }
}    // anonymous (private) working area

namespace Domain::User
{
  using TechnicalServices::Persistence::PaymentCredentials;
  using TechnicalServices::Persistence::ReportQuery;

  UserBase::UserBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }




  UserBase::~UserBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }




  std::vector<std::string> UserBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }




  std::any UserBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
      std::string results = "";
      if (command == "Buy Game")
      {
        // send to external payment system
        std::unique_ptr<Domain::PaymentSystem::PaymentSystemHandler> sessionControl;

        PaymentCredentials paymentInfo;
        paymentInfo.firstName = args[0];
        paymentInfo.lastName  = args[1];
        paymentInfo.creditCardNumber = args[2];
        paymentInfo.expMonth         = args[3];
        paymentInfo.expYear          = args[4];
        paymentInfo.address          = args[5];


        sessionControl = Domain::PaymentSystem::PaymentSystemHandler::createSession( paymentInfo );

        // STUB would execute command to buy game and return TransactionSession with Transaction ID
        
        //std::any transaction = sessionControl->executeCommand( command, args );
        if (
            //transaction.has_value()
            true)
        {
          results = "Game Purchased!";
        }
      }
      else if (command == "Play Game")
      {
        // stub for launching the game
        std::cout << "play game";
      }
      else if( command == "Run Reports" )
      {
        // stub generating report


        std::unique_ptr<Domain::ReportSystem::ReportSystemHandler> sessionControl;

        ReportQuery reportRequest;
        reportRequest.reportEndDate = args[1];
        reportRequest.reportStartDate = args[0];
        reportRequest.reportType      = args[2];

        sessionControl = Domain::ReportSystem::ReportSystemHandler::createSession( reportRequest );



        results = "Report is Generated Please Download.";


      }
    return results;
  }

  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  AdministratorSession::AdministratorSession( const UserCredentials & credentials ) : UserBase( "Administrator", credentials )
  {
    _commandDispatch = {
        { "Play Game", playGame },
        { "Buy Game", buyGame },
        { "Run Reports", generateReport },
                         
    };
  }




  PlayerSession::PlayerSession( const UserCredentials & credentials ) : UserBase( "Player", credentials )
  {
    _commandDispatch = { {"Play Game", playGame },
                         {"Buy Game",   buyGame      }};
  }

}    // namespace Domain::Session
