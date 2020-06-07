#!/bin/sh
# This script generate shader script and define files for eth

SHADER_SCRIPT=EThax_PK3/scripts/eth.shader
SHADER_DEFINE=shaders.h

rm -rf $SHADER_SCRIPT $SHADER_DEFINE

# Function to create script and define files
makeShader() {
	for SHADER in $1; do
		# Create shader script
		NAME=`echo $SHADER | cut -f1 -d:`
		SIZE=`echo $SHADER | cut -f2 -d:`
		MAP=`echo $SHADER | cut -f3 -d:`
		$2 >> $SHADER_SCRIPT

		# Create shader define
		COLOR=`echo $SHADER | cut -f4 -d:`
		echo "eth.shaders[$COLOR][$3] = syscall_CG_R_RegisterShader(\"$NAME\");" >> $SHADER_DEFINE
	done

	echo >> $SHADER_SCRIPT
	echo >> $SHADER_DEFINE
}

# Function to create script and define files
makeMenuShader() {
	for SHADER in $1; do
		# Create shader script
		NAME=`echo $SHADER | cut -f1 -d:`
		MAP=`echo $SHADER | cut -f2 -d:`
		$2 >> $SHADER_SCRIPT

		# Create shader define
		SHADERNAME=`echo $SHADER | cut -f3 -d:`
		echo "eth.menuShader[$SHADERNAME] = syscall_CG_R_RegisterShader(\"$NAME\");" >> $SHADER_DEFINE
	done

	echo >> $SHADER_SCRIPT
	echo >> $SHADER_DEFINE
}

# Function to create script and define files
makeMenuPartShader() {
	for SHADER in $1; do
		# Create shader script
		NAME=`echo $SHADER | cut -f1 -d:`
		MAP=`echo $SHADER | cut -f2 -d:`
		$2 >> $SHADER_SCRIPT

		# Create shader define
		SHADERNAME=`echo $SHADER | cut -f3 -d:`
		echo "eth.menuPart[$SHADERNAME] = syscall_CG_R_RegisterShader(\"$NAME\");" >> $SHADER_DEFINE
	done

	echo >> $SHADER_SCRIPT
	echo >> $SHADER_DEFINE
}

# Menu shader
menuShaderSkel() {
	echo "$NAME
{
	nocompress
	nomipmaps
	nopicmip
	{
		map $MAP.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}"
}
MENU_SHADERS="
	menu:gfx/menu/menu:CAT_STYLE
	aimbot:gfx/menu/aimbot:CAT_AIMBOTM
	aimbotx:gfx/menu/aimbotx:CAT_AIMBOTP
	hitbox:gfx/menu/hitbox:CAT_HITBOX
	aimbote:gfx/menu/aimbote:CAT_AIMBOTE
	human:gfx/menu/human:CAT_HUMAN
	humane:gfx/menu/humane:CAT_HUMANE
	riflebot:gfx/menu/rifle:CAT_RIFLE
	esp:gfx/menu/esp:CAT_ESP
	hud:gfx/menu/hud:CAT_HUD
	hud2:gfx/menu/hud2:CAT_HUD2
	misc:gfx/menu/misc:CAT_MISC
	sounds:gfx/menu/sounds:CAT_SOUND
	spycam:gfx/menu/spycam:CAT_SPYCAM
	visual:gfx/menu/visual:CAT_VISUAL
	version:gfx/menu/version:CAT_VERSION
"
makeMenuShader "$MENU_SHADERS" menuShaderSkel



