#version 120


uniform sampler2D texture;
uniform float hit_multiplier;

void main() {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec3 red = vec3(1.0, 0.0, 0.0);
    gl_FragColor = vec4(pixel.rgb * (1.0 - hit_multiplier) + red * hit_multiplier, pixel.a);
}
