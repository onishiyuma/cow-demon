/*!
 * @brief	繧ｹ繝励Λ繧､繝医す繧ｧ繝ｼ繝繝ｼ縲?
 */

cbuffer cb : register(b0){
	float4x4 mvp;		// 繝｢繝?繝ｫ繝薙Η繝ｼ繝励Ο繧ｸ繧ｧ繧ｯ繧ｷ繝ｧ繝ｳ陦悟??
	float4 mulColor;	// 荵礼ｮ励き繝ｩ繝ｼ縲ゅヴ繧ｯ繧ｻ繝ｫ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ蜃ｺ蜉帷ｵ先棡縺ｫ荵礼ｮ励＆繧後∪縺吶?
};
struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}
float4 PSMainGamma( PSInput In ) : SV_Target0
{
	float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	color.xyz =  pow(max( color.xyz, 0.0001f ), 1.0f/2.2f);
	return color;
}