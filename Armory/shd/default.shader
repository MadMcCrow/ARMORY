shader_type spatial;
render_mode diffuse_burley;

uniform vec4 color : hint_color;
uniform float metalicness ;

void vertex ()
{

}

void fragment()
{
	METALLIC = metalicness;
	SPECULAR = 0.8;
	ROUGHNESS = 0.01;
	ALBEDO = color.xyz;
}