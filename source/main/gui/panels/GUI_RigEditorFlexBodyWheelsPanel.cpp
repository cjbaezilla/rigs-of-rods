/*
	This source file is part of Rigs of Rods
	Copyright 2005-2012 Pierre-Michel Ricordel
	Copyright 2007-2012 Thomas Fischer
	Copyright 2013-2015 Petr Ohlidal

	For more information, see http://www.rigsofrods.com/

	Rigs of Rods is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License version 3, as
	published by the Free Software Foundation.

	Rigs of Rods is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

/** 
	@file
	@author Petr Ohlidal
	@date   03/2015
*/

#include "GUI_RigEditorFlexBodyWheelsPanel.h"
#include "RigDef_File.h" // For wheel propulsion/braking specs
#include "RigEditor_Config.h"
#include "RigEditor_RigElementsAggregateData.h"

#include <MyGUI.h>

using namespace RoR;
using namespace GUI;

// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------

#define SETUP_EDITBOX(NAME, UNIFLAG, SRC, SRC_TYPE) \
	SetupEditboxField(&NAME##_field, NAME##_label, NAME##_editbox, \
		m_data.GetFlagsPtr(), RigEditor::FlexBodyWheelAggregateData::UNIFLAG, ((void*) &(SRC)), EditboxFieldSpec::SRC_TYPE);

#define SETUP_COMBOBOX(NAME, UNIFLAG, SRC, SRC_TYPE) \
	SetupGenericField(&NAME##_field, NAME##_label, NAME##_combobox, \
		m_data.GetFlagsPtr(), RigEditor::FlexBodyWheelAggregateData::UNIFLAG, ((void*) &(SRC)), GenericFieldSpec::SRC_TYPE);

RigEditorFlexBodyWheelsPanel::RigEditorFlexBodyWheelsPanel(RigEditor::IMain* rig_editor_interface, RigEditor::Config* config):
	RigEditor::RigElementGuiPanelBase(rig_editor_interface, config, m_flexbodywheels_panel, nullptr)
{
	SETUP_EDITBOX  ( m_num_rays              , FIELD_RAY_COUNT_IS_UNIFORM            , m_data.num_rays               , SOURCE_DATATYPE_INT);
	SETUP_EDITBOX  ( m_mass	                 , FIELD_MASS_IS_UNIFORM                 , m_data.mass                   , SOURCE_DATATYPE_FLOAT);
	SETUP_COMBOBOX ( m_propulsion            , FIELD_PROPULSION_MODE_IS_UNIFORM      , m_data.propulsion             , SOURCE_DATATYPE_INT); // ENUM
	SETUP_COMBOBOX ( m_braking               , FIELD_BRAKING_MODE_IS_UNIFORM         , m_data.braking                , SOURCE_DATATYPE_INT); // ENUM
	SETUP_EDITBOX  ( m_rim_mesh_name         , FIELD_RIM_MESH_NAME_IS_UNIFORM        , m_data.rim_mesh_name          , SOURCE_DATATYPE_STRING);
	SETUP_EDITBOX  ( m_tyre_mesh_name        , FIELD_TYRE_MESH_NAME_IS_UNIFORM       , m_data.tyre_mesh_name         , SOURCE_DATATYPE_STRING);
    //TODO SETUP_EDITBOX  ( m_side	                 , FIELD_SIDE_IS_UNIFORM                 , m_data.is_right_side          , SOURCE_DATATYPE_BOOL);
	SETUP_EDITBOX  ( m_rim_radius            , FIELD_RIM_RADIUS_IS_UNIFORM           , m_data.rim_radius             , SOURCE_DATATYPE_FLOAT);
	SETUP_EDITBOX  ( m_rim_spring            , FIELD_RIM_SPRING_IS_UNIFORM           , m_data.rim_spring             , SOURCE_DATATYPE_FLOAT);
	SETUP_EDITBOX  ( m_rim_damping           , FIELD_RIM_DAMPING_IS_UNIFORM          , m_data.rim_damping            , SOURCE_DATATYPE_FLOAT);
	//SETUP_EDITBOX  ( m_rim_deform_threshold  , FIELD_RIM_DEFORM_THRESHOLD_IS_UNIFORM , m_data.rim_deform_threshold   , SOURCE_DATATYPE_FLOAT);
	//SETUP_EDITBOX  ( m_rim_break_threshold   , FIELD_RIM_BREAK_THRESHOLD_IS_UNIFORM  , m_data.rim_breaking_threshold , SOURCE_DATATYPE_FLOAT);
	SETUP_EDITBOX  ( m_tyre_radius           , FIELD_TYRE_RADIUS_IS_UNIFORM          , m_data.tyre_radius            , SOURCE_DATATYPE_FLOAT);
	SETUP_EDITBOX  ( m_tyre_spring           , FIELD_TYRE_SPRING_IS_UNIFORM          , m_data.tyre_spring            , SOURCE_DATATYPE_FLOAT);
	SETUP_EDITBOX  ( m_tyre_damping          , FIELD_TYRE_DAMPING_IS_UNIFORM         , m_data.tyre_damping           , SOURCE_DATATYPE_FLOAT);

	this->AlignToScreen(&config->gui_flexbodywheels_panel_position);
    this->SetDefaultTextColor(m_tyre_damping_label->getTextColour());
}

// ----------------------------------------------------------------------------
// Data manipulation
// ----------------------------------------------------------------------------

void RigEditorFlexBodyWheelsPanel::UpdateFlexBodyWheelsData(RigEditor::FlexBodyWheelAggregateData* data)
{
	m_data = *data;

	// Panel name
	if (data->num_elements == 1)
	{
		m_panel_widget->setCaption("FlexBody wheel");
	}
	else
	{
		char caption[30];
		sprintf(caption, "FlexBody wheel [%d]", data->num_elements);
		m_panel_widget->setCaption(caption);
	}

	// Fields
    EditboxRestoreValue ( &m_num_rays_field             );
    EditboxRestoreValue ( &m_mass_field	                );   
    ComboboxRestoreValue( &m_propulsion_field           );
    ComboboxRestoreValue( &m_braking_field              );
    EditboxRestoreValue ( &m_rim_mesh_name_field        );
    EditboxRestoreValue ( &m_tyre_mesh_name_field       );  
    EditboxRestoreValue ( &m_rim_radius_field           );
    EditboxRestoreValue ( &m_rim_spring_field           );
    EditboxRestoreValue ( &m_rim_damping_field          );
    EditboxRestoreValue ( &m_tyre_radius_field          );
    EditboxRestoreValue ( &m_tyre_spring_field          );
    EditboxRestoreValue ( &m_tyre_damping_field         );
}
