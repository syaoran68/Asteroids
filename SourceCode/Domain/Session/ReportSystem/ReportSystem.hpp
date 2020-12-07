#pragma once
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
    using TechnicalServices::Persistence::ReportQuery;

    class ReportSystemHandler
  {
  public:
    ReportSystemHandler( ReportQuery reportDetails )
      : _reportDetails(reportDetails)
    {}

    virtual void open() = 0;

    virtual ~ReportSystemHandler() = 0; 

  protected:
    ReportQuery _reportDetails;
  };

  inline ReportSystemHandler::~ReportSystemHandler()
  {}

  // Daily Payment Concrete Product
  class Daily : public ReportSystemHandler
  {
  public:
    Daily( ReportQuery reportDetails )
      : ReportSystemHandler( reportDetails )
    {
      std::cout << "Created  Daily report session " << '\n';
    }

    void open() override
    {
      //open db to grab data for processing logic on report
      std::cout << "Processing Daily Report" << '\n';
    }

    ~Daily() override
    {
      std::cout << "Destroyed Daily report session " << '\n';
    }

  private:
    static long unsigned _counter;  
    std::string          _byteStringArray;
  };
  long unsigned Daily::_counter = 0;  

 
  class Monthly : public ReportSystemHandler
  {
  public:
    Monthly( ReportQuery reportDetails )
      : ReportSystemHandler( reportDetails )
    {
      std::cout << "Created Monthly Report Session " << '\n';
    }

    void open() override
    {
      //open db to grab data for processing logic on report
        std::cout << "Processing Monthly Report" << '\n';
    }

    ~Monthly() override
    {
      std::cout << "Destroyed Monthly Report Session  " << '\n';
    }

  private:
    static long unsigned _counter;
    std::string          _byteStringArray;
  };
  long unsigned Monthly::_counter = 0;

//base payment factory
  struct ReportFactory
  {
    // Must be static
    static ReportFactory * createFactory( std::string factoryPreference );

    // All Payment Factories have these functions
    virtual ReportSystemHandler * createReports( ReportQuery reportDetails ) = 0;
  };

  // Daily Concrete Factory
  struct DailyFactory : ReportFactory
  {
    Daily * createReports( ReportQuery reportDetails ) override
    {
      return new Daily( reportDetails );
    }
  };

  // Credit Concrete Factory
  struct MonthlyFactory : ReportFactory
  {
    Monthly * createReports( ReportQuery reportDetails ) override
    {
      return new Monthly( reportDetails );
    }
  };

  ReportFactory * ReportFactory::createFactory( std::string factoryPreference )
  {

      if (factoryPreference == "Daily")
      {
        return new DailyFactory();
      }
      else if (factoryPreference == "Monthly")
      {
        return new MonthlyFactory();
      }
    else
    {
      // error - Preference not support.
      throw std::domain_error( "Unsupported factory preference encountered: " + factoryPreference );
    }
  }
}    // namespace