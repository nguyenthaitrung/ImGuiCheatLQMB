#pragma once

class Camera {
	public:
	
	static Camera *get_main() {
		Camera *(*get_main_) () = (Camera *(*)()) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"), 0));
		
		//Camera *(*get_main_) () = (Camera *(*)()) (il2cppMap + 0x31b8dd0);
		return get_main_();
	}
	
	Vector3 WorldToScreenPoint(Vector3 position) {
		Vector3 (*WorldToScreenPoint_)(Camera *camera, Vector3 position) = (Vector3 (*)(Camera *, Vector3)) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1));
		
		//Vector3 (*WorldToScreenPoint_)(Camera *camera, Vector3 position) = (Vector3 (*)(Camera *, Vector3)) (il2cppMap + 0x31b84c0);
		return WorldToScreenPoint_(this, position);
	}
};


class CActorInfo {
	public:
	
	String *ActorName() {
		return *(String **) ((uintptr_t) this + IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameLogic"), OBFUSCATE("CActorInfo"), OBFUSCATE("ActorName")));
		//return *(String **) ((uintptr_t) this + 0xC);
	}
	
    
    int hudHeight(){
        
        return *(int *) ((uintptr_t) this + IL2Cpp::Il2CppGetFieldOffset(OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameLogic"), OBFUSCATE("CActorInfo"), OBFUSCATE("hudHeight")));
        
    }
};

