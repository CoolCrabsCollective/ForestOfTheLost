uniform sampler2D texture;
uniform float timeAccumulator;
uniform float grayscaleness;

#define PI 3.141592654

float malformed_euclidean_distance(vec2 v1, vec2 v2, float xStretch) {
    vec2 d = v2 - v1;
    d.x *= xStretch;
	return sqrt(d.x * d.x + d.y * d.y);
}

void main()
{
    float darkness_interval = 10.0;
    float accumulated_time = mod(timeAccumulator * 0.001, darkness_interval);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec2 center = vec2(0.5, 0.5);
    float speed = 5.0;

    float timeCounter = speed * timeAccumulator * 0.001;
    float periodic_divider = 10.0;
    float normalized_sin = (sin(timeCounter) + 1.0) / 2.0;
    float periodic = 1.0 - ( normalized_sin / periodic_divider);

    float distance = malformed_euclidean_distance(center, gl_TexCoord[0].xy, 16.0/9.0);

    float darkness_duration = 2.0;

    float darkness_threshold_min = darkness_interval - darkness_duration / 2.0;
    float darkness_threshold_max = mod(darkness_interval + darkness_duration / 2.0, 10.0);

    float ten_second_darkness_multiplier = (sin(timeAccumulator * 0.001 * 2.0 * PI / darkness_duration - PI/2.0) + 1.0) / 2.0;

    float ambient_darkness = 1.0 - 2.0 * periodic * distance;

    if(accumulated_time < darkness_threshold_max || accumulated_time > darkness_threshold_min)
        gl_FragColor = vec4(pixel.rgb, ambient_darkness * ten_second_darkness_multiplier);
    else
        gl_FragColor = vec4(pixel.rgb, ambient_darkness);

	float gray = 0.299 * gl_FragColor.r + 0.587 * gl_FragColor.g + 0.114 * gl_FragColor.b;

	gl_FragColor = vec4(vec3(gray) * grayscaleness + gl_FragColor.rgb * (1.0 - grayscaleness), gl_FragColor.a);
}