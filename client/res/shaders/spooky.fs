uniform sampler2D texture;
uniform float timeAccumulator;

float malformed_euclidean_distance(vec2 v1, vec2 v2, float xStretch) {
    vec2 d = v2 - v1;
    d.x *= xStretch;
	return sqrt(d.x * d.x + d.y * d.y);
}
void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec2 center = vec2(0.5, 0.5);
    float speed = 5.0;

    float timeCounter = speed * timeAccumulator * 0.001;
    float periodic_divider = 10.0;
    float normalized_sin = (sin(timeCounter) + 1.0) / 2.0;
    float periodic = 1.0 - ( normalized_sin / periodic_divider);


    float distance = malformed_euclidean_distance(center, gl_TexCoord[0].xy, 16.0/9.0);

    gl_FragColor = vec4(pixel.rgb, 1.0 - 2.0 * periodic * distance);
    //gl_FragColor = vec4(pixel.rgb, value);
}