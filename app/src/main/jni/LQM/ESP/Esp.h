#ifndef ESP_H
#define ESP_H


#include <jni.h>


class ESP {

public:
    ESP() {
        
    }

    void
    DrawLine(Color color, float thickness, Vector2 start, Vector2 end) {
        ImGui::GetForegroundDrawList()->AddLine(
        ImVec2(start.x, start.y),
        ImVec2(end.x, end.y),
        IM_COL32(color.R, color.G, color.B, color.A),
        thickness
    );
    }

    void DrawText(Color color, const char *txt, Vector2 pos, float size) {
        
        ImGui::GetForegroundDrawList()->AddText(
        ImVec2(pos.x, pos.y),
        IM_COL32(color.R, color.G, color.B, color.A),
        txt
    );/*.FontSize = size;*/

    }

    void DrawCircle(Color color,float stroke, Vector2 pos, float radius) {
       
       ImGui::GetForegroundDrawList()->AddCircle(
        ImVec2(pos.x, pos.y),
        radius,
        IM_COL32(color.R, color.G, color.B, color.A),
        12, // Số lượng đoạn thẳng để vẽ đường tròn
        stroke
    );

    }
    
    void DrawBox(Color color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.m_XMin, rect.m_YMin);
        Vector2 v2 = Vector2(rect.m_XMin + rect.m_Width, rect.m_YMin);
        Vector2 v3 = Vector2(rect.m_XMin + rect.m_Width, rect.m_YMin + rect.m_Height);
        Vector2 v4 = Vector2(rect.m_XMin, rect.m_YMin + rect.m_Height);

        DrawLine(color, stroke, v1, v2); // ALINHAR
        DrawLine(color, stroke, v2, v3); // LINHA DIREITA
        DrawLine(color, stroke, v3, v4); // LINHA ABAIXO
        DrawLine(color, stroke, v4, v1); // LINHA ESQUERDA
    }


    void DrawHorizontalHealthBar(Vector2 screenPos, float width, float maxHealth, float currentHealth) {
        screenPos -= Vector2(0.0f, 8.0f);
        DrawBox(Color(0, 0, 0, 255), 3, Rect(screenPos.x, screenPos.y, width + 2, 5.0f));
        screenPos += Vector2(1.0f, 1.0f);
        Color clr = Color(0, 255, 0, 255);
        float hpWidth = (currentHealth * width) / maxHealth;
        if (currentHealth <= (maxHealth * 0.6)) {
            clr = Color(255, 255, 0, 255);
        }
        if (currentHealth < (maxHealth * 0.3)) {
            clr = Color(255, 0, 0, 255);
        }
        DrawBox(clr, 3, Rect(screenPos.x, screenPos.y, hpWidth, 3.0f));
    }

    void DrawCrosshair(Color clr, Vector2 center, float size, float thickness) {
        float x = center.x - (size / 2.0f);
        float y = center.y - (size / 2.0f);
        DrawLine(clr, thickness, Vector2(x, center.y), Vector2(x + size, center.y));
        DrawLine(clr, thickness, Vector2(center.x, y), Vector2(center.x, y + size));
    }
    
    void DrawB(Vector2 pos, float height,float widght) {
        Vector2 v1 = Vector2(pos.x, pos.y-height/2-1);
        Vector2 v2 = Vector2(pos.x + widght, pos.y-height/2-1);
        Color clr2 = Color(255, 0, 0, 80);
        DrawLine(clr2, height, v1, v2);
    }
    
    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        
        ImGui::GetForegroundDrawList()->AddCircleFilled(
        ImVec2(pos.x, pos.y),
        radius,
        IM_COL32(color.R, color.G, color.B, color.A),
        12 // Số lượng đoạn thẳng để vẽ đường tròn
    );

    }
	
	void DrawFilledCircle2(Color color, Vector3 pos, float radius) {
        
        ImVec2 screenPos = ImGui::GetIO().DisplayFramebufferScale * ImVec2(pos.x, pos.y);
    ImGui::GetForegroundDrawList()->AddCircleFilled(
        screenPos,
        radius,
        IM_COL32(color.R, color.G, color.B, color.A),
        12
    );

    }
    
	void DrawText2(Color color, float stroke, std::string str, Vector3 pos, float size) {
        
		ImVec2 screenPos = ImGui::GetIO().DisplayFramebufferScale * ImVec2(pos.x, pos.y);
    ImGui::GetForegroundDrawList()->AddText(
        screenPos,
        IM_COL32(color.R, color.G, color.B, color.A),
        str.c_str()
    );
    }

	
    
    void DrawH(Vector2 pos,float curHp, float maxHp, float height,float widght, float stroke) {
        Vector2 v1 = Vector2(pos.x + widght/2 + stroke-1, pos.y - stroke+1);
        Vector2 v2 = Vector2(pos.x + widght/2 + stroke-1, pos.y - height - stroke+1);
        
        Color clr1 = Color(0, 0, 0, 255);
        DrawLine(clr1, widght + stroke, v1, v2);
        
        float args0 = (curHp * height) / maxHp;
        Vector2 v3 = Vector2(pos.x + widght/2 + stroke-1, pos.y - stroke-1);
        Vector2 v4 = Vector2(pos.x + widght/2 + stroke-1, pos.y - args0);
        Color clr2 = Color(0, 255, 0, 255);
        if (curHp <= (maxHp * 0.6)) clr2 = Color(255, 255, 0, 255);
        if (curHp < (maxHp * 0.3)) clr2 = Color(255, 0, 0, 255);
        
        char hp_str[0xFF] = {0};
        string s;
        s.append(std::to_string((int)(curHp/maxHp*100)).c_str());
        s.append("%");
        strcpy(hp_str, s.c_str());
        
        DrawText(Color::White(), hp_str, v4 - Vector2(height/10+14,-(height/10+0)), height/10+2);
        DrawLine(clr2, widght, v3, v4);

}
    
};

#endif
