#include "stdafx.h"

#include "entry_controller\api\ec_iaccessor.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "aep\api\aep_iaccessor.hpp"
#include "aep_model\api\aep_model_iaccessor.hpp"

#include "aep_main\aep_main_container_bootstrapper.hpp"

#include <iostream>

/***************************************************************************/

int main( int _argc, char* _argv[] )
{
	if( _argc < 2 )
	{
		std::cout << "Usage: aep [list of verilog files]";
		return 0;
	}

	AepMain::ContainerBootstrapper bootstrapper;

	auto ec = bootstrapper.takeContainer().resolve< EntryController::IAccessor >();

	for( int i = 1; i < _argc; ++i )
		ec->addFile( _argv[ i ] );

	try
	{
		bool importResult = ec->runVerilogImport();

		if( !importResult )
		{
			ec->dumpErrors( std::cout );

			return 0;
		}

	Aep::IAccessor::GlobalResetParameters reset
	{ 
			"rst_n"
		,	AepModel::ResetPolarity::Kind::OVL_ACTIVE_HIGH 
	};

	std::cout << "running aep analysis..." << std::endl;
	ec->runAepAnalysis( 
			Aep::CheckerIds::All
		,	Aep::IAccessor::GlobalClockParameters{ "clk", AepModel::ClockEdge::Kind::OVL_POSEDGE }
		,	reset
	);

	bootstrapper.takeContainer().resolve< AepModel::IAccessor >()->regenerateAssertions( "" );
	
	std::cout << "assertions has been succesfully generated" << std::endl;

	}
	catch( std::exception const & _ex )
	{
		std::cout << _ex.what() << std::endl;
	}

	return 0;
}

