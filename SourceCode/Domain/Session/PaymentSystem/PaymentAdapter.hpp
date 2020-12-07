#pragma once

#include "Domain/Session/PaymentSystem/PaymentSystemHandler.hpp"

namespace Domain
{
  class PaymentAdapter : public PaymentSystemHandler, private PaypalExternal, private ChaseExternal
  {
  public:
    PaymentAdapter( PaymentCredentials paymentInfo ) : PaypalExternal( paymentInfo ), ChaseExternal( paymentInfo );
    void processPayment();
  };
}