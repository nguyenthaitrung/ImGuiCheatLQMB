#include <jni.h>

Color colorByDistance(int distance, float alpha){
    Color _colorByDistance;
    if (distance < 450)
        _colorByDistance = Color(255,0,0, alpha);
    if (distance < 200)
        _colorByDistance = Color(255,0,0, alpha);
    if (distance < 121)
        _colorByDistance = Color(0,10,51, alpha);
    if (distance < 51)
        _colorByDistance = Color(0,67,0, alpha);
    return _colorByDistance;
}
Vector2 pushToScreenBorder(Vector2 Pos, Vector2 screen, int offset) {
    int X = (int)Pos.x;
    int Y = (int)Pos.y;
    if (Pos.y < 50) {
        // top
        Y = 42 - offset;
    }
     if (Pos.x > screen.x) {
        // right
        X =  (int)screen.x + offset;
    }
    if (Pos.y > screen.y) {
        // bottom
        Y = (int)screen.y +  offset;
    }
    if (Pos.x < 60) {
        // left
        X = 20 - offset;
    }
    return Vector2(X, Y);
}
bool isOutsideSafeZone(Vector2 pos, Vector2 screen) {
    if (pos.y < 60) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 50;
    
}

