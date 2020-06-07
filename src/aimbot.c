// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

/*
==============================
All aimbot related funtions
==============================
*/

#include "ethax.h"
#include "offsets.h"


// FreeHax
void newHitboxCorrection() {
   if (seth.value[VAR_NEW_HITBOX_CORRECTION]) {

	hitboxDef[HITBOX_ETPRO][MS_STANDING] = (vec3_union) {-1.0, 0.0, 6.5};
	hitboxDef[HITBOX_ETPRO][MS_CROUCHING] = (vec3_union){-1.0, 0.0, 6.5};
	hitboxDef[HITBOX_ETPRO][MS_PRONE] = (vec3_union){1.5, -1.0, 6.5};

	hitboxDef[HITBOX_ETMAIN][MS_STANDING] = (vec3_union){0.0, 0.0, 4.0}; 
	hitboxDef[HITBOX_ETMAIN][MS_CROUCHING] = (vec3_union){0.0, 0.0, 4.0};
	hitboxDef[HITBOX_ETMAIN][MS_PRONE] = (vec3_union){0.0, 0.0, 4.0};

	hitboxDef[HITBOX_ETPUB][MS_STANDING] = (vec3_union){1.0, -1.0, 6.5};
	hitboxDef[HITBOX_ETPUB][MS_CROUCHING] = (vec3_union){1.0, -1.0, 6.5};
	hitboxDef[HITBOX_ETPUB][MS_PRONE] = (vec3_union){2.0, 0.0, 6.5};


	hitboxDef[HITBOX_GENERIC][MS_STANDING] = (vec3_union){0.5, 0.0, 6.5};
	hitboxDef[HITBOX_GENERIC][MS_CROUCHING] = (vec3_union){0.5, 0.0, 6.5};
	hitboxDef[HITBOX_GENERIC][MS_PRONE] = (vec3_union){0.5, 0.0, 6.5};
		}
	}

void snapshotPredict( int player ){
	//vec3_t a;
	//vec3_t vo;
	vec3_t va;
	//vec3_t dPos;
	float dt;
	int curTime = orig_syscall( CG_MILLISECONDS );
		
	if( (curTime - (int) history[player][0].t)  > 150  || !history[player][1].t || !history[player][2].t ){
		memset( history[player][0].prPos, 0, sizeof(vec3_t));
		return;
	}

	dt = 1000.0 / (history[player][0].t - history[player][1].t);
	va[0] = (history[player][0].trPos[0] - history[player][1].trPos[0])*dt;
	va[1] = (history[player][0].trPos[1] - history[player][1].trPos[1])*dt;
	va[2] = (history[player][0].trPos[2] - history[player][1].trPos[2])*dt;

	// interpolate roughly 2 frames ahead
	history[player][0].prTime = (curTime - history[player][2].t)/333.3;
	VectorCopy(va, history[player][0].prPos );
	
}

void aimAt(vec3_t target) {
	#ifdef ETH_DEBUG
		if (seth.value[VAR_AIM_POINT] == AIM_POINT_2D) {
			#define POINT_SIZE 4
		int x, y;
			if (worldToScreen(target, &x, &y))
				drawFillRect(x - (POINT_SIZE / 2), y - (POINT_SIZE / 2), POINT_SIZE, POINT_SIZE, colorYellow);
		} else if (seth.value[VAR_AIM_POINT] == AIM_POINT_3D) {
			crossRailTrail(target);
		}
	#endif

	vec3_t org, ang;

	// Self Prediction
	if (seth.value[VAR_SELFPREDICT]) {
		vec3_t pVieworg;
		if (seth.value[VAR_SELFPREDICT]) {
			VectorAdd(eth.cg_refdef.vieworg,history[eth.cg_snap->ps.clientNum][0].prPos,pVieworg);
		} else {
			ethLog("error: invalid aim prediction type: %i", seth.value[VAR_SELFPREDICT]);
			VectorCopy(eth.cg_refdef.vieworg, pVieworg);
		}
		VectorSubtract(target, pVieworg, org);
    } else {																											
		VectorSubtract(target, eth.cg_refdef.vieworg, org);
    }
	vectoangles(org, ang);

	ang[PITCH] -= eth.cg_refdefViewAngles[PITCH];
	ang[YAW] -= eth.cg_refdefViewAngles[YAW];

// human MODE by FreeHax
		if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == LIL_HUMAN_AIM) {
void humanAim(float pitch, float yaw){

		while (ang[PITCH] < -360.0f)
			ang[PITCH] += 360.0f;
		while (ang[PITCH] > 360.0f)
			ang[PITCH] -= 360.0f;
		while (ang[YAW] < -360.0f)
			ang[YAW] += 360.0f;
		while (ang[YAW] > 360.0f)
			ang[YAW] -= 360.0f;
		if (ang[PITCH] > 180.0f)
			ang[PITCH] -= 360.0f;
		if (ang[PITCH] < -180.0f)
			ang[PITCH] += 360.0f;
		if (ang[YAW] > 180.0f)
			ang[YAW] -= 360.0f;
		if (ang[YAW] < -180.0f)
			ang[YAW] += 360.0f;

		float aimDiv = seth.value[VAR_DIVHUMAN];
		float humanvalue = seth.value[VAR_HUMANVALUE];
		ang[PITCH] *= (humanvalue/aimDiv)*seth.value[VAR_YSPEED];
		ang[YAW] *= humanvalue/aimDiv;
		aimDiv -= humanvalue;
		blockMouse(qfalse);
	if((ang[PITCH] <0) && (eth.isaimedEnemy)) ang[PITCH] *=0.02;
	if(eth.isaimedEnemy)ang[YAW] *=seth.value[VAR_XSPEED];

	*(float *)sethET->cl_mouseDx += ang[PITCH];
	*(float *)sethET->cl_mouseDy += ang[YAW];

	}
	if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == LIL_HUMAN_AIM) humanAim(ang[PITCH], ang[YAW]);
    	else
	{
		*(float *)sethET->cl_mouseDx += ang[PITCH];
		*(float *)sethET->cl_mouseDy += ang[YAW];
		}
	}
		else

		if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == LOGIN_HUMAN_AIM) {
void humanAimLogin(float pitch, float yaw){
		while (pitch < -360.0f)
			pitch += 360.0f;
		while (pitch > 360.0f)
			pitch -= 360.0f;
		while (yaw < -360.0f)
			yaw += 360.0f;
		while (yaw > 360.0f)
			yaw -= 360.0f;
		if (pitch > 180.0f)
			pitch -= 360.0f;
		if (pitch < -180.0f)
			pitch += 360.0f;
		if (yaw > 180.0f)
			yaw -= 360.0f;
		if (yaw < -180.0f)
			yaw += 360.0f;
		float aimDiv = seth.value[VAR_DIVHUMAN];
		float humanvalue =seth.value[VAR_HUMANVALUE];
			pitch *= (humanvalue/aimDiv)*seth.value[VAR_YSPEED];
			yaw *= humanvalue/aimDiv;
			aimDiv -= humanvalue;

	if((pitch <0)&&(eth.isaimedEnemy2)) pitch*=0.03;
	if(eth.isaimedEnemy) yaw*=seth.value[VAR_XSPEED];
    *(float *)sethET->cl_mouseDx += pitch;
    *(float *)sethET->cl_mouseDy += yaw;

	}
	if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == LOGIN_HUMAN_AIM) humanAimLogin(ang[PITCH], ang[YAW]);
	else
	{
		*(float *)sethET->cl_mouseDx += ang[PITCH];
		*(float *)sethET->cl_mouseDy += ang[YAW];
	}
}
	else
		if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == FAST_HUMAN_AIM) {
void humanAimFast(float pitch, float yaw){
		while (pitch < -360.0f)
			pitch += 360.0f;
		while (pitch > 360.0f)
			pitch -= 360.0f;
		while (yaw < -360.0f)
			yaw += 360.0f;
		while (yaw > 360.0f)
			yaw -= 360.0f;
		if (pitch > 180.0f)
			pitch -= 360.0f;
		if (pitch < -180.0f)
			pitch += 360.0f;
		if (yaw > 180.0f)
			yaw -= 360.0f;
		if (yaw < -180.0f)
			yaw += 360.0f;
		float aimDiv = seth.value[VAR_DIVHUMAN];
		float humanvalue =seth.value[VAR_HUMANVALUE];
			pitch *= (humanvalue/aimDiv)*seth.value[VAR_YSPEED];
			yaw *= humanvalue/aimDiv;
			aimDiv -= humanvalue;

	if((pitch <0)&&(eth.isaimedEnemy2)) pitch*=0.05;
	if(eth.isaimedEnemy) yaw*=seth.value[VAR_XSPEED];
    *(float *)sethET->cl_mouseDx += pitch;
    *(float *)sethET->cl_mouseDy += yaw;

	}
	if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == FAST_HUMAN_AIM) humanAimFast(ang[PITCH], ang[YAW]);
	else
	{
		*(float *)sethET->cl_mouseDx += ang[PITCH];
		*(float *)sethET->cl_mouseDy += ang[YAW];
		}
	}
	else
		if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == AGGRESSIVE_HUMAN_AIM) {
void humanAimAggressive(float pitch, float yaw){
		while (ang[PITCH] < -360.0f)
			ang[PITCH] += 360.0f;
		while (ang[PITCH] > 360.0f)
			ang[PITCH] -= 360.0f;
		while (ang[YAW] < -360.0f)
			ang[YAW] += 360.0f;
		while (ang[YAW] > 360.0f)
			ang[YAW] -= 360.0f;
		if (ang[PITCH] > 180.0f)
			ang[PITCH] -= 360.0f;
		if (ang[PITCH] < -180.0f)
			ang[PITCH] += 360.0f;
		if (ang[YAW] > 180.0f)
			ang[YAW] -= 360.0f;
		if (ang[YAW] < -180.0f)
			ang[YAW] += 360.0f;

		float aimDiv = seth.value[VAR_DIVHUMAN];
		float humanvalue = seth.value[VAR_HUMANVALUE];
		ang[PITCH] *= (humanvalue/aimDiv)*seth.value[VAR_YSPEED];
		ang[YAW] *= humanvalue/aimDiv*seth.value[VAR_XSPEED];
		aimDiv -= humanvalue;
		blockMouse(qfalse);
	if((ang[PITCH] <0) && (eth.isaimedEnemy)) ang[PITCH] *=0.08;
	if(eth.isaimedEnemy)ang[YAW] *=seth.value[VAR_XSPEED];

	*(float *)sethET->cl_mouseDx += ang[PITCH];
	*(float *)sethET->cl_mouseDy += ang[YAW];

	}
	if ((seth.value[VAR_HUMAN]) && seth.value[VAR_HUMAN_MODE] == AGGRESSIVE_HUMAN_AIM) humanAimAggressive(ang[PITCH], ang[YAW]);
    	else
	{
	*(float *)sethET->cl_mouseDx += ang[PITCH];
	*(float *)sethET->cl_mouseDy += ang[YAW];
		}
	}else{
		float aimDiv = seth.value[VAR_DIVHUMAN];
		float humanvalue =seth.value[VAR_HUMANVALUE];
			ang[PITCH] *= (humanvalue/aimDiv)*seth.value[VAR_YSPEED];
			ang[YAW] *= (humanvalue/aimDiv)*seth.value[VAR_XSPEED];
			aimDiv -= humanvalue;

	if((ang[PITCH] <0)&&(eth.isaimedEnemy2)) ang[PITCH]*=0.05;
	if(eth.isaimedEnemy) ang[YAW]*=seth.value[VAR_XSPEED];
    *(float *)sethET->cl_mouseDx += ang[PITCH];
    *(float *)sethET->cl_mouseDy += ang[YAW];
	}
	{
		*(float *)sethET->cl_mouseDx += ang[PITCH];
		*(float *)sethET->cl_mouseDy += ang[YAW];
	}
}


void rifleAimAt(vec3_t target) {
	if (!seth.value[VAR_RIFFLE_AIM])
		return;
	vec3_t org, ang;

	VectorSubtract(target, eth.cg_refdef.vieworg, org);
	vectoangles(org, ang);


	// Calculate y distance
	vec3_t me, enemy;
	VectorCopy(eth.cg_refdef.vieworg, me);
	VectorCopy(target, enemy);
	me[ROLL] = 0;
	enemy[ROLL] = 0;
	float y = target[ROLL] - eth.cg_refdef.vieworg[ROLL];

	float v = seth.value[VAR_RIFFLE_SPEED];	// FreeHax Riffle speed port to Rifle Bot Test 
	float g = DEFAULT_GRAVITY;
	float x = VectorDistance(me, enemy);
	
	float angle = atan((pow(v, 2) - (sqrt(pow(v, 4) + (g * ((g * pow(x, 2)) + (2.0f * y * pow(v, 2))))))) / (g * x));
	angle = RAD2DEG(angle);
	ang[PITCH] = angle;


	ang[PITCH] -= eth.cg_refdefViewAngles[PITCH];
	ang[YAW] -= eth.cg_refdefViewAngles[YAW];

*(float *)sethET->cl_mouseDx += ang[PITCH];
*(float *)sethET->cl_mouseDy += ang[YAW];
}

// This tag are in priority order. The first tags are near the center of the
// models, the last tag are at edge of the models
static char *modelBodyTags[] = {
	"tag_chest",
	"tag_torso",
	"tag_bright",
	"tag_lbelt",
	"tag_bleft",
	"tag_ubelt",
	"tag_back",
	"tag_armleft",
	"tag_weapon",
	"tag_armright",
	"tag_weapon2",
	"tag_legright",
	"tag_legleft",
	"tag_footleft",
	"tag_footright"
};

qboolean getVisibleModelBodyTag(const int player, vec3_t *origin) {
	int count = 0;
	for (; count < (sizeof(modelBodyTags) / sizeof(char *)); count++) {
		char *tagText = modelBodyTags[count];
		orientation_t tagOrientation;

		if (!eth_CG_GetTag(player, tagText, &tagOrientation))
			ethLog("error: can't find tag %i[%s] for player: %i", count, tagText, player);

		if (isVisible(tagOrientation.origin, NULL, NULL )) {
			VectorCopy(tagOrientation.origin, *origin);
			#ifdef ETH_DEBUG
				ethDebug("found visible tag: %s for player: %i", tagText, player);
			#endif
			return qtrue;
		}
		
	}
	return qfalse;
}

void doAutoShoot(qboolean shoot) {
	if (eth.cg_time == eth.cg_snap->serverTime)
	    return;

	if(eth.aimTime < eth.shoot)
	
	// We don't want autoshoot
	if (!seth.value[VAR_AUTOSHOOT])
		return;

	// Don't shoot if we're specing/following a player
	if (eth.cg_clientNum != eth.cg_snap->ps.clientNum)
		return;

	qboolean trigger;
	static int anylastShootTime = 0;
	if ((eth.cg_time - anylastShootTime) >= (seth.value[VAR_SNIPERDELAY])) {
		anylastShootTime = eth.cg_time;
		setAction(ACTION_ATTACK, 0); // u can remove it for testing so leave return only;
	}
	
	if(eth.shoot == eth.cg_time)
	    return;
	eth.shoot = eth.cg_time;

	if (seth.value[VAR_AUTOSHOOT_TYPE] == AUTOSHOOT_TYPE_TRIGGER) {
		// Set a far away end point
		vec3_t aheadPos;
		VectorMA(eth.cg_refdef.vieworg, 8192, eth.cg_refdef.viewaxis[0], aheadPos);
	
		// Get trace for this point
		trace_t trace;
		eth.CG_Trace(&trace, eth.cg_refdef.vieworg, NULL, NULL, aheadPos, eth.cg_snap->ps.clientNum, CONTENTS_SOLID | CONTENTS_BODY | CONTENTS_ITEM);
		trigger = IS_PLAYER_ENEMY(trace.entityNum);
	// Don't use trigger
	} else {
		trigger = qtrue;
	}

	// For tce
	if (eth.mod->type == MOD_TCE) {
		if (shoot && trigger && (syscall_CG_Key_IsDown(K_MOUSE1) || (seth.value[VAR_AUTOSHOOT] == AUTOSHOOT_ON))) {
			static qboolean lastFrameAttack = qfalse;
			if (!lastFrameAttack) {
				setAction(ACTION_ATTACK, 1);
				lastFrameAttack = qtrue;
			} else {
				setAction(ACTION_ATTACK, 0);
				lastFrameAttack = qfalse;
			}
		} else {
			setAction(ACTION_ATTACK, 0);
		}
	// For all others mod
	} else {
		if (shoot && trigger && (syscall_CG_Key_IsDown(K_MOUSE1) || (seth.value[VAR_AUTOSHOOT] == AUTOSHOOT_ON))) {
			// Check for sniper weapon delay
			if (((eth.cg_entities[eth.cg_clientNum].currentState->weapon == WP_K43_SCOPE)
						|| (eth.cg_entities[eth.cg_clientNum].currentState->weapon == WP_GARAND_SCOPE)) && !BG_PlayerMounted(eth.cg_snap->ps.eFlags)) {
				static int lastShootTime = 0;
				if ((eth.cg_time - lastShootTime) >= (seth.value[VAR_SNIPERDELAY])) {
					isTimeHack = 1;
					setAction(ACTION_ATTACK, 1);
					lastShootTime = eth.cg_time;
				} else {
					setAction(ACTION_ATTACK, 0);
				}
			// Check for weapon overheating
			#define OVERHEATING_LIMIT 160
			} else if (seth.value[VAR_OVERHEAT] && (eth.cg_snap->ps.curWeapHeat > OVERHEATING_LIMIT)) {
				setAction(ACTION_ATTACK, 0);
			} else {
 				timenudge(seth.value[VAR_NUDGEHACK]);
				isTimeHack = 1;
				setAction(ACTION_ATTACK, 1);
 				timenudge(0);
				#ifdef ETH_DEBUG
					ethDebug("autoshoot: shoot on");
				#endif
			}
		} else {
			setAction(ACTION_ATTACK, 0);
			#ifdef ETH_DEBUG
				ethDebug("autoshoot: shoot off");
			#endif
		}
	}
}

void doSatchelAutoShoot() {
	int satchelEntityNum = findSatchel();

	// If don't find satchel
	if (satchelEntityNum == -1) {
		#ifdef ETH_DEBUG
			ethDebug("autoshoot: don't find satchel for %i", eth.cg_snap->ps.clientNum);
		#endif
		setAction(ACTION_ATTACK, 0);
		return;
	}

	// Find an enemy near the satchel
	#define SATCHEL_SHOOT_DISTANCE 100
	int entityNum = 0;
	for (; entityNum < MAX_CLIENTS; entityNum++) {
		ethEntity_t *entity = &eth.entities[entityNum];
		
		if (entity->isValid
				&& IS_PLAYER_ENEMY(entityNum)
				&& (VectorDistance(entity->origin, eth.entities[satchelEntityNum].origin) < SATCHEL_SHOOT_DISTANCE)) {
			setAction(ACTION_ATTACK, 1);
			return;
		}
	}

	// TODO: find a breakable object near the satchel

	setAction(ACTION_ATTACK, 0);
}


// Jaymod 2.1.x changes quite a lot of things, more attention needed
int findTarget(int targetFlag) {
	int nearest = -1;
	int maxEntities = MAX_GENTITIES;
	float distance;
	// Get max entities
	if (targetFlag & TARGET_PLAYER)
		maxEntities = MAX_CLIENTS;

	int entityNum = 0;

	if( (seth.value[VAR_TARGET_PRIO] == TARGET_ATTACKER ) ){
		int ent = eth.cg_snap->ps.persistant[PERS_ATTACKER];
		if( ent >= 0 && ent <= MAX_CLIENTS ){
			// Jaymod 2.1.x aimbot workaround
			if( eth.mod->crc32 == 0x5f24fa23 || eth.mod->crc32 == 0x8352a951 || eth.mod->crc32 == 0x3eac383d || eth.mod->crc32 == 0x2aca67dd )
				eth.cg_entities[ent].currentState->eType = ET_PLAYER;

			if( ((targetFlag & TARGET_ENEMY) && (targetFlag & TARGET_PLAYER) && IS_PLAYER_ENEMY(entityNum))
				&& eth.entities[ent].isVisible && !IS_PLAYER_DEAD(ent) )
				return ent;
		}
	}
	
	for (; entityNum < maxEntities; entityNum++) {
		ethEntity_t* entity = &eth.entities[entityNum];

		if (!*eth.cg_entities[entityNum].currentValid || (entityNum == eth.cg_snap->ps.clientNum))
			continue;

		// Jaymod 2.1.x aimbot workaround
		if( entityNum < MAX_CLIENTS && (eth.mod->crc32 == 0x5f24fa23 || eth.mod->crc32 == 0x8352a951 || eth.mod->crc32 == 0x3eac383d || eth.mod->crc32 == 0x2aca67dd) )
			eth.cg_entities[entityNum].currentState->eType = ET_PLAYER;
		
		// Player
		if ((targetFlag & TARGET_PLAYER) && !IS_PLAYER_VALID(entityNum))
			continue;
		if ((targetFlag & TARGET_PLAYER_VULN) && !IS_PLAYER_VULNERABLE(entityNum))
			continue;
		if ((targetFlag & TARGET_PLAYER_ALIVE) && IS_PLAYER_DEAD(entityNum))
			continue;
		if ((targetFlag & TARGET_PLAYER_DEAD) && !IS_PLAYER_DEAD(entityNum))
			continue;

		// Target
		if ((targetFlag & TARGET_PLAYER_HEAD) && !entity->isHeadVisible)
			continue;
		if ((targetFlag & TARGET_PLAYER_BODY) && VectorCompare(entity->bodyPart, vec3_origin))
			continue;
			
		// Targeting specific player has priority over other settings
		if ( (targetFlag & TARGET_VISIBLE) && entity->isVisible &&
			(seth.value[VAR_TARGET_PRIO]==TARGET_PERSON) && eth.clAttack[entityNum] )
			return entityNum;

		// Common
		if ((targetFlag & TARGET_ENEMY) && (targetFlag & TARGET_PLAYER) && !IS_PLAYER_ENEMY(entityNum) && !entity->isEnemy)
			continue;
		if ((targetFlag & TARGET_ENEMY) && (targetFlag & TARGET_MISSILE) && !IS_MISSILE_ENEMY(entityNum) && entity->isEnemy)
			continue;
		if ((targetFlag & TARGET_FRIEND) && (targetFlag & TARGET_PLAYER) && IS_PLAYER_ENEMY(entityNum) && !entity->isFreind)
			continue;	
		if ((targetFlag & TARGET_FRIEND) && (targetFlag & TARGET_MISSILE) && IS_MISSILE_ENEMY(entityNum) && entity->isFreind)
			continue;	
		if ((targetFlag & TARGET_VISIBLE) && !entity->isVisible)
			continue;
		if ((targetFlag & TARGET_NOTVISIBLE) && entity->isNotVisible)
			continue;

		// Missile
		if ((targetFlag & TARGET_MISSILE) && !IS_MISSILE(entityNum) && entity->isMissile)
			continue;
		if ((targetFlag & TARGET_MISSILE_ARMED) && !IS_MISSILE_ARMED(entityNum) && !entity->isMissileArmed)
			continue;
		if ((targetFlag & TARGET_MISSILE_NOTARMED) && IS_MISSILE_ARMED(entityNum) && entity->isMissileArmed)
			continue;
		if ((targetFlag & TARGET_MISSILE_DYNAMITE) && !IS_DYNAMITE(entityNum) && entity->isDynamite)
			continue;

		if (seth.value[VAR_AIMFOV] != 360.00f) {
			vec3_t aimPoint, ang, org;
			if (eth.entities[entityNum].isHeadVisible)
				VectorCopy(eth.entities[entityNum].head, aimPoint);
			else if (seth.value[VAR_AIM_PRIO] != AIM_PRIO_HEAD_ONLY)
				VectorCopy(eth.entities[entityNum].bodyPart, aimPoint);
			else {
				ethLog("findTarget: can't find a point to aim");
				return -1;
			}

			VectorSubtract(aimPoint, eth.cg_refdef.vieworg, org);
			vectoangles(org, ang);

			ang[PITCH] -= eth.cg_refdefViewAngles[PITCH];
			ang[YAW] -= eth.cg_refdefViewAngles[YAW];


			if (ang[PITCH] < 0.0)
				ang[PITCH] *= -1.0;
			if (ang[YAW] < 0.0)
				ang[YAW] *= -1.0;

			if (ang[PITCH] > 360.0f)
				ang[PITCH] -= 360.0f;
			if (ang[YAW] > 360.0f)
				ang[YAW] -= 360.0f;

			float aimFov[2];

			aimFov[0] = (ang[PITCH] - 360.0) * -1.0;
			aimFov[1] = (ang[YAW] - 360.0) * -1.0;

			if (ang[PITCH] > aimFov[0])
				ang[PITCH] = aimFov[0];
			if (ang[YAW] > aimFov[1])
				ang[YAW] = aimFov[1];

			if ((ang[PITCH] > seth.value[VAR_AIMFOV]) || (ang[YAW] > seth.value[VAR_AIMFOV]))
				continue;
		}

		if(seth.value[VAR_TARGET_PRIO] == TARGET_CROSSHAIR){
		if(entity->isInScreen){
		int x_dis=0, y_dis=0, centerX=eth.cgs_screenXScale, centerY=eth.cgs_screenYScale;
			x_dis = entity->screenX > centerX ? entity->screenX - centerX : centerX - entity->screenX;
			y_dis = entity->screenY > centerY ? entity->screenY - centerY : centerY - entity->screenY;
		float dist = ((x_dis*x_dis)+(y_dis*y_dis));
		if(distance < dist)
		{
			distance = dist;
			nearest=entityNum;
		}
	}
		}else{
        if ((entity->distance != 0)
                && (nearest == -1 || (entity->distance < eth.entities[nearest].distance))) {
            nearest = entityNum;
        }
		if ((!seth.value[VAR_HUMAN]) && !seth.value[VAR_RANDOM_AIM]) {
        float dist = entity->distance / 1500.f;
        static int lastShake = 0;
        int freq = rand() %freq * seth.value[VAR_SHAKE];
        	dist = dist < 0.6 ? 0.6 : dist;
        	dist = dist > 1.0 ? 1.0 : dist;
        if (freq >= 500) {
        if  (eth.cg_time - lastShake > freq) {
        	entity->aimPoint[0] += (crandom() * seth.value[VAR_RANDOM_X]) * dist;
        	entity->aimPoint[1] += (crandom() * seth.value[VAR_RANDOM_Y]) * dist;
        	entity->aimPoint[2] += (crandom() * seth.value[VAR_RANDOM_Z]) * dist;
        	lastShake = eth.cg_time;
                }
            }
        }
	}
	float screenX = eth.cgs_screenXScale;
	float screenY = eth.cgs_screenYScale;
	float size = 0.25f*screenX;
	float x = 320*screenX;
	float y = 158*screenY;
	if (seth.value[VAR_DRAW_WARN_MSG]) // FreeHax Warning MSG
        drawText(x, y, size, "^1.:.^7WARNING ENEMY^1.:.", colorRed, (entity->isInScreen) ? qfalse : qtrue, qtrue, &eth.fontFixed);
	float size2 = 0.20f*screenX;
	float a = 320*screenX;
	float b = 180*screenY;
	if (seth.value[VAR_DRAW_HEAD_MSG]) // FreeHax Head MSG
        drawText(a, b, size2, "^0.:.^2Head ^7Visible^0.:.", colorRed, (entity->isInScreen && entity->isHeadVisible) ? qfalse : qtrue, qtrue, &eth.fontFixed);
}
	#ifdef ETH_DEBUG
		if (nearest != -1)
			ethDebug("findTarget: target found for flags 0x%x", targetFlag);
		else
			ethDebug("findTarget: target not found for flags 0x%x", targetFlag);
	#endif
	return nearest;
}

void blockMouse(qboolean state) {
	if (!seth.value[VAR_BLOCK_MOUSE])
		return;

	#define SENSITIVITY_STR "sensitivity"
	static float sensitivity = 0;	// For backup user sensitivity
	static qboolean mouseBlocked = qfalse;	// Current state
	char buffer[32];

	// Set sensitivity
	if (state && !mouseBlocked) {
		syscall_CG_Cvar_VariableStringBuffer(SENSITIVITY_STR, buffer, sizeof(buffer));
		sensitivity = atof(buffer);

		syscall_CG_SendConsoleCommand(SENSITIVITY_STR " 0\n");
		mouseBlocked = qtrue;
		#ifdef ETH_DEBUG
			ethDebug("blockMouse: mouse off");
		#endif
	} else if (!state && mouseBlocked) {
		snprintf(buffer, sizeof(buffer), SENSITIVITY_STR " %f\n", sensitivity);
		syscall_CG_SendConsoleCommand(buffer);
		mouseBlocked = qfalse;
		#ifdef ETH_DEBUG
			ethDebug("blockMouse: mouse on");
		#endif
	}
}

void doAimbot() {
	qboolean autoShootWeapon = qfalse;
	int targetFlag[2] = { -1, -1 };	// If a targetFlag failed try the next one

	// For tce
	if ((eth.mod->type == MOD_TCE) && (eth.mod->type == MOD_ETNAM)) {

    	int clips = eth.cg_snap->ps.ammoclip[eth.cg_snap->ps.weapon];
		int ammo = eth.cg_snap->ps.ammo[eth.cg_snap->ps.weapon];
		static qboolean lastframeReload = qfalse;
	
		if(clips == 0 && ammo > 0) {
		    if(eth.cg_snap->ps.weapon != WP_KNIFE) 
			if(!lastframeReload) {
			    setAction(ACTION_RELOAD, 1);
			    lastframeReload = qtrue;
			    return;
			}
		}
		if(lastframeReload) {
			setAction(ACTION_RELOAD, 0);
			lastframeReload = qfalse;
		}
			
		autoShootWeapon = qtrue;
		targetFlag[0] = TARGET_PLAYER_ENEMY | TARGET_PLAYER_ALIVE;

		// Aim priority
		if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_HEAD_BODY) {
			targetFlag[0] |= TARGET_PLAYER_HEAD_BODY;
		} else if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_HEAD_ONLY) {
			targetFlag[0] |= TARGET_PLAYER_HEAD;
		} else if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_HEAD) {
			targetFlag[1] = targetFlag[0] | TARGET_PLAYER_BODY;
			targetFlag[0] |= TARGET_PLAYER_HEAD;
		} else if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_BODY_ONLY) {
			targetFlag[0] |= TARGET_PLAYER_BODY;
		}
	// For all others mod
	} else {
		// if player is mounted (tank mg, mobile mg42, static mg42) aim for body
		if (BG_PlayerMounted(eth.cg_snap->ps.eFlags) || (eth.cg_snap->ps.weapon == WP_MOBILE_MG42) || (eth.cg_snap->ps.weapon == WP_MOBILE_MG42_SET)) {
			autoShootWeapon = qtrue;
			targetFlag[0] = TARGET_PLAYER_ENEMY | TARGET_PLAYER_HEAD;

			if (!seth.value[VAR_AIM_DEAD])
				targetFlag[0] |= TARGET_PLAYER_ALIVE;
			
			targetFlag[1] = targetFlag[0] | TARGET_PLAYER_HEAD_BODY;
		} else {
		// different targets for differents weapons
			switch (eth.cg_snap->ps.weapon) {
				case WP_LUGER:
				case WP_SILENCER:
				case WP_AKIMBO_LUGER:
				case WP_AKIMBO_SILENCEDLUGER:
				case WP_COLT:
				case WP_SILENCED_COLT:
				case WP_AKIMBO_COLT:
				case WP_AKIMBO_SILENCEDCOLT:
				case WP_MP40:
				case WP_THOMPSON:
				case WP_GARAND:
				case WP_K43:
				case WP_FG42:
				case WP_STEN:
				case WP_CARBINE:
				case WP_KAR98:
					autoShootWeapon = qtrue;
					targetFlag[0] = TARGET_PLAYER_ENEMY;

					// Aim at dead player
					if (!seth.value[VAR_AIM_DEAD])
						targetFlag[0] |= TARGET_PLAYER_ALIVE;
		
					// Aim priority
					if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_HEAD_BODY) {
						targetFlag[0] |= TARGET_PLAYER_HEAD_BODY;
					} else if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_HEAD_ONLY) {
						targetFlag[0] |= TARGET_PLAYER_HEAD;
					} else if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_HEAD) {
						targetFlag[1] = targetFlag[0] | TARGET_PLAYER_BODY;
						targetFlag[0] |= TARGET_PLAYER_HEAD;
					} else if (seth.value[VAR_AIM_PRIO] == AIM_PRIO_BODY_ONLY) {
						targetFlag[0] |= TARGET_PLAYER_BODY;
					}
					break;
				case WP_GPG40:
				case WP_M7:
					autoShootWeapon = qtrue;
					targetFlag[0] = TARGET_PLAYER_ENEMY | TARGET_PLAYER_ALIVE | TARGET_PLAYER_BODY;
					break;
				case WP_GARAND_SCOPE:
				case WP_K43_SCOPE:
				case WP_FG42SCOPE:
					autoShootWeapon = qtrue;
					targetFlag[0] = TARGET_PLAYER_ENEMY | TARGET_PLAYER_ALIVE | TARGET_PLAYER_HEAD;
					break;
				case WP_KNIFE:
					targetFlag[0] = TARGET_PLAYER_ENEMY | TARGET_PLAYER_ALIVE | TARGET_PLAYER_HEAD;
					targetFlag[1] = TARGET_PLAYER_ENEMY | TARGET_PLAYER_DEAD | TARGET_PLAYER_HEAD;
					break;
				case WP_MEDIC_SYRINGE:
					targetFlag[0] = TARGET_PLAYER | TARGET_FRIEND | TARGET_PLAYER_DEAD | TARGET_PLAYER_BODY;
					break;
				case WP_PLIERS:
					targetFlag[0] = TARGET_MISSILE | TARGET_MISSILE_DYNAMITE | TARGET_ENEMY | TARGET_MISSILE_ARMED;
					targetFlag[1] = TARGET_MISSILE | TARGET_MISSILE_DYNAMITE | TARGET_FRIEND | TARGET_MISSILE_NOTARMED;
				default:
					break;
			}
		}
	}

	// Check if we want aimbot
	if ((syscall_CG_Key_IsDown(K_MOUSE1) || seth.value[VAR_AIM_AUTO])
			&& (targetFlag[0] != -1) && seth.value[VAR_AIM_PRIO] &&
			(eth.cg_snap->ps.clientNum == eth.cg_clientNum) ) {
		// Find target aim point
		int count = 0;
		int target;
		for (; count < (sizeof(targetFlag) / sizeof(int)); count++) {
			if (targetFlag[count] != -1) {
				vec3_t aimPoint;
				VectorCopy(vec3_origin, aimPoint);
				target = findTarget(targetFlag[count]);

#ifdef ETH_DEBUG
				ethDebug("target: found target %i %s targetFlag[0]=%i targetFlag[1]=%i", target, eth.clientInfo[target].name, targetFlag[0], targetFlag[1]);
#endif
				
				// No target found
				if (target == -1)
					continue;
				if( seth.value[VAR_ENTCAM] == ENTCAM_TARGET )
					eth.entCamTarget = target;

				doPrediction(target);
//				doVecZ(target);

				if ((!seth.value[VAR_LOCKTARGET]) && seth.lastTarget && seth.lastTargetValid )
					target = seth.lastTarget;

				// Target found
				if (targetFlag[count] & TARGET_PLAYER) {
					if (targetFlag[count] & TARGET_PLAYER_HEAD) {
						if (seth.value[VAR_HITBOX])
							VectorCopy(eth.entities[target].head_visible_pt, aimPoint);
						else
							VectorCopy(eth.entities[target].head, aimPoint);
						#ifdef ETH_DEBUG
							ethDebug("aimbot: found head player: %s", eth.clientInfo[target].name);
						#endif
					} else if (targetFlag[count] & TARGET_PLAYER_BODY) {
						if (seth.value[VAR_HITBOX])
							VectorCopy(eth.entities[target].body_visible_pt, aimPoint);
						else
							VectorCopy(eth.entities[target].bodyPart, aimPoint);
						#ifdef ETH_DEBUG
							ethDebug("aimbot: found body player: %s", eth.clientInfo[target].name);
						#endif
					} else if (targetFlag[count] & TARGET_PLAYER_HEAD_BODY) {
						// Head or body ?
						if (eth.entities[target].isHeadVisible) {
							if (seth.value[VAR_HITBOX])
								VectorCopy(eth.entities[target].head_visible_pt, aimPoint);
							else
								VectorCopy(eth.entities[target].head, aimPoint);
						} else {
							if (seth.value[VAR_HITBOX])
								VectorCopy(eth.entities[target].body_visible_pt, aimPoint);
							else
								VectorCopy(eth.entities[target].bodyPart, aimPoint);
						}

						#ifdef ETH_DEBUG
							ethDebug("aimbot: found head/body player: %s", eth.clientInfo[target].name);
						#endif
					} else {
						ethLog("error: target found but no aimpoint set in target flags");
					}
				} else if (targetFlag[count] & TARGET_MISSILE) {
					VectorCopy(eth.entities[target].origin, aimPoint);
					#ifdef ETH_DEBUG
						ethDebug("aimbot: found missile: %i", target);
					#endif
				} else {
					ethLog("error: target found but it's not a player/missile");
				}

				// If aim point is set, aim and shoot
				if (!VectorCompare(aimPoint, vec3_origin)) {
					if (!seth.value[VAR_HUMAN])
					    doAutoShoot(qtrue);

				vec3_t aheadPos;
				VectorMA(eth.cg_refdef.vieworg, 9999, eth.cg_refdef.viewaxis[0], aheadPos);
				trace_t trace;
				eth.CG_Trace(&trace, eth.cg_refdef.vieworg, NULL, NULL, aheadPos, eth.cg_snap->ps.clientNum, CONTENTS_SOLID | CONTENTS_BODY | CONTENTS_ITEM);
				eth.isaimedEnemy = IS_PLAYER_ENEMY(trace.entityNum);
				eth.isaimedEnemy2=qfalse;

				// Free Testing Special NQ Mod Support
					if ((eth.cg_snap->ps.weapon == WP_GPG40) || (eth.cg_snap->ps.weapon == WP_M7)) {

						rifleAimAt(aimPoint);
						doAutoShoot(!autoShootWeapon);
				} else
						eth.aimedEnemy = target;
						doVecZ(target);
						aimAt(aimPoint);

			} else {
					 if ((eth.cg_snap->ps.weapon == WP_NQ_GPG40) || (eth.cg_snap->ps.weapon == WP_NQ_M7)) {
						rifleAimAt(aimPoint);
						doAutoShoot(!autoShootWeapon);
				} else {
						eth.aimedEnemy = target;
						doVecZ(target);
						aimAt(aimPoint);

					// FreeHax test NQ Mod Akimbo
					if((eth.cg_snap->ps.weapon == WP_NQ_AKIMBO_COLT) || (eth.cg_snap->ps.weapon == WP_NQ_AKIMBO_LUGER)) {
						aimAt(aimPoint);
						doAutoShoot(!autoShootWeapon);
					}
				}
				blockMouse(qtrue);
				if (seth.value[VAR_AUTO_CROUCH])			
   syscall_CG_SendConsoleCommand(eth.actions[ACTION_CROUCH].startAction);

			else
				if (seth.value[VAR_AUTO_SPRINT])			
   syscall_CG_SendConsoleCommand(eth.actions[ACTION_SPRINT].startAction);
					return;
			}
		}
}
		#ifdef ETH_DEBUG
			ethDebug("aimbot: no target found");
		#endif
	} else eth.isaimedEnemy2=qfalse;

	blockMouse(qfalse);
	if (seth.value[VAR_AUTO_CROUCH])				
    syscall_CG_SendConsoleCommand(eth.actions[ACTION_CROUCH].stopAction);
	if (seth.value[VAR_AUTO_SPRINT])			
   syscall_CG_SendConsoleCommand(eth.actions[ACTION_SPRINT].stopAction);

   // Bunny jump FreeHax
   if (seth.value[VAR_BUNNY_JUMP]) {
      // Find the current key for jump.
      int key1, key2;
      orig_syscall(CG_KEY_BINDINGTOKEYS, "+moveup", &key1, &key2);
      // If jump keys press
      if (syscall_CG_Key_IsDown(key1) || syscall_CG_Key_IsDown(key2)) {
         // If player fall
         if (eth.cg_snap->ps.velocity[ROLL] <= 00.0f)
            setAction(ACTION_JUMP, 1);
         else
            setAction(ACTION_JUMP, 0);
      } else {
         setAction(ACTION_JUMP, 0);
      }
   }

	// For satchel
	if (seth.value[VAR_SATCHEL_AUTOSHOOT]
			&& (eth.cg_entities[eth.cg_clientNum].currentState->weapon == WP_SATCHEL_DET)
			&& (eth.mod->type != MOD_TCE)) {
		doSatchelAutoShoot();
	// All others weapons
	} else if (isCommandTime()==1)
	    doAutoShoot(!autoShootWeapon);

}

void doVecZ(int player) {
	ethEntity_t *entity = &eth.entities[player];
	
	// No need if not an enemy
	if (!IS_PLAYER_ENEMY(player))
		return;

	// For tce
	if (eth.mod->type != MOD_TCE) {
		VectorMA(entity->head, seth.value[VAR_VECZ], entity->headAxis[2], entity->head);
	// For all others mod
	} else {
		// Set different vecz for different weapon
		switch (eth.cg_snap->ps.weapon) {
			case WP_LUGER:
			case WP_SILENCER:
			case WP_AKIMBO_LUGER:
			case WP_AKIMBO_SILENCEDLUGER:
			case WP_COLT:
			case WP_SILENCED_COLT:
			case WP_AKIMBO_COLT:
			case WP_AKIMBO_SILENCEDCOLT:
			case WP_MP40:
			case WP_NQ_STG44: 
			case WP_THOMPSON:
			case WP_NQ_BAR:
			case WP_MOBILE_MG42:
			case WP_GARAND:
			case WP_K43:
			case WP_FG42:
			case WP_STEN:
			case WP_NQ_STEN_MKII:
			case WP_NQ_MP34: 
			case WP_CARBINE:
			case WP_KAR98:
			case WP_GARAND_SCOPE:
			case WP_K43_SCOPE:
			case WP_FG42SCOPE:
				if (seth.value[VAR_AIMVECZ_TYPE] == VECZ_HITBOX) {
					vec3_t rmin;
					vec3_t rmax;
					VectorCopy(entity->rmin,rmin);
					VectorCopy(entity->rmax,rmax);

					entity->head[0]=entity->head[0]+(headModel.mins[0]+headModel.maxs[0])*0.5f;
					entity->head[1]=entity->head[1]+(headModel.mins[1]+headModel.maxs[1])*0.5f;
					entity->head[2]=entity->head[2]+(headModel.mins[2]+headModel.maxs[2])*0.5f;

					int corrType = (int) seth.value[VAR_HITBOX];
					if( corrType != HITBOX_OFF ){
						orientation_t or;
						orig_syscall(CG_R_LERPTAG, &or, &eth.cg_entities[player].pe_bodyRefEnt, "tag_head", 0);
					// FreeHax new hitbox correction
						// crouching 
						if( eth.cg_entities[player].currentState->eFlags & EF_CROUCHING ){
							entity->head[0] += hitboxDef[corrType][MS_CROUCHING].x;
							entity->head[1] += hitboxDef[corrType][MS_CROUCHING].y;
							entity->head[2] += hitboxDef[corrType][MS_CROUCHING].z;
						// prone bastards
						} else if ( eth.cg_entities[player].currentState->eFlags & EF_PRONE ||
							eth.cg_entities[player].currentState->eFlags & EF_PRONE_MOVING){
							entity->head[0] += hitboxDef[corrType][MS_PRONE].x;
							entity->head[1] += hitboxDef[corrType][MS_PRONE].y;
							entity->head[2] += hitboxDef[corrType][MS_PRONE].z;
							
						} else {
							entity->head[0] += hitboxDef[corrType][MS_STANDING].x;
							entity->head[1] += hitboxDef[corrType][MS_STANDING].y;
							entity->head[2] += hitboxDef[corrType][MS_STANDING].z;								
						}
					}

				} else if (seth.value[VAR_AIMVECZ_TYPE] == VECZ_MANUAL) {
				
				// Simple vecz correction
					switch (eth.cg_snap->ps.weapon) {
						case WP_STEN:
						case WP_NQ_MP34:
						case WP_NQ_STEN_MKII:
							VectorMA(entity->head, seth.value[VAR_VECZ_STEN], entity->headAxis[2], entity->head);
							break ;
						case WP_K43_SCOPE:
						case WP_NQ_K43_SCOPE:
						case WP_GARAND_SCOPE:
						case WP_NQ_GARAND_SCOPE:
						case WP_FG42SCOPE:
							VectorMA(entity->head, seth.value[VAR_VECZ_SCOPE], entity->headAxis[2], entity->head);
							break;
						default:
							VectorMA(entity->head, seth.value[VAR_VECZ], entity->headAxis[2], entity->head);
							break;
					}
				// Auto vecz
				} else if (seth.value[VAR_AIMVECZ_TYPE] == VECZ_AUTO) {
					#define NEAR_TARGET_VECZ 5.0f

					// Scoped weapons always aim at the middle of head
					if (eth.cg_snap->ps.weapon == WP_NQ_GARAND_SCOPE || eth.cg_snap->ps.weapon == WP_NQ_K43_SCOPE || eth.cg_snap->ps.weapon == WP_NQ_FG42_SCOPE) {
						VectorMA(entity->head, 5.0f, entity->headAxis[2], entity->head);
						return;
					}
					// FreeHax Auto VecZ on NQ Mods
					if(( eth.mod->type == MOD_NQ ) || (eth.cg_snap->ps.weapon == WP_NQ_GARAND_SCOPE || eth.cg_snap->ps.weapon == WP_NQ_K43_SCOPE || eth.cg_snap->ps.weapon == WP_NQ_FG42_SCOPE)) {
						VectorMA(entity->head, 4.9f, entity->headAxis[2], entity->head);
						return;
					}
					// Different 'near distance' for sten
					int nearTarget;
					if (eth.cg_snap->ps.weapon == WP_STEN)
						nearTarget = 700.0f;
					else
						nearTarget = 500.0f;

					if (entity->distance <= nearTarget)
						VectorMA(entity->head, NEAR_TARGET_VECZ, entity->headAxis[2], entity->head);
					else if ((entity->distance > nearTarget) && (entity->distance < 2000.0f))
						VectorMA(entity->head, (NEAR_TARGET_VECZ * (100.0f - ((entity->distance - nearTarget) / 5.0f))) / 100.0f, entity->headAxis[2], entity->head);
				}
				break;
			default:
				break;
		}
	}
}

void doPrediction(int player) {
	// No predicton
	if (!seth.value[VAR_AIMPREDICT])
		return;
	
	ethEntity_t *entity = &eth.entities[player];

	// Frametime prediction based
		if (seth.value[VAR_AIMPREDICT] == AIMPREDICT_AUTO_1) {
			vec3_t displ, v1, vp, p;
			VectorSubtract(entity->head, eth.muzzle, p);
			VectorNormalizeFast(p);
				float f = DotProduct(eth.cg_snap->ps.velocity, p);
			VectorScale(p, f, v1);
			VectorSubtract(eth.cg_snap->ps.velocity, v1, vp);
			VectorScale(vp, seth.value[VAR_PREDICT_VALUE], displ);
	
			VectorAdd(entity->head, displ, entity->head);            
	} else if (seth.value[VAR_AIMPREDICT] == AIMPREDICT_AUTO_2) {
		vec3_t velocity;
		VectorScale(eth.cg_entities[player].currentState->pos.trDelta, 1000.0f / ((float)(eth.cg_frametime) - eth.cg_entities[player].currentState->pos.trTime) , velocity);
		VectorMA(entity->origin, (float)(eth.cg_frametime) / 1000.0f, velocity, entity->origin);
		VectorMA(entity->head, (float)(eth.cg_frametime) / 1000.0f, velocity, entity->head);
	} else if (seth.value[VAR_AIMPREDICT] == AIMPREDICT_AUTO_3) {
		VectorAdd(history[player][2].prPos,entity->head,entity->head);
	VectorAdd(history[player][2].prPos,entity->origin,entity->origin);
		//kobj if want pred also add to head refent for hitbox ( i assume angles dont need pred, just pos )
		VectorAdd(history[player][2].prPos,entity->refHead.origin,entity->refHead.origin);
	} else if (seth.value[VAR_AIMPREDICT] == AIMPREDICT_AUTO_4) {

	    if (seth.value[VAR_INTERPOLATE] == qtrue)
		eth_interpolate(player);
		VectorAdd(history[player][0].prPos,entity->head,entity->head);
		VectorAdd(history[player][0].prPos,entity->origin,entity->origin);
		//kobj if want pred also add to head refent for hitbox ( i assume angles dont need pred, just pos )
		VectorAdd(history[player][0].prPos,entity->refHead.origin,entity->refHead.origin);
	        } else if (seth.value[VAR_AIMPREDICT] == AIMPREDICT_UNSEEN) {		
		VectorMA(entity->head, (float)(eth.cg_frametime) / 182.0f, eth.cg_entities[player].currentState->pos.trDelta, entity->head);
		VectorMA (entity->head, eth.cg_snap->ping / 800, eth.cg_entities[player].currentState->pos.trDelta, entity->head);
                vec3_t velocity;
		VectorScale(eth.cg_entities[player].currentState->pos.trDelta, 1999.0f / ((float)(eth.cg_frametime) - eth.cg_entities[player].currentState->pos.trTime) , velocity);
		VectorMA(entity->origin, (float)(eth.cg_frametime) / 928.0f, velocity, entity->origin);
		VectorMA(entity->head, (float)(eth.cg_frametime) / 182.0f, velocity, entity->head);
	} else if (seth.value[VAR_AIMPREDICT] == AIMPREDICT_SNAPSHOT ) {
		snapshotPredict(player);
		VectorMA(entity->origin,  (eth.myping/2) * 0.001f, history[player][0].prPos, entity->origin);
		VectorMA(entity->head, (eth.myping/2)  * 0.001f, history[player][0].prPos, entity->head);

	} else 
		ethLog("error: invalid aim prediction type: %i", seth.value[VAR_AIMPREDICT]);
}

#ifdef ETH_DEBUG

void doPredictionStats() {
	static int lastTarget = -1;
	int target = -1;

	// Find the nearest moving player
	int count;
	int targetDistance = -1;
	static vec3_t lastPosition[MAX_CLIENTS];
	for (count = 0; count < MAX_CLIENTS; count++) {
		// If valid and moving
		if (IS_PLAYER_VALID(count) && !VectorCompare(lastPosition[count], eth.entities[count].origin)) {
			// If nearest
			if ((targetDistance == -1) || (eth.entities[count].distance < targetDistance)) {
				target = count;
				targetDistance = eth.entities[count].distance;
			}
		}
	}

	// Backup for next frame
	lastTarget = target;

	// Store all players positions for next frame
	for (count = 0; count < MAX_CLIENTS; count++) {
		if (IS_PLAYER_VALID(count))
			VectorCopy(eth.entities[count].origin, lastPosition[count]);
	}

	// If no target found or not the same target
	if ((target == -1) || (lastTarget != target))
		return;

	// Init prediction stats
	ethEntity_t *entity = &eth.entities[target];
	static vec3_t lastOrigin;
	static vec3_t lastPredictOrigin;


	// Backup var for next frame
	VectorCopy(entity->origin, lastOrigin);

	doPrediction(target);

	// Backup var for next frame
	VectorCopy(entity->origin, lastPredictOrigin);
}

#endif // ETH_DEBUG
