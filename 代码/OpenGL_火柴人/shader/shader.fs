#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 FragPos;

uniform vec3 color;
uniform vec3 eyePos;
uniform vec3 lightPos1;
uniform vec3 lightColor1;
uniform vec3 lightPos2;
uniform vec3 lightColor2;

void main()
{    
	vec3 N = normalize(normal);
	vec3 Cs = vec3(0.1,0.1,0.1); 
	vec3 Cd = vec3(0.5,0.5,0.5);
	vec3 Ca = vec3(0.2,0.2,0.2); 
	vec3 V = normalize(eyePos-FragPos); //眼睛方向
	float K = 64;

	// 光源1 漫反射
    vec3 L1 = normalize(lightPos1-FragPos);  //入射方向
    float diff1=max(dot(N,L1),0.0);
    vec3 diffuse1=diff1*lightColor1;
    vec3 D1=diffuse1*Cd;
	vec3 result = D1;

	//镜面反射
	vec3 R1 = reflect(-L1,N);      //反射方向
	float spec1 = pow(max(dot(V,R1),0.0),K);
	vec3 S1=Cs*spec1*lightColor1;
	result=result+S1;

	//光源2 漫反射
    vec3 L2=normalize(lightPos2-FragPos);
    float diff2=max(dot(N,L2),0.0);
    vec3 diffuse2=diff2*lightColor2;
	vec3 D2 = diffuse2*Cd;
    result=result + D2;

	//镜面反射
	vec3 R2=reflect(-L2,N);
	float spec2=pow(max(dot(V,R2),0.0),K);
	vec3 S2=Cs*spec2*lightColor2;
	result=result+S2;

	vec3 A = Ca * (lightColor1 + lightColor2 );
	result = result + A;

    FragColor = vec4(color, 0.0f)*vec4(result,1.0);
}