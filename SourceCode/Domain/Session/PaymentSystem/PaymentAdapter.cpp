#include "Domain/Session/PaymentSystem/PaymentAdapter.hpp"

namespace Domain
{
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
