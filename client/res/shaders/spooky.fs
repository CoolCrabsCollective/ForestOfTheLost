uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    pixel.g = 1.0;
    gl_FragColor = gl_Color * pixel;
}