#include "graphic.h"
#include "utils.h"
#include <GLES/gl.h>

void Graphic::DrawPolygon(const std::vector<float>& points, const Vec2& p,
 float angle, utils::Color color) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glTranslatef(p.x(), p.y(), 0);
    glRotatef(angle * 180.0f / PI, 0.0f, 0.0f, 1.0f);
    glColor4f(color.r(), color.g(), color.b(), color.a());
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(4.0f);
    glVertexPointer(2, GL_FLOAT, 0, &points[0]);
    glDrawArrays(GL_LINE_STRIP, 0, points.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}
