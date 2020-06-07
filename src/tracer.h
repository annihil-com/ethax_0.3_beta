// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

#ifndef _TRACER_H
#define _TRACER_H

// stupid include hell workaround
#ifndef ETH_H_
#include "ethax.h"
#endif

#define RAILTRAIL_INTERVAL	33

void debug_head_box( int player );
qboolean trace_body( int player, vec3_t hitpoint );
qboolean trace_head( refEntity_t *head, vec3_t hitpoint, int player );

typedef struct {
	vec3_t stand_offset;
	vec3_t crouch_offset;
	vec3_t prone_offset;

	vec3_t stand_offset_moving;
	vec3_t crouch_offset_moving;
	
	vec3_t size;

	// for body boxes
	vec3_t size2;
} hitbox_t;

/* these define the head hitboxes. format is { fwd, right, up }, relative to the tag's orientation
	matched them as good as possibly with server head hitboxes using hacked servercode

	hitboxes don't rotate, but their origin does! it rotates with tag_head

	etpub/etmain boxes are really based on centity position, not on tag_head position, so need
	different aimbot code to handle those mods... for now use everything tag_head based

	always use correct hitbox mode.. wrong vecs == suck4ge
*/

const static hitbox_t head_hitboxes[] =
{
// stand               crouch         prone              stand moving      crouch moving    hitbox size (x,y,z)
{ { 0.0, 0.0, 0.0}, { 0.0, 0.0, 0.0}, { 0.0,  0.0, 0.0}, { 0.0,  0.0, 0.0}, { 0.0,  0.0, 0.0}, { 0.0, 0.0, 0.0}, },	// OFF
{ { 0.5, 0.2, 5.5}, { 0.5, 0.2, 5.5}, { 0.5, 0.2, 5.5}, { 0.5, 0.0, 5.5}, { 0.5, 0.2, 5.5}, {10.0,10.0,13.0}, },	// ETMAIN
{ { 0.3, 0.3, 7.0}, { -0.3, -0.8, 7.0}, { 0.0,  0.3, 6.7}, {0.0, -0.5, 7.0}, { 0.0, -0.7, 7.0}, {11.0,11.0,12.0}, },	// ETPUB FIXED
{ { 0.3,-0.6, 7.5}, { 0.0, 0.6, 7.8}, { 1.5, -1.0, 7.0}, { 0.0,  0.0, 7.5}, { 0.9,  0.7, 6.8}, {12.5,12.5,12.0}, },	// ETPRO b_realhead 1
{ { 0.3, 0.3, 7.0}, {-0.3, 0.8, 7.0}, { 0.0,  0.3, 6.9}, { 0.5,  0.0, 6.5}, { 0.0, -0.7, 7.0}, {11.0,11.0,12.0}, },    // GENERIC realhead

};

// seems to be the same for every mod      stand              crouch              prone         stand moving       prone moving      stand bounds      prone bounds
const static hitbox_t body_hitbox = { {36.0,36.0,72.0}, {36.0,36.0,72.0}, {36.0, 36.0,48.0}, {36.0,36.0,72.0}, {36.0, 36.0,48.0}, {36.0,36.0,72.0}, {36.0, 36.0,48.0} };

hitbox_t custom_headhitbox;

#endif
