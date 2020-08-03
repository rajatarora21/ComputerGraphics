#version 330 core
in vec2 uv;
in vec3 shadowCoord;
in vec3 normal;
in vec3 lightDir;
in vec3 viewDir;

out vec4 FragColor;

uniform float roughness=1.0;
uniform sampler2D tex;
uniform sampler2DShadow shadowTex;

void main()
{
    vec4 baseColor=texture(tex,uv);
    float atten=texture(shadowTex,shadowCoord);

    vec3 N=normalize(normal);
    vec3 L=normalize(lightDir);
    vec3 E=normalize(viewDir);

    vec3 R=reflect(-L,N);

    float diff=max(dot(N,L),0);
    float spec=pow(max(dot(R,E),0),32);

    diff=mix(0.2,1.0,atten*diff);

    FragColor = vec4(baseColor.rgb*diff+spec*atten*(1-roughness), baseColor.a);
    //FragColor.rgb=vec3(diff);
};
