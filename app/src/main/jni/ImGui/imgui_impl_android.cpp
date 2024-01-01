#include "imgui.h"
#include "imgui_impl_android.h"
#include <map>
#include <queue>
#include <time.h>
#include <android/native_window.h>
#include <android/input.h>
#include <android/keycodes.h>
#include <android/log.h>

// Android data
static double                                   g_Time = 0.0;
static ANativeWindow*                           g_Window;
static char                                     g_LogTag[] = "ImGuiExample";
static std::map<int32_t, std::queue<int32_t>> g_KeyEventQueues; // FIXME: Remove dependency on map and queue once we use upcoming input queue.


typedef enum { TOUCH_ACTION_DOWN = 0, TOUCH_ACTION_UP, TOUCH_ACTION_MOVE } TOUCH_ACTION;

typedef struct {
    TOUCH_ACTION action;
    float x;
    float y;
    int pointers;
    float y_velocity;
    float x_velocity;
} TOUCH_EVENT;
TOUCH_EVENT g_LastTouchEvent;

int32_t ImGui_ImplAndroid_HandleInputEvent(int motionEvent, int x, int y, int p)
{
    float velocity_y = (float)((float)y - g_LastTouchEvent.y) / 100.f;
    g_LastTouchEvent = {.action = (TOUCH_ACTION) motionEvent, .x = static_cast<float>(x), .y = static_cast<float>(y), .pointers = p, .y_velocity = velocity_y};
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos.x = g_LastTouchEvent.x;
    io.MousePos.y = g_LastTouchEvent.y;

    if (motionEvent == TOUCH_ACTION_MOVE) {
        
        //io.MouseWheel += g_LastTouchEvent.y_velocity;
    }

    if (motionEvent == TOUCH_ACTION_DOWN) {
        io.MouseDown[0] = true;
    }

    if (motionEvent == TOUCH_ACTION_UP) {
        io.MouseDown[0] = false;
        should_clear_mouse_pos = true;
    }

    return true;
}

static ImGuiKey ImGui_ImplAndroid_KeyCodeToImGuiKey(int32_t key_code)
{
    switch (key_code)
    {
        case AKEYCODE_TAB:                  return ImGuiKey_Tab;
        case AKEYCODE_DPAD_LEFT:            return ImGuiKey_LeftArrow;
        case AKEYCODE_DPAD_RIGHT:           return ImGuiKey_RightArrow;
        case AKEYCODE_DPAD_UP:              return ImGuiKey_UpArrow;
        case AKEYCODE_DPAD_DOWN:            return ImGuiKey_DownArrow;
        case AKEYCODE_PAGE_UP:              return ImGuiKey_PageUp;
        case AKEYCODE_PAGE_DOWN:            return ImGuiKey_PageDown;
        case AKEYCODE_MOVE_HOME:            return ImGuiKey_Home;
        case AKEYCODE_MOVE_END:             return ImGuiKey_End;
        case AKEYCODE_INSERT:               return ImGuiKey_Insert;
        case AKEYCODE_FORWARD_DEL:          return ImGuiKey_Delete;
        case AKEYCODE_DEL:                  return ImGuiKey_Backspace;
        case AKEYCODE_SPACE:                return ImGuiKey_Space;
        case AKEYCODE_ENTER:                return ImGuiKey_Enter;
        case AKEYCODE_ESCAPE:               return ImGuiKey_Escape;
        case AKEYCODE_APOSTROPHE:           return ImGuiKey_Apostrophe;
        case AKEYCODE_COMMA:                return ImGuiKey_Comma;
        case AKEYCODE_MINUS:                return ImGuiKey_Minus;
        case AKEYCODE_PERIOD:               return ImGuiKey_Period;
        case AKEYCODE_SLASH:                return ImGuiKey_Slash;
        case AKEYCODE_SEMICOLON:            return ImGuiKey_Semicolon;
        case AKEYCODE_EQUALS:               return ImGuiKey_Equal;
        case AKEYCODE_LEFT_BRACKET:         return ImGuiKey_LeftBracket;
        case AKEYCODE_BACKSLASH:            return ImGuiKey_Backslash;
        case AKEYCODE_RIGHT_BRACKET:        return ImGuiKey_RightBracket;
        case AKEYCODE_GRAVE:                return ImGuiKey_GraveAccent;
        case AKEYCODE_CAPS_LOCK:            return ImGuiKey_CapsLock;
        case AKEYCODE_SCROLL_LOCK:          return ImGuiKey_ScrollLock;
        case AKEYCODE_NUM_LOCK:             return ImGuiKey_NumLock;
        case AKEYCODE_SYSRQ:                return ImGuiKey_PrintScreen;
        case AKEYCODE_BREAK:                return ImGuiKey_Pause;
        case AKEYCODE_NUMPAD_0:             return ImGuiKey_Keypad0;
        case AKEYCODE_NUMPAD_1:             return ImGuiKey_Keypad1;
        case AKEYCODE_NUMPAD_2:             return ImGuiKey_Keypad2;
        case AKEYCODE_NUMPAD_3:             return ImGuiKey_Keypad3;
        case AKEYCODE_NUMPAD_4:             return ImGuiKey_Keypad4;
        case AKEYCODE_NUMPAD_5:             return ImGuiKey_Keypad5;
        case AKEYCODE_NUMPAD_6:             return ImGuiKey_Keypad6;
        case AKEYCODE_NUMPAD_7:             return ImGuiKey_Keypad7;
        case AKEYCODE_NUMPAD_8:             return ImGuiKey_Keypad8;
        case AKEYCODE_NUMPAD_9:             return ImGuiKey_Keypad9;
        case AKEYCODE_NUMPAD_DOT:           return ImGuiKey_KeypadDecimal;
        case AKEYCODE_NUMPAD_DIVIDE:        return ImGuiKey_KeypadDivide;
        case AKEYCODE_NUMPAD_MULTIPLY:      return ImGuiKey_KeypadMultiply;
        case AKEYCODE_NUMPAD_SUBTRACT:      return ImGuiKey_KeypadSubtract;
        case AKEYCODE_NUMPAD_ADD:           return ImGuiKey_KeypadAdd;
        case AKEYCODE_NUMPAD_ENTER:         return ImGuiKey_KeypadEnter;
        case AKEYCODE_NUMPAD_EQUALS:        return ImGuiKey_KeypadEqual;
        case AKEYCODE_CTRL_LEFT:            return ImGuiKey_LeftCtrl;
        case AKEYCODE_SHIFT_LEFT:           return ImGuiKey_LeftShift;
        case AKEYCODE_ALT_LEFT:             return ImGuiKey_LeftAlt;
        case AKEYCODE_META_LEFT:            return ImGuiKey_LeftSuper;
        case AKEYCODE_CTRL_RIGHT:           return ImGuiKey_RightCtrl;
        case AKEYCODE_SHIFT_RIGHT:          return ImGuiKey_RightShift;
        case AKEYCODE_ALT_RIGHT:            return ImGuiKey_RightAlt;
        case AKEYCODE_META_RIGHT:           return ImGuiKey_RightSuper;
        case AKEYCODE_MENU:                 return ImGuiKey_Menu;
        case AKEYCODE_0:                    return ImGuiKey_0;
        case AKEYCODE_1:                    return ImGuiKey_1;
        case AKEYCODE_2:                    return ImGuiKey_2;
        case AKEYCODE_3:                    return ImGuiKey_3;
        case AKEYCODE_4:                    return ImGuiKey_4;
        case AKEYCODE_5:                    return ImGuiKey_5;
        case AKEYCODE_6:                    return ImGuiKey_6;
        case AKEYCODE_7:                    return ImGuiKey_7;
        case AKEYCODE_8:                    return ImGuiKey_8;
        case AKEYCODE_9:                    return ImGuiKey_9;
        case AKEYCODE_A:                    return ImGuiKey_A;
        case AKEYCODE_B:                    return ImGuiKey_B;
        case AKEYCODE_C:                    return ImGuiKey_C;
        case AKEYCODE_D:                    return ImGuiKey_D;
        case AKEYCODE_E:                    return ImGuiKey_E;
        case AKEYCODE_F:                    return ImGuiKey_F;
        case AKEYCODE_G:                    return ImGuiKey_G;
        case AKEYCODE_H:                    return ImGuiKey_H;
        case AKEYCODE_I:                    return ImGuiKey_I;
        case AKEYCODE_J:                    return ImGuiKey_J;
        case AKEYCODE_K:                    return ImGuiKey_K;
        case AKEYCODE_L:                    return ImGuiKey_L;
        case AKEYCODE_M:                    return ImGuiKey_M;
        case AKEYCODE_N:                    return ImGuiKey_N;
        case AKEYCODE_O:                    return ImGuiKey_O;
        case AKEYCODE_P:                    return ImGuiKey_P;
        case AKEYCODE_Q:                    return ImGuiKey_Q;
        case AKEYCODE_R:                    return ImGuiKey_R;
        case AKEYCODE_S:                    return ImGuiKey_S;
        case AKEYCODE_T:                    return ImGuiKey_T;
        case AKEYCODE_U:                    return ImGuiKey_U;
        case AKEYCODE_V:                    return ImGuiKey_V;
        case AKEYCODE_W:                    return ImGuiKey_W;
        case AKEYCODE_X:                    return ImGuiKey_X;
        case AKEYCODE_Y:                    return ImGuiKey_Y;
        case AKEYCODE_Z:                    return ImGuiKey_Z;
        case AKEYCODE_F1:                   return ImGuiKey_F1;
        case AKEYCODE_F2:                   return ImGuiKey_F2;
        case AKEYCODE_F3:                   return ImGuiKey_F3;
        case AKEYCODE_F4:                   return ImGuiKey_F4;
        case AKEYCODE_F5:                   return ImGuiKey_F5;
        case AKEYCODE_F6:                   return ImGuiKey_F6;
        case AKEYCODE_F7:                   return ImGuiKey_F7;
        case AKEYCODE_F8:                   return ImGuiKey_F8;
        case AKEYCODE_F9:                   return ImGuiKey_F9;
        case AKEYCODE_F10:                  return ImGuiKey_F10;
        case AKEYCODE_F11:                  return ImGuiKey_F11;
        case AKEYCODE_F12:                  return ImGuiKey_F12;
        default:                            return ImGuiKey_None;
    }
}

int32_t ImGui_ImplAndroid_HandleInputEvent(AInputEvent *input_event, ImVec2 screen_scale) {
	ImGuiIO &io = ImGui::GetIO();
    
	int32_t event_type = AInputEvent_getType(input_event);
    switch (event_type) {
        case AINPUT_EVENT_TYPE_KEY: {
            int32_t event_key_code = AKeyEvent_getKeyCode(input_event);
            int32_t event_action = AKeyEvent_getAction(input_event);
            int32_t event_meta_state = AKeyEvent_getMetaState(input_event);

            io.KeyCtrl = ((event_meta_state & AMETA_CTRL_ON) != 0);
            io.KeyShift = ((event_meta_state & AMETA_SHIFT_ON) != 0);
            io.KeyAlt = ((event_meta_state & AMETA_ALT_ON) != 0);

            switch (event_action) {
                // FIXME: AKEY_EVENT_ACTION_DOWN and AKEY_EVENT_ACTION_UP occur at once as soon as a touch pointer
                // goes up from a key. We use a simple key event queue/ and process one event per key per frame in
                // ImGui_ImplAndroid_NewFrame()...or consider using IO queue, if suitable: https://github.com/ocornut/imgui/issues/2787
                case AKEY_EVENT_ACTION_DOWN:
                case AKEY_EVENT_ACTION_UP:
                    g_KeyEventQueues[event_key_code].push(event_action);
                    break;
                default:
                    break;
            }
            break;
        }
        case AINPUT_EVENT_TYPE_MOTION: {
            int32_t event_action = AMotionEvent_getAction(input_event);
            int32_t event_pointer_index = (event_action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            event_action &= AMOTION_EVENT_ACTION_MASK;
            switch (event_action) {
                case AMOTION_EVENT_ACTION_DOWN:
                case AMOTION_EVENT_ACTION_UP:
                    // Physical mouse buttons (and probably other physical devices) also invoke the actions AMOTION_EVENT_ACTION_DOWN/_UP,
                    // but we have to process them separately to identify the actual button pressed. This is done below via
                    // AMOTION_EVENT_ACTION_BUTTON_PRESS/_RELEASE. Here, we only process "FINGER" input (and "UNKNOWN", as a fallback).
                    if ((AMotionEvent_getToolType(input_event, event_pointer_index) == AMOTION_EVENT_TOOL_TYPE_FINGER) || (AMotionEvent_getToolType(input_event, event_pointer_index) == AMOTION_EVENT_TOOL_TYPE_UNKNOWN)) {
                        io.MouseDown[0] = (event_action == AMOTION_EVENT_ACTION_DOWN);
                        ImVec2 pos(AMotionEvent_getRawX(input_event, event_pointer_index), AMotionEvent_getRawY(input_event, event_pointer_index));
                        io.MousePos = ImVec2(screen_scale.x > 0 ? pos.x / screen_scale.x : pos.x, screen_scale.y > 0 ? pos.y / screen_scale.y : pos.y);
                    }
                    break;
                case AMOTION_EVENT_ACTION_BUTTON_PRESS:
                case AMOTION_EVENT_ACTION_BUTTON_RELEASE: {
                    int32_t button_state = AMotionEvent_getButtonState(input_event);
                    io.MouseDown[0] = ((button_state & AMOTION_EVENT_BUTTON_PRIMARY) != 0);
                    io.MouseDown[1] = ((button_state & AMOTION_EVENT_BUTTON_SECONDARY) != 0);
                    io.MouseDown[2] = ((button_state & AMOTION_EVENT_BUTTON_TERTIARY) != 0);
                }
                    break;
                case AMOTION_EVENT_ACTION_HOVER_MOVE: // Hovering: Tool moves while NOT pressed (such as a physical mouse)
                case AMOTION_EVENT_ACTION_MOVE: {       // Touch pointer moves while DOWN
                    ImVec2 pos(AMotionEvent_getRawX(input_event, event_pointer_index), AMotionEvent_getRawY(input_event, event_pointer_index));
                    io.MousePos = ImVec2(screen_scale.x > 0 ? pos.x / screen_scale.x : pos.x, screen_scale.y > 0 ? pos.y / screen_scale.y : pos.y);
                    break;
                }
                case AMOTION_EVENT_ACTION_SCROLL:
                    io.MouseWheel = AMotionEvent_getAxisValue(input_event,AMOTION_EVENT_AXIS_VSCROLL,event_pointer_index);
                    io.MouseWheelH = AMotionEvent_getAxisValue(input_event,AMOTION_EVENT_AXIS_HSCROLL,event_pointer_index);
                    break;
                default:
                    break;
            }
        }
            return 1;
        default:
            break;
    }

    return 0;
}

bool ImGui_ImplAndroid_Init(ANativeWindow* window)
{
    g_Window = window;
    g_Time = 0.0;

    // Setup backend capabilities flags
    ImGuiIO& io = ImGui::GetIO();
    io.BackendPlatformName = "imgui_impl_android";
	
	io.KeyMap[ImGuiKey_Tab] = AKEYCODE_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = AKEYCODE_DPAD_LEFT;   // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_RightArrow] = AKEYCODE_DPAD_RIGHT; // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_UpArrow] = AKEYCODE_DPAD_UP;       // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_DownArrow] = AKEYCODE_DPAD_DOWN;   // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_PageUp] = AKEYCODE_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = AKEYCODE_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = AKEYCODE_MOVE_HOME;
    io.KeyMap[ImGuiKey_End] = AKEYCODE_MOVE_END;
    io.KeyMap[ImGuiKey_Insert] = AKEYCODE_INSERT;
    io.KeyMap[ImGuiKey_Delete] = AKEYCODE_FORWARD_DEL;
    io.KeyMap[ImGuiKey_Backspace] = AKEYCODE_DEL;
    io.KeyMap[ImGuiKey_Space] = AKEYCODE_SPACE;
    io.KeyMap[ImGuiKey_Enter] = AKEYCODE_ENTER;
    io.KeyMap[ImGuiKey_Escape] = AKEYCODE_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = AKEYCODE_NUMPAD_ENTER;
    io.KeyMap[ImGuiKey_A] = AKEYCODE_A;
    io.KeyMap[ImGuiKey_C] = AKEYCODE_C;
    io.KeyMap[ImGuiKey_V] = AKEYCODE_V;
    io.KeyMap[ImGuiKey_X] = AKEYCODE_X;
    io.KeyMap[ImGuiKey_Y] = AKEYCODE_Y;
    io.KeyMap[ImGuiKey_Z] = AKEYCODE_Z;

    return true;
}

void ImGui_ImplAndroid_Shutdown() {
	
}

void ImGui_ImplAndroid_Addkeyboard(int keyCode, int unicodeChar) {

    ImGuiIO& io = ImGui::GetIO();
    
        switch (keyCode)
                {
                    
                    case AKEYCODE_DPAD_UP:
                        io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = true;
                        break;
                    case AKEYCODE_DPAD_DOWN:
                        io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = true;
                        break;
                    case AKEYCODE_DPAD_LEFT:
                        io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = true;
                        break;
                    case AKEYCODE_DPAD_RIGHT:
                        io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = true;
                        break;
                    case AKEYCODE_TAB:
                        io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = true;
                        break;
                    case AKEYCODE_ENTER:
                        io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = true;
                        break;
                    case AKEYCODE_DEL:
                        io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = true;;
                        break;
                    case AKEYCODE_PAGE_UP:
                        io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = true;
                        break;
                    case AKEYCODE_PAGE_DOWN:
                        io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = true;
                        break;
                    case AKEYCODE_ESCAPE:
                        io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = true;
                        break;
                    case AKEYCODE_FORWARD_DEL:
                        io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = true;
                        break;
                    case AKEYCODE_MOVE_HOME:
                        io.KeysDown[io.KeyMap[ImGuiKey_Home]] = true;
                        break;
                    case AKEYCODE_MOVE_END:
                        io.KeysDown[io.KeyMap[ImGuiKey_End]] = true;
                        break;
                    case AKEYCODE_INSERT:
                        io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = true;
                        break;
                    default:
                        io.AddInputCharacter(unicodeChar);
                        break;
                }
}

void ImGui_ImplAndroid_NewFrame(int screen_width, int screen_height, float scaleX, float scaleY) {
	ImGuiIO& io = ImGui::GetIO();
	
	for (auto& key_queue : g_KeyEventQueues) {
		if (key_queue.second.empty())
			continue;
		io.KeysDown[key_queue.first] = (key_queue.second.front() == AKEY_EVENT_ACTION_DOWN);
		key_queue.second.pop();
	}
	
	int32_t window_width = g_Window ? screenWidth : screen_width;
	int32_t window_height = g_Window ? screenHeight : screen_height;
	int display_width = window_width;
	int display_height = window_height;
	
	io.DisplaySize = ImVec2((float)window_width, (float)window_height);
	if (window_width > 0 && window_height > 0)
		io.DisplayFramebufferScale = ImVec2((float)display_width / window_width, (float)display_height / window_height);

    
    // Setup time step
    struct timespec current_timespec;
    clock_gettime(CLOCK_MONOTONIC, &current_timespec);
    double current_time = (double)(current_timespec.tv_sec) + (current_timespec.tv_nsec / 1000000000.0);
    io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
    g_Time = current_time;
}
