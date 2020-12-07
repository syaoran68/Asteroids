#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include <any>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

/*******************************************************************************
**          PAYMENTS
*******************************************************************************/
// Payment Abstract Product Interface
namespace Domain
{
    using TechnicalServices::Persistence::PaymentCredentials;

    class Payment
  {
  public:
    Payment( PaymentCredentials paymentDetails )
      : _paymentDetails(paymentDetails)
    {}

    virtual void open() = 0;

    virtual ~Payment() = 0; 

  protected:
    PaymentCredentials _paymentDetails;
  };

  inline Payment::~Payment()
  {}

  // Visa Payment Concrete Product
  class Visa : public Payment
  {
  public:
    Visa( PaymentCredentials paymentDetails )
      : Payment( paymentDetails )
    {
      std::cout << "Created Amazon Credit Card payment number " << ( _paymentID = ++_counter ) << '\n';
    }

    void open() override
    {
        //open external transaction and process the transaction 
    }

    ~Visa() override
    {
      std::cout << "Destroyed Amazon Credit Card payment number " << _paymentID << '\n';
    }

  private:
    static long unsigned _counter;  
    long unsigned        _paymentID = 0;
  };
  long unsigned Visa::_counter = 0;  

 
  class Amex : public Payment
  {
  public:
    Amex( PaymentCredentials paymentDetails )
      : Payment( paymentDetails )
    {
      std::cout << "Created Amex Credit Card payment number " << ( _paymentID = ++_counter ) << '\n';
    }

    void open() override
    {
      //open external transaction and process the transaction 
    }

    ~Amex() override
    {
      std::cout << "Destroyed Amex Credit Credit payment number " << _paymentID << '\n';
    }

  private:
    static long unsigned _counter;
    long unsigned        _paymentID = 0;
  };
  long unsigned Amex::_counter = 0;

//base payment factory
  struct PaymentFactory
  {
    // Must be static
    static PaymentFactory * createFactory( std::string factoryPreference );

    // All Payment Factories have these functions
    virtual Payment * createPayment( PaymentCredentials paymentDetails ) = 0;
  };

  // Visa Concrete Factory
  struct VisaFactory : PaymentFactory
  {
    Visa * createPayment( PaymentCredentials paymentDetails ) override
    {
      return new Visa( paymentDetails );
    }
  };

  // Credit Concrete Factory
  struct AmexFactory : PaymentFactory
  {
    Amex * createPayment( PaymentCredentials paymentDetails ) override
    {
      return new Amex( paymentDetails );
    }
  };

  PaymentFactory * PaymentFactory::createFactory( std::string factoryPreference )
  {

      if (factoryPreference == "Visa")
      {
        return new VisaFactory();
      }
      else if (factoryPreference == "Amex")
      {
        return new AmexFactory();
      }
    else
    {
      // error - Preference not support.
      throw std::domain_error( "Unsupported factory preference encountered: " + factoryPreference );
    }
  }
}    // namespace