shader_type canvas_item;

uniform vec4 positive_color; 
uniform vec4 negative_color;
uniform vec4 zero_color;

void fragment() {
	COLOR = texture(TEXTURE, UV); //read from texture
  	float value = ((.3 * COLOR.r + .3 * COLOR.b + .3 * COLOR.g) * 2.0)- 1.0;
	
	if (value < .0)
	{
		COLOR = (1.0 - value) * negative_color;
	}
	else if (value > .0)
	{
		COLOR = value * positive_color;
	}
	else
	{
		COLOR = value * zero_color;
	}
}
