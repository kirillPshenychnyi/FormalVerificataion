#include "stdafx.h"

#include "entry_controller\api\ec_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "aep\api\aep_iaccessor.hpp"

#include "aep_main\aep_main_container_bootstrapper.hpp"

int main()
{
	AepMain::ContainerBootstrapper bootstrapper;
	
	auto ec = bootstrapper.takeContainer().resolve< EntryController::IAccessor >();
	
	std::string code =
		"module top (input a, b, c, output reg d );	\n"
		"	always@( * )							\n"
		"		case( a )							\n"
		"			b: d = 1;						\n"
		"			c: d = 0;						\n"
		"			default: d = a;					\n"
		"		endcase								\n"
		"endmodule									\n"
		;

	ec->importVerilog( code );
	ec->runAepAnalysis();

	return 0;
}

