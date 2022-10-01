uniform sampler2D texture;
uniform float timeAccumulator;

#define PI 3.141592654

void main()
{
    float darkness_interval = 10.0f;
    float accumulated_time = mod(timeAccumulator * 0.001, darkness_interval);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    float darkness_duration = 2.0;

    float darkness_threshold_min = darkness_interval - darkness_duration / 2.0;
    float darkness_threshold_max = mod(darkness_interval + darkness_duration / 2.0, 10.0);

    float ten_second_darkness_multiplier = (sin(timeAccumulator * 0.001 * 2.0 * PI / darkness_duration - PI/2.0) + 1.0) / 2.0;

    if(accumulated_time < darkness_threshold_max || accumulated_time > darkness_threshold_min)
    {
        gl_FragColor = vec4(pixel.rgba);
    }
    else
    {
        gl_FragColor = vec4(pixel.rgb, 1.0 - ten_second_darkness_multiplier);
    }
}