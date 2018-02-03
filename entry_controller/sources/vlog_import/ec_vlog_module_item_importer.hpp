#ifndef __EC_VLOG_MODULE_ITEM_IMPORTER_HPP__
#define __EC_VLOG_MODULE_ITEM_IMPORTER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class ModuleItemImporter
	:	public BaseImporter
{

/***************************************************************************/

public:

/***************************************************************************/

	ModuleItemImporter( 
			VlogDM::IAccessor & _accessor
		,	VlogDM::Writable::DesignUnit & _targetUnit 
	);
	
/***************************************************************************/

	void importItems( Verilog2001Parser::Non_port_module_itemContext & _ctx );

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitModule_or_generate_item_declaration( 
		Verilog2001Parser::Module_or_generate_item_declarationContext * ctx 
	) override;

	antlrcpp::Any visitNet_declaration( 
		Verilog2001Parser::Net_declarationContext * ctx 
	) override;

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::Writable::DesignUnit & m_targetUnit;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_MODULE_ITEM_IMPORTER_HPP__
