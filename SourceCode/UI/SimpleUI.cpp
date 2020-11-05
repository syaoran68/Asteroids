#include "SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>

#include "Domain/Library/Books.hpp"    // Include for now - will replace next increment
#include "Domain/Session/UserHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"





namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  :    // will replace these with factory calls in the next increment
    _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() )
  {
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }




  // Operations
  void SimpleUI::launch()
  {
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();


    // 2) Present login screen to user and get username, password, and valid role
    Domain::User::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::User::UserHandler> sessionControl;

    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      std::cout << "  UserName: ";
      std::getline( std::cin, credentials.userName );

      std::cout << "  Password: ";
      std::getline( std::cin, credentials.passPhrase );

      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::User::UserHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        _logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

    } while( true );


    // 4) Fetch functionality options for this role
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Quit\n";

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      if( menuSelection == commands.size() ) break;

      selectedCommand = commands[menuSelection];
      _logger << "Command selected \"" + selectedCommand + '"';


      /******************************************************************************************************************************
      **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
      **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
      **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
      **     parameters.
      ******************************************************************************************************************************/
      if( selectedCommand == "Buy Game" )
      {
        std::vector<std::string> parameters( 6 );

        std::cout << " First Name: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters[0] );
        std::cout << " Last Name: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters[1] );
        std::cout << " Credit Card Number: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters[2] );
        std::cout << " Credit Card Expire Month: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters[3] );
        std::cout << " Credit Card Expire Year: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters[4] );
        std::cout << " Address: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters[5] );



        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "Play Game" )
      {
      }
      else if( selectedCommand == "Run Reports" )
      {
        std::vector<std::string> parameters( 3 );

        std::cout << " Report Start Date: "; std::cin >> std::ws; std::getline( std::cin, parameters[0] );
        std::cout << " Report End Date: "; std::cin >> std::ws; std::getline( std::cin, parameters[1] );
        std::cout << " Report Type: "; std::cin >> std::ws; std::getline( std::cin, parameters[2] );

        auto results = sessionControl->executeCommand( selectedCommand, parameters );

        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else
        sessionControl->executeCommand( selectedCommand, {} );

    } while( true );

    _logger << "Ending session and terminating";
  }

}
