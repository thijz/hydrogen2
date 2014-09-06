/*
 * Hydrogen
 * Copyright(c) 2002-2008 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <hydrogen/basics/drumkit_component.h>

#include <cassert>

#include <hydrogen/audio_engine.h>

#include <hydrogen/helpers/xml.h>
#include <hydrogen/helpers/filesystem.h>

#include <hydrogen/basics/adsr.h>
#include <hydrogen/basics/sample.h>
#include <hydrogen/basics/drumkit.h>
#include <hydrogen/basics/instrument_list.h>
#include <hydrogen/basics/instrument_layer.h>

namespace H2Core
{

const char* DrumkitComponent::__class_name = "DrumkitComponent";

DrumkitComponent::DrumkitComponent( const int id, const QString& name )
	: Object( __class_name )
	, __id( id )
	, __name( name )
	, __volume( 1.0 )
	, __muted( false )
	, __soloed( false )
{
}

DrumkitComponent::DrumkitComponent( DrumkitComponent* other )
	: Object( __class_name )
	, __id( other->get_id() )
	, __name( other->get_name() )
    , __volume( other->__volume )
    , __muted( other->__muted )
    , __soloed( other->__soloed )
{

}

DrumkitComponent::~DrumkitComponent()
{

}

void DrumkitComponent::load_from( Drumkit* drumkit, DrumkitComponent* component, bool is_live )
{
    if ( is_live )
		AudioEngine::get_instance()->lock( RIGHT_HERE );

	this->set_id( component->get_id() );
	this->set_name( component->get_name() );
	this->set_muted( component->is_muted() );
	this->set_volume( component->get_volume() );

	if ( is_live )
		AudioEngine::get_instance()->unlock();
}

DrumkitComponent* DrumkitComponent::load_from( XMLNode* node, const QString& dk_path )
{
	int id = node->read_int( "id", EMPTY_INSTR_ID, false, false );
	if ( id==EMPTY_INSTR_ID ) return 0;

	DrumkitComponent* component = new DrumkitComponent( id, node->read_string( "name", "" ) );
	component->set_volume( node->read_float( "volume", 1.0f, true, false ) );

	return component;
}

void DrumkitComponent::save_to( XMLNode* node )
{
	XMLNode component_node = node->ownerDocument().createElement( "drumkitComponent" );
	component_node.write_int( "id", __id );
	component_node.write_string( "name", __name );
	component_node.write_float( "volume", __volume );
	node->appendChild( component_node );
}

};
