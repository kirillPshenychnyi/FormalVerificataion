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
	"module test ( input rst, clk, a, output reg y );                        \n"
	"                                                                        \n"
	"    reg [1:0] sel;                                                      \n"
	"                                                                        \n"
	"    always@( posedge clk )                                              \n"
	"        if( rst )                                                       \n"
	"            sel = 0;                                                    \n"
	"        else                                                            \n"
	"            sel = sel + 1;                                              \n"
	"                                                                        \n"
	"    always @ ( * )                                                      \n"
	"          (* full_case *)case (sel)                                     \n"
	"            2'b10: y = a;                                               \n"
	"            2'b01: y = 0;                                               \n"
	"            2'b00: y = !a;                                              \n"
	"  endcase                                                               \n"
	"                                                                        \n"
	"endmodule                                                               \n"
	;

	ec->importVerilog( code );
	ec->runAepAnalysis();

	return 0;
}

