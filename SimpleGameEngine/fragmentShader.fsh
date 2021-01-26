uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
varying highp vec4 v_position;
varying highp vec2 v_textCoord;
varying highp vec3 v_normal;


void main(void)
{
    vec4 resultColor = vec4(0 , 0 , 0 , 0);
    vec4 eyePosition = vec4(0 , 0 , 0 , 0);

    vec4 diffMatColor = texture2D(u_texture, v_textCoord);

    vec3 lightVector = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVector , v_normal));

    float ambientFactor = 0.1 ;
    float distance = length(v_position.xyz - eyePosition.xyz);

    vec4 diffuseColor = diffMatColor * u_lightPower * max(0.0 , dot(v_normal , -lightVector)) / (1.0 + 0.25 * pow(distance , 2.0));
    resultColor += diffuseColor;

    vec4 ambientColor = diffMatColor * ambientFactor;
     resultColor += ambientColor;

    gl_FragColor = resultColor;

}





























/*
    vec4 resultColor = vec4(0 , 0 , 0 , 0);
    vec4 eyePosition = vec4(0 , 0 , 0 , 0);

    vec4 diffMatColor = texture2D(u_texture, v_textCoord);

    vec3 lightVector = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVector , v_normal));

    float ambientFactor = 0.1 ;
    float distance = length(v_position.xyz - eyePosition.xyz);

    vec4 diffuseColor = diffMatColor * u_lightPower * max(0.0 , dot(v_normal , -lightVector)) / (1.0 + 0.25 * pow(distance , 2.0));
    resultColor += diffuseColor;

    vec4 ambientColor = diffMatColor * ambientFactor;
     resultColor += ambientColor;

    gl_FragColor = resultColor;
  */

/*
  //
  //    vec3 eyeVector = normalize(v_position.xyz - eyePosition.xyz);
    float speculatorFactor = 10.0;
    float ambientFactor = 0.1 ;
  */
