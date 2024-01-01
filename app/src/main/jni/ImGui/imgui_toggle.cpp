#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_toggle.h"
#include "font6.h"
#include <math.h>
#include <cmath>
#include <algorithm>

void ImGui::LoadingIndicatorCircle(const char* label, const float indicator_radius,
                                   const ImVec4& main_color, const ImVec4& backdrop_color,
                                   const int circle_count, const float speed) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems) {
        return;
    }

    ImGuiContext& g = *GImGui;
    const ImGuiID id = window->GetID(label);
    ImGuiStyle &style = ImGui::GetStyle();
    
    const ImVec2 pos = window->DC.CursorPos;
    const float circle_radius = indicator_radius / 10.0f;
    const ImRect bb(pos, ImVec2(pos.x + indicator_radius * 2.0f,
                                pos.y + indicator_radius * 2.0f));
    ItemSize(bb, style.FramePadding.y);
    if (!ItemAdd(bb, id)) {
        return;
    }
    const float t = g.Time;
    const auto degree_offset = 2.0f * IM_PI / circle_count;
    for (int i = 0; i < circle_count; ++i) {
        const auto x = indicator_radius * std::sin(degree_offset * i);
        const auto y = indicator_radius * std::cos(degree_offset * i);
        const auto growth = std::max(0.0f, std::sin(t * speed - i * degree_offset));
        ImVec4 color;
        color.x = main_color.x * growth + backdrop_color.x * (1.0f - growth);
        color.y = main_color.y * growth + backdrop_color.y * (1.0f - growth);
        color.z = main_color.z * growth + backdrop_color.z * (1.0f - growth);
        color.w = 1.0f;
        window->DrawList->AddCircleFilled(ImVec2(pos.x + indicator_radius + x,
                                                 pos.y + indicator_radius - y),
                                                 circle_radius + growth * circle_radius,
                                                 GetColorU32(color));
    }
}

bool ImGui::Toggle( const char* label, bool* v )
{
    
	ImGuiWindow* window = GetCurrentWindow( );
	if ( window->SkipItems )
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID( label );
	const ImVec2 label_size = CalcTextSize( label, NULL, true );

	float height = ImGui::GetFrameHeight( );
	const ImVec2 pos = window->DC.CursorPos;

	float width = height * 2.f;
	float radius = height * 0.50f;

	const ImRect total_bb( pos, pos + ImVec2( width + ( label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f ), label_size.y + style.FramePadding.y * 2.0f ) );

	ItemSize( total_bb, style.FramePadding.y );
	if ( !ItemAdd( total_bb, id ) )
		return false;

	float last_active_id_timer = g.LastActiveIdTimer;

    ImU32 color_active = ImGui::GetColorU32(IM_COL32_WHITE);
    
    
    
	bool hovered, held;
	bool pressed = ButtonBehavior( total_bb, id, &hovered, &held );
	if ( pressed )
	{
		*v = !( *v );
		MarkItemEdited( id );
		g.LastActiveIdTimer = 0.f;
        
	}

	if ( g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed )
		g.LastActiveIdTimer = last_active_id_timer;

	float t = *v ? 1.0f : 0.0f;

	if ( g.LastActiveId == id )
	{
		float t_anim = ImSaturate( g.LastActiveIdTimer / 0.16f );
		t = *v ? ( t_anim ) : ( 1.0f - t_anim );
	}

    
    const char* text_status = ICON_FA_FACE_MEH;
    
    if(*v){
        text_status = ICON_FA_FACE_SMILE;
        color_active = ImGui::GetColorU32(IM_COL32(0, 128, 0, 255));
    }
	ImU32 col_bg = GetColorU32( ( held && hovered ) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg );

	const ImRect frame_bb( pos, pos + ImVec2( width, height ) );

	RenderFrame( frame_bb.Min, frame_bb.Max, col_bg, true, height * 0.5f );
	RenderNavHighlight( total_bb, id );

    
    ImVec2 textSize = CalcTextSize(text_status);
    
	ImVec2 label_pos = ImVec2( frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y );
	RenderText( label_pos, label );
    window->DrawList->AddText(ImVec2( pos.x + t * ( width - radius * 2.0f ), pos.y + 5), color_active, text_status);

	//window->DrawList->AddCircleFilled( ImVec2( pos.x + radius + t * ( width - radius * 2.0f ), pos.y + radius ), radius - 1.5f,  color_active, 36 );

	return pressed;
}

bool ImGui::ButtonScrollableEx( const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags )
{
	ImGuiWindow* window = GetCurrentWindow( );
	if ( window->SkipItems )
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID( label );
	const ImVec2 label_size = CalcTextSize( label, NULL, true );

	ImVec2 pos = window->DC.CursorPos;
	if ( ( flags & ImGuiButtonFlags_AlignTextBaseLine ) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset ) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = CalcItemSize( size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f );

	const ImRect bb( pos, pos + size );
	ItemSize( size, style.FramePadding.y );
	if ( !ItemAdd( bb, id ) )
		return false;

	if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
		flags |= ImGuiButtonFlags_Repeat;

	bool hovered, held;
	bool pressed = ButtonBehavior( bb, id, &hovered, &held, flags );

	const ImU32 col = GetColorU32( ( held && hovered ) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button );
	RenderNavHighlight( bb, id );
	RenderFrame( bb.Min, bb.Max, col, true, style.FrameRounding );

	const float offset = size.x >= label_size.x + style.FramePadding.x * 2.0f ? size.x + style.FramePadding.x : static_cast< int >( g.Time * 60.f ) % static_cast< int >( label_size.x + size.x + style.FramePadding.x * 2.f + 4 );
	const ImRect text = ImRect( ImVec2( bb.Min.x + size.x - offset + style.FramePadding.x * 2.f, bb.Min.y + style.FramePadding.y ), bb.Max - style.FramePadding );

	RenderTextClipped( text.Min, text.Max, label, NULL, &label_size, size.x >= label_size.x + style.FramePadding.x * 2.0f ? g.Style.ButtonTextAlign : ImVec2( 0, 0 ), &bb );
	return pressed;
}

bool ImGui::ButtonScrollable( const char* label, const ImVec2& size_arg )
{
	return ButtonScrollableEx( label, size_arg, ImGuiButtonFlags_None );
}
