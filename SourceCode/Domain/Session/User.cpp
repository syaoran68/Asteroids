
#include "Domain/Session/User.hpp"

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
      if (command == "Buy Game")
      {
        //STUB()
      }
      else if (command == "Play Game")
      {

      }
      else if( command == "Generate Report" )
      {

      }
      std::string results = "testing";
    return results;
  }








  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  AdministratorSession::AdministratorSession( const UserCredentials & credentials ) : UserBase( "Administrator", credentials )
  {
    _commandDispatch = { {"Run Reports",    generateReport     } };
  }




  PlayerSession::PlayerSession( const UserCredentials & credentials ) : UserBase( "Player", credentials )
  {
    _commandDispatch = { {"Play Game", playGame },
                         {"Buy Game",   buyGame      }};
  }

}    // namespace Domain::Session
