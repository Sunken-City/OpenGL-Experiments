#version 410
in vec3 normal, eyePosition;
out vec4 frag_color;

uniform mat4 View;

//Fixed point light properties
vec3 lightPosition = vec3(-10, 10, 10.0);
vec3 Ls = vec3(1.0, 1.0, 1.0); //White specular light color
vec3 Ld = vec3(0.7, 0.7, 0.7); //Dull white diffuse light color
vec3 La = vec3(0.2, 0.2, 0.2); //Grey ambient color

//Surface reflectance
vec3 Ks = vec3(1.0, 1.0, 1.0); //Fully reflect specular
vec3 Kd = vec3(1.0, 0.5, 0.0); //Orange diffuse surface reflectance 
vec3 Ka = vec3(1.0, 1.0, 1.0); //Fully reflect ambient
float specularExponent = 100.0; //Specular power


void main () 
{
	//Ambient Intensity
	vec3 newNormal = normalize(normal);
	vec3 Ia = La * Ka;

	//Raise the light position to eye space
	vec3 lightPosEye = vec3(View * vec4(lightPosition, 1.0));
	vec3 distanceToLightEye = lightPosEye - eyePosition;
	vec3 directionToLightEye = normalize(distanceToLightEye);
	float dotProd = max(0.0, dot(directionToLightEye, newNormal));

	//Diffuse Intensity
	vec3 Id = Ld * Kd * dotProd;

	//Specular Intensity
	vec3 reflectionEye = reflect (-directionToLightEye, newNormal);
	vec3 surfaceToViewerEye = normalize (-eyePosition);
	float dotProdSpecular = max(0.0, dot(reflectionEye, surfaceToViewerEye));
	float specularFactor = pow(dotProdSpecular, specularExponent);

	vec3 Is = Ls * Ks * specularFactor;

	//Frag Color
	frag_color = vec4 (Is + Id + Ia, 1.0);
}

//  vec3 s = normalize(vec3(lightPosition - eyePosition));
//  vec3 v = normalize(-eyePosition.xyz);
//  vec3 r = reflect(-s, normal);
//  vec3 ambient = La * Ka;
//  float sDotN = max(dot(s, normal), 0.0);
//  vec3 diffuse = Ld * Kd * sDotN;
//  vec3 spec = vec3(0.0);
//  if(sDotN > 0.0)
//	spec = Ls * Ks * pow(max(dot(r,v), 0.0), specularExponent);

  //vec3 lightIntensity = ambient + diffuse + spec;

  //frag_color = vec4 (lightIntensity, 1.0);