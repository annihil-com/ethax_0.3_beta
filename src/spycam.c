// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

#include "ethax.h"
// to get info about windowchanging
vec4_t colorCam = {0.0f,0.0f,0.0f,0.0f};

void drawSpyCam(float x, float y, float width, float height, refdef_t *refDef, qhandle_t enemyShader, qhandle_t friendShader, qboolean crosshair) {
	// Add all backuped refEntities to the scene
	int count = 0;
	for (; count < eth.refEntitiesCount; count++) {
		refEntity_t* refEnt = &eth.refEntities[count];
		int entityNum = refEnt->entityNum ;
		// If valid player
		if ((eth.cg_entities[entityNum].currentState->eType == ET_PLAYER)
				&& (entityNum < MAX_CLIENTS)
				&& eth.clientInfo[entityNum].infoValid
				&& (entityNum != eth.cg_snap->ps.clientNum)
				// If not dead
				&& !(eth.cg_entities[entityNum].currentState->eFlags & EF_DEAD)
				// If not vulnerable
				&& (!(eth.cg_entities[entityNum].currentState->powerups & (1 << PW_INVULNERABLE)))
				// If body
				&& refEnt->torsoFrameModel) {
			if (IS_PLAYER_ENEMY(entityNum))
				refEnt->customShader = enemyShader;
			else
				refEnt->customShader = friendShader;

			refEnt->renderfx |= RF_DEPTHHACK | RF_NOSHADOW;
		}
		orig_syscall(CG_R_ADDREFENTITYTOSCENE, refEnt);
	}

	// Adjust refDef from 640
	refDef->x = x * eth.cgs_screenXScale;
	refDef->y = y * eth.cgs_screenYScale;
	refDef->width = width * eth.cgs_screenXScale;
	refDef->height = height * eth.cgs_screenYScale;
	
	// Draw the spycam scene
	drawFillRect(x, y, width, height, colorBlack);
	orig_syscall(CG_R_RENDERSCENE, refDef);

	// Draw border
	drawRect(x, y, width, height, colorBlack, 1);

	if(colorCam[3] != 0.0f) 
	    drawFillRect(x,y,width,height,colorCam);	
	// Draw the crosshair
	#define CROSSHAIR_SIZE 4
	if (crosshair)
		drawRect(x + (width / 2) - (CROSSHAIR_SIZE / 2), y + (height / 2) - (CROSSHAIR_SIZE / 2) , CROSSHAIR_SIZE, CROSSHAIR_SIZE, colorRed, 1);
}

void drawSatchelCam() {
	int satchelEntityNum = findSatchel();
	
	// If don't find satchel
	if (satchelEntityNum == -1)
		return;

	// Set the view
	refdef_t camRefDef;
	memcpy(&camRefDef, &eth.cg_refdef, sizeof(refdef_t));
	// fov
	camRefDef.fov_x = 60;
	camRefDef.fov_y = 60;
	// origin
	VectorCopy(eth.entities[satchelEntityNum].origin, camRefDef.vieworg);
	camRefDef.vieworg[ROLL] += seth.value[VAR_SATCHELCAM_H];		// Up the cam
	// view angle
	vec3_t camAngle;
	VectorCopy(eth.cg_refdefViewAngles, camAngle);
	camAngle[PITCH] = 90;	// Look down
	AnglesToAxis(camAngle, camRefDef.viewaxis);

	// Draw the spycam
	drawSpyCam(10, 10, 240, 240, &camRefDef, eth.enemyVisibleShader, eth.friendVisibleShader, qfalse);
}
// windowed mortarcam
eth_window_t mortarwin;
void drawMortarCam() {
	// Set mortar trajectory from current view
	vec3_t angles, forward;
	VectorCopy(eth.cg_refdef.viewaxis[ROLL], forward);  // TODO: seems not need
	VectorCopy(eth.cg_snap->ps.viewangles, angles);
	angles[PITCH] -= 60.f;
	AngleVectors(angles, forward, NULL, NULL);
	forward[0] *= 3000 * 1.1f;
	forward[1] *= 3000 * 1.1f;
	forward[2] *= 1500 * 1.1f;

	trajectory_t mortarTrajectory;
	mortarTrajectory.trType = TR_GRAVITY;
	mortarTrajectory.trTime = eth.cg_time;
	VectorCopy(eth.cg_refdef.vieworg, mortarTrajectory.trBase);	 // TODO: Not precise need some muzzle
	VectorCopy(forward, mortarTrajectory.trDelta);

	// Calculate mortar impact
	int timeOffset = 0;
	trace_t mortarTrace;
	vec3_t mortarImpact;
	VectorCopy(mortarTrajectory.trBase, mortarImpact);
	#define TIME_STEP 20
	while (timeOffset < 10000) {
		vec3_t nextPos;
		timeOffset += TIME_STEP;
		eth.BG_EvaluateTrajectory(&mortarTrajectory, eth.cg_time + timeOffset, nextPos, qfalse, 0);
		eth.CG_Trace(&mortarTrace, mortarImpact, 0, 0, nextPos, eth.cg_snap->ps.clientNum, MASK_MISSILESHOT);
		if ((mortarTrace.fraction != 1)
				// Check for don't hit sky
				&& !((mortarTrace.surfaceFlags & SURF_NODRAW) || (mortarTrace.surfaceFlags & SURF_NOIMPACT))
				&& (mortarTrace.contents != 0)) {
			break;
		}
		VectorCopy(nextPos, mortarImpact);
	}

	// Set the view
	refdef_t camRefDef;
	memcpy(&camRefDef, &eth.cg_refdef, sizeof(refdef_t));
	// fov
	camRefDef.fov_x = 90;
	camRefDef.fov_y = 90;
	// origin
	VectorCopy(mortarImpact, camRefDef.vieworg);
	camRefDef.vieworg[ROLL] += seth.value[VAR_MORTARCAM_H];		// Up the cam
	// angle
	vec3_t camAngle;
	VectorCopy(eth.cg_refdefViewAngles, camAngle);
	camAngle[PITCH] = 90;	// Look down
	AnglesToAxis(camAngle, camRefDef.viewaxis);


	//initialize window
	if(!mortarwin.posX) {
	    mortarwin.posX = 10;
	    mortarwin.posY = 10;
	    mortarwin.windowW = 320;
	    mortarwin.windowH = 320;
	}

	getWindowStatus(&mortarwin);    
	//clear it anyway
	memset(&colorCam,0,sizeof(vec4_t));

        if (mortarwin.isMouseOn) {
            colorCam[3]=5.0f;
            if(mortarwin.isSticked) {
                int i=0;
                for (; i < 3 ; i++)
                    colorCam[i] += 0.5f;
            }
        }

	// Draw the mortarcam
	drawSpyCam(mortarwin.posX, mortarwin.posY, mortarwin.windowW, mortarwin.windowH, &camRefDef, eth.enemyMortarShader, eth.friendMortarShader, qtrue);

	// Draw impact time	
	char str[128];
	sprintf(str, "^0[ ^3Impact in:^2 %.1f ^3seconds ^0]", (float)timeOffset / 1000.0f);
	drawText(mortarwin.posX + (mortarwin.windowW - sizeTextWidth(0.19f, str, &eth.fontVariable)) / 2, mortarwin.posY + mortarwin.windowH - 15, 0.19f, str, 
colorWhite, qfalse, qtrue, &eth.fontVariable);
}

void drawPanzerCam() {
	// Set panzer direction
	vec3_t forward;
	AngleVectors(eth.cg_snap->ps.viewangles, forward, NULL, NULL );

	// Set a far away end point
	vec3_t aheadPos;
	VectorMA(eth.muzzle, 65536.0f, forward, aheadPos);
	
	// Find panzer impact
	trace_t panzerTrace;
	eth.CG_Trace(&panzerTrace, eth.muzzle, NULL, NULL, aheadPos, eth.cg_snap->ps.clientNum, MASK_MISSILESHOT);
	
	// If no impact or hit sky don't draw cam
	if ((panzerTrace.fraction == 1.0f) || (panzerTrace.surfaceFlags & SURF_NOIMPACT))
		return;

	// Set the view
	refdef_t camRefDef;
	memcpy(&camRefDef, &eth.cg_refdef, sizeof(refdef_t));
	// fov
	camRefDef.fov_x = 30;
	camRefDef.fov_y = 30;
	// angle
	AnglesToAxis(eth.cg_refdefViewAngles, camRefDef.viewaxis);
	VectorCopy(panzerTrace.endpos, camRefDef.vieworg);
	// origin
	vec3_t stepBack;
	VectorMA(vec3_origin, 400, forward, stepBack);
	VectorSubtract(camRefDef.vieworg, stepBack, camRefDef.vieworg);
	
	// Draw the panzer cam
	drawSpyCam(10, 10, 160, 160, &camRefDef, eth.enemyVisibleShader, eth.friendVisibleShader, qtrue);
}

void drawMirrorCam() {
	#define MIRRORCAM_WIDTH 640.0f
	#define MIRRORCAM_HEIGHT 100.0f
	// Set the view
	refdef_t camRefDef;
	memcpy(&camRefDef, &eth.cg_refdef, sizeof(refdef_t));
	// fov
	camRefDef.fov_x = 90.0f;
	camRefDef.fov_y = 90.0f * (MIRRORCAM_HEIGHT / MIRRORCAM_WIDTH);
	// view angle
	vec3_t camAngle;
	VectorCopy(eth.cg_refdefViewAngles, camAngle);
	camAngle[YAW] -= 180.0f;	// Look behind
	AnglesToAxis(camAngle, camRefDef.viewaxis);

	// Draw the spycam
	drawSpyCam(0, 0, MIRRORCAM_WIDTH - 1, MIRRORCAM_HEIGHT - 1, &camRefDef, eth.enemyVisibleShader, eth.friendVisibleShader, qfalse);
}

void drawRiffleCam() {
	vec3_t angles, forward, viewpos;

	trajectory_t riffleTrajectory;
	riffleTrajectory.trType = TR_GRAVITY;
	riffleTrajectory.trTime = eth.cg_time;
	VectorCopy(eth.muzzle, riffleTrajectory.trBase);
	VectorCopy(riffleTrajectory.trBase, viewpos);

	VectorCopy(eth.cg_snap->ps.viewangles, angles);
	AngleVectors(angles, forward, NULL,NULL);
	viewpos[2] += eth.cg_snap->ps.viewheight;
	VectorMA(viewpos, 32, forward, viewpos);
	VectorScale(forward, 2000, forward);

	VectorCopy(forward, riffleTrajectory.trDelta);
	SnapVector(riffleTrajectory.trDelta);

	// Calculate riffle impact
	int timeOffset = 0;
	trace_t riffleTrace;
	vec3_t riffleImpact;
	VectorCopy(riffleTrajectory.trBase, riffleImpact);
	#define TIME_STEPP 50
	int maxTime = 3250;
	int totalFly = 0;

	while (timeOffset < maxTime) {
		vec3_t nextPos;
		timeOffset += TIME_STEPP;
		totalFly += TIME_STEPP;

		eth.BG_EvaluateTrajectory(&riffleTrajectory, eth.cg_time + timeOffset, nextPos, qfalse, 0);
		eth.CG_Trace(&riffleTrace, riffleImpact, 0, 0, nextPos, eth.cg_snap->ps.clientNum, MASK_MISSILESHOT);

		// check for hit 
		if (riffleTrace.startsolid || riffleTrace.fraction != 1) {
			// When a nade flies for over 750ms and hits something, it'll explode
			if (totalFly > 750)
				break;

			// calculate reflect angle (forward axis)
			int hitTime = eth.cg_time + totalFly - TIME_STEPP + TIME_STEPP * riffleTrace.fraction;
			eth_BG_EvaluateTrajectoryDelta(&riffleTrajectory, hitTime, riffleTrajectory.trDelta, qfalse, 0);
			float dot = DotProduct(riffleTrajectory.trDelta, riffleTrace.plane.normal);
			VectorMA(riffleTrajectory.trDelta, -2*dot, riffleTrace.plane.normal, riffleTrajectory.trDelta);

			VectorScale(riffleTrajectory.trDelta, 0.35, riffleTrajectory.trDelta);

			if (riffleTrace.surfaceFlags == 0)
				VectorScale(riffleTrajectory.trDelta, 0.5, riffleTrajectory.trDelta);

			// calc new max time and reset trTime
			maxTime -= timeOffset;
			timeOffset = 0;
			riffleTrajectory.trTime = eth.cg_time;

			// new base origins 
			VectorCopy(riffleTrace.endpos, riffleTrajectory.trBase);
			
			SnapVector(riffleTrajectory.trDelta);
			SnapVector(riffleTrajectory.trBase);
		} else {
			VectorCopy(nextPos, riffleImpact);
       		#define POINT_SIZE 2
			int x, y;
       		if (worldToScreen(nextPos, &x, &y)) {
		  		if (isVisible(nextPos, NULL, NULL ))
					drawFillRect(x - (POINT_SIZE / 2), y - (POINT_SIZE / 2), POINT_SIZE, POINT_SIZE, colorYellow);
				else 
					drawFillRect(x - (POINT_SIZE / 2), y - (POINT_SIZE / 2), POINT_SIZE, POINT_SIZE, colorRed);
			}
		}
	}

	// Set the view
	refdef_t camRefDef = eth.cg_refdef;
	// fov
	camRefDef.fov_x = 90;
	camRefDef.fov_y = 90;
	// origin
	VectorCopy(riffleImpact, camRefDef.vieworg);
	camRefDef.vieworg[ROLL] += seth.value[VAR_RIFLECAM_H];		// Up the cam
	// angle
	vec3_t camAngle;
	VectorCopy(eth.cg_refdefViewAngles, camAngle);
	camAngle[PITCH] = 55.0 ;	// Look down
	AnglesToAxis(camAngle, camRefDef.viewaxis);

	// Draw the rifflecam
	drawSpyCam(10, 10, 250, 250, &camRefDef, eth.enemyMortarShader, eth.friendMortarShader, qtrue);

	// Draw impact time	
	char str[128];
	sprintf(str, "^2%.1f ^3s", (float)totalFly / 1000.0f);
	drawText(10 + (250 - sizeTextWidth(0.19f, str, &eth.fontVariable)) / 2, 10 + 250 - 15, 0.19f, str, colorWhite, qfalse, qtrue, &eth.fontVariable);
}

void drawEntityCam( int player ) {
	if( player < 0 || player > MAX_CLIENTS )
		return;
	if ( !eth.entities[player].isValid )
		return;

	ethEntity_t *ent = &eth.entities[player];

	//set camera view
	refdef_t camRefDef;
	memcpy(&camRefDef, &eth.cg_refdef, sizeof(refdef_t));
	camRefDef.fov_x = 90;
	camRefDef.fov_y = 90;

	//set origin and translate a bit forward
	vec3_t origin;
	VectorCopy( ent->head, origin );
	VectorMA( origin, 5, ent->headAxis[0], origin );
	VectorCopy( origin, camRefDef.vieworg );

	//set angles //FIXME: find lerped angles somewhere for smoother view
	memcpy(ent->headAxis, camRefDef.viewaxis, sizeof(vec3_t) * 3);
	AnglesToAxis( eth.cg_entities[player].currentState->apos.trBase, camRefDef.viewaxis );
	//memcpy( eth.cg_entities[player].pe_bodyRefEnt.axis, camRefDef.viewaxis, sizeof(vec3_t) * 3);

	/*
	vec3_t camangle;
	AxisToAngles( camRefDef.viewaxis, camangle ); 
	printf("{%.1f,%.1f,%.1f}\n", camangle[0], camangle[1], camangle[2]);
	*/

	// Draw the spycam
	refdef_t *refDef = &camRefDef;

	float x = 10;
	float y = 10;
	float width = 240;
	float height = 240;

	// fool engine/mod into drawing ourselves :D
	int oldflags = eth.cg_entities[eth.cg_snap->ps.clientNum].currentState->eFlags;
	int *flags = &eth.cg_entities[eth.cg_snap->ps.clientNum].currentState->eFlags;
	*flags &= ~EF_NODRAW;
	
	// Add all backuped refEntities to the scene
	int count = 0;
	for (; count < eth.refEntitiesCount; count++) {
		refEntity_t* refEnt = &eth.refEntities[count];
		int entityNum = refEnt->entityNum ;

		// set special flag for entcam subject
		if( entityNum == player )
			refEnt->renderfx &= RF_FIRST_PERSON;

		if( entityNum == player && seth.value[VAR_ENTCAM] == ENTCAM_SNIPER )
			continue;

		// make sure we draw ourselves :D
		if( entityNum == eth.cg_snap->ps.clientNum )
			refEnt->renderfx &= ~RF_THIRD_PERSON;

		orig_syscall(CG_R_ADDREFENTITYTOSCENE, refEnt);
	}

	// Adjust refDef from 640
	refDef->x = x * eth.cgs_screenXScale;
	refDef->y = y * eth.cgs_screenYScale;
	refDef->width = width * eth.cgs_screenXScale;
	refDef->height = height * eth.cgs_screenYScale;
	
	// Draw the entcam scene
	drawFillRect(x, y, width, height, colorBlack);
	orig_syscall(CG_R_RENDERSCENE, refDef);

	// Draw border
	drawRect(x, y, width, height, colorBlack, 1);

	if(colorCam[3] != 0.0f)
		drawFillRect(x,y,width,height,colorCam);
	// Draw the crosshair
#define CROSSHAIR_SIZE 4
	drawRect(x + (width / 2) - (CROSSHAIR_SIZE / 2), y + (height / 2) - (CROSSHAIR_SIZE / 2) , CROSSHAIR_SIZE, CROSSHAIR_SIZE, colorRed, 1);

	// back us up please
	*flags = oldflags; 
}

void dropCam() {
	if( VectorCompare(eth.dropCamRefDef[1], vec3_origin) )
		return;
	refdef_t camRefDef;
	memcpy(&camRefDef, &eth.cg_refdef, sizeof(refdef_t));
	camRefDef.fov_x = 90.0f;
	camRefDef.fov_y = 90.0f;
	VectorCopy(eth.dropCamRefDef[1], camRefDef.vieworg );
	AnglesToAxis(eth.dropCamRefDef[0], camRefDef.viewaxis);
	
	// Draw the spycam
// Draw the spycam
	refdef_t *refDef = &camRefDef;

	float x = 5;
	float y = 10;
	float width = 260;
	float height = 260;

	// fool engine/mod into drawing ourselves :D
	int oldflags = eth.cg_entities[eth.cg_snap->ps.clientNum].currentState->eFlags;
	int *flags = &eth.cg_entities[eth.cg_snap->ps.clientNum].currentState->eFlags;
	*flags &= ~EF_NODRAW;
	
	// Add all backuped refEntities to the scene
	int count = 0;
	for (; count < eth.refEntitiesCount; count++) {
		refEntity_t* refEnt = &eth.refEntities[count];
		int entityNum = refEnt->entityNum ;

		if ((eth.cg_entities[entityNum].currentState->eType == ET_PLAYER)
				   && (entityNum < MAX_CLIENTS)
				   && eth.clientInfo[entityNum].infoValid
				   && (entityNum != eth.cg_snap->ps.clientNum)
				// If not dead
				   && !(eth.cg_entities[entityNum].currentState->eFlags & EF_DEAD)
				// If not vulnerable
				   && (!(eth.cg_entities[entityNum].currentState->powerups & (1 << PW_INVULNERABLE)))
				// If body
				   && refEnt->torsoFrameModel) {
			if (IS_PLAYER_ENEMY(entityNum))
				refEnt->customShader = eth.enemyVisibleShader;
			else
				refEnt->customShader = eth.friendVisibleShader;

			refEnt->renderfx |= RF_DEPTHHACK | RF_NOSHADOW;
		}
		
		// make sure we draw ourselves :D
		if( entityNum == eth.cg_snap->ps.clientNum ){
			refEnt->renderfx |= RF_DEPTHHACK | RF_NOSHADOW;
			refEnt->renderfx &= ~RF_THIRD_PERSON;
		}

		orig_syscall(CG_R_ADDREFENTITYTOSCENE, refEnt);
	}

	// Adjust refDef from 640
	refDef->x = x * eth.cgs_screenXScale;
	refDef->y = y * eth.cgs_screenYScale;
	refDef->width = width * eth.cgs_screenXScale;
	refDef->height = height * eth.cgs_screenYScale;
	
	// Draw the entcam scene
	drawFillRect(x, y, width, height, colorBlack);
	orig_syscall(CG_R_RENDERSCENE, refDef);

	// Draw border
	drawRect(x, y, width, height, colorBlack, 1);

	if(colorCam[3] != 0.0f)
		drawFillRect(x,y,width,height,colorCam);

	// back us up please
	*flags = oldflags; 
}

void drawGrenadeCam() {
	vec3_t angles, forward, viewpos;
	trajectory_t grenadeTrajectory;
	
	grenadeTrajectory.trType = TR_GRAVITY;
	grenadeTrajectory.trTime = eth.cg_time;
	
	VectorCopy(eth.muzzle, grenadeTrajectory.trBase);
	VectorCopy(grenadeTrajectory.trBase, viewpos);
	VectorCopy(eth.cg_snap->ps.viewangles, angles);
	
	AngleVectors(angles, forward, NULL,NULL);
	viewpos[2] += eth.cg_snap->ps.viewheight;
	VectorMA(viewpos, 32, forward, viewpos);
	VectorScale(forward, 2000, forward);
	
	VectorCopy(forward, grenadeTrajectory.trDelta);
	SnapVector(grenadeTrajectory.trDelta);
	
    // Calculate Gre impact
	int timeOffset = 0;
	trace_t grenadeTrace;
	vec3_t grenadeImpact;
	VectorCopy(grenadeTrajectory.trBase, grenadeImpact);

#define TIME_STEPP 50

	int maxTime = 2000;
	int totalFly = 0;
	
	while (timeOffset < maxTime) {
		vec3_t nextPos;
		timeOffset += TIME_STEPP;
		totalFly += TIME_STEPP;
		
		eth.BG_EvaluateTrajectory(&grenadeTrajectory, eth.cg_time + timeOffset, nextPos, qfalse, 0);
		eth.CG_Trace(&grenadeTrace, grenadeImpact, 0, 0, nextPos, eth.cg_snap->ps.clientNum, MASK_MISSILESHOT);
        // check for hit
		if (grenadeTrace.startsolid || grenadeTrace.fraction != 1) {
			if (totalFly > 350)
				break;
            // calculate reflect angle (forward axis)
			int hitTime = eth.cg_time + totalFly - TIME_STEPP + TIME_STEPP * grenadeTrace.fraction;
			eth_BG_EvaluateTrajectoryDelta(&grenadeTrajectory, hitTime, grenadeTrajectory.trDelta, qfalse, 0);
			float dot = DotProduct(grenadeTrajectory.trDelta, grenadeTrace.plane.normal);
			VectorMA(grenadeTrajectory.trDelta, -2*dot, grenadeTrace.plane.normal, grenadeTrajectory.trDelta);
			VectorScale(grenadeTrajectory.trDelta, 0.15, grenadeTrajectory.trDelta);
			if (grenadeTrace.surfaceFlags == 0)
				VectorScale(grenadeTrajectory.trDelta, 0.5, grenadeTrajectory.trDelta);
            // calc new max time and reset trTime
			maxTime -= timeOffset;
			timeOffset = 0;
			grenadeTrajectory.trTime = eth.cg_time;
                        // new base origins
			VectorCopy(grenadeTrace.endpos, grenadeTrajectory.trBase);
			SnapVector(grenadeTrajectory.trDelta);
			SnapVector(grenadeTrajectory.trBase);
		} else {
			VectorCopy(nextPos, grenadeImpact);
#define POINT_SIZE 2
			int x, y;
			if (worldToScreen(nextPos, &x, &y)) {
				if (isVisible(nextPos, NULL, NULL))
					drawFillRect(x - (POINT_SIZE / 2), y - (POINT_SIZE / 2), POINT_SIZE, POINT_SIZE, colorGreen);
				else
				drawFillRect(x - (POINT_SIZE / 2), y - (POINT_SIZE / 2), POINT_SIZE, POINT_SIZE, colorBlue);
			}
		}
	}
        // Set the view
	refdef_t camRefDef;
	camRefDef.fov_x = 80;
	camRefDef.fov_y = 80;
	VectorCopy(grenadeImpact, camRefDef.vieworg);
	camRefDef.vieworg[ROLL] += seth.value[VAR_GRENADECAM_H];                // Up the cam
	vec3_t camAngle;
	VectorCopy(eth.cg_refdefViewAngles, camAngle);
	camAngle[PITCH] = 80;   // Look down
	AnglesToAxis(camAngle, camRefDef.viewaxis);
	drawSpyCam(10, 10, 130, 150, &camRefDef, eth.enemyMortarShader, eth.friendMortarShader, qtrue);
	char str[128];
	sprintf(str, "^2%.1f ^3s", (float)totalFly / 1000.0f);
	drawText(10 + (250 - sizeTextWidth(0.19f, str, &eth.fontVariable)) / 2, 10 + 250 - 15, 0.19f, str, colorWhite, qfalse, qtrue, &eth.fontVariable);
}
