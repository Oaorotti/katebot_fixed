#include "main.h"
#include "csgo\netvars.h"
#include "csgo\csgo.h"

Ofs* ofs = new Ofs();

std::string Ofs::toHex(DWORD offset) {
    std::stringstream ss;
    ss << std::hex << offset;
    std::string x = ss.str();
    for (auto &c : x) c = toupper(c);

    return x;
}

void Ofs::FindOffsets() {
	if (!c_netvars::get().init())
	{
		printf(xorstr("Can't initialize netvar manager!").crypt_get());
		return;
	}

	if (cfg->debugEnable)
		c_netvars::get().dump();

	static auto find_ptr = [](Module* mod, const char* sig, DWORD sig_add, DWORD off_add, bool sub_base = true) -> DWORD
	{
		auto off = mem->FindPattern(mod, sig);
		auto sb = sub_base ? mod->GetImage() : 0;
		off = mem->Read<DWORD>(off + sig_add);
		
		return (!off ? 0 : off + off_add - sb);
	};

	m_dwIndex = 0x64;

	m_dwClientState = find_ptr(engine, xorstr("A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0").crypt_get(), 0x1, 0, true);
	m_dwViewAngles = find_ptr(engine, xorstr("F3 0F 11 86 ? ? ? ? F3 0F 10 44 24 ? F3 0F 11 86").crypt_get(), 0x4, 0, false);
	m_dwInGame = find_ptr(engine, xorstr("83 B8 ? ? ? ? ? 0F 94 C0 C3").crypt_get(), 0x2, 0, false);
	m_nDeltaTick = find_ptr(engine, xorstr("C7 87 ? ? ? ? ? ? ? ? FF 15 ? ? ? ? 83 C4 08").crypt_get(), 0x2, 0, false);
	m_dwLocalPlayer = find_ptr(client, xorstr("8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF").crypt_get(), 0x3, 0x4, true);
	m_dwEntityList = find_ptr(client, xorstr("BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8").crypt_get(), 0x1, 0, true);
	m_dwGlowObject = find_ptr(client, xorstr("A1 ? ? ? ? A8 01 75 4B").crypt_get(), 0x1, 0x4, true);
	m_dwForceJump = find_ptr(client, xorstr("8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02").crypt_get(), 0x2, 0, true);
	m_dwForceAttack = find_ptr(client, xorstr("89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04").crypt_get(), 0x2, 0, true);
	m_bDormant = find_ptr(client, xorstr("8A 81 ? ? ? ? C3 32 C0").crypt_get(), 0x2, 0x8, false);
	m_dwGlobalVars = find_ptr(engine, xorstr("68 ? ? ? ? 68 ? ? ? ? FF 50 08 85 C0").crypt_get(), 0x1, 0, true);
	m_dwPlayerResource = find_ptr(client, xorstr("8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7").crypt_get(), 0x2, 0, true);
	dwClientState_MaxPlayer = find_ptr(engine, xorstr("A1 ? ? ? ? 8B 80 ? ? ? ? C3 CC CC CC CC 55 8B EC 8A 45 08").crypt_get(), 0x7, 0x0, true);

	 m_hActiveWeapon = GET_NETVAR(xorstr("DT_BasePlayer").crypt_get(), xorstr("m_hActiveWeapon").crypt_get());
	 m_iCrossHairID = 0x11838;
	 m_iHealth = GET_NETVAR(xorstr("DT_BasePlayer").crypt_get(), xorstr("m_iHealth").crypt_get());
	 m_iTeamNum = GET_NETVAR(xorstr("DT_BasePlayer").crypt_get(), xorstr("m_iTeamNum").crypt_get());
	 m_iShotsFired = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_iShotsFired").crypt_get());
	 m_fFlags = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_fFlags").crypt_get());
	 m_lifeState = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_lifeState").crypt_get());
	 m_bSpottedByMask = GET_NETVAR(xorstr("DT_BaseEntity").crypt_get(), xorstr("m_bSpottedByMask").crypt_get());
	 m_vecOrigin = GET_NETVAR(xorstr("DT_BasePlayer").crypt_get(), xorstr("m_vecOrigin").crypt_get());
	 m_vecViewOffset = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_vecViewOffset[0]").crypt_get());
	 m_angEyeAngles = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_angEyeAngles").crypt_get());
	 m_vecVelocity = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_vecVelocity[0]").crypt_get());
	 m_aimPunchAngle = GET_NETVAR(xorstr("DT_BasePlayer").crypt_get(), xorstr("m_aimPunchAngle").crypt_get());
	 m_dwBoneMatrix = 0x26A8;
	 m_flNextPrimaryAttack = GET_NETVAR(xorstr("DT_BaseCombatWeapon").crypt_get(), xorstr("m_flNextPrimaryAttack").crypt_get());
	 m_nTickBase = GET_NETVAR(xorstr("DT_BasePlayer").crypt_get(), xorstr("m_nTickBase").crypt_get());
	 // m_iPlayerC4 = GET_NETVAR("DT_CSPlayer", "m_iPlayerC4");
	 m_bIsDefusing = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_bIsDefusing").crypt_get());
	 m_iItemDefinitionIndex = GET_NETVAR(xorstr("DT_BaseCombatWeapon").crypt_get(), xorstr("m_iItemDefinitionIndex").crypt_get());
	 m_iWorldModelIndex = GET_NETVAR(xorstr("DT_BaseViewModel").crypt_get(), xorstr("m_nViewModelIndex").crypt_get());
	 m_nModelIndex = GET_NETVAR(xorstr("DT_BaseViewModel").crypt_get(), xorstr("m_nModelIndex").crypt_get());
	 m_hViewModel = GET_NETVAR(xorstr("DT_CSPlayer").crypt_get(), xorstr("m_hViewModel[0]").crypt_get());
	 m_iAccountID = GET_NETVAR(xorstr("DT_BaseAttributableItem").crypt_get(), xorstr("m_iAccountID").crypt_get());
	 m_nFallbackPaintKit = GET_NETVAR(xorstr("DT_BaseAttributableItem").crypt_get(), xorstr("m_nFallbackPaintKit").crypt_get());
	 m_OriginalOwnerXuidLow = GET_NETVAR(xorstr("DT_BaseAttributableItem").crypt_get(), xorstr("m_OriginalOwnerXuidLow").crypt_get());
	 m_iItemIDLow = GET_NETVAR(xorstr("DT_BaseAttributableItem").crypt_get(), xorstr("m_iItemIDLow").crypt_get());
	 m_hMyWeapons = 0x2E08;
	 // m_iGlowIndex = GET_NETVAR("DT_CSPlayer", "m_flFlashDuration") + 0x24;

	m_iGlowIndex = 0x10488;
}

bool Ofs::CheckOffsets()
{
#define CHECK_OFFSET(n) \
	if (cfg->debugEnable) \
		printf(xorstr("%s = %X\n").crypt_get(), #n, n); \
	if (!n) { \
		result = false; \
		printf(xorstr("\n\nOffset: %s Outdated!\n\n").crypt_get(), #n); }

	bool result = true;

	CHECK_OFFSET(m_dwIndex);

	CHECK_OFFSET(m_dwClientState);
	CHECK_OFFSET(m_dwViewAngles);
	CHECK_OFFSET(m_dwInGame);
	CHECK_OFFSET(m_nDeltaTick);
	CHECK_OFFSET(m_dwLocalPlayer);
	CHECK_OFFSET(m_dwEntityList);
	CHECK_OFFSET(m_dwGlowObject);
	CHECK_OFFSET(m_dwForceJump);
	CHECK_OFFSET(m_dwForceAttack);
	CHECK_OFFSET(m_bDormant);
	CHECK_OFFSET(m_dwGlobalVars);
	CHECK_OFFSET(m_dwPlayerResource);

	CHECK_OFFSET(m_hActiveWeapon);
	CHECK_OFFSET(m_iCrossHairID);
	CHECK_OFFSET(m_iHealth);
	CHECK_OFFSET(m_iTeamNum);
	CHECK_OFFSET(m_iShotsFired);
	CHECK_OFFSET(m_fFlags);
	CHECK_OFFSET(m_lifeState);
	CHECK_OFFSET(m_bSpottedByMask);
	CHECK_OFFSET(m_vecOrigin);
	CHECK_OFFSET(m_vecViewOffset);
	CHECK_OFFSET(m_angEyeAngles);
	CHECK_OFFSET(m_vecVelocity);
	CHECK_OFFSET(m_aimPunchAngle);
	CHECK_OFFSET(m_dwBoneMatrix);
	CHECK_OFFSET(m_flNextPrimaryAttack);
	CHECK_OFFSET(m_nTickBase);
	// CHECK_OFFSET(m_iPlayerC4);
	CHECK_OFFSET(m_bIsDefusing);
	CHECK_OFFSET(m_iItemDefinitionIndex);
	CHECK_OFFSET(m_iWorldModelIndex);
	CHECK_OFFSET(m_nModelIndex);
	CHECK_OFFSET(m_hViewModel);
	CHECK_OFFSET(m_iAccountID);
	CHECK_OFFSET(m_nFallbackPaintKit);
	CHECK_OFFSET(m_OriginalOwnerXuidLow);
	CHECK_OFFSET(m_iItemIDLow);
	CHECK_OFFSET(m_hMyWeapons);

	return result;
}

void Ofs::getOffsets() {
	FindOffsets();
	
	if (!CheckOffsets())
	{
		printf(xorstr("Offsets outdated!\n").crypt_get());
		std::system(xorstr("pause").crypt_get());
		exit(1);
	}
	//std::system("pause");
	Sleep(1000);

	m_dwClientState = mem->Read<DWORD_PTR>(engine->GetImage() + m_dwClientState);
}
