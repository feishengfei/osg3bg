#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform int segments;

void main()
{
    float delta = 1.0 / float(segments);
    vec4 v;
    for (int i = 0; i <= segments; ++i)
    {
        float t = delta * float(i);
        float t2 = t * t;
        float one_minus_t = 1.0 - t;
        float one_minus_t2 = one_minus_t * one_minus_t;
        v = gl_PositionIn[0] * one_minus_t2 * one_minus_t +
            gl_PositionIn[1] * 3.0 * t * one_minus_t2 +
            gl_PositionIn[2] * 3.0 * t2 * one_minus_t +
            gl_PositionIn[3] * t2 * t;
        gl_Position = v;
        EmitVertex();
    }
    EndPrimitive();
}
