#include "Includes/obfuscate.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Utils.h"
#include "Includes/Macros.h"
#include "foxcheats/include/ScanEngine.h"
#include "LQM/Call_Me.h"
#include <zip.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sys/ptrace.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iomanip>
#define SNOW_LIMIT 300
#include <mutex>
std::vector<Snowflake::Snowflake> snow;
#include <random>
#include <cmath>
using namespace kFox;

bool getName = true;
bool isLoading = false;

#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )


std::string directoryPath;
std::vector<GLuint> textureIDs; // Lưu trữ ID của các texture
float time_ani = 0.0f; // Biến thời gian
float animationSpeed = 0.3f; // Tốc độ animation
bool animation_init = false; // Biến check animation

zip *archive;
int fishLevel;



void ShowLoading(){
    
     auto windowWidth = ImGui::GetWindowSize().x;
     
     auto windowHeight = ImGui::GetWindowSize().y;
     
            
     ImGui::SetCursorPosX((windowWidth - ((windowWidth * 0.50f) * 2)) * 0.5f);
            
     ImGui::SetCursorPosY((windowHeight - ((windowWidth * 0.50f) * 2)) * 0.5f);

            
     ImGui::LoadingIndicatorCircle("##loading", windowWidth * 0.40f, ImVec4(0.529f, 0.808f, 0.922f, 0.5f), ImVec4(0.529f, 0.808f, 0.922f, 1.0f), 10, ImGui::GetTime() * 0.175f);
     

}


#if defined(TOUCH_IL2CPP)


struct UnityEngine_Vector2_Fields {
    float x;
    float y;
};

struct UnityEngine_Vector2_o {
    UnityEngine_Vector2_Fields fields;
};

enum TouchPhase {
    Began = 0,
    Moved = 1,
    Stationary = 2,
    Ended = 3,
    Canceled = 4
};

struct UnityEngine_Touch_Fields {
    int32_t m_FingerId;
    struct UnityEngine_Vector2_o m_Position;
    struct UnityEngine_Vector2_o m_RawPosition;
    struct UnityEngine_Vector2_o m_PositionDelta;
    float m_TimeDelta;
    int32_t m_TapCount;
    int32_t m_Phase;
    int32_t m_Type;
    float m_Pressure;
    float m_maximumPossiblePressure;
    float m_Radius;
    float m_fRadiusVariance;
    float m_AltitudeAngle;
    float m_AzimuthAngle;
};

#endif
int sizeApp;
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
	
	eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
	eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
	
	if (glWidth <= 0 || glHeight <= 0) {
		return eglSwapBuffers(dpy, surface);
	}
	scaleX = (float) glWidth / screenWidth;
    scaleY = (float) glHeight / screenHeight;
    
    
    static std::string md5data;
    
	if (!Config.InitImGui.initImGui) {
		ImGui::CreateContext();
		
		ImGuiStyle *style = &ImGui::GetStyle();
        ImGui::StyleColorsLight(style);
		ImVec4 whiteColor(1.0f, 1.0f, 1.0f, 1.0f);
        style->WindowTitleAlign = ImVec2(0.5f,0.5f);
        style->WindowRounding = 0.0f;
        style->FrameRounding = 7.2f;
		style->ScrollbarSize = 20;
        
		ImGui_ImplAndroid_Init();
		ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 100"));

		
		
		ImGuiIO* io = &ImGui::GetIO();
		
		io->ConfigWindowsMoveFromTitleBarOnly = false;
        
        
        
        static const ImWchar icons_ranges_fa[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
        ImFontConfig icons_config_fa; 
        icons_config_fa.MergeMode = true; 
        icons_config_fa.PixelSnapH = true; 
        icons_config_fa.GlyphMinAdvanceX = 8;
        
        ImFontConfig icons_config_md;
        icons_config_md.MergeMode = true;
        icons_config_md.PixelSnapH = true;
        icons_config_md.OversampleH = 2.5;
        icons_config_md.GlyphExtraSpacing.y = -3.0;
        icons_config_md.GlyphOffset.y = 3.0;
        icons_config_md.OversampleV = 2.5;
        static const ImWchar icons_ranges_md[] = { ICON_MIN_MD, ICON_MAX_16_MD, 0 };
        
        static const ImWchar icons_ranges_gg[] = {0xf000, 0xf3ff, 0x1F000, 0x1F9FF, 0 };
        
        
		io->Fonts->AddFontFromMemoryTTF((void *)PIRO_data, PIRO_size, 15.0f, NULL, io->Fonts->GetGlyphRangesVietnamese());
        
        io->Fonts->AddFontFromMemoryTTF((void *)MaterialIcons_Regular, MaterialIcons_Regular_size, 10.0f, &icons_config_md, icons_ranges_md);
        
  		io->Fonts->AddFontFromMemoryTTF((void *)fa_solid, fa_solid_size, 16.0f, &icons_config_fa, icons_ranges_fa);
        
        
        md5data = getSignatureMD5();
        sizeApp = getSizeApp();
        
		Config.InitImGui.initImGui = true;
	}
	
	ImGuiIO* io = &ImGui::GetIO();
    
	static bool IsShowKeyBoard = false;
	static bool WantTextInputLast = false;
    if (io->WantTextInput && !WantTextInputLast){
        if(!IsShowKeyBoard){
            
            ShowSoftKeyboardInput();
            IsShowKeyBoard = true;
        }
    }
    
    
    WantTextInputLast = io->WantTextInput;
    
    if (!io->WantTextInput && IsShowKeyBoard){
        ShowSoftKeyboardInput();
        IsShowKeyBoard = false;
    }
	
	#if defined(TOUCH_IL2CPP)
    
    int (*TouchCount)(void*) = (int (*)(void*)) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_touchCount"), 0));
    int touchCount = TouchCount(nullptr);
    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields (*)(int)) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("GetTouch"), 1))) (0);
        float reverseY = io->DisplaySize.y - touch.m_Position.fields.y;

        switch (touch.m_Phase) {
            case TouchPhase::Began:
            case TouchPhase::Stationary:
                io->MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                io->MouseDown[0] = true;
                break;
            case TouchPhase::Ended:
            case TouchPhase::Canceled:
                io->MouseDown[0] = false;
                should_clear_mouse_pos = true;
                break;
            case TouchPhase::Moved:
                io->MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                break;
            default:
                break;
        }
    } else {
        io->MouseDown[0] = false;
    }
    
    #endif
    
    
    #if defined(__aarch64__) && !defined(TOUCH_IL2CPP)
    
    if(screenWidth < 0 || screenHeight < 0){
        
        
        int (*_screenHeight)() = (int (*)()) IL2Cpp::Il2CppGetMethodOffset("UnityEngine.CoreModule.dll","UnityEngine", "Screen", "get_systemHeight",0);
        int (*_screenWidth)() = (int (*)()) IL2Cpp::Il2CppGetMethodOffset("UnityEngine.CoreModule.dll","UnityEngine", "Screen", "get_systemWidth", 0);
    
        
        
        if(_screenHeight && _screenWidth){
            screenHeight = _screenHeight();
        
            screenWidth = _screenWidth();
        }
        
        
    }
    
    #endif
    
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth,glHeight, scaleX, scaleY);
    ImGui::NewFrame();
    
	DrawESP(ImGui::GetBackgroundDrawList());
    time_ani += animationSpeed;
    ImGui::SetNextWindowSize(ImVec2(screenWidth * 0.3 * scaleX, screenHeight * 0.3 * scaleY),ImGuiCond_Once);
	if (ImGui::Begin(OBFUSCATE("Share By: github.com/ImTienNguyenZ")), nullptr , ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse) {
		
		ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 viewport_size = viewport->Size;
        float width = viewport_size.x;
        float height = viewport_size.y;

        ImVec2 viewport_min = viewport->Pos;
        ImVec2 viewport_max = ImVec2(viewport_min.x + width, viewport_min.y + height);

        ImVec2 menu_pos = ImGui::GetWindowPos();
        
        ImVec2 menu_size = ImGui::GetWindowSize();
        
		static std::string err;
		static bool first = true;
		static char gg[500];
		static char s[300];
        
         {
			
			
		if (ImGui::BeginTabBar("mymenu"))
    	{
		
        #if !defined(__aarch64__)
        
       
        if (ImGui::BeginTabItem(OBFUSCATE(ICON_MD_RADAR" NAME")))
        {
        
            if(ImGui::BeginTable("split",2)){
                
             
				ImGui::TableNextColumn();
                ImGui::Checkbox(OBFUSCATE("ACTIVETED"), &Config.ESPMenu.Enable_ESP);
               
                   ImGui::TableNextColumn();
                   ImGui::Checkbox(OBFUSCATE("ĐƯỜNG KẺ"), &Config.ESPMenu.PlayerLine); ImGui::SameLine(); ImGui::ColorEdit4("##ColorLine", Config.Color.line, ALPHA);
                   ImGui::TableNextColumn();
                   ImGui::Checkbox(OBFUSCATE("HỘP"), &Config.ESPMenu.PlayerBox); ImGui::SameLine(); ImGui::ColorEdit4("##ColorBox", Config.Color.box, ALPHA);
                   ImGui::TableNextColumn();
                   ImGui::Checkbox(OBFUSCATE("MÁU"), &Config.ESPMenu.PlayerHealth);
                   ImGui::TableNextColumn();
                  ImGui::Checkbox(OBFUSCATE("NAME HERO"), &Config.ESPMenu.PlayerName);
                  ImGui::TableNextColumn();
                  ImGui::Checkbox(OBFUSCATE("KHOẢNG CÁCH"), &Config.ESPMenu.PlayerDistance);
                  ImGui::TableNextColumn();
                  ImGui::Checkbox(OBFUSCATE("CẢNH BÁO 360°"), &Config.ESPMenu.PlayerAlert);
                  ImGui::TableNextColumn();
                  ImGui::Checkbox(OBFUSCATE("SHOW SKILL CD"), &Config.ESPMenu.PlayerCd);
                  ImGui::TableNextColumn();
                  ImGui::Checkbox(OBFUSCATE("BỎ QUA KHÔNG CÓ SIGHT"), &Config.ESPMenu.IgnoreInvisible);
                  ImGui::TableNextColumn();
                  ImGui::Checkbox(OBFUSCATE("BỎ QUA CÓ SIGHT"), &Config.ESPMenu.IgnoreVisible);
                  ImGui::TableNextColumn();
            }
            
            ImGui::EndTable();
            ImGui::EndTabItem();
		}
        
        
        #endif
            
       if (ImGui::BeginTabItem(OBFUSCATE(ICON_MD_MAP" SHOW INFO")))
        {
            
         ImGui::Checkbox(OBFUSCATE("MAP SÁNG"), &Config.FEATMenu.HackMap);
            ImGui::Checkbox(OBFUSCATE("SHOW SKILL CD"), &Config.FEATMenu.showCd);
            ImGui::Checkbox(OBFUSCATE("HỦY HỒI CHIÊU"), &Config.FEATMenu.noCd);
            
            #if !defined(__aarch64__)
        
          ImGui::Checkbox(OBFUSCATE("HIỆN AVATAR GHÉP TRẬN"), &Config.FEATMenu.avatar);
            ImGui::Checkbox(OBFUSCATE("SHOW UNTI, HP"), &Config.FEATMenu.ultimate);
            
        
            #endif
        
            
            ImGui::EndTabItem();
		}
            
       #if !defined(__aarch64__)
        
		if (ImGui::BeginTabItem(OBFUSCATE(ICON_MD_DOUBLE_ARROW" AIM SKILL")))
        {
            
            ImGui::Checkbox("AIM SKILL", &Config.FEATMenu.AimSkill);
            ImGui::Checkbox("HIDE LINE SKILL", &Config.FEATMenu.AutoTrung);
            ImGui::Checkbox("SKILL 1",&Config.FEATMenu.aimSkill1);
            ImGui::Checkbox("SKILL 2",&Config.FEATMenu.aimSkill2);
            ImGui::Checkbox("SKILL 3",&Config.FEATMenu.aimSkill3);
            ImGui::SliderInt( "FOV##2", &Config.FEATMenu.Radius, 0, 100, "%dm" );
            ImGui::EndTabItem();
        }
        
		
			
        
       if (ImGui::BeginTabItem(OBFUSCATE(ICON_MD_CAMERA" CAMERA")))
        {

            ImGui::Text(OBFUSCATE("CUSTOM CAMERA :"));
            ImGui::Checkbox("##CAMERA", &Config.WideView.Active);
            ImGui::SameLine();
            ImGui::SliderFloat(OBFUSCATE("##DroneView"), &Config.WideView.SetFieldOfView, 0.f, 5.f);
            ImGui::EndTabItem();
                
		}
        
        #endif
        if (ImGui::BeginTabItem(OBFUSCATE(ICON_MD_KEY" ADMIN INFO")))
        {

            
            ImGui::TextWrapped(thongbao.c_str());
            ImGui::Text(OBFUSCATE("Leak : Nguyen Minh Tien"));
			ImGui::Text(OBFUSCATE("Verison : v0.1"));
			ImGui::Text(OBFUSCATE("Developer: Nguyen Tien"));
			ImGui::Text(OBFUSCATE("Telegram : t.me/mtienmodder"));
			ImGui::Text(OBFUSCATE("Github : github.com/ImTienNguyenZ"));
			ImGui::Text(OBFUSCATE("Source Code Esp Aov All Sever"));
			ImGui::Text(OBFUSCATE("All Function Auto Update All Version"));
            ImGui::EndTabItem();
                
		}
		
        
        
		if (ImGui::BeginTabItem(OBFUSCATE(ICON_MD_SETTINGS" SETTING")))
        {
            
            auto windowWidth = ImGui::GetWindowSize().x;
            auto textWidth   = ImGui::CalcTextSize(Config.Other.config_filename.c_str()).x;
            
            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
            ImGui::Text(Config.Other.config_filename.c_str());
            static float textDisplayStartTime = -1.0f;
            static float textDisplayStartTimeLoad = -1.0f;
            const float textDisplayDuration = 5.0f;
            static bool saveSuccess;
            static bool loadSuccess = false;
            
            if(ImGui::Button(OBFUSCATE("Dumper"), ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                
                isLoading = true;
                
                std::thread t1([]() {
        
                    auto il2cpp_handle = dlopen("libil2cpp.so", 4);
                    il2cpp_dump(il2cpp_handle);
                
                    isLoading = false;
                    
                });

                t1.detach();
                
               
                
            }
            
            
            if (ImGui::Button(OBFUSCATE(ICON_MD_SAVE" Save"), ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                
                
                if(writeStructToFile(Config,Config.Other.config_filename)){
                    
                    textDisplayStartTime = ImGui::GetTime();
                    saveSuccess = true;
                
                }else{
                    
                    textDisplayStartTime = ImGui::GetTime();
                    saveSuccess = false;
                    
                }
                                
            }
            
            if(saveSuccess){
                if (textDisplayStartTime >= 0 && ImGui::GetTime() - textDisplayStartTime < textDisplayDuration)
                    ImGui::Text("Save successfully");
            }else{
                if (textDisplayStartTime >= 0 && ImGui::GetTime() - textDisplayStartTime < textDisplayDuration)
                    ImGui::Text("Save failed");
            }
            
            if (ImGui::Button(OBFUSCATE(ICON_MD_INSTALL_MOBILE" Load"), ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                        
                
                textDisplayStartTimeLoad = ImGui::GetTime();
                
                if(readStructFromFile(Config,Config.Other.config_filename)){
                    
                    textDisplayStartTimeLoad = ImGui::GetTime();
                    loadSuccess = true;
                
                }else{
                    
                    textDisplayStartTimeLoad = ImGui::GetTime();
                    loadSuccess = false;
                    
                    
                }
                
                                
            }
            if(loadSuccess){
                if (textDisplayStartTimeLoad >= 0 && ImGui::GetTime() - textDisplayStartTimeLoad < textDisplayDuration)
                    ImGui::Text("Load successfully");
            }else{
                if (textDisplayStartTimeLoad >= 0 && ImGui::GetTime() - textDisplayStartTimeLoad < textDisplayDuration)
                    ImGui::Text("Load failed");
            }
            
            ImGui::EndTabItem();
                
		}
		
		}
	}
	
	    
	}
	
	
	
	ImGui::End();
    ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	if (should_clear_mouse_pos) {
        io->MousePos = ImVec2(-1, -1);
        should_clear_mouse_pos = false;
    }
	return orig_eglSwapBuffers(dpy, surface);
}


bool (*olk_Bypass)(void *instance);
bool Bypasss(void *instance) {
    {
        return false;
    }
    return olk_Bypass(instance);
}

#if defined(__aarch64__)

void (*old_Update)(void *instance);
void AUpdate(void *instance) {
    if (instance != NULL) {
        
        
        uintptr_t SkillControl = AsHero(instance);
        uintptr_t HudControl = *(uintptr_t *) ((uintptr_t)instance + 0x78);
        if (HudControl > 0 && SkillControl > 0) {
            uintptr_t Skill1Cd = *(int *) (SkillControl + 0x44) / 1000;
            uintptr_t Skill2Cd = *(int *) (SkillControl + 0x64) / 1000;
            uintptr_t Skill3Cd = *(int *) (SkillControl + 0x84) / 1000;
            uintptr_t Skill4Cd = *(int *) (SkillControl + 0xC4) / 1000;
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
                String *playerName = Il2CppString::Create("Share By");
                String *prefixName = Il2CppString::Create("Nguyen Tien");
                _SetPlayerName(HudControl, playerName, prefixName, true);
            }
        }
        
        
        old_Update(instance);
       
    }
}


#endif

void *Init_Thread(void *) {
	espManager = new ESPManager();
    ActorLinker_enemy = new ESPManager();
    while (!il2cppMap) {
        il2cppMap = Tools::GetBaseAddress(targetLib);
        sleep(1);
    }
    
    
    
    
    
    IL2Cpp::Il2CppAttach();
    
    
    Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libEGL.so"), OBFUSCATE("eglSwapBuffers")), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);
   
    Tools::Hook((void *) (uint64_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LVActorLinker") , OBFUSCATE("SetVisible"), 3), (void *) LActorRoot_Visible, (void **) &_LActorRoot_Visible);
        
    AsHero = (uintptr_t(*)(...)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("AsHero"), 0);
    
    _SetPlayerName = (void (*)(...)) ((uint64_t)IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameLogic","HudComponent3D","SetPlayerName",3));
        
    OpenURL = (void (*)(String *))IL2Cpp::Il2CppGetMethodOffset("UnityEngine.CoreModule.dll","UnityEngine","Application","OpenURL",1);
    
    
    #if defined(__aarch64__)
    
        
        Tools::Hook((void *) (uint64_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("Update"), 0), (void *) AUpdate, (void **) &old_Update);
        
        
        
        MemoryPatch::createWithHex("libil2cpp.so",0x56adc4c ,"1E FF 2F E1" ).Modify();
        
        
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdc468 ,"1E FF 2F E1" ).Modify();
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdbfc4 ,"1E FF 2F E1" ).Modify();
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdc0e4 ,"1E FF 2F E1" ).Modify();
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdc468,"1E FF 2F E1" ).Modify();
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdc8c0,"1E FF 2F E1" ).Modify();
 
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdca90,"1E FF 2F E1" ).Modify();
 
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdc600,"1E FF 2F E1" ).Modify();
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdcb04,"1E FF 2F E1" ).Modify();
        MemoryPatch::createWithHex("libil2cpp.so",0x3bdcc0c,"1E FF 2F E1" ).Modify();
 
         MemoryPatch::createWithHex("libil2cpp.so",0x3bdbee0,"1E FF 2F E1" ).Modify();
         MemoryPatch::createWithHex("libil2cpp.so",0x1d8ccf4,"1E FF 2F E1" ).Modify();
 
         MemoryPatch::createWithHex("libil2cpp.so",0x27b3b0c,"1E FF 2F E1" ).Modify();
 
 
         MemoryPatch::createWithHex("libil2cpp.so",0x27b3c10,"1E FF 2F E1" ).Modify();
        
        
    #else
    
    
     MemoryPatch::createWithHex(((uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("PVPLoadingView") , OBFUSCATE("OnEnter"), 0) + 0xBB0) ,"00F020E3").Modify();
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("InBattleMsgUT") , OBFUSCATE("ShowInBattleMsg"), 8), (void *) ShowChatMsg, (void **) &_ShowChatMsg);
    
        
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("HeroInfoPanel") , OBFUSCATE("Update"), 0), (void *) _HeroInfoPanel_Update, (void **) &HeroInfoPanel_Update);
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("Update"), 0), (void *) ActorLinker_Update, (void **) &old_ActorLinker_Update);
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("UpdateLogic"), 1), (void *) LActorRoot_UpdateLogic, (void **) &old_LActorRoot_UpdateLogic);
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("DestroyActor"), 0), (void *) ActorLinker_ActorDestroy, (void **) &old_ActorLinker_ActorDestroy);
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("DestroyActor"), 1), (void *) LActorRoot_ActorDestroy, (void **) &old_LActorRoot_ActorDestroy);
    
    MiniMapHeroInfo_Show = (void (*)(void *,bool)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("MiniMapHeroInfo") , OBFUSCATE("Show"), 1);
    
    MiniMapHeroInfo_get_ObjID = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("MiniMapHeroInfo") , OBFUSCATE("get_ObjID"), 0);
    
    ActorLinker_IsHostPlayer = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("IsHostPlayer"), 0);
    ActorLinker_IsHostCamp = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("IsHostCamp"), 0);
    ActorLinker_ActorTypeDef = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("get_objType"), 0);
    ActorLinker_COM_PLAYERCAMP = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("get_objCamp"), 0);
    ActorLinker_getPosition = (Vector3 (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("get_position"), 0);
    ActorLinker_get_HPBarVisible = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("get_HPBarVisible"), 0);
    ActorLinker_get_ObjID = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("get_ObjID"), 0);
    ActorLinker_get_bVisible = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ActorLinker") , OBFUSCATE("get_bVisible"), 0);

    LActorRoot_get_forward = (VInt3 (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("get_forward"), 0);
    LActorRoot_get_location = (VInt3 (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("get_location"), 0);
    LActorRoot_LHeroWrapper = (uintptr_t (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("AsHero"), 0);
    LActorRoot_COM_PLAYERCAMP = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("GiveMyEnemyCamp"), 0);
    LActorRoot_get_bActive = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("get_bActive"), 0);
    LActorRoot_get_ObjID = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LActorRoot") , OBFUSCATE("get_ObjID"), 0);


    LObjWrapper_get_IsDeadState = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LObjWrapper") , OBFUSCATE("get_IsDeadState"), 0);

    LObjWrapper_IsAutoAI = (bool (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LObjWrapper") , OBFUSCATE("IsAutoAI"), 0);
    
    ValuePropertyComponent_get_actorHp = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("ValuePropertyComponent") , OBFUSCATE("get_actorHp"), 0);
    ValuePropertyComponent_get_actorHpTotal = (int (*)(void *)) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("ValuePropertyComponent") , OBFUSCATE("get_actorHpTotal"), 0);
    
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameSystem","CRoleInfo","IsCanUseSkin",2), (void *) IsCanUseSkin, (void **) &_IsCanUseSkin);

    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameLogic","SkillComponent","IsUseSkillJoystick",1), (void *) IsUseSkillJoystick, (void **) &_IsUseSkillJoystick);

    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameLogic","GameInput","IsSmartUse",0), (void *) IsSmartUse, (void **) &_IsSmartUse);

    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameLogic","Skill","get_IsUseCameraMoveWithIndicator",0), (void *) get_IsUseCameraMoveWithIndicator, (void **) &_get_IsUseCameraMoveWithIndicator);
    
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Kyrios.Actor"), OBFUSCATE("ObjLinkerWrapper") , OBFUSCATE("IsDistanceLowerEqualAsAttacker"), 2), (void *) IsDistanceLowerEqualAsAttacker, (void **) &old_IsDistanceLowerEqualAsAttacker);

    OnCameraHeightChanged = (void(*)(void *))IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("CameraSystem") , OBFUSCATE("OnCameraHeightChanged"), 0);
    
    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("CameraSystem") , OBFUSCATE("Update"), 0), (void *) CameraSystemUpdate, (void **) &old_CameraSystemUpdate);

    Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("CameraSystem") , OBFUSCATE("GetCameraHeightRateValue"), 1), (void *) GetCameraHeightRateValue, (void **) &old_GetCameraHeightRateValue);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("MiniMapHeroInfo") , OBFUSCATE("ShowSkillStateInfo"), 2), (void *) ShowSkillStateInfo, (void **) &_ShowSkillStateInfo);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE(""), OBFUSCATE("MiniMapHeroInfo") , OBFUSCATE("ShowHeroHpInfo"), 2), (void *) ShowHeroHpInfo, (void **) &_ShowHeroHpInfo);      
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("HeroInfoPanel") , OBFUSCATE("ShowHeroInfo"), 2), (void *) ShowHeroInfo, (void **) &_ShowHeroInfo);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("CPlayerProfile") , OBFUSCATE("get_IsHostProfile"), 0), (void *) IsHostProfile, (void **) &_IsHostProfile);
  
      Tools::Hook(IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameSystem","HeroSelectBanPickWindow","InitTeamHeroList", 4),(void *) InitTeamHeroList,(void **) &_InitTeamHeroList);

      Tools::Hook(IL2Cpp::Il2CppGetMethodOffset("Project_d.dll","Assets.Scripts.GameSystem","CMatchingSystem","checkTeamLaderGradeMax", 1),(void *) checkTeamLaderGradeMax,(void **) &_checkTeamLaderGradeMax);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.Framework"), OBFUSCATE("GameSettings") , OBFUSCATE("get_Supported60FPSMode"), 0), (void *) get_Supported60FPSMode , (void **) &_get_Supported60FPSMode);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.Framework"), OBFUSCATE("GameSettings") , OBFUSCATE("get_Supported90FPSMode"), 0), (void *) get_Supported60FPSMode , (void **) &_get_Supported60FPSMode);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.Framework"), OBFUSCATE("GameSettings") , OBFUSCATE("get_Supported120FPSMode"), 0), (void *) get_Supported60FPSMode , (void **) &_get_Supported60FPSMode);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.Framework"), OBFUSCATE("GameSettings") , OBFUSCATE("get_SupportedBoth60FPS_CameraHeight"), 0), (void *) get_SupportedBoth60FPS_CameraHeight , (void **) &_get_SupportedBoth60FPS_CameraHeight);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.Framework"), OBFUSCATE("GameSettings") , OBFUSCATE("IsIPadDevice"), 0), (void *) IsIPadDevice , (void **) &_IsIPadDevice);
    
      Tools::Hook((void *) (uintptr_t)IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameSystem"), OBFUSCATE("SettlementHelper") , OBFUSCATE("SetPlayerName"), 2), (void *) SettlementHelper_SetPlayerName, (void **) &_SettlementHelper_SetPlayerName);
    
    
    #endif
    
    
    
	return nullptr;
}


jclass UnityPlayer_cls;
jfieldID UnityPlayer_CurrentActivity_fid;


JNIEXPORT jint JNICALL 
JNI_OnLoad(JavaVM *vm, void * reserved) {
	jvm = vm;
	JNIEnv *env;
	
	vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    
    #if defined(__aarch64__)
    
    #else
    
        #if !defined(TOUCH_IL2CPP)
        
            Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libandroid.so"), OBFUSCATE("ANativeWindow_getWidth")), (void *) _ANativeWindow_getWidth, (void **) &orig_ANativeWindow_getWidth);
	        Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libandroid.so"), OBFUSCATE("ANativeWindow_getHeight")), (void *) _ANativeWindow_getHeight, (void **) &orig_ANativeWindow_getHeight);
    
        #endif
        
    #endif
    
    UnityPlayer_cls = env->FindClass(OBFUSCATE("com/unity3d/player/UnityPlayer"));
    UnityPlayer_CurrentActivity_fid = env->GetStaticFieldID(UnityPlayer_cls, OBFUSCATE("currentActivity"),OBFUSCATE("Landroid/app/Activity;"));
    DobbyHook((void *) env->functions->RegisterNatives, (void *) hook_RegisterNatives, (void **) &old_RegisterNatives);
    
    
    
	pthread_t myThread;
	pthread_create(&myThread, NULL, Init_Thread, NULL);
	
    
    
	return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

    
}


