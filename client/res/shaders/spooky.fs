uniform sampler2D texture;

float euclidean_distance(vec2 v1, vec2 v2) {
    vec2 d = v2 - v1;
	return sqrt(d.x * d.x + d.y * d.y);
}

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec2 center = vec2(0.5, 0.5);
    float speed = 2.0;

    float distance = euclidean_distance(center, gl_TexCoord[0].xy);
    //vec2 center = vec2(textureDimensions.x / 2.0, textureDimensions.y / 2.0);

    //pixel.b = center.r;
    //gl_FragColor = gl_Color * pixel;
    gl_FragColor = vec4(pixel.rgb, 1.0 - distance);
}