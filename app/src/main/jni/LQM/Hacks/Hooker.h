#pragma once

#include <iostream>
#include <sstream>
#include <string>

bool (*_IsSmartUse)(void *instance);
bool (*_get_IsUseCameraMoveWithIndicator)(void *instance);

bool IsSmartUse(void *instance){
    
    bool aim = false;
    
    if(Config.FEATMenu.skillSlot == 1 && Config.FEATMenu.aimSkill1){
        aim = true;
    }
    
    if(Config.FEATMenu.skillSlot == 2 && Config.FEATMenu.aimSkill2){
        aim = true;
    }
    
    if(Config.FEATMenu.skillSlot == 3 && Config.FEATMenu.aimSkill3){
        aim = true;
    }
    
    if(Config.FEATMenu.AutoTrung && aim){
        return true;
    }
    
    return _IsSmartUse(instance);
}


bool get_IsUseCameraMoveWithIndicator(void *instance){
    
    bool aim = false;
    
    if(Config.FEATMenu.skillSlot == 1 && Config.FEATMenu.aimSkill1){
        aim = true;
    }
    
    if(Config.FEATMenu.skillSlot == 2 && Config.FEATMenu.aimSkill2){
        aim = true;
    }
    
    if(Config.FEATMenu.skillSlot == 3 && Config.FEATMenu.aimSkill3){
        aim = true;
    }
    
    
    if(Config.FEATMenu.AutoTrung && aim){
        return true;
    }
    
    return _get_IsUseCameraMoveWithIndicator(instance);
}


bool (*_IsUseSkillJoystick)(...);
bool IsUseSkillJoystick(void *instance, int slot){
    Config.FEATMenu.skillSlot = slot;
    return _IsUseSkillJoystick(instance, slot);
}

void (*_LActorRoot_Visible)(...);
void LActorRoot_Visible(void *instance, int camp, bool bVisible, const bool forceSync = false) {
    if (instance != nullptr && Config.FEATMenu.HackMap) {
        if(camp == 1 || camp == 2 || camp == 110 || camp == 255) {
            bVisible = true;
        }
    } 
 return _LActorRoot_Visible(instance, camp, bVisible, forceSync);
}

float (*old_GetCameraHeightRateValue)(void *instance, int *type);
float GetCameraHeightRateValue(void *instance, int *type) {
	if (instance != NULL) {
		Config.WideView.GetFieldOfView = old_GetCameraHeightRateValue(instance, type);
		if (Config.WideView.SetFieldOfView != 0) {
			return (float) Config.WideView.SetFieldOfView + Config.WideView.GetFieldOfView;
		}
		return Config.WideView.GetFieldOfView;
	}
	return old_GetCameraHeightRateValue(instance, type);
}

void (*OnCameraHeightChanged)(void *instance);
void (*old_CameraSystemUpdate)(void *instance);
void CameraSystemUpdate(void *instance) {
	if (instance != NULL && Config.WideView.Active) {
		OnCameraHeightChanged(instance);
	}
	old_CameraSystemUpdate(instance);
}



// Tên Cấm Chọn //

void *(*_InitTeamHeroList)(void* instance, void *listScript, int camp, bool isLeftList, bool isMidPos);
void *InitTeamHeroList(void* instance, void *listScript, int camp, bool isLeftList = true, bool isMidPos = false) {
 if (instance && Config.FEATMenu.banpick) {
      isLeftList = true;
 }
 return _InitTeamHeroList(instance, listScript, camp, isLeftList, isMidPos);

 }
 


bool ShowInfHero;
void (*_ShowSkillStateInfo)(void *instance, bool bShow);
void ShowSkillStateInfo(void *instance, bool bShow) {
    if (instance != NULL && Config.FEATMenu.ultimate) {
      bShow = true;
    }
    _ShowSkillStateInfo(instance, bShow);

}


   // Hiện Icon
bool ShowIcon;
void (*_ShowHeroInfo)(void *instance,int actor, bool bShow);
void ShowHeroInfo(void *instance, int actor,bool bShow) {
    if (instance != NULL && Config.FEATMenu.ultimate) {
      bShow = true;
    } 
    _ShowHeroInfo(instance,actor, bShow);
}
 //Hiện máu //
bool ShowHP;
void (*_ShowHeroHpInfo)(void *instance, bool bShow);
void ShowHeroHpInfo(void *instance, bool bShow) {
    if (instance != NULL && Config.FEATMenu.ultimate) {
      bShow = true;
    } 
    _ShowHeroHpInfo(instance, bShow);
}


void (*old_IsDistanceLowerEqualAsAttacker)(void *instance, int targetActor, int radius);
void IsDistanceLowerEqualAsAttacker(void *instance, int targetActor, int radius) {
    
    bool aim = false;
    
    if(Config.FEATMenu.skillSlot == 1 && Config.FEATMenu.aimSkill1){
        aim = true;
    }
    
    if(Config.FEATMenu.skillSlot == 2 && Config.FEATMenu.aimSkill2){
        aim = true;
    }
    
    if(Config.FEATMenu.skillSlot == 3 && Config.FEATMenu.aimSkill3){
        aim = true;
    }
    
    
    if (instance != NULL && Config.FEATMenu.AimSkill && aim) {
        radius = Config.FEATMenu.Radius * 1000;
    }
    old_IsDistanceLowerEqualAsAttacker(instance, targetActor, radius);
}

 /////Lịch sử đấu////
bool LSD;
bool (*_IsHostProfile)(void *instance);
bool IsHostProfile(void *instance) {
    if (instance != NULL) 
	{
        return true;
    }
    return _IsHostProfile(instance);

}

 //show Avatar
 bool IsShowAvatar;
int (*_checkTeamLaderGradeMax)(void *instance, int MapType);
int checkTeamLaderGradeMax(void *instance, int MapType) {
 if (instance && Config.FEATMenu.avatar) 
	 {
  		return 0;
 	}
 return _checkTeamLaderGradeMax(instance, MapType);
}


const bool (*_get_Supported60FPSMode)(void *instance);
const bool get_Supported60FPSMode(void *instance) {
    if (instance != NULL) { 
        return true;
    } 
}

const bool (*_get_SupportedBoth60FPS_CameraHeight)(void *instance);
const bool get_SupportedBoth60FPS_CameraHeight(void *instance) {
    if (instance != NULL) {
        return true;
    } 
}

const bool (*_IsIPadDevice)(void *instance);
const bool IsIPadDevice(void *instance) {
    if (instance != NULL) {
        return true;
    }
}


bool (*_IsCanUseSkin)(...);
bool IsCanUseSkin(void *instance, int heroid, int skinid){
    
    return true;
}

void (*_onAddHeroSkinNty)(...);
void onAddHeroSkinNty(void *instance, void *msg){
    
    
    return;
}

void (*_SettlementHelper_SetPlayerName)(...);
void SettlementHelper_SetPlayerName(void *instance, String *playerName, bool isHostPlayer){
    
    if(instance){
        
        String *fake = Il2CppString::Create("Youtube-Minaov");
    
        _SettlementHelper_SetPlayerName(instance, fake, isHostPlayer);
        
    }
    
}



void (*_ShowChatMsg)(...);
void ShowChatMsg(void *instance,int type, int uid, int heroid, String *content, int target, int thumbsUpCount, int style, int intimacyLevel){
    
    
    if(instance){
        
    std::istringstream iss(content->CString());

    std::string command;
    std::vector<std::string> arguments;

    // Extract the command
    iss >> command;

    // Extract the arguments
    std::string arg;
    while (iss >> arg) {
        arguments.push_back(arg);
    }
    
    if(command == "hm"){
        
        if(arguments[0] == "on"){
            
            content = Il2CppString::Create("HACK MAP BẬT");
            
            Config.FEATMenu.HackMap = true;
            
        }else if (arguments[0] == "off"){
            
            Config.FEATMenu.HackMap = false;
            
            content = Il2CppString::Create("HACK MAP TẲT");
        }
        
    }else if(command == "st"){
        
        if(arguments[0] == "on"){
            
            Config.FEATMenu.showCd = true;
            
            content = Il2CppString::Create("HIỆN HỒI CHIÊU BẬT");
            
            
        }else if (arguments[0] == "off"){
            
            Config.FEATMenu.showCd = false;
            
            content = Il2CppString::Create("HIỆN HỒI CHIÊU TẲT");
        }
        
    }
    
    content = Il2CppString::Create("ABCXYZ");
    return _ShowChatMsg(instance, type, uid, heroid, content, target, thumbsUpCount, style, intimacyLevel);
    
    
    }
    
}
