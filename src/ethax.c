// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

#include <unistd.h>

#include "ethax.h"

/*
==============================
Some utils functions
==============================
*/

int getSpawntimer(qboolean enemySpawn) {
	int team = eth.clientInfo[eth.cg_snap->ps.clientNum].team;
	int limbotime = 0;

	// Reverse the value from clientinfo[myself].team to make the function return the spawn time of the other team
    if(enemySpawn == qtrue) {
		if (team == TEAM_AXIS) {
			team = TEAM_ALLIES;
			limbotime = eth.cg_bluelimbotime;
		} else if (team == TEAM_ALLIES) {
			team = TEAM_AXIS;
			limbotime = eth.cg_redlimbotime;
		} else
			return -1;
    } else {
		if (team == TEAM_AXIS) {
			limbotime = eth.cg_redlimbotime;
		} else if (team == TEAM_ALLIES) {
			limbotime = eth.cg_bluelimbotime;
		} else
			return -1;
    }
    
    // Sanity check
    if (limbotime == 0) {
    	ethLog("warning: can't get spawntimer for team %i", team);
    	return -1;
    }

    return (int)(1 + (limbotime - ((eth.cgs_aReinfOffset[team] + eth.cg_time - eth.cgs_levelStartTime) % limbotime)) * 0.001f);
}

int findSatchel() {
	int entityNum = 0;
	for (; entityNum < MAX_GENTITIES; entityNum++) {
		if ((eth.cg_entities[entityNum].currentState->weapon == WP_SATCHEL)
				&& (eth.cg_entities[entityNum].currentState->clientNum == eth.cg_snap->ps.clientNum)
				&& (!VectorCompare(eth.entities[entityNum].origin, vec3_origin)))
			return entityNum;
	}
	#ifdef ETH_DEBUG
		ethDebug("satchel cam: don't find satchel for %i", eth.cg_snap->ps.clientNum);
	#endif
	return -1;
}

qboolean isKeyActionDown(char *action) {
	int key1, key2;
	orig_syscall(CG_KEY_BINDINGTOKEYS, action, &key1, &key2);

	if (syscall_CG_Key_IsDown(key1) || syscall_CG_Key_IsDown(key2))
		return qtrue;
	else
		return qfalse;
}

int getIdByName (const char *name, int len) {
	int i;
	if (!len)
		len = strlen(name);
	
	for (i=0; i < MAX_CLIENTS; i++)
		if (eth.clientInfo[i].infoValid && !strncmp(eth.clientInfo[i].name, name, len))
			return i;
	return -1;
}

qboolean isVisible(vec3_t target, vec3_t mins, vec3_t maxs ) {
	trace_t trace;
	eth.CG_Trace(&trace, eth.cg_refdef.vieworg, mins, maxs, target, eth.cg_snap->ps.clientNum, CONTENTS_SOLID | CONTENTS_CORPSE);
	return (trace.fraction == 1.0f);
}

qboolean isPlayerVisible(vec3_t target, int player) {
	trace_t traceVisible;
	eth.CG_Trace(&traceVisible, eth.cg_refdef.vieworg, NULL, NULL, target, eth.cg_snap->ps.clientNum, CONTENTS_SOLID | CONTENTS_CORPSE);

	trace_t tracePlayer;
	eth.CG_Trace(&tracePlayer, eth.cg_refdef.vieworg, NULL, NULL, target, eth.cg_snap->ps.clientNum, CONTENTS_SOLID | CONTENTS_BODY);

	//printf("XXX: want %i got %i\n", player, tracePlayer.entityNum);

	return ((traceVisible.fraction == 1.0f) && (tracePlayer.entityNum == player));
}

void ethLog(const char *format, ...) {
	printf("EThax: ");

	va_list arglist;
	va_start(arglist, format);
		vprintf(format, arglist);
	va_end(arglist);

	printf("\n");

	#ifdef ETH_DEBUG
		// If log file
		if (debugFile) {
			fprintf(debugFile, "log: ");
			va_list arglist;
			va_start(arglist, format);
				vfprintf(debugFile, format, arglist);
			va_end(arglist);	
			fprintf(debugFile, "\n");
		}
	#endif
}

#ifdef ETH_DEBUG

FILE *debugFile = NULL;
void ethDebug(const char *format, ...) {
	// If log file
	if (debugFile) {
		va_list arglist;
		va_start(arglist, format);
			vfprintf(debugFile, format, arglist);
		va_end(arglist);	
		fprintf(debugFile, "\n");
	}
}

#endif // ETH_DEBUG

void fatalError(const char *msg) {
	char str[256];
	snprintf(str, sizeof(str), "A fatal error has occured. You must restart the game.\n\nError: %s\n\n\nEThax-%s", msg, ETH_VERSION);
	orig_syscall(CG_ERROR, str);
	#ifdef ETH_DEBUG
		ethLog("fatal error: %s", msg);
	#endif
}

// Helper function for get ouput of a system command
// This function return the first line of this command output
char *getOutputSystemCommand(const char *command) {
	static char buf[256];
	memset(buf, 0, sizeof(buf));

	FILE *cmd = popen(command, "r");

	int c; 
	int count = 0;
	while (((c = getc(cmd)) != EOF) && (count < (sizeof(buf) - 1))) {
		if (c == '\n')
			break;
		buf[count++] = c;
	}

	pclose(cmd);
	return buf;
}

// If cgame is load, send a UI_PRINT message else just show a message at console,
// WARNING ! use this function only when call from ui vmMain. ex: irc and game command
#define MESSAGE_COLOR "^n"
void gameMessage(qboolean forceConsole, char *format, ...) {
	char msg[MAX_SAY_TEXT];
	memset(msg, 0, sizeof(msg));
	char buffer[sizeof(msg)];
	memset(buffer, 0, sizeof(buffer));
	va_list arglist;

	va_start(arglist, format);
		vsnprintf(msg, sizeof msg, format, arglist);
	va_end(arglist);

	if (eth.hookLoad && !forceConsole) {
		snprintf(buffer, sizeof(buffer), "echo \"" MESSAGE_COLOR "%s\"\n", msg);
		orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, buffer);
	} else {
		snprintf(buffer, sizeof(buffer), MESSAGE_COLOR "%s\n", msg);
		orig_syscall(UI_PRINT, buffer);
	}
}


void doAutoVote(char *str) {
	char *ptr = strstr(str, "^7 called a vote.  Voting for: ");
	int id = getIdByName(str, ptr - str);

	// id not found
	if (id == -1)
		return;

	// who votes
	switch (eth.clientInfo[id].targetType) {
		case PLIST_FRIEND:	
			syscall_CG_SendConsoleCommand("vote yes\n");
			return;
		case PLIST_TEAMKILLER:
			syscall_CG_SendConsoleCommand("vote no\n");
			return;
		default:
			break;
	}
	
	// Voter is not a friend/teamkiller
	ptr += strlen("^7 called a vote.  Voting for: ");

	if (!strncmp(ptr, "KICK ", 5) || !strncmp(ptr, "MUTE ", 5)) {
		ptr += 5;
		id = getIdByName(ptr, strrchr(ptr, '\n') - ptr);

		// id not found
		if (id == -1)
			return;

		// vote against client
		if (id == eth.cg_clientNum) {
			syscall_CG_SendConsoleCommand("vote no\n");
			return;
		}
		
		// who is voted against
		switch (eth.clientInfo[id].targetType) {
			case PLIST_FRIEND:
				syscall_CG_SendConsoleCommand("vote no\n");
				return;
			case PLIST_TEAMKILLER:
				syscall_CG_SendConsoleCommand("vote yes\n");
				return;
			default:
				break;
		}
	}
}

// Calc muzzle
void setCurrentMuzzle() {
	vec3_t forward, right, up;

	VectorCopy(eth.cg_snap->ps.origin, eth.muzzle);
	eth.muzzle[2] += eth.cg_snap->ps.viewheight;
	AngleVectors(eth.cg_snap->ps.viewangles, forward, right, up);

	switch (eth.weapon)	{
		case WP_PANZERFAUST:
			VectorMA(eth.muzzle, 10, right, eth.muzzle);
			break;
		case WP_DYNAMITE:
		case WP_GRENADE_PINEAPPLE:
		case WP_GRENADE_LAUNCHER:
		case WP_SATCHEL:
		case WP_SMOKE_BOMB:
			VectorMA(eth.muzzle, 20, right, eth.muzzle);
			break;
		case WP_AKIMBO_COLT:
		case WP_NQ_AKIMBO_COLT:
		case WP_AKIMBO_SILENCEDCOLT:
		case WP_NQ_AKIMBO_SILENCEDCOLT:
		case WP_AKIMBO_LUGER:
		case WP_NQ_AKIMBO_LUGER:
		case WP_AKIMBO_SILENCEDLUGER:
		case WP_NQ_AKIMBO_SILENCEDLUGER:
			VectorMA(eth.muzzle, -6, right, eth.muzzle);
			VectorMA(eth.muzzle, -4, up, eth.muzzle);
			break;
		default:
			VectorMA(eth.muzzle, 6, right, eth.muzzle);
			VectorMA(eth.muzzle, -4, up, eth.muzzle);
			break;
	}
	SnapVector(eth.muzzle);
}

/* for now this is only used to determine if weapon
   is an aimbot-capable weapon. If so, return mp40 */
int NQWeapon2BaseWeapon( int weaponIndex ) {
	int weapon = WP_NONE;

	if ( eth.mod->type != MOD_NQ ) return weaponIndex;

	switch ( weaponIndex ) {
		case WP_NQ_NONE:
			weapon =  WP_NONE;
			break;
			case WP_NQ_POISON_SYRINGE:            // NEW WEAPON
		case WP_NQ_KNIFE:
			weapon =  WP_KNIFE;
			break;
		case WP_NQ_LUGER:
			weapon =  WP_LUGER;
			break;
		case WP_NQ_STG44:                // NEW WEAPON
		case WP_NQ_MP40:
			weapon =  WP_MP40;
			break;
		case WP_NQ_GRENADE_LAUNCHER:
			weapon =  WP_GRENADE_LAUNCHER;
			break;
		case WP_NQ_BAZOOKA:                // NEW WEAPON
		case WP_NQ_PANZERFAUST:
			weapon =  WP_PANZERFAUST;
			break;
		case WP_NQ_FLAMETHROWER:
			weapon =  WP_FLAMETHROWER;
			break;
		case WP_NQ_COLT:
			weapon =  WP_COLT;
			break;
		case WP_NQ_BAR:                    // NEW WEAPON
		case WP_NQ_THOMPSON:
			weapon =  WP_THOMPSON;
			break;
		case WP_NQ_GRENADE_PINEAPPLE:
			weapon =  WP_GRENADE_PINEAPPLE;
			break;
		case WP_NQ_STEN_MKII:                // NEW WEAPON
		case WP_NQ_MP34:                // NEW WEAPON
			weapon =  WP_STEN;
			break;
		case WP_NQ_STEN:
			weapon =  WP_STEN;
			break;
		case WP_NQ_MEDIC_SYRINGE:
			weapon =  WP_MEDIC_SYRINGE;
			break;
		case WP_NQ_AMMO:
			weapon =  WP_AMMO;
			break;
		case WP_NQ_ARTY:
			weapon =  WP_ARTY;
			break;
		case WP_NQ_SILENCER:
			weapon =  WP_SILENCER;
			break;
		case WP_NQ_DYNAMITE:
			weapon =  WP_DYNAMITE;
			break;
		case WP_NQ_SMOKETRAIL:
			weapon =  WP_SMOKETRAIL;
			break;
		case WP_NQ_MEDKIT:
			weapon =  WP_MEDKIT;
			break;
		case WP_NQ_BINOCULARS:
			weapon =  WP_BINOCULARS;
			break;
		case WP_NQ_PLIERS:
			weapon =  WP_PLIERS;
			break;
		case WP_NQ_SMOKE_MARKER:
			weapon =  WP_SMOKE_MARKER;
			break;
		case WP_NQ_KAR98:
			weapon =  WP_KAR98;
			break;
		case WP_NQ_CARBINE:
			weapon =  WP_CARBINE;
			break;
		case WP_NQ_GARAND:
			weapon =  WP_GARAND;
			break;
		case WP_NQ_LANDMINE:
			weapon =  WP_LANDMINE;
			break;
		case WP_NQ_SATCHEL:
			weapon =  WP_SATCHEL;
			break;
		case WP_NQ_SATCHEL_DET:
			weapon =  WP_SATCHEL_DET;
			break;
		case WP_NQ_TRIPMINE:
			weapon =  WP_TRIPMINE;
			break;
		case WP_NQ_SMOKE_BOMB:
			weapon =  WP_SMOKE_BOMB;
			break;
		case WP_NQ_MOBILE_BROWNING:            // NEW WEAPON
			case WP_NQ_VENOM:                // NEW WEAPON
		case WP_NQ_MOBILE_MG42:
			weapon =  WP_MOBILE_MG42;
			break;
		case WP_NQ_K43:
			weapon =  WP_K43;
			break;
		case WP_NQ_FG42:
			weapon =  WP_FG42;
			break;
		case WP_NQ_DUMMY_MG42:
			weapon =  WP_DUMMY_MG42;
			break;
		case WP_NQ_MORTAR2:                // NEW WEAPON
		case WP_NQ_MORTAR:
			weapon =  WP_MORTAR;
			break;
		case WP_NQ_AKIMBO_COLT:
			weapon =  WP_AKIMBO_COLT;
			break;
		case WP_NQ_AKIMBO_LUGER:
			weapon =  WP_AKIMBO_LUGER;
			break;
		case WP_NQ_GPG40:
			weapon =  WP_GPG40;
			break;
		case WP_NQ_M7:
			weapon =  WP_M7;
			break;
		case WP_NQ_SILENCED_COLT:
			weapon =  WP_SILENCED_COLT;
			break;
		case WP_NQ_GARAND_SCOPE:
			weapon =  WP_GARAND_SCOPE;
			break;
		case WP_NQ_K43_SCOPE:
			weapon =  WP_K43_SCOPE;
			break;
		case WP_NQ_FG42_SCOPE:
			weapon =  WP_FG42SCOPE;
			break;
		case WP_NQ_MORTAR2_SET:                // NEW WEAPON
		case WP_NQ_MORTAR_SET:
			weapon =  WP_MORTAR_SET;
			break;
		case WP_NQ_MEDIC_ADRENALINE:
			weapon =  WP_MEDIC_ADRENALINE;
			break;
		case WP_NQ_AKIMBO_SILENCEDCOLT:
			weapon =  WP_AKIMBO_SILENCEDCOLT;
			break;
		case WP_NQ_AKIMBO_SILENCEDLUGER:
			weapon =  WP_AKIMBO_SILENCEDLUGER;
			break;
		case WP_NQ_MOBILE_BROWNING_SET:            // NEW WEAPON
		case WP_NQ_BAR_SET:                // NEW WEAPON
		case WP_NQ_MOBILE_MG42_SET:
			weapon =  WP_MOBILE_MG42_SET;
			break;
		case WP_NQ_SHOTGUN:                // NEW WEAPON
		case WP_NQ_KNIFE_KABAR:        // NEW WEAPON
			weapon =  WP_KNIFE;
			break;
		case WP_NQ_FIREBOLT:                // NEW WEAPON
			weapon =  WP_MP40;
			break;
		default:
			break;
	}

	return weapon;
}

int JmodWeapon2BaseWeapon( int weaponIndex ) {
	int weapon = WP_NONE;

	if ( eth.mod->type != MOD_JMOD ) return weaponIndex;
	if( weaponIndex <= WP_MOBILE_MG42_SET )
		return weaponIndex;

	switch( weaponIndex ){
		case WP_JM_POISON_SYRINGE:
			break;
		case WP_JM_UNKNOW_WEAPON:
			break;
		case WP_JM_M97:
			break;
		case WP_JM_POISON_GAS:
			break;
		case WP_JM_LANDMINE_BOUNCING_BETTY:
			break;
		case WP_JM_LANDMINE_POISON_GAS:
			break;
		case WP_JM_NUM_WEAPONS:
			weapon = WP_NUM_WEAPONS;
			break;
		default:
			break;
	}


#ifdef ETH_DEBUG
	ethLog( "NQWeapon2BaseWeapon: %d -> %d\n", weaponIndex, weapon );
#endif

	return weapon;
}

// test ETnam Weapons
int ETnamWeapon2BaseWeapon( int weaponIndex ) {
	int weapon = WP_NONE;

	if ( eth.mod->type != MOD_ETNAM ) return weaponIndex;

	switch ( weaponIndex ) {
		case WP_ETNAM_NONE:
			weapon =  WP_NONE;
			break;
		case WP_ETNAM_KNIFE:
			weapon =  WP_KNIFE;
			break;
		case WP_ETNAM_LUGER:
			weapon =  WP_LUGER;
			break;
		case WP_ETNAM_AK47:
			weapon =  WP_MP40;
			break;
		case WP_ETNAM_REVOLVER:
			weapon =  WP_COLT;
			break;
		case WP_ETNAM_M16:
			weapon =  WP_THOMPSON;
			break;
		case WP_ETNAM_STEN:
			weapon =  WP_STEN;
			break;
		case WP_ETNAM_MEDIC_SYRINGE:
			weapon =  WP_MEDIC_SYRINGE;
			break;
		case WP_ETNAM_AMMO:
			weapon =  WP_AMMO;
			break;
		case WP_ETNAM_ARTY:
			weapon =  WP_ARTY;
			break;
		case WP_ETNAM_C4:
			weapon =  WP_DYNAMITE;
			break;
		case WP_ETNAM_MEDKIT:
			weapon =  WP_MEDKIT;
			break;
		case WP_ETNAM_BINOCULARS:
			weapon =  WP_BINOCULARS;
			break;
		case WP_ETNAM_PLIERS:
			weapon =  WP_PLIERS;
			break;
		case WP_ETNAM_SMOKE_MARKER:
			weapon =  WP_SMOKE_MARKER;
			break;
		case WP_ETNAM_CARBINE:
			weapon =  WP_CARBINE;
			break;
		case WP_ETNAM_LANDMINE:
			weapon =  WP_LANDMINE;
			break;
		case WP_ETNAM_SATCHEL:
			weapon =  WP_SATCHEL;
			break;
		case WP_ETNAM_SATCHEL_DET:
			weapon =  WP_SATCHEL_DET;
			break;
		case WP_ETNAM_TRIPMINE:
			weapon =  WP_TRIPMINE;
			break;
		case WP_ETNAM_SMOKE_BOMB:
			weapon =  WP_SMOKE_BOMB;
			break;
		case WP_ETNAM_SNIPER_M16:
			weapon =  WP_FG42;
			break;
		case WP_ETNAM_DUMMY_M16:
			weapon =  WP_DUMMY_MG42;
			break;
		case WP_ETNAM_MORTAR:
			weapon =  WP_MORTAR;
			break;
		case WP_ETNAM_AKIMBO_COLT:
			weapon =  WP_AKIMBO_COLT;
			break;
		case WP_ETNAM_AKIMBO_LUGER:
			weapon =  WP_AKIMBO_LUGER;
			break;
		case WP_ETNAM_GARAND_SCOPE:
			weapon =  WP_GARAND_SCOPE;
			break;
		case WP_ETNAM_K43_SCOPE:
			weapon =  WP_K43_SCOPE;
			break;
		case WP_ETNAM_SNIPER_M16_SCOPE:
			weapon =  WP_FG42SCOPE;
			break;
		case WP_ETNAM_MORTAR_SET:
			weapon =  WP_MORTAR_SET;
			break;
		default:
			break;
	}

	return weapon;
}

qboolean isAimbotWeapon(int weapon){
	switch( weapon ){
		case WP_LUGER:
		case WP_MP40:
		case WP_GRENADE_LAUNCHER:
		case WP_PANZERFAUST:
		case WP_COLT:
		case WP_THOMPSON:
		case WP_GRENADE_PINEAPPLE:
		case WP_STEN:
		case WP_SILENCER:
		case WP_KAR98:
		case WP_CARBINE:
		case WP_GARAND:
		case WP_MOBILE_MG42:
		case WP_K43:
		case WP_FG42:
		case WP_DUMMY_MG42:
		case WP_AKIMBO_COLT:
		case WP_AKIMBO_LUGER:
		case WP_SILENCED_COLT:
		case WP_GARAND_SCOPE:
		case WP_K43_SCOPE:
		case WP_FG42SCOPE:
		case WP_AKIMBO_SILENCEDCOLT:
		case WP_AKIMBO_SILENCEDLUGER:
		case WP_MOBILE_MG42_SET:
			return qtrue;
		default:
			return qfalse;
	}
	return qfalse;
}

int playerWeapon( int player ) {
	int weapon = eth.cg_entities[player].currentState->weapon;
	if( eth.mod->type == MOD_NQ )
		weapon = NQWeapon2BaseWeapon( weapon );
	else if( eth.mod->type == MOD_JMOD )
		weapon = JmodWeapon2BaseWeapon( weapon );
	else if( eth.mod->type == MOD_ETNAM )
		weapon = ETnamWeapon2BaseWeapon( weapon );
	return weapon; 
}

/*
==============================
 Config stuff
==============================
*/

char *getConfigFilename() {
	// If config filename is set by enviromment var
	if (getenv("EThax_CONF_FILE"))
		return getenv("EThax_CONF_FILE");
	
	static char filename[PATH_MAX];
	snprintf(filename, sizeof(filename), "%s/%s", getenv("HOME"), ETH_CONFIG_FILE);
	return filename;
}

void readConfig() {
	FILE *file;
	// Init all user vars with the default value
	int count = 0;
	for (; count < VARS_TOTAL; count++)
		seth.value[count] = seth.vars[count].defaultValue;

	if ((file = fopen(getConfigFilename(), "rb")) == NULL)
		return;

	// Get config file line by line
	char line[1024];
	while (fgets(line, sizeof(line) - 1, file) != 0) {
		char *sep = strrchr(line, '=');
		*sep = '\0';	// Separate name from value

		if( !sep )
			fatalError("Config error. Check your config file!");
		// Search this var
		int count = 0;
		if( !strcmp(line,"bnFormat") ) {
			strncpy(bnFormat, Q_ValidStr(sep+1), sizeof(ksFormat));
		} else {
			for (; count < VARS_TOTAL; count++) {
				if (!seth.vars[count].cvarName) {
					ethLog("readConfig: error: VAR_%i undefine", count);
				} else if (!strcmp(line, seth.vars[count].cvarName)) {
					seth.value[count] = atof(sep + 1);
					break;
				} else if ((count + 1) == VARS_TOTAL) {
					ethLog("readConfig: don't know this var: [%s]", line);
				}
				if (count == VAR_CHUD)
					if (atoi(sep + 1))
						syscall_CG_SendConsoleCommand(va("cg_draw2d %s\n", seth.value[count] ? "0" : "1"));
			}
		}
	}

	fclose(file);

}

void writeConfig() {
	FILE *file;
	
	if ((file = fopen(getConfigFilename(), "w")) == NULL) {
		ethLog("EThax: can't write config file.");
		return;
	}
	
	int count = 0;
	fprintf(file,"ksFormat=%s\n",ksFormat);
	fprintf(file,"bnFormat=%s\n",bnFormat);
	for (; count < VARS_TOTAL; count++) {
		if (!seth.vars[count].cvarName)
			ethLog("writeConfig: error: VAR_%i undefine", count);
		else if (seth.value[count] == (float)(int)seth.value[count])
			fprintf(file, "%s=%i\n", seth.vars[count].cvarName, (int)seth.value[count]);
		else
			fprintf(file, "%s=%.2f\n", seth.vars[count].cvarName, seth.value[count]);
	}

	fclose(file);
}

/*
==============================
 Console actions
==============================
*/

void initActions() {
	eth.actions[ACTION_ATTACK]		= (ethAction_t){ 0, 0, "+attack\n",				"-attack\n" };
	eth.actions[ACTION_BACKWARD]	= (ethAction_t){ 0, 0, "+backward\n",			"-backward\n" };
	eth.actions[ACTION_BINDMOUSE1]	= (ethAction_t){ 1, 1, "bind mouse1 +attack\n",	"unbind mouse1\n" };
	eth.actions[ACTION_CROUCH]		= (ethAction_t){ 0, 0, "+movedown\n",			"-movedown\n" };
	eth.actions[ACTION_JUMP]		= (ethAction_t){ 0, 0, "+moveup\n",				"-moveup\n" };
	eth.actions[ACTION_PRONE]		= (ethAction_t){ 0, 0, "+prone; -prone\n",		"+moveup; -moveup\n" };
	eth.actions[ACTION_RUN]			= (ethAction_t){ 0, 0, "+forward\n",	"-forward\n" };
	eth.actions[ACTION_SCOREBOARD]	= (ethAction_t){ 0, 0, "cg_draw2d 1; +scores\n", "-scores; cg_draw2d 0\n" };
	eth.actions[ACTION_RELOAD]		= (ethAction_t){ 0, 0, "+reload\n",	"-reload\n" };
	eth.actions[ACTION_SPRINT]		= (ethAction_t){ 1, 1, "+sprint;\n", 	"-sprint\n" };
}

// Set an action if not already set.
void setAction(int action, int state) {
	if (state && !eth.actions[action].state)
		forceAction(action, state);
	else if (!state && eth.actions[action].state)
		forceAction(action, state);
}

// Use this with caution
void forceAction(int action, int state) {
	if (state) {
		eth.actions[action].state = 1;
		syscall_CG_SendConsoleCommand(eth.actions[action].startAction);
		#ifdef ETH_DEBUG
			ethDebug("forceAction: %s", eth.actions[action].startAction);
		#endif
	} else {
		eth.actions[action].state = 0;
		syscall_CG_SendConsoleCommand(eth.actions[action].stopAction);
		#ifdef ETH_DEBUG
			ethDebug("forceAction: %s", eth.actions[action].stopAction);
		#endif
	}
}

void resetAllActions() {
	int action;
	for (action=0; action<ACTIONS_TOTAL; action++)
		if (action != ACTION_SCOREBOARD)
			forceAction(action, eth.actions[action].defaultState);
}

/*
==============================
 Killing spree/stats/sound stuff
==============================
*/

// Spree sound
void playSpreeSound() {
	if( !seth.value[VAR_SPREE_SOUNDS] )
		return;
	
	if ((eth.cg_time - eth.lastKillTime) < (SPREE_TIME * 8000)) {
		// Define spree levels range - TODO: Dirty. find a better way to play with level range
		typedef struct { int start; int end; } spreeLevel_t;
		#define SPREE_LEVEL_SIZE 4
		spreeLevel_t spreeLevels[SPREE_LEVEL_SIZE] = {
			{ SOUND_DOUBLEKILL1,	SOUND_PERFECT }	,	// Spree level 1
			{ SOUND_GODLIKE1,		SOUND_TRIPLEKILL },
			{ SOUND_DOMINATING1,	SOUND_ULTRAKILL3 },
			{ SOUND_MONSTERKILL1,	SOUND_WICKEDSICK }	// Spree level 4
		};
		int spreeLevelMax = SPREE_LEVEL_SIZE - 1;

		// Modify level+sound values to fit to spreeLevels_t and eth.sounds order
		int level = eth.killSpreeCount - 2; // never '< 0' because first time here is with 2 kills
		if (level > spreeLevelMax)
			level = spreeLevelMax;
		int levelSize = spreeLevels[level].end - spreeLevels[level].start;
		int sound = (int)((float)(levelSize + 1) * rand() / (RAND_MAX + 1.0f));
		sound += spreeLevels[level].start;
		eth.spreelevel = sound;
		eth.startFadeTime = eth.cg_time;
		eth.s_level = level;
		orig_syscall(CG_S_STARTLOCALSOUND, eth.sounds[sound], CHAN_LOCAL_SOUND, 230);
	}
}

/* replaces tokens with correct value and returns pointer parsed string
	[c] - current spree count
	[v] - victim name
	[n] - clean victim name
	[t] - total kills
	[m] - double/triple/multikill msg
	[x]	- Player XP
	[p] - Player name
	[M] - Mod name
	[h] - Player health
	[k] - Killer name
	[K] - Clean killer name
	[q] - amount of punkbuster screenshots requested
*/
char *Format(char *in){
	char out[256];
	memset(out, 0, sizeof(out));
	
	int a, b, len = strlen(in);
	for (a = 0, b = 0; a < len; a++) {
		if ((a <= len-2) && (in[a] == '[' && in[a+2] == ']')) {
			switch (in[a+1]) {
					case '1': {
						char *multikillmsg ;
						if (eth.killSpreeCount == 2) {
								multikillmsg = " ^1*** DOUBLEKILL***^7";
						}
						else if (eth.killSpreeCount == 3) {
							
								multikillmsg = " ^1*** MULTIKILL***^7";
						}
						else if (eth.killSpreeCount == 4) {
								multikillmsg = " ^1*** ULTRAKILL***^7";
						}
						else if (eth.killSpreeCount == 5) {
								multikillmsg = " ^1*** MONSTERKILL***^7";
						}
						else if (eth.killSpreeCount > 5) {
								multikillmsg = " ^1*** HOLY SHIT***^7";
						}
						else
					break;
					}
				default:
					break;
			}
			a += 2;
		}
		else
			out[b] = in[a];
		b = strlen(out);
	}
	strncpy(in,out,sizeof(out));
	return in;
}

//tes: once per command call
int isCommandTime(void) {
	static int lastTimeC;
	
	if(seth.value[VAR_SNAPDELAY] != 0) {
	    if(lastTimeC + (int)seth.value[VAR_SNAPDELAY] > (eth.cg_time )) 
		return 0;
	
	    lastTimeC = eth.cg_time;
	    return 1;
	} 
	// tes: so if set to 0 then we do it like this:
	// count time delay for max commands we can send between snapshots 
	// this is strictly ping based and seems to be solution i search for :)
	
	
	if((lastTimeC + (eth.cg_snap->ping/(CMD_BACKUP -1))) <= (eth.cg_time)){
	    lastTimeC = eth.cg_time;
	    return 1;
	}
	    return 0;
    
}

void timenudge(int nTime) {
	char send[256];
	snprintf(send, sizeof(send), "cl_timenudge %d\n", nTime);
	syscall_CG_SendConsoleCommand(send);
}

/*
==============================
et guid
==============================
*/

// Init cl_guid by environnement var
void loadCL_GUID(void) {
	char *cl_guid = getenv("CLGUID");
	if (cl_guid) {
		syscall_CG_Cvar_Set("cl_guid", cl_guid);
		// Delete env var so cl_guid is set once, and not each cg_init
		unsetenv("CLGUID");
	}
}
