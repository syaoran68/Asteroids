#pragma once
#include <any>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

#include "Domain/Session/PaymentSystem/PaymentSystemHandler.hpp"

namespace Domain
{
  // Credit Payment Concrete Product
  class Amex : public Payment
  {
  public:
    Amex( std::string cardNum, int pin, std::string billAdd, int cost, std::string type = "Amex" )
      : Payment( cardNum, pin, billAdd, cost, type )
    {
      std::cout << "Created Apple Pay Credit Card payment number " << ( _paymentID = ++_counter ) << '\n';
    }

    void open() override
    {}

    ~Amex() override
    {
      std::cout << "Destroyed Apple Pay Credit Credit payment number " << _paymentID << '\n';
    }

  private:
    static long unsigned _counter;    // class attribute to count the number of wooden door made
    long unsigned        _paymentID = 0;
  };
  long unsigned Amex::_counter = 0;    // Allocate storage for class attribute

  //base payment factory
  struct PaymentFactory
  {
    // Must be static
    static PaymentFactory * createFactory( std::string factoryPreference );

    // All Payment Factories have these functions
    virtual Payment * createPayment( std::string cardNum, int pin, std::string billAdd, int cost, std::string type ) = 0;
  };

  // Visa Concrete Factory
  struct AmazonFactory : PaymentFactory
  {
    Amazon * createPayment( std::string cardNum, int pin, std::string billAdd, int cost, std::string type ) override
    {
      return new Amazon( cardNum, pin, billAdd, cost, type );
    }
  };

  // Credit Concrete Factory
  struct AmexFactory : PaymentFactory
  {
    Amex * createPayment( std::string cardNum, int pin, std::string billAdd, int cost, std::string type ) override
    {
      return new Amex( cardNum, pin, billAdd, cost, type );
    }
  };
}

