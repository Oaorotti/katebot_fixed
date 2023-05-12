#include "main.h"

Config* cfg = new Config();



void Config::SaveConfig()
{
	for (auto& map_data : m_mapWeapons)
	{
		char * weaponName = new char[map_data.second.size() + 1];
		std::copy(map_data.second.begin(), map_data.second.end(), weaponName);
		weaponName[map_data.second.size()] = '\0';
		
		char* weapontype = WeaponType(map_data.first);
		
		g_pFiles->WriteBoolParam	(weapontype,weaponName, xorstr(".aimbot.enable").crypt_get(), aimbot[map_data.first].enable);
		g_pFiles->WriteIntParam		(weapontype,weaponName, xorstr(".aimbot.start").crypt_get(), aimbot[map_data.first].startbullet);
		g_pFiles->WriteIntParam		(weapontype,weaponName, xorstr(".aimbot.end").crypt_get(),aimbot[map_data.first].endbullet);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, xorstr(".aimbot.delay").crypt_get(),aimbot[map_data.first].delay);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, xorstr(".aimbot.fov").crypt_get(),aimbot[map_data.first].fov);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, xorstr(".aimbot.smooth").crypt_get(),aimbot[map_data.first].smooth);
		g_pFiles->WriteIntParam		(weapontype,weaponName, xorstr(".aimbot.bone").crypt_get(),aimbot[map_data.first].bone);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, xorstr(".aimbot.rcsAmount").crypt_get(),aimbot[map_data.first].rcsAmount);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, xorstr(".aimbot.killDelay").crypt_get(),aimbot[map_data.first].killdelay);
		
		delete[] weaponName;
	}
}

void Config::LoadConfig()
{
	keys.aimbot_toggle = g_pFiles->ReadInt(xorstr("Keys").crypt_get(), xorstr("Aimbot.Toggle").crypt_get());
	keys.aimbot_hold = g_pFiles->ReadInt(xorstr("Keys").crypt_get(), xorstr("Aimbot.Hold").crypt_get());
	keys.glowesp_toggle = g_pFiles->ReadInt(xorstr("Keys").crypt_get(), xorstr("GlowESP.Toggle").crypt_get());
	keys.triggerbot_hold = g_pFiles->ReadInt(xorstr("Keys").crypt_get(), xorstr("Triggerbot.Hold").crypt_get());
	keys.bunnyhop_hold = g_pFiles->ReadInt(xorstr("Keys").crypt_get(), xorstr("Bunnyhop.Hold").crypt_get());
	keys.skinchanger_toggle = g_pFiles->ReadInt(xorstr("Keys").crypt_get(), xorstr("Skinchanger.Toggle").crypt_get());
	//keys.panic_mode = g_pFiles->ReadInt("Keys","PANIC_MODE");
	
	debugEnable = g_pFiles->ReadBool(xorstr("Features").crypt_get(), xorstr("Debug.Enable").crypt_get());
	glowEspEnabled = g_pFiles->ReadBool(xorstr("Features").crypt_get(), xorstr("GlowESP.Enable").crypt_get());
	aimbotEnabled = g_pFiles->ReadBool(xorstr("Features").crypt_get(), xorstr("Aimbot.Enable").crypt_get());
	triggerbotEnabled = g_pFiles->ReadBool(xorstr("Features").crypt_get(), xorstr("Triggerbot.Enable").crypt_get());
	bunnyhopEnabled = g_pFiles->ReadBool(xorstr("Features").crypt_get(), xorstr("Bunnyhop.Enable").crypt_get());
	skinchangerEnabled = g_pFiles->ReadBool(xorstr("Features").crypt_get(), xorstr("Skinchanger.Enable").crypt_get());
	
	AdaptiveSmoothMultiplier = g_pFiles->ReadFloat(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.Multiplier").crypt_get());
	RiflesAdaptiveSmooth = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.Rifles").crypt_get());
	PistolsAdaptiveSmooth = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.Pistol").crypt_get());
	SnipersAdaptiveSmooth = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.Sniper").crypt_get());
	SMGsAdaptiveSmooth = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.SMG").crypt_get());
	ShotGunsAdaptiveSmooth = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.Shotgun").crypt_get());
	LMGsAdaptiveSmooth = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.AdaptiveSmooth.LMG").crypt_get());
	
	spiralAim = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.Spiral.Enable").crypt_get());
	spiralAimX = g_pFiles->ReadFloat(xorstr("Settings").crypt_get(), xorstr("Aimbot.Spiral.X").crypt_get());
	spiralAimY = g_pFiles->ReadFloat(xorstr("Settings").crypt_get(), xorstr("Aimbot.Spiral.Y").crypt_get());
	
	SaveTargetAim = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.SaveTarget").crypt_get());
	faceitAim = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Aimbot.FaceitMode").crypt_get());
	bspParsing = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("BSPParsing").crypt_get());
	skinchangerAutoUpdate = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Skinchanger.AutoUpdate").crypt_get());
	triggerbot.fovBased = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("Triggerbot.FovBased").crypt_get());
	triggerbot.delay = g_pFiles->ReadFloat(xorstr("Settings").crypt_get(), xorstr("Triggerbot.Delay").crypt_get());
	glowesp.alpha = g_pFiles->ReadInt(xorstr("Settings").crypt_get(), xorstr("GlowESP.Alpha").crypt_get());
	glowesp.onlyVisible = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("GlowESP.OnlyVisible.Enable").crypt_get());
	GlowESPNoFlickerEnable = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("GlowESP.NoFlicker.Enable").crypt_get());
	GlowESPEnemiesOnlyEnable = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("GlowESP.EnemiesOnly.Enable").crypt_get());
	glowesp.bodycolorenable = g_pFiles->ReadBool(xorstr("Settings").crypt_get(), xorstr("GlowESP.BodyColors.Enable").crypt_get());
	glowesp.bodyred = g_pFiles->ReadInt(xorstr("Settings").crypt_get(), xorstr("GlowESP.BodyRed").crypt_get());
	glowesp.bodygreen = g_pFiles->ReadInt(xorstr("Settings").crypt_get(), xorstr("GlowESP.BodyGreen").crypt_get());
	glowesp.bodyblue = g_pFiles->ReadInt(xorstr("Settings").crypt_get(), xorstr("GlowESP.BodyBlue").crypt_get());
	glowesp.bodyalpha = g_pFiles->ReadInt(xorstr("Settings").crypt_get(), xorstr("GlowESP.BodyAlpha").crypt_get());
	knifeModel = g_pFiles->ReadInt(xorstr("Settings").crypt_get(), xorstr("KnifeChanger.Model(0-10)").crypt_get());
	
	for (auto& map_data : m_mapWeapons)
	{
		char * weaponName = new char[map_data.second.size() + 1];
		std::copy(map_data.second.begin(), map_data.second.end(), weaponName);
		weaponName[map_data.second.size()] = '\0';
		
		char* weapontype = WeaponType(map_data.first);
		
		aimbot[map_data.first].enable 		= g_pFiles->ReadBoolParam(weapontype,weaponName, xorstr(".aimbot.enable").crypt_get());
		aimbot[map_data.first].startbullet 	= g_pFiles->ReadIntParam(weapontype,weaponName, xorstr(".aimbot.start").crypt_get());
		aimbot[map_data.first].endbullet 	= g_pFiles->ReadIntParam(weapontype,weaponName, xorstr(".aimbot.end").crypt_get());
		aimbot[map_data.first].delay 		= g_pFiles->ReadFloatParam(weapontype,weaponName, xorstr(".aimbot.delay").crypt_get());
		aimbot[map_data.first].fov 			= g_pFiles->ReadFloatParam(weapontype,weaponName, xorstr(".aimbot.fov").crypt_get());
		aimbot[map_data.first].smooth 		= g_pFiles->ReadFloatParam(weapontype,weaponName, xorstr(".aimbot.smooth").crypt_get());
		aimbot[map_data.first].bone 		= g_pFiles->ReadIntParam(weapontype,weaponName, xorstr(".aimbot.bone").crypt_get());
		aimbot[map_data.first].rcsAmount 	= g_pFiles->ReadFloatParam(weapontype,weaponName, xorstr(".aimbot.rcsAmount").crypt_get());
		aimbot[map_data.first].killdelay 	= g_pFiles->ReadFloatParam(weapontype,weaponName, xorstr(".aimbot.killDelay").crypt_get());
		skin[map_data.first].id 	= g_pFiles->ReadIntParam(weapontype,weaponName, xorstr(".skin.id").crypt_get());
		skin[map_data.first].statTrack 	= g_pFiles->ReadIntParam(weapontype,weaponName, xorstr(".skin.statTrack").crypt_get());
		
		delete[] weaponName;
	}
	
	needIndexes = true;
}
	
char* Config::WeaponType(int ID)
{
	switch (ID)
	{
		case WID_Negev:
		case WID_M249:
		return xorstr("LMG").crypt_get();

		case WID_AWP:
		case WID_G3SG1_Auto:
		case WID_SCAR_Auto:
		case WID_Scout:
		return xorstr("Snipers").crypt_get();

		case WID_XM1014:
		case WID_MAG7:
		case WID_Nova:
		case WID_SawedOff:
		return xorstr("Shotguns").crypt_get();

		case WID_MAC10:
		case WID_P90:
		case WID_UMP45:
		case WID_PPBizon:
		case WID_MP7:
		case WID_MP9:
		return xorstr("SMGs").crypt_get();

		case WID_Deagle:
		case WID_Dual_Berettas:
		case WID_Five_Seven:
		case WID_USP:
		case WID_Glock:
		case WID_Tec9:
		case WID_P2000:
		case WID_P250:
		case WID_CZ75:
		case WID_Revolver:
		case WID_Zeus:
		return xorstr("Pistols").crypt_get();

		case WID_AK47:
		case WID_AUG:
		case WID_FAMAS:
		case WID_M4A4:
		case WID_M4A1S:
		case WID_Galil:
		case WID_SG553:
		return xorstr("Rifles").crypt_get();

		default:
		return xorstr("null").crypt_get();
	}
}