shader_type canvas_item;

uniform vec4 land_color;
uniform vec4 sea_color;
uniform float sea_level;

float remap(float value, float in_min ,float in_max, float out_min, float out_max)
{
    return out_min + (out_max - out_min) * ((value - in_min) / (in_max - in_min));
}


void fragment() {
	COLOR = texture(TEXTURE, UV); //read from texture
  	float value = (.3 * COLOR.r + .3 * COLOR.b + .3 * COLOR.g);
	
	if (value < sea_level)
	{
		COLOR.rgb = sea_color.rgb * remap(value, 0., sea_level, 0.,1.);
	}
	else 
	{
		COLOR.rgb = land_color.rgb * (1. - remap(value,sea_level,1.,0.,1.));
	}
}
