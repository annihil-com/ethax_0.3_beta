// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

/*
==============================
 Game commands
==============================
*/

#include "ethax.h"
#include "names.h"


void saveCommand (void) {
	if (syscall_UI_Argc() == 1)
		orig_syscall(UI_PRINT, "^nSave config to a file\n");

	if ((syscall_UI_Argc() == 1) || (syscall_UI_Argc() > 2)) {
		orig_syscall(UI_PRINT, "^nUsage: EThax_save config_name\n");
		return;
	}
	
	if (syscall_UI_Argc() == 2) {
		char path[128 + 16];
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/%s", getenv("HOME"), syscall_UI_Argv(1));

		FILE *file;
		
		if ((file = fopen(path, "w")) == NULL) {
			orig_syscall(UI_PRINT, "^nCan't write config file.\n");
			ethLog("EThax: can't write config file.");
			return;
		}
		
		int count = 0;
		for (; count < VARS_TOTAL; count++) {
			if (seth.value[count] == (float)(int)seth.value[count])
				fprintf(file, "%s=%i\n", seth.vars[count].cvarName, (int)seth.value[count]);
			else
				fprintf(file, "%s=%.2f\n", seth.vars[count].cvarName, seth.value[count]);
		}

		char done[512];
		snprintf(done, sizeof(done), "^nConfig '%s' saved.\n", path);

		orig_syscall(UI_PRINT, done);
	
		fclose(file);
	}
}

void loadCommand (void) {
	if (syscall_UI_Argc() == 1)
		orig_syscall(UI_PRINT, "^nLoad settings from a config file\n");

	if ((syscall_UI_Argc() == 1) || (syscall_UI_Argc() > 2)) {
		orig_syscall(UI_PRINT, "^nUsage: EThax_load config_name\n");
		return;
	}
	
	if (syscall_UI_Argc() == 2) {
		FILE *file;
	
		char path[128 + 16];
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/%s", getenv("HOME"), syscall_UI_Argv(1));
	
		if ((file = fopen(path, "rb")) == NULL) {
			orig_syscall(UI_PRINT, "^nCan't read config file.\n");
			return;
		}
	
		// Get config file line by line
		char line[32];
		while (fgets(line, sizeof(line) - 1, file) != 0) {
			char *sep = strrchr(line, '=');
			*sep = '\0';	// Separate name from value
			// Search this var
			int count = 0;
			for (; count < VARS_TOTAL; count++) {
				if (strcmp(line, seth.vars[count].cvarName) == 0) {
					seth.value[count] = atof(sep + 1);
					break;
				} else if ((count + 1) == VARS_TOTAL) {
					ethLog("readConfig: don't know this var: [%s]", line);
				}
			}
		}

		char done[512];
		snprintf(done, sizeof(done), "^nConfig '%s' loaded.\n", path);

		orig_syscall(UI_PRINT, done);
	
		fclose(file);
	}
}


/*
void goHome() {
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "connect IP ADRESS\n");
}*/

void HumanModeCfg() {
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "EThax_load human.cfg\n");
}

void HumanModeCfg2() {
	orig_syscall(UI_CMD_EXECUTETEXT, EXEC_APPEND, "EThax_load human2.cfg\n");
}


void setValueCommand() {
	char msg[MAX_STRING_CHARS];
	const char *var;
	int p[VARS_TOTAL];
	qboolean found;
	int i,match,k;
	match = found = k = 0;
	if(!eth.hookLoad){
		orig_syscall(UI_PRINT,"^nEThax vars not yet initialized, connect to a server first!\n");
		return;
	}

	if (syscall_UI_Argc() == 1){
		orig_syscall(UI_PRINT, "^nUsage " ETH_CMD_PREFIX "set [var] [value]\n");
		return;
	}

	if (syscall_UI_Argc() >= 2) {
		var = syscall_UI_Argv(1);
		memset(p,-1,sizeof(p));
		for(i=0;i<VARS_TOTAL;i++){
			if( !seth.vars[i].cvarName )
				continue;
			if( strstr( seth.vars[i].cvarName, var ) ){
				p[k++] = i;
				found = qtrue;
				if( !strcmp( var, seth.vars[i].cvarName ) )
					match = i;
			}
		}
	
		if(!found){
			snprintf(msg,sizeof(msg),"^nNo cvars found matching ^2%s\n",var);
			orig_syscall(UI_PRINT, msg);
			return;
		}
		if( syscall_UI_Argc() == 2 ) {
			for(k=0;k<VARS_TOTAL;k++){
				if( p[k] < 0 )
					continue;
				snprintf(msg,sizeof(msg),"^f%s ^nhas value ^2%f\n", seth.vars[p[k]].cvarName, seth.value[p[k]]);
				orig_syscall(UI_PRINT, msg);
			}
		}
	}

	if (syscall_UI_Argc() == 3) {
		if(k > 1 && !match ){
			orig_syscall(UI_PRINT, "^nWarning: more than than 1 cvars match query, aborting\n");
			return;
		}
		if( match )
			p[0]=match;
		
		seth.value[p[0]] = atof(syscall_UI_Argv(2));
		snprintf(msg,sizeof(msg),"^nnew value: ^f%s = ^2%f\n", seth.vars[p[0]].cvarName, seth.value[p[0]]);
		orig_syscall(UI_PRINT, msg);
	}
}




void registerGameCommands() {
	orig_Cmd_AddCommand(ETH_CMD_PREFIX "save", &saveCommand);
	orig_Cmd_AddCommand(ETH_CMD_PREFIX "load", &loadCommand);
//	orig_Cmd_AddCommand(ETH_CMD_PREFIX "home", &goHome);
	orig_Cmd_AddCommand(ETH_CMD_PREFIX "set", &setValueCommand);
	orig_Cmd_AddCommand(ETH_CMD_PREFIX "HumanCfg", &HumanModeCfg);
	orig_Cmd_AddCommand(ETH_CMD_PREFIX "Human2Cfg", &HumanModeCfg2);


}
