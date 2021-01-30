attribute highp vec4 a_position;
attribute highp vec2 a_textCoord;
attribute highp vec3 a_normal;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_projectionMatrix;
varying highp vec2 v_textCoord;


void main(void)
{
    mat4 modelviewMatrix = u_viewMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * modelviewMatrix * a_position;
    v_textCoord = a_textCoord;
}
