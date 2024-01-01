#pragma once

#include "imgui.h"

namespace ImGui
{
    
    IMGUI_API void LoadingIndicatorCircle(const char* label, const float indicator_radius,
                                   const ImVec4& main_color, const ImVec4& backdrop_color,
                                   const int circle_count, const float speed);
                                   
	IMGUI_API bool Toggle( const char* label, bool* v );

	IMGUI_API bool ButtonScrollableEx( const char* label, const ImVec2& size_arg = ImVec2( 0, 0 ), ImGuiButtonFlags flags = 0 );
	IMGUI_API bool ButtonScrollable( const char* label, const ImVec2& size_arg = ImVec2( 0, 0 ) );
}
