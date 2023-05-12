#include "main.h"

bool g_IsPanorama{};

std::unique_ptr< Valve::BSPParser > g_pBSPParser = std::make_unique< Valve::BSPParser >();
std::string m_pGameDirectory;
std::string m_pMapDirectory;

using std::cout;
using std::endl;
using std::cin;
using std::thread;
#define caseStringify(x) case x: return std::string(#x)
std::string vkToString(int vk);


void printInfo() {
	std::system(xorstr("cls").crypt_get());
	
	g_pCon->SetConsoleColor( red, black );
	cout << xorstr("\n   MeloBot \n\n").crypt_get();
	g_pCon->SetConsoleColor( aqua, black );
	cout << xorstr(" WARNING: \n").crypt_get();
	cout << xorstr("    For work features type command in console!\n").crypt_get();
	cout << xorstr("    unbind mouse1;bind / +attack\n\n").crypt_get();
	g_pCon->SetConsoleColor( green, black );
	cout << xorstr("           DELETE       - Reload Config\n").crypt_get();
	cout << xorstr("           END          - Panic Mode\n\n").crypt_get();
	g_pCon->SetConsoleColor( white, black );
	
	g_pCon->SetConsoleColor( magenta, black );
	cout << xorstr("          HOLD KEYS\n").crypt_get();
	g_pCon->SetConsoleColor( white, black );
	
	cout << xorstr("           Aimbot          - ").crypt_get() << vkToString(cfg->keys.aimbot_hold) << xorstr("\n").crypt_get();
	cout << xorstr("           Triggerbot      - ").crypt_get() << vkToString(cfg->keys.triggerbot_hold) << xorstr("\n").crypt_get();
	cout << xorstr("           Bunnyhop        - ").crypt_get() << vkToString(cfg->keys.bunnyhop_hold) << xorstr("\n").crypt_get();
	cout << xorstr("           ForceUpdateSkin - 0\n\n").crypt_get();
	
	g_pCon->SetConsoleColor( magenta, black );
	cout << xorstr("          TOGGLE KEYS\n").crypt_get();
	g_pCon->SetConsoleColor( white, black );
	
	g_pCon->SetConsoleColor( white, black );cout<<"           ";
	if (cfg->aimbotEnabled) {
		g_pCon->SetConsoleColor( white, green );
	} else {
		g_pCon->SetConsoleColor( white, red );
	}
	
	if (cfg->faceitAim) {
	cout << xorstr("Aimbot[Faceit]  - ").crypt_get() << vkToString(cfg->keys.aimbot_toggle) << xorstr("\n").crypt_get();
	} else {
	cout << xorstr("Aimbot[MM]      - ").crypt_get() << vkToString(cfg->keys.aimbot_toggle) << xorstr("\n").crypt_get();
	}
	
	g_pCon->SetConsoleColor( white, black );cout<<"           ";
	if (cfg->glowEspEnabled) {
		g_pCon->SetConsoleColor( white, green );
	} else {
		g_pCon->SetConsoleColor( white, red );
	}
	cout << xorstr(" GlowESP         - ").crypt_get() << vkToString(cfg->keys.glowesp_toggle) << xorstr("\n").crypt_get();
	
	g_pCon->SetConsoleColor( white, black );cout<<"           ";
	if (cfg->skinchangerEnabled) {
		g_pCon->SetConsoleColor( white, green );
	} else {
		g_pCon->SetConsoleColor( white, red );
	}
	cout << xorstr("Skinchanger     - ").crypt_get() << vkToString(cfg->keys.skinchanger_toggle) << xorstr("\n\n").crypt_get();
	
	g_pCon->SetConsoleColor( aqua, black );
	cout << xorstr("     GL&HF\n").crypt_get();
	g_pCon->SetConsoleColor( white, black );
	
}

void UpdateEntity()
{
try {
	for (;;) { 
		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		
		if (GetAsyncKeyState(VK_DELETE))
		{
			cfg->LoadConfig();
			printInfo();
			Beep(1000, 200);
		}
		
		if (cfg->keys.aimbot_toggle != 0 && GetAsyncKeyState(cfg->keys.aimbot_toggle))
		{
			cfg->aimbotEnabled = !cfg->aimbotEnabled;
			if (cfg->aimbotEnabled) {
				Beep(1000, 200);
			} else {
				Beep(500, 200);
			}
			printInfo();
			Sleep(200);
		}
		
		if (cfg->keys.glowesp_toggle != 0 && GetAsyncKeyState(cfg->keys.glowesp_toggle))
		{
			cfg->glowEspEnabled = !cfg->glowEspEnabled;
			if (cfg->glowEspEnabled) {
				Beep(1000, 200);
			} else {
				Beep(500, 200);
			}
			printInfo();
			Sleep(200);
		}
		
		if (cfg->keys.skinchanger_toggle != 0 && GetAsyncKeyState(cfg->keys.skinchanger_toggle))
		{
			cfg->skinchangerEnabled = !cfg->skinchangerEnabled;
			if (cfg->skinchangerEnabled) {
				Beep(1000, 200);
			} else {
				Beep(500, 200);
			}
			printInfo();
			Sleep(200);
		}
		
		static bool is_clicked = false;
		if (GetAsyncKeyState(VK_END))
		{
			if (!is_clicked) {
				cfg->panicMode = true;
				Sleep(50);
				csgo->ForceFullUpdate();
				Beep(1000, 200);
				
				std::system(xorstr("cls").crypt_get());
	
				g_pCon->SetConsoleColor( red, black );
				printf(xorstr("Hold END \nfor exit from panic mode ;)\n").crypt_get());
				g_pCon->SetConsoleColor( white, black );
				
				unsigned int panicTimer = 0;
				while (panicTimer < 2000) {
					if (GetAsyncKeyState(VK_END) & 0x8000) {
						panicTimer++;
					} else {
						panicTimer = 0;
					}
					
					Sleep(1);
				}
				Beep(800, 100);
				Beep(800, 100);
				cfg->panicMode = false;
				printInfo();
				is_clicked = true;
			}
		} else is_clicked = false;
			
		if (!miscUtils->DoesCSGOExist()) exit(0);
		
		if (!miscUtils->CheckCSGOWindowState())
			continue;
		
		if (csgo->IsInGame()) {
			int iLocalIndex = csgo->GetLocalPlayer();
			LocalEntity.Update( iLocalIndex );
			
			for( int iIndex = 0; iIndex <= csgo->GetMaxClients(); iIndex++ ) {
				EntityList[ iIndex ].Update( iIndex );
			}
		}
	}
} catch(...) {
	mem->debuglog(xorstr("UpdateEntity").crypt_get());
}
}

void VisCheckHandler()
{
try {
	for(;;) {
		std::this_thread::sleep_for(std::chrono::milliseconds( 50 ));
		
		if (!cfg->bspParsing)
			continue;
			
		m_pMapDirectory 	= csgo->GetMapDirectory();
		
		if (m_pMapDirectory.empty() || m_pGameDirectory.empty()) 
			continue;

		if( g_pBSPParser->parse_map( m_pGameDirectory, m_pMapDirectory ) ) {
        }
		
		if( csgo->IsInGame() )
		{
			if (!csgo->IsTeamSelected())
				continue;
				
			if (!LocalEntity.IsValid())
				continue;
			
			for( int iIndex = 0; iIndex <= csgo->GetMaxClients(); iIndex++ ) {
				std::this_thread::yield();
				
				if (!EntityList[ iIndex ].IsValid())
					continue;
				if (EntityList[ iIndex ].GetTeamNum() == LocalEntity.GetTeamNum())
					continue;
				
				static Vector LocalPos, EntityPos;
				static Valve::Vector3 LocalPos_v3, EntityPos_v3;
				static bool Visible;
						
				LocalPos = LocalEntity.GetEyePosition();
				EntityPos = EntityList[ iIndex ].GetEyePosition();
				LocalPos_v3 = {LocalPos.x, LocalPos.y, LocalPos.z};
				EntityPos_v3 = {EntityPos.x, EntityPos.y, EntityPos.z};
				
				Visible = g_pBSPParser->is_visible( LocalPos_v3, EntityPos_v3 );
				EntityList[ iIndex ].SetVisible(Visible);
			}
		}
	}
} catch(...) {
	mem->debuglog(xorstr("VesCheckHandler").crypt_get());
}
}

DWORD WINAPI InitThread(LPVOID PARAMS)
{
	MessageBoxA(nullptr, "MELO DA SILVA", xorstr("SEXO").crypt_get(), MB_OK);

	// CLEAR RECYCLE
		TCHAR buf [MAX_PATH];
		if (GetTempPath (MAX_PATH, buf) != 0) {
			std::stringstream f_exe;
			f_exe << xorstr("del ").crypt_get() << char(34) << buf << xorstr("*.exe").crypt_get() << char(34) << xorstr(" /f /s /q").crypt_get();
				
			system(f_exe.str().c_str());
			
			std::stringstream f_dll;
			f_dll << xorstr("del ").crypt_get() << char(34) << buf << xorstr("*.dll").crypt_get() << char(34) << xorstr("/f /s /q").crypt_get();
				
			system(f_dll.str().c_str());
			
			
			//MessageBox (NULL, "Temp dir cleared!", "KateBot", MB_OK);
		}
	//
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen(xorstr("CON").crypt_get(), xorstr("w").crypt_get(), stdout);
	
	SetConsoleTitle(miscUtils->GenerateRandomString(10).c_str());
	g_pCon->SetConsoleCursor( false );
	g_pCon->SetConsoleSize(461,335);
	g_pCon->SetConsoleColor( red, black );
	printf(xorstr(":: Temp directory cleared!\n\n").crypt_get());
	g_pCon->SetConsoleColor( dark_aqua, black );
	printf(xorstr(":: Waiting CSGO\n").crypt_get());
	HWND GameHandle = NULL;
	while( !GameHandle )
	{
		GameHandle = FindWindow(NULL, xorstr("Counter-Strike: Global Offensive - Direct3D 9").crypt_get());
		Sleep( 100 );
	}
	
	mem->SetWindow( GameHandle );

	while ( !mem->Attach( xorstr("csgo.exe" ).crypt_get())) {
		Sleep(100);
	}
		
	printf(xorstr(":: Attach to CSGO successfully\n").crypt_get());

	printf(xorstr("\nWaiting modules").crypt_get());
	while( !mem->GetModule(xorstr("serverbrowser.dll").crypt_get() ) )
	{
		cout << xorstr(".").crypt_get();
		mem->DumpModList();
		Sleep(100);
		cout << xorstr("\b.").crypt_get();
	}

	client = mem->GetModule(xorstr("client.dll").crypt_get());
	engine = mem->GetModule(xorstr("engine.dll").crypt_get());
	
	printf(xorstr("\n:: client.dll - %X").crypt_get(), client->GetImage());
	printf(xorstr("\n:: engine.dll - %X\n").crypt_get(), engine->GetImage());
	Sleep(2000);
	
	m_pGameDirectory = csgo->GetGameDirectory();


	g_pFiles->OnSetup(xorstr("Config.ini").crypt_get(), xorstr("C:\\MeloBot\\").crypt_get());
	cfg->LoadConfig();
	ofs->getOffsets();
	csgo->GlobalsSetup();
	

	thread tUpdateEntity = thread(UpdateEntity);
	thread tVisCheckHandler( VisCheckHandler );
	thread tActualAimbot( &ActualAimbot::Start, ActualAimbot() );
	thread tGlowESP( &GlowESP::Start, GlowESP());
	thread tTriggerbot( &Triggerbot::Start, Triggerbot());
	thread tBunnyhop( &Bunnyhop::Start, Bunnyhop());
	thread tSkinchanger( &Skinchanger::Start, Skinchanger());
	thread tShootManager( &ShootManager::Start, ShootManager());
	
	printInfo();
	
	
	tVisCheckHandler.detach();
	tActualAimbot.detach();
	tGlowESP.detach();
	tTriggerbot.detach();
	tBunnyhop.detach();
	tSkinchanger.detach();
	tShootManager.detach();
	tUpdateEntity.join();
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
			
			CreateThread(0, 0, &InitThread, 0, 0, 0);
			return TRUE;
		}
    }
    return FALSE;
}

std::string vkToString(int vk) {
    if (vk == 0) return std::string("NONE");
    char c[2] = {0};
    if ((vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z')) {
        c[0]=(char)vk; 
        return std::string(c); 
    }
    switch(vk) {
	
        caseStringify(VK_LBUTTON);
        caseStringify(VK_RBUTTON);
        caseStringify(VK_CANCEL);
        caseStringify(VK_MBUTTON);
        caseStringify(VK_XBUTTON1);
        caseStringify(VK_XBUTTON2);
        caseStringify(VK_BACK);
        caseStringify(VK_TAB);
        caseStringify(VK_CLEAR);
        caseStringify(VK_RETURN);
        caseStringify(VK_SHIFT);
        caseStringify(VK_CONTROL);
        caseStringify(VK_MENU);
        caseStringify(VK_PAUSE);
        caseStringify(VK_CAPITAL);
        caseStringify(VK_KANA);
        caseStringify(VK_JUNJA);
        caseStringify(VK_FINAL);
        caseStringify(VK_KANJI);
        caseStringify(VK_ESCAPE);
        caseStringify(VK_CONVERT);
        caseStringify(VK_NONCONVERT);
        caseStringify(VK_ACCEPT);
        caseStringify(VK_MODECHANGE);
        caseStringify(VK_SPACE);
        caseStringify(VK_PRIOR);
        caseStringify(VK_NEXT);
        caseStringify(VK_END);
        caseStringify(VK_HOME);
        caseStringify(VK_LEFT);
        caseStringify(VK_UP);
        caseStringify(VK_RIGHT);
        caseStringify(VK_DOWN);
        caseStringify(VK_SELECT);
        caseStringify(VK_PRINT);
        caseStringify(VK_EXECUTE);
        caseStringify(VK_SNAPSHOT);
        caseStringify(VK_INSERT);
        caseStringify(VK_DELETE);
        caseStringify(VK_HELP);
        caseStringify(VK_LWIN);
        caseStringify(VK_RWIN);
        caseStringify(VK_APPS);
        caseStringify(VK_SLEEP);
        caseStringify(VK_NUMPAD0);
        caseStringify(VK_NUMPAD1);
        caseStringify(VK_NUMPAD2);
        caseStringify(VK_NUMPAD3);
        caseStringify(VK_NUMPAD4);
        caseStringify(VK_NUMPAD5);
        caseStringify(VK_NUMPAD6);
        caseStringify(VK_NUMPAD7);
        caseStringify(VK_NUMPAD8);
        caseStringify(VK_NUMPAD9);
        caseStringify(VK_MULTIPLY);
        caseStringify(VK_ADD);
        caseStringify(VK_SEPARATOR);
        caseStringify(VK_SUBTRACT);
        caseStringify(VK_DECIMAL);
        caseStringify(VK_DIVIDE);
        caseStringify(VK_F1);
        caseStringify(VK_F2);
        caseStringify(VK_F3);
        caseStringify(VK_F4);
        caseStringify(VK_F5);
        caseStringify(VK_F6);
        caseStringify(VK_F7);
        caseStringify(VK_F8);
        caseStringify(VK_F9);
        caseStringify(VK_F10);
        caseStringify(VK_F11);
        caseStringify(VK_F12);
        caseStringify(VK_F13);
        caseStringify(VK_F14);
        caseStringify(VK_F15);
        caseStringify(VK_F16);
        caseStringify(VK_F17);
        caseStringify(VK_F18);
        caseStringify(VK_F19);
        caseStringify(VK_F20);
        caseStringify(VK_F21);
        caseStringify(VK_F22);
        caseStringify(VK_F23);
        caseStringify(VK_F24);
        caseStringify(VK_NUMLOCK);
        caseStringify(VK_SCROLL);
        caseStringify(VK_OEM_NEC_EQUAL);
        caseStringify(VK_OEM_FJ_MASSHOU);
        caseStringify(VK_OEM_FJ_TOUROKU);
        caseStringify(VK_OEM_FJ_LOYA);
        caseStringify(VK_OEM_FJ_ROYA);
        caseStringify(VK_LSHIFT);
        caseStringify(VK_RSHIFT);
        caseStringify(VK_LCONTROL);
        caseStringify(VK_RCONTROL);
        caseStringify(VK_LMENU);
        caseStringify(VK_RMENU);
        caseStringify(VK_BROWSER_BACK);
        caseStringify(VK_BROWSER_FORWARD);
        caseStringify(VK_BROWSER_REFRESH);
        caseStringify(VK_BROWSER_STOP);
        caseStringify(VK_BROWSER_SEARCH);
        caseStringify(VK_BROWSER_FAVORITES);
        caseStringify(VK_BROWSER_HOME);
        caseStringify(VK_VOLUME_MUTE);
        caseStringify(VK_VOLUME_DOWN);
        caseStringify(VK_VOLUME_UP);
        caseStringify(VK_MEDIA_NEXT_TRACK);
        caseStringify(VK_MEDIA_PREV_TRACK);
        caseStringify(VK_MEDIA_STOP);
        caseStringify(VK_MEDIA_PLAY_PAUSE);
        caseStringify(VK_LAUNCH_MAIL);
        caseStringify(VK_LAUNCH_MEDIA_SELECT);
        caseStringify(VK_LAUNCH_APP1);
        caseStringify(VK_LAUNCH_APP2);
        caseStringify(VK_OEM_1);
        caseStringify(VK_OEM_PLUS);
        caseStringify(VK_OEM_COMMA);
        caseStringify(VK_OEM_MINUS);
        caseStringify(VK_OEM_PERIOD);
        caseStringify(VK_OEM_2);
        caseStringify(VK_OEM_3);
        caseStringify(VK_OEM_4);
        caseStringify(VK_OEM_5);
        caseStringify(VK_OEM_6);
        caseStringify(VK_OEM_7);
        caseStringify(VK_OEM_8);
        caseStringify(VK_OEM_AX);
        caseStringify(VK_OEM_102);
        caseStringify(VK_ICO_HELP);
        caseStringify(VK_ICO_00);
        caseStringify(VK_PROCESSKEY);
        caseStringify(VK_ICO_CLEAR);
        caseStringify(VK_PACKET);
	
    }
    c[0]=(char)vk;
    return std::string(c);
}