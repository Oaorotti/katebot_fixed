#ifndef _GLOWESP_H_
#define _GLOWESP_H_

#include "..\main.h"


class GlowESP
{
public:
	void Start()
	{
		try {
			for (;;) {

				if (cfg->GlowESPNoFlickerEnable) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->glowEspEnabled)
					continue;

				if (!csgo->IsInGame())
					continue;

				DWORD glow_manager = mem->Read<DWORD>(client->GetImage() + ofs->m_dwGlowObject);
				for (int g = 1; g <=32; g++) {
					int entity = mem->Read<int>(client->GetImage() + ofs->m_dwEntityList + g * 0x10);
					if (entity != 0) {
						EntityList[g].CheckVisible();
						int entity_team_id = mem->Read <int>(entity + ofs->m_iTeamNum);
						int LocalPlayer_TeamNum = LocalEntity.GetTeamNum();
						int entity_glow = mem->Read<int>(entity + ofs->m_iGlowIndex);
						mem->Write<float>(glow_manager + entity_glow * 0x38 + 0x8, float(cfg->glowesp.bodyred * 1.0f));//R
						mem->Write<float>(glow_manager + entity_glow * 0x38 + 0xC, float(cfg->glowesp.bodygreen * 1.0f));//G
						mem->Write<float>(glow_manager + entity_glow * 0x38 + 0x10, float(cfg->glowesp.bodyblue * 1.0f));//B
						mem->Write<float>(glow_manager + entity_glow * 0x38 + 0x14, float(cfg->glowesp.alpha * 1.0f));//A
						if (entity_team_id != LocalPlayer_TeamNum)
						{
							if (cfg->glowesp.onlyVisible && EntityList[g].IsVisible()) {
								mem->Write<int>(glow_manager + entity_glow * 0x38 + 0x28, 1);
							}else if(!cfg->glowesp.onlyVisible) {
								mem->Write<int>(glow_manager + entity_glow * 0x38 + 0x28, 1);
							}
						}
					}
				}
			}
		}
		catch (...){}
	}

private:

};

#endif