// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2006 *nixCoders team - don't forget to credit us
// Update 2011 by *UnixCheats Team - don't forget to credit us
// Questions? requests? Bugs? Updates? http://unixcheats.freeforums.org

#define _GNU_SOURCE
#include "ethax.h"

void eth_glReadPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels )
{
    // Get the current values of our menus, visuals, and cams
    qboolean menu = eth.isMenuOpen;
    qboolean plist = eth.isPlistOpen;
    qboolean visuals = seth.value[VAR_VISUALS];
    qboolean entcam = seth.value[VAR_ENTCAM];
    qboolean playercam = seth.value[VAR_ENTCAM_PLAYER];
    qboolean mortarcam = seth.value[VAR_MORTARCAM];
    qboolean dropcam = seth.value[VAR_DROPCAM];
    qboolean panzercam = seth.value[VAR_PANZERCAM];
    qboolean satchelcam = seth.value[VAR_SATCHELCAM];
    qboolean mirrorcam = seth.value[VAR_MIRRORCAM];
    qboolean riflecam = seth.value[VAR_RIFLECAM];
    qboolean grenadecam = seth.value[VAR_GRENADECAM];
    qboolean binocsniperblack = seth.value[VAR_BINOCSNIPERBLACK];
    qboolean smoke = seth.value[VAR_SMOKE];
    qboolean warn_msg = seth.value[VAR_DRAW_WARN_MSG];
    qboolean head_msg = seth.value[VAR_DRAW_HEAD_MSG];
    qboolean hp_detector = seth.value[VAR_HEALTH_DETECTOR];

eth.pbss++;
    typedef void (*SCR_UpdateScreen_t)(void);
    SCR_UpdateScreen_t SCR_UpdateScreen = (SCR_UpdateScreen_t)sethET->SCR_UpdateScreen;

    // Turn off our menus, visuals, cams, Warns, Detector, etc
    eth.isMenuOpen = qfalse;
    eth.isPlistOpen = qfalse;
    seth.value[VAR_VISUALS]=qfalse;
    seth.value[VAR_ENTCAM]=qfalse;
    seth.value[VAR_ENTCAM_PLAYER]=qfalse;
    seth.value[VAR_MORTARCAM]=qfalse;
    seth.value[VAR_DROPCAM]=qfalse;
    seth.value[VAR_PANZERCAM]=qfalse;
    seth.value[VAR_SATCHELCAM]=qfalse;
    seth.value[VAR_MIRRORCAM]=qfalse;
    seth.value[VAR_RIFLECAM]=qfalse;
    seth.value[VAR_GRENADECAM]=qfalse;
    seth.value[VAR_BINOCSNIPERBLACK]=qfalse;
    seth.value[VAR_SMOKE]=qfalse;
    seth.value[VAR_DRAW_WARN_MSG]=qfalse;
    seth.value[VAR_DRAW_HEAD_MSG]=qfalse;
    seth.value[VAR_HEALTH_DETECTOR]=qfalse;

    SCR_UpdateScreen();
    SCR_UpdateScreen();
    SCR_UpdateScreen();
    SCR_UpdateScreen();

    orig_glReadPixels(x,y,width,height,format,type,pixels);

    // Set our menus, visuals, and cams back to values before pbss call
    eth.isMenuOpen = menu;
    eth.isPlistOpen = plist;    
    seth.value[VAR_VISUALS] = visuals;
    seth.value[VAR_ENTCAM] = entcam;
    seth.value[VAR_ENTCAM_PLAYER] = playercam;
    seth.value[VAR_MORTARCAM] = mortarcam;
    seth.value[VAR_DROPCAM] = dropcam;
    seth.value[VAR_PANZERCAM] = panzercam;
    seth.value[VAR_SATCHELCAM] = satchelcam;
    seth.value[VAR_MIRRORCAM] = mirrorcam;
    seth.value[VAR_RIFLECAM] = riflecam;
    seth.value[VAR_GRENADECAM] = grenadecam;
    seth.value[VAR_BINOCSNIPERBLACK] = binocsniperblack;
    seth.value[VAR_SMOKE] = smoke;
    seth.value[VAR_DRAW_WARN_MSG] = warn_msg;
    seth.value[VAR_DRAW_HEAD_MSG] = head_msg;
    seth.value[VAR_HEALTH_DETECTOR] = hp_detector;
    return;
}
