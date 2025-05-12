/*!
 * @brief	火打ち石用のシェーダー。
 */


#include "Sampler.h"

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////

// ピクセルシェーダーへの入力
struct SPSIn
{
	float4 pos : SV_POSITION; //座標。
	float3 normal : NORMAL; //法線。
	float3 tangent : TANGENT; //接ベクトル。
	float3 biNormal : BINORMAL; //従ベクトル。
	float2 uv : TEXCOORD0; //UV座標。
	float3 worldPos : TEXCOORD1; // ワールド座標
    float3 posInView : TEXCOORD2;
    float3 normalInView : TEXCOORD3;
};


///////////////////////////////////////
// 定数バッファ。
///////////////////////////////////////
// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////

// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos : POSITION; //頂点座標。
    float3 normal : NORMAL; //法線。
    float2 uv : TEXCOORD0; //UV座標。
    float3 tangent : TANGENT; //接ベクトル。
    float3 biNormal : BINORMAL; //従ベクトル。
};


////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

// モデル用の頂点シェーダーのエントリーポイント
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psIn;
    
    // 頂点座標をワールド座標系に変換する。
    psIn.pos = mul(mWorld, vsIn.pos);
    
    // 頂点シェーダーからワールド座標を出力
	psIn.worldPos = psIn.pos;

	psIn.pos = mul(mView, psIn.pos); // ワールド座標系からカメラ座標系に変換
    psIn.posInView = psIn.pos.xyz;
	psIn.pos = mul(mProj, psIn.pos); // カメラ座標系からスクリーン座標系に変換
    
	psIn.uv = vsIn.uv;
    psIn.normal = mul(mWorld, vsIn.normal);
    psIn.normalInView = mul(mView, psIn.normal);
	
	return psIn;
}
Texture2D<float4> albedoTexture : register(t0); // アルベド

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMainCore( SPSIn In, uniform int isSoftShadow ) 
{
	//G-Bufferの内容を使ってライティング
    //アルベドカラーをサンプリング。
    float4 albedoColor = albedoTexture.Sample(Sampler, In.uv);
    
    float2 viewportPos = In.pos.xy;

    
    // ここで計算しているのは石全体に掛かる光。1000離れると光が０
    float3 lig = lerp(0.001f/*マックスの光の強さ*/, 0.0f, saturate(length(In.posInView) / 1000.0f));
    // ここで計算しているのがエッジの光。
    float3 rim = float3(
        pow((1 - abs(In.normalInView.z)), 10.0f/*リムの絞り*/) * 0.01f,
        pow((1 - abs(In.normalInView.z)), 10.0f /*リムの絞り*/) * 0.01f,
        pow((1 - abs(In.normalInView.z)), 10.0f /*リムの絞り*/) * 0.01f);
    // 2000離れるとエッジの光も０
    rim *= lerp(1, 0, saturate(length(In.posInView) / 1000.0f));
    lig += rim;
    
	float4 finalColor = 1.0f;
    finalColor.xyz = albedoColor * lig ;
    return float4(finalColor.xyz, albedoColor.a);
}
float4 PSMain(SPSIn In) : SV_Target0
{
    return PSMainCore(In, false);
}
