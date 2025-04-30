/////////////////////////////////////////////////////
// PBR繝ｩ繧､繝・ぅ繝ｳ繧ｰ縺ｧ菴ｿ縺・Λ繧､繝育畑縺ｮ螳壽焚繝舌ャ繝輔ぃ縺ｮ荳ｭ霄ｫ縲・
/////////////////////////////////////////////////////

#ifndef _PBRLIGHTING_LIGHTCB_BODY_H_
#define _PBRLIGHTING_LIGHTCB_BODY_H_

DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
PointLight pointLight[MAX_POINT_LIGHT];
SpotLight spotLight[MAX_SPOT_LIGHT];
float4x4 mViewProjInv;  // 繝薙Η繝ｼ繝励Ο繧ｸ繧ｧ繧ｯ繧ｷ繝ｧ繝ｳ陦悟・縺ｮ騾・｡悟・
float3 eyePos;          // 繧ｫ繝｡繝ｩ縺ｮ隕也せ
int numPointLight;      // 繝昴う繝ｳ繝医Λ繧､繝医・謨ｰ縲・   
float3 ambientLight;    // 迺ｰ蠅・・
int numSpotLight;       // 繧ｹ繝昴ャ繝医Λ繧､繝医・謨ｰ縲・
float4x4 mlvp[NUM_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];
float iblLuminance;     // IBL縺ｮ譏弱ｋ縺輔・
int isIBL;              // IBL繧定｡後≧縲・
int isEnableRaytracing; // 繝ｬ繧､繝医Ξ縺梧怏蜉ｹ縲・

#endif // _PBRLIGHTING_LIGHTCB_BODY_H_