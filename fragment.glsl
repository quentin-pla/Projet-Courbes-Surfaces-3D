varying lowp vec4 col;
varying highp vec3 nor;

void main() {
    vec3 light = normalize(vec3(0.0, 0.0, -1.0));
    vec3 nor3 = normalize(nor + vec3(0.0, 1, 0.0));
    float cosTheta = clamp(dot(nor3, light), 0.1, 1.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambiantLight = vec3 (0.6, 0.6, 0.6);
    vec3 sumLight = lightColor * cosTheta + ambiantLight;
    gl_FragColor = vec4(clamp(sumLight, 0.1, 1.0), 0.1) * col;
}