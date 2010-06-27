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

#include <hydrogen/basics/note.h>
#include <hydrogen/basics/instrument.h>

#include <cassert>
//#include <cstdlib>

namespace H2Core
{

const char* Note::__class_name = "Note";
const char* Note::__key_str[] = { "C", "Cs", "D", "Ef", "E", "F", "Fs", "G", "Af", "A", "Bf", "B" };

Note::Note( Instrument* instrument, int position, float velocity, float pan_l, float pan_r, int length, float pitch )
    : Object( __class_name ),
    __instrument( 0 ),
    __position( position ),
    __velocity( velocity ),
    __pan_l( 0.0 ),
    __pan_r( 0.0 ),
    __length( 0 ),
    __pitch( 0.0 ),
    __key( C ),
    __octave( 0 ),
    __adsr( ADSR() ),
    __lead_lag( 0.0 ),
    __cut_off( 1.0 ),
    __resonance( 0.0 ),
    __humanize_delay( 0 ),
    __sample_position( 0.0 ),
    __bpfb_l( 0.0 ),
    __bpfb_r( 0.0 ),
    __lpfb_l( 0.0 ),
    __lpfb_r( 0.0 ),
    __pattern_idx( 0 ),
    __midi_msg( -1 ),
    __note_off( false ),
    __just_recorded( false )
{
    set_pan_l( pan_l );
    set_pan_r( pan_r );
    set_length( length );
    set_instrument( instrument );
    set_pitch( pitch );
}

Note::Note( Note* other )
    : Object( __class_name ),
    __instrument( other->get_instrument() ),
    __position( other->get_position() ),
    __velocity( other->get_velocity() ),
    __pan_l( other->get_pan_l() ),
    __pan_r( other->get_pan_r() ),
    __length( other->get_length() ),
    __pitch( other->get_pitch() ),
    __key( other->get_key() ),
    __octave( other->get_octave() ),
    __adsr( ADSR() ),
    __lead_lag( other->get_lead_lag() ),
    __cut_off( other->get_cut_off() ),
    __resonance( other->get_resonance() ),
    __humanize_delay( other->get_humanize_delay() ),
    __sample_position( other->get_sample_position() ),
    __bpfb_l( other->get_bpfb_l() ),
    __bpfb_r( other->get_bpfb_r() ),
    __lpfb_l( other->get_lpfb_l() ),
    __lpfb_r( other->get_lpfb_r() ),
    __pattern_idx( other->get_pattern_idx() ),
    __midi_msg( other->get_midi_msg() ),
    __note_off( other->get_note_off() ),
    __just_recorded( other->get_just_recorded() )
{ }

Note::~Note() { }

void Note::set_instrument( Instrument* instrument ) {
    if ( instrument == 0 ) return;
    __instrument = instrument;
    assert( __instrument->get_adsr() );
    __adsr = ADSR( *( __instrument->get_adsr() ) );
}

QString Note::key_to_string() {
    return QString("%1%2").arg(__key_str[__key]).arg( __octave );
}

void Note::set_key_octave( const QString& str ) {
    int l = str.length();
    QString s_key = str.left( l-1 );
    QString s_oct = str.mid( l-1, l );
    if ( s_key.endsWith( "-" ) ){
        s_key.replace("-", "");
        s_oct.insert( 0, "-");
    }
    __octave = s_oct.toInt();
    for( int i=0; i<=(int)B; i++){
        if(__key_str[i]==s_key)
            __key = (Key)i;
        return;
    }
    ___ERRORLOG( "Unhandled key: " + s_key );
}

void Note::dump() {
    INFOLOG( QString("Note : pos: %1\t humanize offset%2\t instr: %3\t key: %4\t pitch: %5")
            .arg( __position )
	        .arg( __humanize_delay )
	        .arg( __instrument->get_name() )
	        .arg( key_to_string() )
	        .arg( __pitch )
	        .arg( __note_off )
            );
}

};