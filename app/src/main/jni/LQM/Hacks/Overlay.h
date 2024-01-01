#pragma once
#include <map>
ESPManager *espManager;
ESPManager *ActorLinker_enemy;
Array<void *> *m_MiniMapHeroInfos;

std::map<void *, void *> player_mini;


void *hack_thread(void *);

void (*OpenURL)(String *url);

VInt3 (*LActorRoot_get_location)(void *instance);
VInt3 (*LActorRoot_get_forward)(void *instance);
uintptr_t (*LActorRoot_LHeroWrapper)(void *instance);
int (*LActorRoot_COM_PLAYERCAMP)(void *instance);
bool (*LActorRoot_get_bActive)(void *instance);
int (*LActorRoot_get_ObjID)(void *instance);
bool (*LObjWrapper_get_IsDeadState)(void *instance);
bool (*LObjWrapper_IsAutoAI)(void *instance);
int (*ValuePropertyComponent_get_actorHp)(void *instance);
int (*ValuePropertyComponent_get_actorHpTotal)(void *instance);
void* (*ValuePropertyComponent_BaseEnergyLogic)(void *instance);

int (*ActorLinker_COM_PLAYERCAMP)(void *instance);
bool (*ActorLinker_IsHostPlayer)(void *instance);
bool (*ActorLinker_IsHostCamp)(void *instance);
int (*ActorLinker_ActorTypeDef)(void *instance);
Vector3 (*ActorLinker_getPosition)(void *instance);
bool (*ActorLinker_get_HPBarVisible)(void *instance);
int (*ActorLinker_get_ObjID)(void *instance);
bool (*ActorLinker_get_bVisible)(void *instance);
uintptr_t (*AsHero)(...);
void (*_SetPlayerName)(...);

int (*MiniMapHeroInfo_get_ObjID)(void *instance);

void (*MiniMapHeroInfo_Show)(void *instance, bool show);


void (*UpdatePosInMiniMap)(void *instance, Vector3 actopos);

int mimapi = 0;
void (*ShowWinLose)(void *instance, bool bWin);

void (*old_ActorLinker_ActorDestroy)(void *instance);
void ActorLinker_ActorDestroy(void *instance) {
    if (instance != NULL) {
        old_ActorLinker_ActorDestroy(instance);
		ActorLinker_enemy->removeEnemyGivenObject(instance);
        if (espManager->MyPlayer==instance){
            espManager->MyPlayer=NULL;
        }
    }
}

void (*old_LActorRoot_ActorDestroy)(void *instance,bool bTriggerEvent);
void LActorRoot_ActorDestroy(void *instance, bool bTriggerEvent) {
    if (instance != NULL) {
        old_LActorRoot_ActorDestroy(instance, bTriggerEvent);
        espManager->removeEnemyGivenObject(instance);
        
    }
}
void (*ByPassEsp)(void *player);
void ByPassesp(void *player) {
    if(player != NULL) {
        return;
    }
    ByPassEsp(player);
}


void (*old_ActorLinker_Update)(void *instance);
void ActorLinker_Update(void *instance) {
    if (instance != NULL) {
		
        
        uintptr_t SkillControl = AsHero(instance);
        uintptr_t HudControl = *(int *) ((uintptr_t)instance + 0x3c);
        if (HudControl > 0 && SkillControl > 0) {
            uintptr_t Skill1Cd = *(int *) (SkillControl + 0x28) / 1000;
            uintptr_t Skill2Cd = *(int *) (SkillControl + 0x40) / 1000;
            uintptr_t Skill3Cd = *(int *) (SkillControl + 0x58) / 1000;
            uintptr_t Skill4Cd = *(int *) (SkillControl + 0x88) / 1000;
            string openSk = "(";
            string closeSk = ") ";
            string sk1 = to_string(Skill1Cd);
            string sk2 = to_string(Skill2Cd);
            string sk3 = to_string(Skill3Cd);
            string sk4 = to_string(Skill4Cd);
            string ShowSkill = openSk + sk1 + closeSk + openSk + sk2 + closeSk + openSk + sk3 + closeSk;
            string ShowSkill2 = openSk + sk4 + closeSk;
            const char *str1 = ShowSkill.c_str();
            const char *str2 = ShowSkill2.c_str();
            if (Config.FEATMenu.showCd) {
                String *playerName = Il2CppString::Create(str1);
                String *prefixName = Il2CppString::Create(str2);
                _SetPlayerName(HudControl, playerName, prefixName, true);
            } else {
                String *playerName = Il2CppString::Create("MinAov");
                String *prefixName = Il2CppString::Create("Youtube-");
                _SetPlayerName(HudControl, playerName, prefixName, true);
            }
        }
        
        
        old_ActorLinker_Update(instance);
        if (ActorLinker_ActorTypeDef(instance)==0){
			
            if (ActorLinker_IsHostPlayer(instance)==true){
                espManager->tryAddMyPlayer(instance);
            } else {
				
				if(espManager->MyPlayer != NULL){
					if(ActorLinker_COM_PLAYERCAMP(espManager->MyPlayer) != ActorLinker_COM_PLAYERCAMP(instance)){
                        
						ActorLinker_enemy->tryAddEnemy(instance);
					}
				}
			}
        }
    }
}

void (*old_LActorRoot_UpdateLogic)(void *instance, int delta);
void LActorRoot_UpdateLogic(void *instance, int delta) {
    if (instance != NULL) {
        old_LActorRoot_UpdateLogic(instance, delta);
       // int id2 = ActorLinker_get_actorHpTotal1(instance);
        // LOGD(OBFUSCATE("id1: %d"),id2);
        if (espManager->MyPlayer!=NULL)
            if (LActorRoot_LHeroWrapper(instance)!=NULL && LActorRoot_COM_PLAYERCAMP(instance) == ActorLinker_COM_PLAYERCAMP(espManager->MyPlayer)) {
				
				espManager->tryAddEnemy(instance);
			}
    }
}


void (*HeroInfoPanel_Update)(...);
void _HeroInfoPanel_Update(void *instance){
    
    
    m_MiniMapHeroInfos = *(Array<void *> **) ((uintptr_t) instance + IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("HeroInfoPanel"), OBFUSCATE("m_MiniMapHeroInfos")));

    return HeroInfoPanel_Update(instance);
    
}

bool isOutsideScreen(ImVec2 pos, ImVec2 screen) {
    if (pos.y < 0) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 0;
}

ImVec2 pushToScreenBorder(ImVec2 Pos, ImVec2 screen, int offset) {
    int x = (int) Pos.x;
    int y = (int) Pos.y;
	
    if (Pos.y < 0) {
        y = -offset;
    }
	
    if (Pos.x > screen.x) {
        x = (int) screen.x + offset;
    }
	
    if (Pos.y > screen.y) {
        y = (int) screen.y + offset;
    }
	
    if (Pos.x < 0) {
        x = -offset;
    }
    return ImVec2(x, y);
}

void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}



int dem(int num){
    int div=1, num1 = num;
    while (num1!=0){
        num1=num1/10;
        div=div*10;
    }
    return div;
}

Vector3 VInt2Vector(VInt3 location, VInt3 forward){
    return Vector3((float)(location.X*dem(forward.X)+forward.X)/(1000*dem(forward.X)), (float)(location.Y*dem(forward.Y)+forward.Y)/(1000*dem(forward.Y)), (float)(location.Z*dem(forward.Z)+forward.Z)/(1000*dem(forward.Z)));
}


int countEnemy = 0;


void base642name(std::string nameP, std::string &heroname, int HudHeight){	

	if(nameP == ""){
		heroname = "Ata";
		return;
	}
	if(nameP == "MTU3X0J1WmhpSHVvV3U=") {	
		heroname = "Raz";	
		return;	
	}	
	if(nameP == "NTAzX1p1a2E=") {	
		heroname = "Zuka";	
		return;	
	}	
	if(nameP == "5p2O55m9") {	
		heroname = "Murad";	
		return;	
	}	
	if(nameP == "6I2G6L2y") {	
		heroname = "Butterfly";	
		return;	
	}	
	if(nameP == "5pu55pON") {	
		heroname = "Lữ Bố";	
		return;	
	}	
	if(nameP == "MTEyX0dvbmdTaHVCYW4=") {	
		heroname = "Yorn";	
		return;	
	}	
	if(nameP == "NTIxX0Zsb3JlbnRpbm8=") {	
		heroname = "Florentino";	
		return;	
	}	
	if(nameP == "5qKF5p6X") {	
		heroname = "Natalia";	
		return;	
	}	
	if(nameP == "5Lqa55Gf546L") {	
		heroname = "Athur";	
		return;	
	}	
	if(nameP == "54uE5LuB5p2w") {	
		heroname = "Valhein";	
		return;	
	}	
	if(nameP == "6Z+p5L+h") {	
		heroname = "Nakroth";	
		return;	
	}	
	if(nameP == "IOWFuOmfpg==") {	
		heroname = "Triệu vân";	
		return;	
	}	
	if(nameP == "5aKo57+f") {	
		heroname = "Gildur";	
		return;	
	}	
	if(nameP == "6I6J6I6J5a6J") {	
		heroname = "Liliana";	
		return;	
	}	
	if(nameP == "6K+46JGb5Lqu") {	
		heroname = "Tulen";	
		return;	
	}	
	if(nameP == "5a2U5aSr5a2Q" && HudHeight > 2000000000) {	
		heroname = "Kil'Groth";	
		return;	
	}	
	if(nameP == "MTY3X1d1S29uZw==") {	
		heroname = "Ngộ Không";	
		return;	
	}	
	if(nameP == "6ZKf6aaX") {	
		heroname = "Grakk";	
		return;	
	}	
	if(nameP == "5ZSQ5LiJ6JeP") {	
		heroname = "Skud";	
		return;	
	}	
	if(nameP == "5Z+D572X") {	
		heroname = "Errol";	
		return;	
	}	
	if(nameP == "NTI0X0NhcGhlbnk=") {	
		heroname = "Capheny";	
		return;	
	}	
	if(nameP == "5Yi5") {	
		heroname = "Zata";	
		return;	
	}	
	if(nameP == "5a2U5aSr5a2Q") {	
		heroname = "Omen";	
		return;	
	}	
	if(nameP == "5a2Z5bCa6aaZ") {	
		heroname = "Violet";	
		return;	
	}	
	if(nameP == "5omB6bmK") {	
		heroname = "Mganga";	
		return;	
	}	
	if(nameP == "VmVyZXM=") {	
		heroname = "Veres";	
		return;	
	}	
	if(nameP == "54m55bCU5a6J5aic5pav") {	
		heroname = "Tel'Annas";	
		return;	
	}	
	if(nameP == "TmFrb3J1cnU=") {	
		heroname = "Kriknak";	
		return;	
	}	
	if(nameP == "55m+6YeM5a6I57qm") {	
		heroname = "Elsu";	
		return;	
	}	
	if(nameP == "MTE3X1pob25nV3VZYW4=") {	
		heroname = "Ormarr";	
		return;	
	}	
	if(nameP == "6Jme5aes") {	
		heroname = "Joker";	
		return;	
	}	
	if(nameP == "6LW15LqR") {	
		heroname = "Zephys";	
		return;	
	}	
	if(nameP == "5Lqa6L+e") {	
		heroname = "Allain";	
		return;	
	}	
	if(nameP == "5a6r5pys5q2m6JeP") {	
		heroname = "Airi";	
		return;	
	}	
	if(nameP == "6ams5Y+v5rOi572X") {	
		heroname = "Hayate";	
		return;	
	}	
	if(nameP == "MTA5X0Rhamk=") {	
		heroname = "Veera";	
		return;	
	}	
	if(nameP == "5bCP5LmU") {	
		heroname = "Krixi";	
		return;	
	}	
	if(nameP == "5aWO5Lym") {	
		heroname = "Quillen";	
		return;	
	}	
	if(nameP == "5YiY5aSH") {	
		heroname = "Rourke";	
		return;	
	}	
	if(nameP == "56iL5ZKs6YeR") {	
		heroname = "Tara";	
		return;	
	}	
	if(nameP == "57qi5ouC") {	
		heroname = "Zill";	
		return;	
	}	
	if(nameP == "5Y+46ams5oe/") {	
		heroname = "Paine";	
		return;	
	}	
	if(nameP == "5buJ6aKH") {	
		heroname = "Toro";	
		return;	
	}	
	if(nameP == "5ZOq5ZCS") {	
		heroname = "Max";	
		return;	
	}	
	if(nameP == "NTMzX0hvdVlp") {	
		heroname = "Laville";	
		return;	
	}	
	if(nameP == "NTMwX0RpcmFr") {	
		heroname = "Dirak";	
		return;	
	}	
	if(nameP == "NTA3X0ZsYXNo") {	
		heroname = "The Flash";	
		return;	
	}	
	if(nameP == "SnVZb3VKaW5n") {	
		heroname = "Ryoma";	
		return;	
	}	
	if(nameP == "5p2O5YWD6Iqz") {	
		heroname = "Fennik";	
		return;	
	}	
	if(nameP == "54K45by55Lq6") {	
		heroname = "Wisp";	
		return;	
	}	
	if(nameP == "5ay05pS/") {	
		heroname = "Kahlii";	
		return;	
	}	
	if(nameP == "5Lic55qH5aSq5LiA") {	
		heroname = "Arum";	
		return;	
	}	
	if(nameP == "U3VuQ2U=") {	
		heroname = "Bijan";	
		return;	
	}	
	if(nameP == "R2VuaXVz") {	
		heroname = "Thorne";	
		return;	
	}	
	if(nameP == "55m+6YeM546E562W") {	
		heroname = "Enzo";	
		return;	
	}	
	if(nameP == "5byg6Imv") {	
		heroname = "Aleister";	
		return;	
	}	
	if(nameP == "MTQxX0RpYW9DaGFu") {	
		heroname = "Lauriel";	
		return;	
	}	
	if(nameP == "MTUyX1dhbmdaaGFvSnVu") {	
		heroname = "Điêu Thuyền";	
		return;	
	}	
	if(nameP == "5YiY5aSH") {	
		heroname = "Moren";	
		return;	
	}	
	if(nameP == "MTU0X0h1YU11TGFu") {	
		heroname = "Yenna";	
		return;	
	}	
	if(nameP == "MTk5X0xp") {	
		heroname = "Eland'orr";	
		return;	
	}	
	if(nameP == "TmluamE=") {	
		heroname = "Aoi";	
		return;	
	}	
	if(nameP == "57uu6JCd") {	
		heroname = "Keera";	
		return;	
	}	
	if(nameP == "5ZCV5biD") {	
		heroname = "Maloch";	
		return;	
	}	
	if(nameP == "56We5aWH5aWz5L6g") {	
		heroname = "Wonder Woman";	
		return;	
	}	
	if(nameP == "5ZCO576/") {	
		heroname = "Slimz";	
		return;	
	}	
	if(nameP == "MTE4X1N1bkJpbg==") {	
		heroname = "Alice";	
		return;	
	}	
	if(nameP == "5pyX5Y2a") {	
		heroname = "Lumburr";	
		return;	
	}	
	if(nameP == "MTIwX0JhaVFp") {	
		heroname = "Mina";	
		return;	
	}	
	if(nameP == "QWlt") {	
		heroname = "Yue";	
		return;	
	}	
	if(nameP == "6Iul5LyK") {	
		heroname = "Rouie";	
		return;	
	}	
	if(nameP == "NTQwMV9CcmlnaHQ=") {	
		heroname = "Bright";	
		return;	
	}	
	if(nameP == "MTc3X0NoZW5nSmlTaUhhbg==") {	
		heroname = "Lindis";	
		return;	
	}	
	if(nameP == "6auY5riQ56a7") {	
		heroname = "Jinna";	
		return;	
	}	
	if(nameP == "6buE5b+g") {	
		heroname = "Celica";	
		return;	
	}	
	if(nameP == "5qyn57Gz6IyE") {	
		heroname = "Omega";	
		return;	
	}	
	if(nameP == "R2VuaXVz") {	
		heroname = "Bonnie";	
		return;	
	}	
	if(nameP == "5YiY6YKm") {	
		heroname = "Xenniel";	
		return;	
	}	
	if(nameP == "6JSh5paH5aes") {	
		heroname = "Helen";	
		return;	
	}	
	if(nameP == "5aSP5L6v5oOH") {	
		heroname = "Arduin";	
		return;	
	}	
	if(nameP == "55SE5aes") {	
		heroname = "Azzen'ka";	
		return;	
	}	
	if(nameP == "55qu55qu") {	
		heroname = "Zip";	
		return;	
	}	
	if(nameP == "562x5riF") {	
		heroname = "Qi";	
		return;	
	}	
	if(nameP == "5a6J5qC85YiX") {	
		heroname = "Volkath";	
		return;	
	}	
	if(nameP == "MTQwX0d1YW5ZdQ==") {	
		heroname = "Supper Man";	
		return;	
	}	
	if(nameP == "MTQ4X0ppYW5nWmlZYQ==") {	
		heroname = "Preyta";	
		return;	
	}	
	if(nameP == "MTUzX0xhbkxpbmdXYW5n") {	
		heroname = "Batman";	
		return;	
	}	
	if(nameP == "5ouJ5paQ5bCU") {	
		heroname = "Amily";	
		return;	
	}	
	if(nameP == "MTIxX01pWXVl") {	
		heroname = "Marja";	
		return;	
	}	
	if(nameP == "5q2m5YiZ5aSp") {	
		heroname = "Ilumia";	
		return;	
	}	
	if(nameP == "6aG55769") {	
		heroname = "Thane";	
		return;	
	}	
	if(nameP == "5aSq5LmZ55yf5Lq6") {	
		heroname = "Teemee";	
		return;	
	}	
	if(nameP == "6Zi/5pav5bSU5b63") {	
		heroname = "Astrid";	
		return;	
	}	
	if(nameP == "NTE1X1JpY2h0ZXI=") {	
		heroname = "Richter";	
		return;	
	}	
	if(nameP == "5byg6aOe") {	
		heroname = "Cresh";	
		return;	
	}	
	if(nameP == "5ZGo55Gc") {	
		heroname = "Ignis";	
		return;	
	}	
	if(nameP == "MTEzX1podWFuZ1pob3U=") {	
		heroname = "Chaugnar";	
		return;	
	}	
	if(nameP == "6IuP54OI") {	
		heroname = "Wiro";	
		return;	
	}	
	if(nameP == "MTg5X0d1aUd1Wmk=") {	
		heroname = "Krizzix";	
		return;	
	}	
	if(nameP == "NTA1X0JhbGR1bQ==") {	
		heroname = "Baldum";	
		return;	
	}	
	if(nameP == "5Y+k5pyo") {	
		heroname = "Y'bneth";	
		return;	
	}	
	if(nameP == "Um94aQ==") {	
		heroname = "Roxie";	
		return;	
	}	
	if(nameP == "5a6J5aWI54m5") {	
		heroname = "Annette";	
		return;	
	}	
	if(nameP == "NTIzX0RBUkNZ") {	
		heroname = "D'Arcy";	
		return;	
	}	
	if(nameP == "SXNoYXI=") {	
		heroname = "Ishar";	
		return;	
	}	
	if(nameP == "5r6c") {	
		heroname = "Shephera";	
		return;	
	}	
	if(nameP == "5aSc5aes") {	
		heroname = "Dextra";	
		return;	
	}	
	if(nameP == "6IuP56a7") {	
		heroname = "Sinestrea";	
		return;	
	}	
	if(nameP == "SWdneQ==") {	
		heroname = "Iggy";	
		return;	
	}	
	if(nameP == "NTM5X1NhbHo=") {	
		heroname = "Lorion";	
		return;	
	}	
	if(nameP == "VGFjaGk=") {	
		heroname = "Tachi";	
		return;	
	}	
	if(nameP == "WWFv") {	
		heroname = "Aya";	
		return;	
	}	
	if(nameP == "V2hpdGVCb3g=") {	
		heroname = "Yan";	
		return;	
	}	
	if(nameP == "SGVjYXRl") {	
		heroname = "Terri";	
		return;	
	}	
			
}


ImColor ToColor(float color[4]){
    
    return IM_COL32(color[0] * 255.0f,color[1] * 255.0f,color[2] * 255.0f,color[3] * 255.0f);
	
}


void Draw3dBox(ImDrawList *draw,Vector3 Transform, Camera * camera,int glHeight,int glWidth)
{
    Vector3 position2 = Transform + Vector3(0.6, 1.6, 0.6); 
    Vector3 position3 = Transform + Vector3(0.6, 0, 0.6);
    Vector3 position4 = Transform + Vector3(-0.5, 0, 0.6); 
    Vector3 position5 = Transform + Vector3(-0.5, 1.6, 0.6);
    Vector3 position6 = (Transform + Vector3(0.6, 1.6, 0)) + Vector3(0, 0, -0.6);
    Vector3 position7 = (Transform + Vector3(0.6, 0, 0)) + Vector3(0, 0, -0.6);
    Vector3 position8 = (Transform + Vector3(-0.5, 0, 0)) + Vector3(0, 0, -0.6); 
    Vector3 position9 = (Transform + Vector3(-0.5, 1.6, 0)) + Vector3(0, 0, -0.6);

    Vector3 vector = camera->WorldToScreenPoint(position2);
    Vector3 vector2 = camera->WorldToScreenPoint(position3);
    Vector3 vector3 = camera->WorldToScreenPoint(position4);
    Vector3 vector4 = camera->WorldToScreenPoint(position5);
    Vector3 vector5 = camera->WorldToScreenPoint(position6);
    Vector3 vector6 = camera->WorldToScreenPoint(position7);
    Vector3 vector7 = camera->WorldToScreenPoint(position8);
    Vector3 vector8 = camera->WorldToScreenPoint(position9);

    if (vector.z > 0 && vector2.z > 0 && vector3.z > 0 && vector4.z > 0 && vector5.z > 0 && vector6.z > 0 && vector7.z > 0 && vector8.z > 0 )
    {
        draw->AddLine({(float) (glWidth -(glWidth -vector.x)),(glHeight -vector.y)}, {glWidth - (glWidth - vector2.x),glHeight -vector2.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector3.x)),(glHeight -vector3.y)}, {glWidth - (glWidth - vector2.x),glHeight -vector2.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector.x)),(glHeight -vector.y)}, {glWidth - (glWidth - vector4.x),glHeight -vector4.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector4.x)),(glHeight -vector4.y)}, {glWidth - (glWidth - vector3.x),glHeight -vector3.y}, ToColor(Config.Color.box), 2.0f);

        draw->AddLine({(float) (glWidth -(glWidth -vector5.x)),(glHeight -vector5.y)}, {glWidth - (glWidth - vector6.x),glHeight -vector6.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector7.x)),(glHeight -vector7.y)}, {glWidth - (glWidth - vector6.x),glHeight -vector6.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector5.x)),(glHeight -vector5.y)}, {glWidth - (glWidth - vector8.x),glHeight -vector8.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector8.x)),(glHeight -vector8.y)}, {glWidth - (glWidth - vector7.x),glHeight -vector7.y}, ToColor(Config.Color.box), 2.0f);

        draw->AddLine({(float) (glWidth -(glWidth -vector.x)),(glHeight -vector.y)}, {glWidth - (glWidth - vector5.x),glHeight -vector5.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector2.x)),(glHeight -vector2.y)}, {glWidth - (glWidth - vector6.x),glHeight -vector6.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector3.x)),(glHeight -vector3.y)}, {glWidth - (glWidth - vector7.x),glHeight -vector7.y}, ToColor(Config.Color.box), 2.0f);
        draw->AddLine({(float) (glWidth -(glWidth -vector4.x)),(glHeight -vector4.y)}, {glWidth - (glWidth - vector8.x),glHeight -vector8.y}, ToColor(Config.Color.box), 2.0f);
    
    }
}


void DrawCd(ImDrawList *draw, ImVec2 position, float size, ImU32 color, int cd){
	
	
    std::string skill_cd = std::string(std::string("(").append(std::to_string(cd)).append(")"));
    
    
    auto textSize = ImGui::CalcTextSize(skill_cd.c_str(), 0, ((float) glHeight / 30.0f));
		
    
    draw->AddText(ImGui::GetFont(), ((float) glHeight / 30.0f), {position.x - (textSize.x / 2 ) , position.y - (textSize.y / 2) }, ImColor(0, 255, 0, 255), skill_cd.c_str());
				
    
}




void DrawESP(ImDrawList *draw) {
	
	if (espManager->enemies->empty() || !Config.ESPMenu.Enable_ESP) {
		
        return;
    }
	
	if (Config.ESPMenu.Enable_ESP) {
		try{
            //ImGui::Text("%d",m_MiniMapHeroInfos->getLength());
            
				for (int i = 0; i < espManager->enemies->size(); i++) {
					
					void *actorLinker = espManager->MyPlayer;
					
					void *Enemy = (*espManager->enemies)[i]->object;
					
					void *EnemyLinker = (*ActorLinker_enemy->enemies)[i]->object;
					
					
					Vector3 EnemyPos = Vector3::zero();
					if (actorLinker && Enemy) {
						
                        
                        CActorInfo *CharInfo = *(CActorInfo **) ((uintptr_t) EnemyLinker + IL2Cpp::Il2CppGetFieldOffset("Project_d.dll","Kyrios.Actor","ActorLinker","CharInfo"));
                        
						Vector3 myPos = ActorLinker_getPosition((void *)actorLinker);
					
					
						Vector3 myPosSC = Camera::get_main()->WorldToScreenPoint(myPos);
						ImVec2 myPos_Vec2 = ImVec2(glWidth - myPosSC.x, myPosSC.y);
				
						if (myPosSC.z > 0) {
							myPos_Vec2 = ImVec2(myPosSC.x, glHeight - myPosSC.y);
						}
				
						EnemyPos = VInt2Vector(LActorRoot_get_location(Enemy), LActorRoot_get_forward(Enemy));
						
						void *LObjWrapper = *(void**)((uint64_t)Enemy + IL2Cpp::Il2CppGetFieldOffset("Project.Plugins_d.dll","NucleusDrive.Logic","LActorRoot","ActorControl")); 
						void *ValuePropertyComponent = *(void**)((uint64_t)Enemy + IL2Cpp::Il2CppGetFieldOffset("Project.Plugins_d.dll","NucleusDrive.Logic","LActorRoot","ValueComponent")); 
						
						Vector3 rootPos_W2S = Camera::get_main()->WorldToScreenPoint(EnemyPos);
						Vector2 rootPos_Vec2 = Vector2(glWidth - rootPos_W2S.x, rootPos_W2S.y);
						
						if (rootPos_W2S.z > 0) {
							rootPos_Vec2 = Vector2(rootPos_W2S.x, glHeight - rootPos_W2S.y);
						}
						
						
							
						Vector2 headPos_Vec2 = Vector2(rootPos_Vec2.x, rootPos_Vec2.y - (glHeight / 6.35));
						float distanceToMe = Vector3::Distance(myPos, EnemyPos);
						
						if(Config.ESPMenu.IgnoreInvisible){
							
							if(!ActorLinker_get_bVisible(EnemyLinker)){
								return;
							}
						}
						
                        
                        if(Config.ESPMenu.IgnoreVisible){
                            
                            if(ActorLinker_get_bVisible(EnemyLinker)){
                                return;
                            }
						}
                        
						if (!LObjWrapper_get_IsDeadState(LObjWrapper)) {
							
							if (Config.ESPMenu.PlayerLine) {
								draw->AddLine(myPos_Vec2, ImVec2(rootPos_Vec2.x, rootPos_Vec2.y), IM_COL32(Config.Color.line[0] * 255.0f, Config.Color.line[1] * 255.0f, Config.Color.line[2] * 255.0f, Config.Color.line[3] * 255.0f), 1.7f);
							}
							
							if (Config.ESPMenu.PlayerBox) {
                                
                                Draw3dBox(draw, EnemyPos, Camera::get_main(), glHeight, glWidth);
                            }
							
							if (Config.ESPMenu.PlayerHealth && !ActorLinker_get_bVisible(EnemyLinker)) {
								float boxHeight = abs(headPos_Vec2.y - rootPos_Vec2.y);
								float boxWidth = boxHeight * 0.75f;
								
								int EnemyHp = ValuePropertyComponent_get_actorHp(ValuePropertyComponent);     
								
                            	int EnemyHpTotal = ValuePropertyComponent_get_actorHpTotal(ValuePropertyComponent);
                            	
								float PercentHP = ((float)EnemyHp * boxHeight) / ((float)EnemyHpTotal);
								
								ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    							if (EnemyHp <= (EnemyHpTotal * 0.6)) {
        							healthColor = IM_COL32(180, 180, 45, 255);
    							}
    							if (EnemyHp < (EnemyHpTotal * 0.3)) {
        							healthColor = IM_COL32(180, 45, 45, 255);
    							}
								
								draw->AddRectFilled(ImVec2(rootPos_Vec2.x + (boxWidth / 2) + 5, rootPos_Vec2.y), ImVec2(rootPos_Vec2.x + (boxWidth / 2) + 15, rootPos_Vec2.y - PercentHP), healthColor);
								draw->AddRect(ImVec2(rootPos_Vec2.x + (boxWidth / 2) + 5, rootPos_Vec2.y), ImVec2(headPos_Vec2.x + (boxWidth / 2) + 15, headPos_Vec2.y), IM_COL32(0, 0, 0, 255), 0, 240, 0.5);
							
								
							}
							
							
							if(Config.ESPMenu.PlayerCd){
								
								
								float boxHeight = abs(headPos_Vec2.y - rootPos_Vec2.y);
                                float boxWidth = boxHeight * 0.75f;
                                
                                ImVec2 vStart = {headPos_Vec2.x - (boxWidth / 2), headPos_Vec2.y};
                                ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};
                                
                                
								uintptr_t SkillControl = AsHero(EnemyLinker);
        						if (SkillControl > 0)
        							{
            							uintptr_t Skill1Cd = *(int *)(SkillControl + 0x28) / 1000;
            							uintptr_t Skill2Cd = *(int *)(SkillControl + 0x40) / 1000;
            							uintptr_t Skill3Cd = *(int *)(SkillControl + 0x58) / 1000;
            							uintptr_t Skill4Cd = *(int *)(SkillControl + 0x88) / 1000;
            							
										float size = boxHeight / 8;
        								ImVec2 position = ImVec2(vStart.x - size - (boxWidth / 2) + 20.0f, vStart.y + (size / 2));
        						
										ImVec2 position2 = ImVec2(vStart.x - size - (boxWidth / 2) + 20.0f, position.y + size * 2);
        						
										ImVec2 position3 = ImVec2(vStart.x - size - (boxWidth / 2) + 20.0f, position2.y + size * 2);
        						
										ImVec2 position4 = ImVec2(vStart.x - size - (boxWidth / 2) + 20.0f, vEnd.y - size / 2);
        						
										ImU32 color = ImColor(1.0f, 0.5f, 0.0f, 1.0f);  // Màu cam
        						
										DrawCd(draw,position,size,color, Skill1Cd);
								
										DrawCd(draw,position2,size,color, Skill2Cd);
								
										DrawCd(draw,position3,size,color, Skill3Cd);
								
										DrawCd(draw,position4,size,color, Skill4Cd);
										
									}
								
								
								
								
								
								
							}
							
							
										
							if(Config.ESPMenu.PlayerName){
                                
									std::string heroname;
									std::string nameP;
									
									String* actorname = CharInfo->ActorName();
									if(actorname != nullptr){
									
										std::string strName = std::string(CharInfo->ActorName()->CString());
								
										nameP = bdvt_encode(strName);
							
										heroname = nameP;
									
									}
									
									base642name(nameP, heroname, abs((int)CharInfo));
										
									
									if(LObjWrapper_IsAutoAI(LObjWrapper)){
											
										heroname  = std::string("BOT | " + heroname);
									}
									
									auto textSize = ImGui::CalcTextSize(heroname.c_str(), 0, ((float) glHeight / 39.0f));
									draw->AddText(ImGui::GetFont(), ((float) glHeight / 39.0f), {rootPos_Vec2.x - (textSize.x / 4), rootPos_Vec2.y + 25}, IM_COL32(255, 255, 255, 255), heroname.c_str());
									
							}
							
							if (Config.ESPMenu.PlayerDistance) {
								std::string strDistance = to_string((int) distanceToMe) + " M";
								
								auto textSize = ImGui::CalcTextSize(strDistance.c_str(), 0, ((float) glHeight / 39.0f));
								draw->AddText(NULL, ((float) glHeight / 39.0f), {rootPos_Vec2.x - (textSize.x / 4), rootPos_Vec2.y + 5}, IM_COL32(0, 180, 255, 255), strDistance.c_str());
							}
							
							if (Config.ESPMenu.PlayerAlert && isOutsideScreen(ImVec2(rootPos_Vec2.x, rootPos_Vec2.y), ImVec2(glWidth, glHeight))) {
								
								
								
								ImVec2 hintDotRenderPos = pushToScreenBorder(ImVec2(rootPos_Vec2.x, rootPos_Vec2.y), ImVec2(glWidth, glHeight), - 50);
								ImVec2 hintTextRenderPos = pushToScreenBorder(ImVec2(rootPos_Vec2.x, rootPos_Vec2.y), ImVec2(glWidth, glHeight), - 50);
								
								int EnemyHp = ValuePropertyComponent_get_actorHp(ValuePropertyComponent);     
								
                            	int EnemyHpTotal = ValuePropertyComponent_get_actorHpTotal(ValuePropertyComponent);
                            	
								
								
								draw->AddCircleFilled(hintDotRenderPos, 25, IM_COL32(255, 0, 0, 110));
								DrawCircleHealth(hintDotRenderPos, EnemyHp, EnemyHpTotal, 25);
								
								std::string strDistance = to_string((int) distanceToMe) + " M";
								auto textSize = ImGui::CalcTextSize(strDistance.c_str(), 0, ((float) glHeight / 45.0f));
								draw->AddText(NULL, ((float) glHeight / 45.0f), {hintTextRenderPos.x - (textSize.x / 4), hintTextRenderPos.y - 7}, IM_COL32(255, 255, 255, 255), strDistance.c_str());
								
								
							}
							
						}
					}
				}
			}catch(...){
				
			}
	}
}
