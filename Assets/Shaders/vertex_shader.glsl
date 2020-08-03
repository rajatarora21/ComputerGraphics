#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aUv;
layout (location = 2) in vec3 aNormal;

uniform mat4 worldMatrix;  
uniform mat4 viewMatrix = mat4(1.0); 
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 lightTransformMatrix;  


uniform mat4 lightVP;

out vec2 uv;
out vec3 shadowCoord;
out vec3 normal;
out vec3 lightDir;
out vec3 viewDir;

void main()
{
  mat4 MV=viewMatrix*worldMatrix;
  normal=inverse(transpose(mat3(MV)))*aNormal;
  vec3 fragPos=vec3(MV* vec4(aPos,1));
  vec3 lightPos=vec3(viewMatrix*lightTransformMatrix* vec4(0,30,0,1));

  viewDir=-fragPos;
  lightDir=lightPos-fragPos;
  
  uv = aUv.xy;

  vec4 shadowNDC=(lightVP*worldMatrix)*vec4(aPos, 1.0);

  if(abs(shadowNDC.x)>shadowNDC.w||abs(shadowNDC.y)>shadowNDC.w||abs(shadowNDC.z)>shadowNDC.w)
  {
    shadowCoord=vec3(0,0,-1);
  }
  else
  {
    shadowNDC.xyz/=shadowNDC.w;
    shadowCoord=shadowNDC.xyz*0.5+0.5;
  }

  mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
  gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};
