#pragma once

#define targetLib OBFUSCATE("libil2cpp.so")
uintptr_t il2cppMap;



enum COM_PLAYERCAMP {
 ComPlayercampMid = 0,
 ComPlayercamp1 = 1,
 ComPlayercamp2 = 2,
 ComPlayercamp3 = 3,
 ComPlayercamp4 = 4,
 ComPlayercamp5 = 5,
 ComPlayercamp6 = 6,
 ComPlayercamp7 = 7,
 ComPlayercamp8 = 8,
 ComPlayercampCount = 9,
 ComPlayercampOb = 10,
 ComPlayercampInvalid = 254,
 ComPlayercampAll = 255
};


struct sConfig {
	struct sInitImGui {
		bool initImGui;
		bool bInitDone;
	};
	
	sInitImGui InitImGui;
	
    struct sEsp {
        
        bool Enable_ESP;
        bool PlayerLine;
        bool PlayerBox;
        bool PlayerHealth;
        bool PlayerName;
        bool HeroName;
        bool PlayerDistance;
        bool PlayerAlert;
        bool PlayerCd;
        bool IgnoreInvisible;
        bool IgnoreVisible;
        
    };
    
    sEsp ESPMenu;
    
    
    struct sWideView{
        
        float GetFieldOfView = 0;
        float SetFieldOfView = 0;
        bool Active = false;
        
    };
    
    sWideView WideView;
    
    struct sColor {
        
        float line[4] = {45 / 255.0f, 180 / 255.0f, 45 / 255.0f, 255 / 255.0f};
        float box[4] = {45 / 255.0f, 180 / 255.0f, 45 / 255.0f, 255 / 255.0f};
        
    };
    
    sColor Color;
    
	struct sFeat {
		bool HackMap;
		bool CamBaNac;
		bool CamChat;
		bool CamChon;
		bool Unti_Hp_Icon;
		bool ModSkin;
		bool AimSkill;
		int Radius = 0;
		bool AutoTrung;
        int skillSlot;
        bool aimSkill1;
        bool aimSkill2;
        bool aimSkill3;
        bool avatar;
        bool banpick;
        bool showCd;
        bool ultimate;
        bool IsAutoWin;
        bool noCd;
	};
	sFeat FEATMenu;
	
	struct sOther {
		
		std::string config_filename = "config_menu.ini";
	};
	sOther Other;
};

sConfig Config{0};



