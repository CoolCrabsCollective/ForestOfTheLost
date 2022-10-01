uniform sampler2D texture;

float malformed_euclidean_distance(vec2 v1, vec2 v2, float xStretch) {
    vec2 d = v2 - v1;
    d.x *= xStretch;
	return sqrt(d.x * d.x + d.y * d.y);
}
void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec2 center = vec2(0.5, 0.5);
    float speed = 2.0;

    float distance = malformed_euclidean_distance(center, gl_TexCoord[0].xy, 16.0/9.0);

    gl_FragColor = vec4(pixel.rgb, 1.0 - 2.0 * distance);
}