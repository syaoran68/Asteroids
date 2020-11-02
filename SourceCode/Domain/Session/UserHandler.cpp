

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/Session/User.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::User
{
  UserHandler::~UserHandler() noexcept = default;




  // returns a specialized object specific to the specified role
  std::unique_ptr<UserHandler> UserHandler::createSession( const UserCredentials & credentials )
  {
    // Just as a smart defensive strategy, one should verify this role is one of the roles in the DB's legal value list.  I'll come
    // back to that

    // This is a good example of a Factory - the function takes the "order" (role) and builds the "product" (session) to fulfill the
    // order. This, however, still leaks knowledge of the kinds of sessions to the client, after all the client needs to specify
    // with role.

    // ToDo: Make this an Abstract Factory by:
    //  1) removing the parameter from the function's signature :  std::unique_ptr<SessionHandler>  SessionHandler::createSession();
    //  2) read the role from a proprieties files or (preferred) look up the role in the persistent data

    // Authenticate the requester
    try
    {
      auto &          persistentData    = TechnicalServices::Persistence::PersistenceHandler::instance();
      
      // normally we'd do this but we're gonna skip looking into the database for now

      //UserCredentials credentialsFromDB = persistentData.findCredentialsByName( credentials.userName );

      // 1)  Perform the authentication
      // std::set_intersection might be a better choice, but here I'm assuming there will be one and only one role in the passed-in
      // credentials I just need to verify the requested role is in the set of authorized roles.  Someday, if a user can sign in
      // with many roles combined, I may have to revisit this approach.  But for now, this is good enough.
      
        // 2) If authenticated user is authorized for the selected role, create a session specific for that role
        //if( credentials.roles[0] == "Borrower"      ) return std::make_unique<Domain::User::BorrowerSession>     ( credentials );
        //if( credentials.roles[0] == "Librarian"     ) return std::make_unique<Domain::User::LibrarianSession>    ( credentials );
        if( credentials.roles[0] == "Administrator" ) return std::make_unique<Domain::User::AdministratorSession>( credentials );
        if( credentials.roles[0] == "Player"    ) return std::make_unique<Domain::User::PlayerSession>   ( credentials );

        throw std::logic_error( "Invalid role requested in function " + std::string(__func__) ); // Oops, should never get here but ...  Throw something
     
    }
    catch( const TechnicalServices::Persistence::PersistenceHandler::NoSuchUser & ) {}  // Catch and ignore this anticipated condition

    return nullptr;
  }
} // namespace Domain::Session
