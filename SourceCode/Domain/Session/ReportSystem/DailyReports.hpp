#pragma once
#include <any>
#include <string>
#include <vector>

#include "Domain/Session/ReportSystem/ReportSystem.hpp"

namespace Domain::ReportSystem
{
  class DailyReports : public ReportSystemBase
	{
  public:
		std::vector<std::string> getCommands();
		std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args );

		
	};
}