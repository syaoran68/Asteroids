#include <iostream>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"



namespace Domain
{
    using TechnicalServices::Persistence::PaymentCredentials;

  // Desired interface (Target)
  class PaymentSystemHandler
  {
  public:
    virtual void processPayment() = 0;
  };

  // Legacy component (Adaptee)
  class PaypalExternal
  {
  public:
    PaypalExternal( PaymentCredentials paymentInfo )
    {
      _paymentinfo = paymentInfo;
    }
    bool paypalProcess()
    {
      std::cout << "Trying to Process Paypal. \n";
      return false;
    }

  private:
    PaymentCredentials _paymentinfo;
  };

  class ChaseExternal
  {
  public:
    ChaseExternal( PaymentCredentials paymentInfo )
    {
      _paymentinfo = paymentInfo;
    }
    bool chaseProcess()
    {
      std::cout << "Trying to Process Chase. \n";
      return true;
    }

  private:
    PaymentCredentials _paymentinfo;
  };



  // Adapter wrapper
  class PaymentAdapter : public PaymentSystemHandler, private PaypalExternal, private ChaseExternal
  {
  public:
    PaymentAdapter( PaymentCredentials paymentInfo ) : PaypalExternal( paymentInfo ), ChaseExternal( paymentInfo )
    {
      std::cout << "New Payment Transaction ready.\n";
    }

    void processPayment()
    {
      std::cout << "Processing Transaction\n";
      paypalProcess();
      chaseProcess();
    }
  };
}
