#version 330

out vec3 out_Color;

in vec3 normal;
in vec4 position;
in vec2 UV;

uniform vec3 lightdir;
uniform vec3 lightcolor;
uniform vec3 camdir;

uniform mat4 M;
uniform sampler2D Mytexture;

void main()
{	
	vec3 color;
	vec3 texture_color =  texture( Mytexture, UV ).rgb;
	
	vec3 n = normalize(normal);
	vec3 l = normalize(-lightdir);
		// Eye vector (towards the camera)
	vec3 E = normalize(camdir);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	float cosTheta = clamp( dot( n,l ), 0,1 );
	 
	color =
	    // Ambient : simulates indirect lighting
	    texture_color +
	    // Diffuse : "color" of the object
	    texture_color * lightcolor * cosTheta ;
	
	//out_Color = texture_color;
	out_Color = color;
}