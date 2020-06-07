// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

#include "ethax.h"

// Categories text definitions
menuCat_t menuCats[] = {
	#ifdef ETH_PRIVATE
		PRIVATE_CATS_NAME
	#endif
	{ CAT_VERSION,	".:.EThax Private Version.:." },
	{ CAT_STYLE,	"[->)MENU SETTINGS(]" },
	{ CAT_AIMBOTM,	"[->)EThax AIM MAIN(]" },
	{ CAT_AIMBOTP,	"[->)EThax AIM MIX(]" },
	{ CAT_HITBOX,	"[->)CUSTOM HITBOX(]" },
	{ CAT_AIMBOTE,	"[->)EThax EXTRA(]" },
	{ CAT_HUMAN,	"[->)HUMAN AIM(]" },
	{ CAT_HUMANE,	"[->)HUMAN AIM EXTRA(]" },
	{ CAT_RIFLE,	"[->)RIFLE BOT(]" },
	{ CAT_VISUAL,	"[->)VISUAL(]" },
	{ CAT_ESP,	"[->)ALL ESP(]" },
	{ CAT_SPYCAM,	"[->)SPY CAMS(]" },
	{ CAT_MISC,	"[->)MISC(]" },
	{ CAT_HUD,	"[->)HUD SKINS(]" },
	{ CAT_HUD2,	"[->)HUD SKINS II(]" },
	{ CAT_SOUND,	"[->)SOUND(]" },
	#ifdef ETH_DEBUG
	{ CAT_DEBUG,	"->> DEBUG <<-" }
	#endif
};

void initUserVars() {

	// Stle settings

	seth.vars[VAR_STYLEDMENU] = (ethVars_t) { "Styled Menu", qtrue, "styledmenu", CAT_STYLE, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_MENUCOLORS] = (ethVars_t) { "Menu Colors", MENU_CYAN, "menucolors", CAT_STYLE, qfalse,
		{ { "Red", MENU_RED }, { "Yellow", MENU_YELLOW }, { "Light Blue", MENU_CYAN }, { "Blue", MENU_BLUE }, { "White", MENU_WHITE }, { "Black", MENU_BLACK } } };
	seth.vars[VAR_STEP] = (ethVars_t) { "Step Value", 100.0f , "step", CAT_STYLE, qfalse,
		{ { "100.0", 100.0f },{ "10.0", 10.0f }, { "1.0", 1.0f }, { "0.1", 0.1f }, { "0.01", 0.01f } } };
	seth.vars[VAR_VISUALS] = (ethVars_t) { "Hacks Visual", qtrue, "visuals", CAT_STYLE, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_ADVERT] = (ethVars_t) { "Advert", qfalse, "advert", CAT_STYLE, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_RADAR] = (ethVars_t) { "Radar", qfalse, "radar", CAT_STYLE, qfalse,
		{ { "Off", qfalse }, { "Huge", 1 }, { "Big", 2 }, { "Medium", 3 }, { "Small", 4 }, { "Big 2", 5 }, { "Medium2", 6 }, { "Small2", 7 } } };

	// Aimbot 

	seth.vars[VAR_AIMFOV] = (ethVars_t) { "Aim Fov", 6.0f, "aimfov", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_AIM_AUTO] = (ethVars_t) { "Autoaim", qfalse, "aimauto", CAT_AIMBOTM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_AUTOSHOOT] = (ethVars_t) { "Autofire", AUTOSHOOT_OFF, "autoshoot", CAT_AIMBOTM, qfalse,
		{ { "Off", AUTOSHOOT_OFF }, { "Left Button", AUTOSHOOT_LBUTTON }, { "On", AUTOSHOOT_ON } } };
	seth.vars[VAR_AUTOSHOOT_TYPE] = (ethVars_t) { "Autofire Type", AUTOSHOOT_TYPE_TRIGGER, "autoshoot_type", CAT_AIMBOTM, qfalse,
		{ { "Enemy Visible", AUTOSHOOT_TYPE_VISIBLE }, { "Trigger", AUTOSHOOT_TYPE_TRIGGER } } };
	seth.vars[VAR_LOCKTARGET] = (ethVars_t) { "Target Lock", qtrue, "Locktarget", CAT_AIMBOTM, qfalse,
        	{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_AIM_PRIO] = (ethVars_t) { "Aim Priority", AIM_PRIO_HEAD_BODY, "aimprio", CAT_AIMBOTM, qfalse,
		{ { "Off", AIM_PRIO_OFF }, { "Head", AIM_PRIO_HEAD }, { "Head-Body" , AIM_PRIO_HEAD_BODY }, { "Head Only" , AIM_PRIO_HEAD_ONLY }, { "Body Only" , AIM_PRIO_BODY_ONLY } } };
	seth.vars[VAR_TARGET_PRIO] = (ethVars_t) { "Target Priority", TARGET_CROSSHAIR, "targetprio", CAT_AIMBOTM, qfalse,
        { { "Nearest", TARGET_NEAREST }, { "Crosshair", TARGET_CROSSHAIR }, { "Attackher", TARGET_ATTACKER }, { "Selected Persons" , TARGET_PERSON } } };
	seth.vars[VAR_HITBOX] = (ethVars_t) { "HitBox", HITBOX_ETPRO, "hitbox", CAT_AIMBOTM, qfalse,
		{ { "Off", HITBOX_OFF }, { "Etmain", HITBOX_ETMAIN }, { "Etpub", HITBOX_ETPUB }, { "ETpr0", HITBOX_ETPRO }, { "Generic", HITBOX_GENERIC }, { "Custom Boxes", HITBOX_CUSTOM } } };
	seth.vars[VAR_BOXADD] = (ethVars_t) { "Box Expand", 5.0f, "boxexpand", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_VECZ] = (ethVars_t) { "All weapons vecZ", 2.5f, "vecz", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_VECZ_STEN] = (ethVars_t) { "Sten vecZ", 3.5f, "vecz_sten", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_VECZ_SCOPE] = (ethVars_t) { "Scooped Weapons vecZ", 4.0f, "vecz_scope", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_AIMVECZ_TYPE] = (ethVars_t) { "VecZ Type", VECZ_HITBOX, "vecztype", CAT_AIMBOTM, qfalse,
		{ { "Auto vecZ", VECZ_AUTO }, { "Manual vecZ", VECZ_MANUAL } , { "HitBox", VECZ_HITBOX } } };
	seth.vars[VAR_PREDICT_VALUE] = (ethVars_t) { "predict value", -0.03f, "newpred", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_AIMPREDICT] = (ethVars_t) { "Enemy prediction type", AIMPREDICT_AUTO_2, "epredict", CAT_AIMBOTM, qfalse,
		{ { "Off", AIMPREDICT_OFF }, { "Auto 1", AIMPREDICT_AUTO_1 }, { "Auto 2", AIMPREDICT_AUTO_2 }, { "Ping based", AIMPREDICT_AUTO_3 }, { "Acceleration / speed based", AIMPREDICT_AUTO_4 }, { "Unseen's pred", AIMPREDICT_UNSEEN }, { "SnapShot", AIMPREDICT_SNAPSHOT } } };
	seth.vars[VAR_PRED_C] = (ethVars_t) { "Pred correction", -150.0f, "pcor", CAT_AIMBOTM, qfalse,
		{} };
	seth.vars[VAR_SELFPREDICT] = (ethVars_t) { "Self Predict", qtrue, "spredict", CAT_AIMBOTM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };


	// Aimbot misc

	seth.vars[VAR_AUTO_CROUCH] = (ethVars_t) { "Auto crouch", qfalse, "auto_crouch", CAT_AIMBOTP, qfalse,
         { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SNIPERDELAY] = (ethVars_t) { "Snyper Delay", 700, "sniperdelay", CAT_AIMBOTP, qfalse,
		{} };
    seth.vars[VAR_SNAPDELAY] = (ethVars_t) { "Snap Delay", 1 ,"snapdelay", CAT_AIMBOTP, qfalse, 
		{} };
	seth.vars[VAR_OVERHEAT] = (ethVars_t) { "Anti Weapon Overheat", qtrue, "overheat", CAT_AIMBOTP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_RECOIL] = (ethVars_t) { "Recoil & Feedback", 0, "recoil", CAT_AIMBOTP, qfalse,
		{ { "Off", 0 }, { "On (detour)", 1 }, { "On (Entity event)", 2 } } };
	seth.vars[VAR_AIM_DEAD] = (ethVars_t) { "Aim at Dead Players", qfalse, "aimdead", CAT_AIMBOTP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SATCHEL_AUTOSHOOT] = (ethVars_t) { "Satchel AutoShoot", qfalse, "satchel_autoshoot", CAT_AIMBOTP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_INTERPOLATE] = (ethVars_t) { "Interpolate", qtrue, "interpolate", CAT_AIMBOTP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_NUDGEHACK] = (ethVars_t) { "Nudge Hax", -5.0f, "nudgehax", CAT_AIMBOTP, qfalse,
		{} };

	// custom Hitbox
	// elite: Hitbox Vecs
	seth.vars[VAR_CUSTOM_HITBOX_STAND_X] = (ethVars_t) { "Stand vecX", 0.0f, "vecX_stand", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_STAND_Y] = (ethVars_t) { "Stand vecY", 0.0f, "vecY_stand", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_STAND_Z] = (ethVars_t) { "Stand vecZ", 5.0f, "vecZ_stand", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_PRONE_X] = (ethVars_t) { "Prone vecX", 0.0f, "vecX_Prone", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_PRONE_Y] = (ethVars_t) { "Prone vecY", 0.0f, "vecY_Prone", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_PRONE_Z] = (ethVars_t) { "Prone vecZ", 5.0f, "vecZ_Prone", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_CROUCH_X] = (ethVars_t) { "Crouch vecX", 0.0f, "vecX_Crouch", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_CROUCH_Y] = (ethVars_t) { "Crouch vecY", 0.0f, "vecY_Crouch", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_CROUCH_Z] = (ethVars_t) { "Crouch vecZ", 5.0f, "vecZ_Crouch", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_CROUCH_MOVING_X] = (ethVars_t) { "Crouch Move vecX", 0.0f, "vecX_Crouch_Moving", CAT_HITBOX, qfalse,
		{} };	
	seth.vars[VAR_CUSTOM_HITBOX_CROUCH_MOVING_Y] = (ethVars_t) { "Crouch Move vecY", 0.0f, "vecY_Crouch_Moving", CAT_HITBOX, qfalse,
		{} };	
	seth.vars[VAR_CUSTOM_HITBOX_CROUCH_MOVING_Z] = (ethVars_t) { "Crouch Move vecZ", 5.0f, "vecZ_Crouch_Moving", CAT_HITBOX, qfalse,
		{} };	
	seth.vars[VAR_CUSTOM_HITBOX_STAND_MOVING_X] = (ethVars_t) { "Stand Move vecX", 0.0f, "vecX_Stand_Moving", CAT_HITBOX, qfalse,
		{} };	
	seth.vars[VAR_CUSTOM_HITBOX_STAND_MOVING_Y] = (ethVars_t) { "Stand Move vecY", 0.0f, "vecY_Stand_Moving", CAT_HITBOX, qfalse,
		{} };	
	seth.vars[VAR_CUSTOM_HITBOX_STAND_MOVING_Z] = (ethVars_t) { "Stand Move vecZ", 5.0f, "vecZ_Stand_Moving", CAT_HITBOX, qfalse,
		{} };	
	seth.vars[VAR_CUSTOM_HITBOX_BOXSIZE_X] = (ethVars_t) { "Box_X Size", 12.0f, "hitboxsize_x", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_BOXSIZE_Y] = (ethVars_t) { "Box_Y Size", 12.0f, "hitboxsize_y", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_BOXSIZE_Z] = (ethVars_t) { "Box_Z Size", 12.0f, "hitboxsize_z", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_B_BOXSIZE_X] = (ethVars_t) { "body Box_X Size", 36.0f, "bhitboxsize_x", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_B_BOXSIZE_Y] = (ethVars_t) { "body Box_Y Size", 36.0f, "bhitboxsize_y", CAT_HITBOX, qfalse,
		{} };
	seth.vars[VAR_CUSTOM_HITBOX_B_BOXSIZE_Z] = (ethVars_t) { "body Box_Z Size", 72.0f, "bhitboxsize_z", CAT_HITBOX, qfalse,
		{} };


	// EThax Extra

	seth.vars[VAR_NEW_HITBOX_CORRECTION] = (ethVars_t) { "Hitbox Correction", qfalse, "newHitboxCorrection", CAT_AIMBOTE, qfalse,
         { { "Off", qfalse }, { "On", qtrue } } };
   	seth.vars[VAR_BUNNY_JUMP] = (ethVars_t) { "Bunny Jump", qfalse, "bunny_jump", CAT_AIMBOTE, qfalse,
                { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_AUTO_SPRINT] = (ethVars_t) { "Auto Sprint", qfalse, "auto_sprint", CAT_AIMBOTE, qfalse,
         { { "Off", qfalse }, { "On", qtrue } } };
seth.vars[VAR_TRACE] = (ethVars_t) { "Trace Selector", qtrue, "trace", CAT_AIMBOTE, qfalse,
        	{ { "Off", qfalse }, { "On", qtrue } } };
    seth.vars[VAR_TRACE_SELECTOR] = (ethVars_t) { "Trace Style", TRACE_ANGLE, "trace_style", CAT_AIMBOTE, qfalse,
		{ { "Trace Distance", TRACE_DISTANCE }, { "Trace Free", TRACE_FREE }, { "Trace Angle", TRACE_ANGLE } } };
    seth.vars[VAR_TRACE_SELECTOR_ANGLE] = (ethVars_t) { "Trace Selector Angle", ANGLE_TRACE_RANDOM_SURFACE, "trace_selector_angle", CAT_AIMBOTE, qfalse,
		{ { "off", qfalse }, { "Trace Center", ANGLE_TRACE_CENTER }, { "Trace Random Volume", ANGLE_TRACE_RANDOM_VOLUME }, { "Trace Contour", ANGLE_TRACE_CONTOUR }, { "Random Surface", ANGLE_TRACE_RANDOM_SURFACE }, { "Trace Body", ANGLE_TRACE_BODY }, { "Trace Capsule Volume", ANGLE_TRACE_CAPSULE_VOLUME }, { "Trace Capsule Surface", ANGLE_TRACE_CAPSULE_SURFACE }, { "X Trace", ANGLE_TRACE_MULTI } } };

	// Human aimbot

	seth.vars[VAR_HUMAN] = (ethVars_t) { "Human Bot", qtrue, "human", CAT_HUMAN, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_HUMAN_MODE] = (ethVars_t) { "Human Mode", LIL_HUMAN_AIM, "humanmode", CAT_HUMAN, qfalse,
		{ { "LIL HUMAN", LIL_HUMAN_AIM }, { "LOGIN HUMAN", LOGIN_HUMAN_AIM }, { "FAST LOGIN", FAST_HUMAN_AIM }, { "AGGRESSIVE HUMAN", AGGRESSIVE_HUMAN_AIM } } };
	seth.vars[VAR_HUMANVALUE] = (ethVars_t) { "Human Skill", 0.15f, "humanvalue", CAT_HUMAN, qfalse,
		{ { "For simple human", 0.2f }, { "Low -", 0.10f }, { "Low", 0.15f }, { "Low +", 0.25f }, { "Med -", 0.35f },{ "Med", 0.45f }, { "Med +", 0.55f }, { "High", 0.65f } } };
	seth.vars[VAR_SHIFTON] = (ethVars_t) { "Shift On Fov", 6.0f, "shifton", CAT_HUMAN, qfalse,
		{ { "5.0", 5.0f }, { "6.0", 6.0f }, { "7.0", 7.0f }, { "8.0", 8.0f } } };
	seth.vars[VAR_SHIFTOFF] = (ethVars_t) { "Shift Off Fov", 1.0f, "shiftoff", CAT_HUMAN, qfalse,
		{ { "1.0", 1.0f }, { "2.0", 2.0f }, { "3.0", 3.0f }, { "4.0", 4.0f } } };
	seth.vars[VAR_BLOCK_MOUSE] = (ethVars_t) { "Block Mouse When Aiming", qfalse, "block_mouse", CAT_HUMAN, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };

	// Human Aimbot Extra
	seth.vars[VAR_DIVHUMAN] = (ethVars_t) { "Human Div", 2.5f, "divmax", CAT_HUMANE, qfalse,
		{ { "2.0", 2.0f }, { "2.5", 2.5f }, { "3.0", 3.0f }, { "4.0", 4.0f }, { "5.0", 5.0f } } };
	seth.vars[VAR_YSPEED] = (ethVars_t) { "Vertical Speed", 1.3f, "vspeed", CAT_HUMANE, qfalse,
		{ { "1.0", 1.0f }, { "1.3", 1.3f }, { "1.7", 1.7f }, { "2.0", 2.0f }, { "2.5", 2.5f }, { "3.0", 3.0f }, { "4.0", 4.0f } } };
	seth.vars[VAR_XSPEED] = (ethVars_t) { "Horizontal Speed", 1.2f, "hspeed", CAT_HUMANE, qfalse,
		{ { "1.0", 1.0f }, { "1.2", 1.2f }, { "1.4", 1.4f }, { "1.7", 1.7f }, { "2.0", 2.0f }, { "2.4", 2.4f }, { "3.0", 3.0f } } };
	seth.vars[VAR_RANDOM_AIM] = (ethVars_t) { "Random Aim" , qtrue, "randomaim", CAT_HUMANE, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SHAKE] = (ethVars_t) { "Shake Value", 588, "shakevalue", CAT_HUMANE, qfalse,
		{} };
	seth.vars[VAR_RANDOM_X] = (ethVars_t) { "Random X", 6, "xvalue", CAT_HUMANE, qfalse,
		{} };
	seth.vars[VAR_RANDOM_Y] = (ethVars_t) { "Random Y", 6, "yvalue", CAT_HUMANE, qfalse,
		{} };
	seth.vars[VAR_RANDOM_Z] = (ethVars_t) { "Random Z", 1.1, "zvalue", CAT_HUMANE, qfalse,
		{} };

	// Rifle Bot Test

	seth.vars[VAR_RIFFLE_AIM] = (ethVars_t) { "Riffle Bot", qfalse, "riffleaim", CAT_RIFLE, qfalse,
        	{ { "Off", qfalse }, { "on", qtrue } } };
	seth.vars[VAR_RIFFLE_SPEED] = (ethVars_t) { "Riffle speed", 2000, "rifflespeed", CAT_RIFLE, qfalse,
		{} };


	// Visual

	seth.vars[VAR_SNIPERHACK] = (ethVars_t) { "Sniperhack", qtrue, "sniperhack", CAT_VISUAL, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_BINOCSNIPERBLACK] = (ethVars_t) { "Binoc/Sniper Black", qtrue, "black", CAT_VISUAL, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_WEAPZOOM] = (ethVars_t) { "Remove weapons zoom", qtrue, "weapzoom", CAT_VISUAL, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SPAWNTIMER] = (ethVars_t) { "Enemy spawntimer", qtrue, "spawntimer", CAT_VISUAL, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SMOKE] = (ethVars_t) { "Smoke", SMOKE_TRANSPARENT, "smoke", CAT_VISUAL, qfalse,
		{ { "Leave normal", SMOKE_NORMAL }, { "Make transparent", SMOKE_TRANSPARENT }, { "Remove completely", SMOKE_REMOVE } } };
	seth.vars[VAR_CROSSHAIR] = (ethVars_t) { "Draw crosshair", XHAIR_TCE, "xhair", CAT_VISUAL, qfalse,
		{ { "Off", XHAIR_OFF }, { "TC:E only", XHAIR_TCE }, { "All mods", XHAIR_ALL } } };
	seth.vars[VAR_DRAW_WARN_MSG] = (ethVars_t) { "Warning MSG", qfalse, "warn_msg", CAT_VISUAL, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_DRAW_HEAD_MSG] = (ethVars_t) { "Head Visible MSG", qfalse, "head_msg", CAT_VISUAL, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_HEALTH_DETECTOR] = (ethVars_t) { "Health Detector", qfalse, "hp_detector", CAT_VISUAL, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };




	// Esp
	
	seth.vars[VAR_WALLHACK] = (ethVars_t) { "Wallhack", qfalse, "wallhack", CAT_ESP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_COLORS] = (ethVars_t) { "Colors", 0, "colors", CAT_ESP, 0,
		{ { "Type 1", 0 }, { "Type 2", 1 }, { "Type 3", 2 } } };
	seth.vars[VAR_ESPSIZE] = (ethVars_t) { "Size", ESP_SCALED, "esp_size", CAT_ESP, qfalse,
		{ { "Distance scaled", ESP_SCALED }, { "Static", ESP_STATIC } } };
	seth.vars[VAR_ESP_FADE] = (ethVars_t) { "Fade color", ESP_FADE_AUTO, "esp_fade", CAT_ESP, qfalse,
		{ { "Auto", ESP_FADE_AUTO }, { "Manual", ESP_FADE_MANUAL } } };
	seth.vars[VAR_ESP_FADE_VALUE] = (ethVars_t) { "Fade color", 70, "esp_fade_value", CAT_ESP, qfalse,
		{ { "30%", 30 }, { "40%", 40 }, { "50%", 50 }, { "60%", 60 }, { "70%", 70 }, { "80%", 80 }, { "90%", 90 }, { "100%", 100 } } };
	seth.vars[VAR_ESP_DIST] = (ethVars_t) { "Distance", 0, "esp_dist", CAT_ESP, qfalse,
		{ { "Unlimited", 0 }, { "500", 500 }, { "750", 750 }, { "1000", 1000 }, { "1250", 1250 }, { "1500", 1500 }, { "1750", 1750 }, { "2000", 2000 }, { "2500", 2500 }, { "3000", 3000 }, { "5000", 5000 } } };
	seth.vars[VAR_ESPNAME] = (ethVars_t) { "Player names", NAMES_ENEMY, "espname", CAT_ESP, qfalse,
		{ { "Off", qfalse }, { "Everyone", NAMES_EVERYBODY }, { "Enemy", NAMES_ENEMY }, { "Team", NAMES_TEAM }, {"Friends only", NAMES_FRIENDS}, { "Custom", NAMES_CUSTOM } } };
	seth.vars[VAR_ESPNAME_COLORS] = (ethVars_t) { "Player name colors", 1, "espname_colors", CAT_ESP, qfalse,
		{ { "Game color", 1 }, { "Unicolor", 2 } } };
	seth.vars[VAR_ESPNAME_BG] = (ethVars_t) { "Player name background", qtrue, "espname_bg", CAT_ESP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_ESPMINES] = (ethVars_t) { "Landmine Spotting", qfalse, "esp_landmine", CAT_ESP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_ESPENT] = (ethVars_t) { "Missile", qtrue, "esp_missile", CAT_ESP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_ESPITEMS] = (ethVars_t) { "Items", qtrue, "esp_items", CAT_ESP, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };



	// Misc

	seth.vars[VAR_RANDOMNAME] = (ethVars_t) { "Random name", qfalse, "randomname", CAT_MISC, qfalse,
		{ { "Off", qfalse }, { "From other servers", 1 }, { "From other players", 2 } } };
	seth.vars[VAR_RANDOMNAME_DELAY] = (ethVars_t) { "Random name delay", 30, "randomname_delay", CAT_MISC, qtrue,
		{ { "2s", 2 }, { "5s", 5 }, { "10s", 10 }, { "15s", 15 }, { "20s", 20 }, { "30s", 30 }, { "45s", 45 }, { "1min", 60 }, { "2min", 60 * 2 } , { "3min", 60 * 3 } , { "5min", 60 * 5 } } };
	seth.vars[VAR_SPEC] = (ethVars_t) { "Show spectators", qtrue, "spec", CAT_MISC, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SPECLOCK] = (ethVars_t) { "Remove spectator locking", qtrue, "speclock", CAT_MISC, qfalse,
		{ { "Off", qfalse }, { "On", qtrue }} };
	seth.vars[VAR_INACTIVITY] = (ethVars_t) { "Remove inactivity kick", qtrue, "inactivity", CAT_MISC, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_AUTOVOTE] = (ethVars_t) { "Auto voting", qfalse, "autovote", CAT_MISC, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_REFLIST] = (ethVars_t) { "Referee counter", REF_OFF, "ref", CAT_MISC, qfalse,
		{ { "Off", REF_OFF }, { "List with nicks", REF_LIST }, { "Number of refs only", REF_NUM } } };
	seth.vars[VAR_PBSS] = (ethVars_t) { "PB_SS", PBSS_CLEAN, "pbss", CAT_MISC, qfalse,
		{ { "Clean PB_SS", PBSS_CLEAN }, { "Spoofed PB_SS", PBSS_SPOOFED }, { "Black PB_SS", PBSS_BLACK }, {"Off", PBSS_OFF } } };
	seth.vars[VAR_ETPRO_OS] = (ethVars_t) { "Etpro OS (needs a /reconnect)", ETPRO_OS_LINUX, "etpro_os", CAT_MISC, qfalse,
		{ { "linux", ETPRO_OS_LINUX }, { "win32", ETPRO_OS_WIN32 } } };

	// Spycam

	seth.vars[VAR_ENTCAM] = (ethVars_t) { "Show entity cam", ENTCAM_OFF, "entcam", CAT_SPYCAM, qfalse,
		{ { "Off", ENTCAM_OFF }, { "Closest", ENTCAM_CLOSEST }, { "Target", ENTCAM_TARGET }, { "Snipers", ENTCAM_SNIPER }, { "Selected player", ENTCAM_CUSTOM } } };
	seth.vars[VAR_ENTCAM_PLAYER] = (ethVars_t) { "Player Cam", qfalse, "playercam", CAT_SPYCAM, qfalse,
		{} };
	seth.vars[VAR_MORTARCAM] = (ethVars_t) { "Show mortar cam", qtrue, "mortarcam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_DROPCAM] = (ethVars_t) { "Drop cam", qfalse, "dropcam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_MORTARCAM_H] = (ethVars_t) { "Mortar cam height", 800.0f, "mortarcam_h", CAT_SPYCAM, qfalse,
		{ { "300", 300.0f }, { "400", 400.0f }, { "500", 500.0f }, { "600", 600.0f }, { "700", 700.0f }, { "800", 800.0f }, { "900", 900.0f }, { "1000", 1000.0f } } };
	seth.vars[VAR_PANZERCAM] = (ethVars_t) { "Show panzer cam", qtrue, "panzercam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SATCHELCAM] = (ethVars_t) { "Show satchel cam", qtrue, "satchelcam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_SATCHELCAM_H] = (ethVars_t) { "Satchel cam height", 300.0f, "satchelcam_h", CAT_SPYCAM, qfalse,
		{ { "300", 300.0f }, { "400", 400.0f }, { "500", 500.0f }, { "600", 600.0f }, { "700", 700.0f }, { "800", 800.0f }, { "900", 900.0f }, { "1000", 1000.0f } } };
	seth.vars[VAR_MIRRORCAM] = (ethVars_t) { "Show mirror cam", qfalse, "mirrorcam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_RIFLECAM] = (ethVars_t) { "Show rifle cam", qtrue, "riflecam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_RIFLECAM_H] = (ethVars_t) { "Rifle cam height", 500.0f, "riflecam_h", CAT_SPYCAM, qfalse,
		{ { "300", 300.0f }, { "400", 400.0f }, { "500", 500.0f }, { "600", 600.0f }, { "700", 700.0f }, { "800", 800.0f }, { "900", 900.0f }, { "1000", 1000.0f } } };
	seth.vars[VAR_GRENADECAM] = (ethVars_t) { "Show grenade cam", qfalse, "grenadecam", CAT_SPYCAM, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_GRENADECAM_H] = (ethVars_t) { "Grenade cam height", 500.0f, "grenadecam_h", CAT_SPYCAM, qfalse,
		{ { "300", 300.0f }, { "400", 400.0f }, { "500", 500.0f }, { "600", 600.0f }, { "800", 800.0f }, { "900", 900.0f }, { "1000", 1000.0f } } };

	// Custom HUD

	seth.vars[VAR_CHUD] = (ethVars_t) { "Draw custom HUD", HUD_OFF, "chud", CAT_HUD, qfalse,
		{ { "Off", HUD_OFF }, { "Type 1", HUD_1 }, { "Type 2", HUD_2 } } }; //{ "Dev", HUD_3 } } };
	seth.vars[VAR_RELOAD_TXT] = (ethVars_t) { "Show Reload tXt", qtrue, "reloadtxt", CAT_HUD, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_RELOAD_NEED] = (ethVars_t) { "Need Reload tXt", qtrue, "needreload", CAT_HUD, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_LOW_HP] = (ethVars_t) { "Low HP tXt", qtrue, "lowhp", CAT_HUD, qfalse,
        { { "Off", qfalse }, { "On", qtrue } } };
	seth.vars[VAR_CHUD_SYS_UPDATEDELAY] = (ethVars_t) { "System info update delay", 5, "chud_sysupdelay", CAT_HUD, qfalse,
		{ { "1s", 1 }, { "3s", 3 }, { "5s", 5 }, { "10s", 10 }, { "20s", 20 } } };
	seth.vars[VAR_CHUD_SYS_FPSUPDATEDELAY] = (ethVars_t) { "FPS update delay", 1000, "chud_fpsupdelay", CAT_HUD, qfalse,
		{ { "250ms", 250 }, { "500ms", 500 }, { "750ms", 750 }, { "1s", 1000 } } };
	seth.vars[VAR_CHUD_SYS_BAR_WIDTH] = (ethVars_t) { "System bar Width", 80, "chud_sbar_width", CAT_HUD, qfalse,
		{ { "50", 50 }, { "60", 60 }, { "70", 70 }, { "80", 80 }, { "90", 90 }, { "100", 100 }, { "110", 110 }, { "120", 120 } } };
	seth.vars[VAR_CHUD_SYS_BAR_HEIGHT] = (ethVars_t) { "System bar Height", 8, "chud_sbar_height", CAT_HUD, qfalse,
		{ { "7", 7 }, { "8", 8 }, { "9", 9 }, { "10", 10 }, { "11", 11 }, { "12", 12 } } };
	seth.vars[VAR_CHUD_OUTPUTNUM] = (ethVars_t) { "Amount of log messages", 5, "chud_lognum", CAT_HUD, qfalse,
		{ { "3", 3 }, { "5", 5 }, { "7", 7 }, { "10", 10 } } }; // must be <= MAX_OUTPUT_MSGS
	seth.vars[VAR_CHUD_OUTICONSIZE] = (ethVars_t) { "Log icon size", 12, "chud_logiconsize", CAT_HUD, qfalse,
		{ { "8x8", 8 }, { "10x10", 10 }, { "12x12", 12 }, { "14x14", 14 }, { "16x16", 16 } } };
	seth.vars[VAR_CHUD_LOG_FONTSIZE] = (ethVars_t) { "Log font size", 0.12f, "chud_logfontsize", CAT_HUD, qfalse,
		{ { "0.10", 0.10f }, { "0.11", 0.11f }, { "0.12", 0.12f }, { "0.13", 0.13f }, { "0.14", 0.14f }, { "0.15", 0.15f } } };
	seth.vars[VAR_CHUD_VICTIM_STAYTIME] = (ethVars_t) { "'You killed..' msg stay time", 6, "chud_victim_staytime", CAT_HUD, qfalse,
		{ { "Off", 0 }, { "2s", 2 }, { "3s", 3 }, { "4s", 4 }, { "5s", 5 }, { "6s", 6 }, { "7s", 7 }, { "8s", 8 }, { "9s", 9 }, { "10s", 10 } } };
	seth.vars[VAR_CHUD_VICTIM_FADETIME] = (ethVars_t) { "'You killed..' msg fade time", 2, "chud_victim_fadetime", CAT_HUD, qfalse,
		{ { "Off", 0 }, { "250ms", 0.25f }, { "500ms", 0.5f }, { "750ms", 0.75f }, { "1s", 1 }, { "1.5s", 1.5f }, { "2s", 2 }, { "3s", 3 }, { "4s", 4 }, { "5s", 5 } } };


	// Custom HUD II
	seth.vars[VAR_CHUD_HPOPUP_HEIGHT] = (ethVars_t) { "Health popup height", 80, "chud_hpp_height", CAT_HUD2, qfalse,
		{ { "50", 50 }, { "60", 60 }, { "70", 70 }, { "80", 80 }, { "90", 90 }, { "100", 100 }, { "110", 110 }, { "120", 120 } } };
	seth.vars[VAR_CHUD_HPOPUP_STAYTIME] = (ethVars_t) { "Health popup stay time", 4, "chud_hpp_staytime", CAT_HUD2, qfalse,
		{ { "Off", 0 }, { "2s", 2 }, { "3s", 3 }, { "4s", 4 }, { "5s", 5 }, { "6s", 6 }, { "7s", 7 }, { "8s", 8 } } };
	seth.vars[VAR_CHUD_CHAT_MSGS] = (ethVars_t) { "Amount of chat messages", 5, "chud_chatnum", CAT_HUD2, qfalse,
		{ { "3", 3 }, { "5", 5 }, { "7", 7 }, { "10", 10 } } }; // must be <= MAX_CHAT_MSGS
	seth.vars[VAR_CHUD_CHAT_STAYTIME] = (ethVars_t) { "Chat stay time", 10, "chud_chat_staytime", CAT_HUD2, qfalse,
		{ { "Off", 0 }, { "6s", 6 }, { "8s", 8 }, { "12s", 12 }, { "16s", 16 }, { "20s", 20 }, { "25s", 25 } } };
	seth.vars[VAR_CHUD_CONSOLE_MSGS] = (ethVars_t) { "Amount of console messages", 5, "chud_connum", CAT_HUD2, qfalse,
		{ { "3", 3 }, { "5", 5 }, { "7", 7 }, { "10", 10 } } }; // must be <= MAX_CONSOLE_MSGS
	seth.vars[VAR_CHUD_CONSOLE_STAYTIME] = (ethVars_t) { "Console msgs stay time", 10, "chud_con_staytime", CAT_HUD2, qfalse,
		{ { "Off", 0 }, { "6s", 6 }, { "8s", 8 }, { "12s", 12 }, { "16s", 16 }, { "20s", 20 }, { "25s", 25 } } };
	seth.vars[VAR_EXTRA_VISUALS] = (ethVars_t) { "Extra Visuals Type 2", qtrue, "extraVisuals", CAT_HUD2, qfalse,
		{ { "Off", qfalse }, { "On", qtrue } } };

	// Sounds

	seth.vars[VAR_WP_SOUNDS] = (ethVars_t)	{ "Weapon Sounds", SND_SERVER, "wpsounds", CAT_SOUND, qfalse,
		{ { "Server", SND_SERVER }, { "Etmain", SND_ETMAIN }, { "Custom", SND_CUSTOM } } };
	seth.vars[VAR_SPREE_SOUNDS] = (ethVars_t) { "EThax Spree Sounds", qtrue, "spreesounds", CAT_SOUND, qfalse,
		{ { "On", qtrue }, { "Off", qfalse } } };
	seth.vars[VAR_SOUND_PAK0] = (ethVars_t) { "ETMain sounds only", qfalse, "globalsounds", CAT_SOUND, qfalse,
		{ { "On", qtrue }, { "Off", qfalse } } };
	seth.vars[VAR_SOUND_HQ] = (ethVars_t) { "HQ sounds", qtrue, "hqsounds", CAT_SOUND, qfalse,
		{ { "On", qtrue }, { "Off", qfalse } } };

	#ifdef ETH_DEBUG

	// Debug

	seth.vars[VAR_MEMDUMP] = (ethVars_t) { "Display mem starting from:", qfalse, "memdump", CAT_DEBUG, qtrue,
		{ { "Off", qfalse }, { "CG_Trace()", 1 } , { "BG_EvalTraj()", 2 } , { "cg.time", 3 } , { "cg.refdef", 4 } , { "cg.refdefViewAngles", 5 } , { "vmMain()", 6 } , { "CL_MOUSEDX_ADDR", 7 } , { "eth.cg_snap->ps.origin", 8 } } };
	seth.vars[VAR_AIM_POINT] = (ethVars_t) { "Show aim point", qfalse, "aimpoint", CAT_DEBUG, qtrue,
		{ { "Off", AIM_POINT_OFF }, { "2D Point", AIM_POINT_2D } , { "3D RailTrail Cross", AIM_POINT_3D } } };
	seth.vars[VAR_PREDICT_STATS] = (ethVars_t) { "Show prediction stats", qfalse, "predict_stats", CAT_DEBUG, qtrue,
		{ { "Off", qfalse }, { "On", qtrue } } };
//	seth.vars[VAR_DLIGHT_CRAZY] = (ethVars_t) { "Show crazy dlight path", qfalse, "debug_dlight", CAT_DEBUG, qtrue,
//		{ { "Off", qfalse }, { "On", qtrue } } };

	#endif

	#ifdef ETH_PRIVATE
		PRIVATE_VARS_DEF
	#endif
				
}

void drawMenu() {
	// Get item height
	int itemHeight = sizeTextHeight(MENU_TEXT_SIZE, &eth.fontFixed) + (2 * 2);

	// Get max menu text width size
	int maxItemWidth = 0;
	int count;
	for (count = 0; count < VARS_TOTAL; count++) {
		int size = sizeTextWidth(MENU_TEXT_SIZE, seth.vars[count].menuText, &eth.fontFixed);
		if (size > maxItemWidth)
			maxItemWidth = size;
	}
	maxItemWidth += itemHeight;

	// Get max choice text width size
	int maxValueWidth = 0;
	for (count = 0; count < VARS_TOTAL; count++) {
		int i = 0;
		for (; i < MAX_CHOICES; i++) {
			int size = sizeTextWidth(MENU_TEXT_SIZE, seth.vars[count].choices[i].name, &eth.fontFixed);
			if (size > maxValueWidth)
				maxValueWidth = size;
		}
	}
	maxValueWidth += itemHeight;

	static int openCategory = -1;
	int nextOpenCategory = openCategory;
	int y = MENU_SCREEN_BORDER;
	if (eth.mod->type == MOD_TCE)
		y += 40;
	int catCount = 0;
	for (; catCount < CATS_MAX; catCount++) {
		qboolean isMouseOn = ((eth.mouseX > MENU_SCREEN_BORDER)
				&& (eth.mouseX < (MENU_SCREEN_BORDER + maxItemWidth))
				&& (eth.mouseY > y)
				&& (eth.mouseY < (y + itemHeight)));

		// Sanity check
		if (!menuCats[catCount].name)
			fatalError("Can't find text for a menu category.");

		// Draw category
		if ( seth.value[ VAR_STYLEDMENU ] ) {
			drawFillRoundRect(MENU_SCREEN_BORDER, y, maxItemWidth, itemHeight, isMouseOn ? colorGreen : gameBackColor);
			drawRoundRect(MENU_SCREEN_BORDER, y, maxItemWidth, itemHeight, isMouseOn ? gameBackColor : gameBorderColor);
			// red
			drawPic( MENU_SCREEN_BORDER + (itemHeight / 2), y - 5, itemHeight + 5, itemHeight + 5, eth.menuShader[ menuCats[ catCount ].id ] );
			if ( seth.value[ VAR_MENUCOLORS ] == 0 ) 
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight + 5, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorRed, qfalse, qfalse, &eth.fontFixed);
			// yellow
			else if ( seth.value[ VAR_MENUCOLORS ] == 1 ) 
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight + 5, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorYellow, qfalse, qfalse, &eth.fontFixed);
			// cyan
			else if ( seth.value[ VAR_MENUCOLORS ] == 2 ) 
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight + 5, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorCyan, qfalse, qfalse, &eth.fontFixed);
			// blue immo
			else if ( seth.value[ VAR_MENUCOLORS ] == 3 ) 
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight + 5, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorBlue, qfalse, qfalse, &eth.fontFixed);
			// white immo
			else if ( seth.value[ VAR_MENUCOLORS ] == 4 ) 
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight + 5, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorWhite, qfalse, qfalse, &eth.fontFixed);
			// black immo
			else if ( seth.value[ VAR_MENUCOLORS ] == 5 ) 
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight + 5, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorBlack, qfalse, qfalse, &eth.fontFixed);

		} else {
			drawFillRect(MENU_SCREEN_BORDER, y, maxItemWidth, itemHeight, isMouseOn ? colorWhite : gameBackColor);
			drawRect(MENU_SCREEN_BORDER, y, maxItemWidth, itemHeight, isMouseOn ? gameBackColor : gameBorderColor, 1);
			// red
			if ( seth.value[ VAR_MENUCOLORS ] == 0 )
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorRed, qfalse, qfalse, &eth.fontFixed);
			// yellow
			else if ( seth.value[ VAR_MENUCOLORS ] == 1 )
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorYellow, qfalse, qfalse, &eth.fontFixed);
			// cyan
			else if ( seth.value[ VAR_MENUCOLORS ] == 2 )
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorCyan, qfalse, qfalse, &eth.fontFixed);
			// blue immo
			else if ( seth.value[ VAR_MENUCOLORS ] == 3 )
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorBlue, qfalse, qfalse, &eth.fontFixed);
			// White immo
			else if ( seth.value[ VAR_MENUCOLORS ] == 4 )
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorWhite, qfalse, qfalse, &eth.fontFixed);
			// black immo
			else if ( seth.value[ VAR_MENUCOLORS ] == 5 )
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + itemHeight, y + 2, MENU_TEXT_SIZE, menuCats[catCount].name, isMouseOn ? gameFontColor : colorBlack, qfalse, qfalse, &eth.fontFixed);
		}

		y += itemHeight + MENU_ITEM_SPACE ;

		// Category click
		if (((eth.mouseButton == Button1) || (eth.mouseButton == Button3)) && isMouseOn) {
			eth.mouseButton = 0;
			if (nextOpenCategory != catCount)
				syscall_CG_S_StartLocalSound(eth.cgs_media_sndLimboSelect, CHAN_LOCAL_SOUND);

			// open & close
			if ( catCount != nextOpenCategory ) {
				nextOpenCategory = catCount;
			} else {
				nextOpenCategory = -1;
			}
		}

		// Draw vars only for this category
		if (openCategory != catCount) {
			if ( seth.value[ VAR_STYLEDMENU ] ) y += 5;
			continue;
		}

		// Search vars in this category
		int varCount = 0;
		for (; varCount < VARS_TOTAL; varCount++) {
			if (menuCats[catCount].id != seth.vars[varCount].menuCategory)
				continue;

			ethVars_t *var = &seth.vars[varCount];
			isMouseOn = ((eth.mouseX > MENU_SCREEN_BORDER + MENU_ENTRY_SPACE)
					&& (eth.mouseX < (MENU_SCREEN_BORDER + MENU_ENTRY_SPACE + maxItemWidth + MENU_ITEM_SPACE + maxValueWidth))
					&& (eth.mouseY > y)
					&& (eth.mouseY < (y + itemHeight)));

			// Draw var
			if ( seth.value[ VAR_STYLEDMENU ] ) {
				drawFillRoundRect(MENU_SCREEN_BORDER + MENU_ENTRY_SPACE, y, maxItemWidth, itemHeight, isMouseOn ? colorBlue : gameBackColor);
				drawRoundRect(MENU_SCREEN_BORDER + MENU_ENTRY_SPACE, y, maxItemWidth, itemHeight, isMouseOn ? gameBackColor : gameBorderColor);
				drawText(MENU_SCREEN_BORDER + MENU_ENTRY_SPACE + (itemHeight / 2) + sizeTextWidth(MENU_TEXT_SIZE, " ", &eth.fontFixed), y + 2, MENU_TEXT_SIZE, var->menuText, colorRed, qfalse, qfalse, &eth.fontFixed);
			} else {
				drawFillRect(MENU_SCREEN_BORDER, y, maxItemWidth, itemHeight, isMouseOn ? colorRed : gameBackColor);
				drawRect(MENU_SCREEN_BORDER, y, maxItemWidth, itemHeight, isMouseOn ? gameBackColor : gameBorderColor, 1);
				drawText(MENU_SCREEN_BORDER + (itemHeight / 2) + sizeTextWidth(MENU_TEXT_SIZE, " ", &eth.fontFixed), y + 2, MENU_TEXT_SIZE, var->menuText, colorWhite, qfalse, qfalse, &eth.fontFixed);
			}

			// Search position of the current value
			int pos = 0;
			while ((var->choices[pos].name != NULL) // Check for valid choice
					&& (var->choices[pos].value != seth.value[varCount])
					&& (pos < MAX_CHOICES)) {
				pos++;
			}

			// Get name of this value
			char value[32];
			memset(value, 0, sizeof(value));
			if ((pos == MAX_CHOICES) || (var->choices[pos].name == NULL))
				sprintf(value, "%.2f", seth.value[varCount]);
			else
				strncpy(value, var->choices[pos].name, sizeof(value));

			// Draw value of this var
			if ( seth.value[ VAR_STYLEDMENU ] ) {
				drawFillRoundRect(MENU_SCREEN_BORDER + MENU_ENTRY_SPACE + MENU_ITEM_SPACE + maxItemWidth, y, maxValueWidth, itemHeight, isMouseOn ? colorCyan : gameBackColor);
				drawRoundRect(MENU_SCREEN_BORDER + MENU_ENTRY_SPACE + MENU_ITEM_SPACE + maxItemWidth, y, maxValueWidth, itemHeight, isMouseOn ? gameBackColor : gameBorderColor);
				int w = sizeTextWidth(MENU_TEXT_SIZE, value, &eth.fontFixed);
				drawText(MENU_SCREEN_BORDER + MENU_ENTRY_SPACE + MENU_ITEM_SPACE + maxItemWidth + (maxValueWidth / 2) - (w / 2), y + 2, MENU_TEXT_SIZE, value, colorWhite, qfalse, qfalse, &eth.fontFixed);
			} else {
				drawFillRect(MENU_SCREEN_BORDER + MENU_ITEM_SPACE + maxItemWidth, y, maxValueWidth, itemHeight, isMouseOn ? colorBlue : gameBackColor);
				drawRect(MENU_SCREEN_BORDER + MENU_ITEM_SPACE + maxItemWidth, y, maxValueWidth, itemHeight, isMouseOn ? gameBackColor : gameBorderColor, 1);
				int w = sizeTextWidth(MENU_TEXT_SIZE, value, &eth.fontFixed);
				drawText(MENU_SCREEN_BORDER + MENU_ITEM_SPACE + maxItemWidth + (maxValueWidth / 2) - (w / 2), y + 2, MENU_TEXT_SIZE, value, colorWhite, qfalse, qfalse, &eth.fontFixed);
			}

			y += itemHeight + MENU_ITEM_SPACE;

			// If not a value click
			if (((eth.mouseButton != Button1) && (eth.mouseButton != Button3)) || !isMouseOn)
				continue;

			// Get max choices
			int max = 0;
			while (var->choices[max].name != NULL)
				max++;

			// Pre-define values
			if (max) {
				// If current value no found take 0
				if ((pos < 0) || (pos == MAX_CHOICES))
					pos = 0;

				// Set new position
				if (eth.mouseButton == Button1)
					pos++;
				else
					pos--;

				// Check bounds
				if (pos >= max)
					pos = 0;
				else if (pos < 0)
					pos = max - 1;

			    seth.value[varCount] = var->choices[pos].value;

				// Automatically disable draw2d when we turn on custom hud
				// and enable it when we turn it off
				if (varCount == VAR_CHUD) {
					if (seth.value[varCount] == HUD_OFF)
						orig_Cvar_Set2("cg_draw2d", "1", qtrue);
					else
						orig_Cvar_Set2("cg_draw2d", "0", qtrue);
				}

			// Manual value
			} else {
				// Set new value
				if (eth.mouseButton == Button1) {
					seth.value[varCount] += seth.value[VAR_STEP];
					if ((varCount == VAR_AIMFOV) && (seth.value[varCount] > 360.0f))
						seth.value[varCount] -= 360.0f;
					if ((varCount == VAR_HUMANVALUE) && (seth.value[varCount] > 1.0f))
						seth.value[varCount] -= seth.value[VAR_STEP];
					if ((varCount == VAR_SHAKE) && (seth.value[varCount] > 1000.0))
						seth.value[varCount] -= seth.value[VAR_STEP];
					if ((varCount == VAR_RANDOM_X) && (seth.value[varCount] > 100.0))
						seth.value[varCount] -= seth.value[VAR_STEP];
					if ((varCount == VAR_RANDOM_Y) && (seth.value[varCount] > 100.0))
						seth.value[varCount] -= seth.value[VAR_STEP];
					if ((varCount == VAR_RANDOM_Z) && (seth.value[varCount] > 100.0))
						seth.value[varCount] -= seth.value[VAR_STEP];
				}
				else {
					seth.value[varCount] -= seth.value[VAR_STEP];
					if ((varCount == VAR_AIMFOV) && (seth.value[varCount] < 0.01f)) // 0.01 to make it 360.0 instead of 0.0 when decreasing
						seth.value[varCount] += 360.0f;
					if ((varCount == VAR_HUMANVALUE) && (seth.value[varCount] < 0.0f))
						seth.value[varCount] += seth.value[VAR_STEP];
					if ((varCount == VAR_SHAKE) && (seth.value[varCount] < 0.0))
						seth.value[varCount] += seth.value[VAR_STEP];
					if ((varCount == VAR_RANDOM_X) && (seth.value[varCount] < 0.0))
						seth.value[varCount] += seth.value[VAR_STEP];
					if ((varCount == VAR_RANDOM_Y) && (seth.value[varCount] < 0.0))
						seth.value[varCount] += seth.value[VAR_STEP];
					if ((varCount == VAR_RANDOM_Z) && (seth.value[varCount] < 0.0))
						seth.value[varCount] += seth.value[VAR_STEP];
				}
			}

			syscall_CG_S_StartLocalSound(eth.cgs_media_sndLimboSelect, CHAN_LOCAL_SOUND);
			eth.mouseButton = 0;
		}
		if ( seth.value[ VAR_STYLEDMENU ] ) y += 5;
	}
	openCategory = nextOpenCategory;
	eth.mouseButton = 0;
}
