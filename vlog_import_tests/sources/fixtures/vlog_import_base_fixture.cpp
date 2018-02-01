
#include "stdafx.h"

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "entry_controller\sources\ec_accessor.hpp"
#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

ContainerBootstrapper::ContainerBootstrapper()
{
	Hypodermic::ContainerBuilder builder;

	builder.registerType< VlogDM::Accessor >()
		.as< VlogDM::IAccessor >()
		.singleInstance();

	builder.registerType< EntryController::Accessor >()
		.with< VlogDM::IAccessor>(
			[ ]( Hypodermic::ComponentContext & _context )
			{
				return _context.resolve< VlogDM::IAccessor >();
			}
		)
		.as< EntryController::IAccessor >()
		.singleInstance();

	m_container = builder.build();
}

/***************************************************************************/

void 
BaseFixture::runImport( std::string const & _code )
{
	m_bootstrapper.m_container->resolve< EntryController::IAccessor >()->importVerilog( _code );
}

/***************************************************************************/

}