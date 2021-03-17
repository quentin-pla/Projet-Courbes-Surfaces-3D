varying lowp vec4 col;
varying highp vec3 nor;

void main() {
   vec3 light = normalize(vec3(0.0, 0.0, 10.0));
   vec3 nor3 = normalize(nor);
   float cosTheta = clamp( dot(nor3,light ), 0.3 , 1.0 );
   vec3 lightColor = vec3(1.0, 1.0, 1.0);

   vec3 ambiantLight = vec3 (0.3, 0.3, 0.3);
   vec3 sumLight = lightColor * cosTheta + ambiantLight;
   gl_FragColor = vec4(clamp(sumLight, 0.0, 1.0), 1.0) * col;
}