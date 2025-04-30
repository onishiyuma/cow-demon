/////////////////////////////////////////////////////
// PBR繝ｩ繧､繝・ぅ繝ｳ繧ｰ髢｢菫ゅ・讒矩菴薙ｒ縺ｾ縺ｨ繧√◆繝倥ャ繝繝ｼ繝輔ぃ繧､繝ｫ
/////////////////////////////////////////////////////

#ifndef _PBRLIGHTING_STRUCT_H_
#define _PBRLIGHTING_STRUCT_H_

// 繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝域ｧ矩菴薙・
struct DirectionalLight
{
    float3 direction;   // 繝ｩ繧､繝医・譁ｹ蜷・
    int castShadow;     // 蠖ｱ繧偵く繝｣繧ｹ繝医☆繧具ｼ・
    float4 color;       // 繝ｩ繧､繝医・濶ｲ
};
// 繝昴う繝ｳ繝医Λ繧､繝・
struct PointLight
{
    float3 position;        // 蠎ｧ讓・
    float3 positionInView;  // 繧ｫ繝｡繝ｩ遨ｺ髢薙〒縺ｮ蠎ｧ讓・
    float3 color;           // 繧ｫ繝ｩ繝ｼ
    float3 attn;            // 貂幄｡ｰ繝代Λ繝｡繝ｼ繧ｿ縲・
};
// 繧ｹ繝昴ャ繝医Λ繧､繝・
struct SpotLight
{
    float3 position;        // 蠎ｧ讓・
    int isUse;              // 菴ｿ逕ｨ荳ｭ繝輔Λ繧ｰ縲・
    float3 positionInView;  // 繧ｫ繝｡繝ｩ遨ｺ髢薙〒縺ｮ蠎ｧ讓吶・
    int no ;                // 繝ｩ繧､繝医・逡ｪ蜿ｷ縲・
    float3 direction;       // 蟆・・譁ｹ蜷代・
    float range;            // 蠖ｱ髻ｿ遽・峇縲・
    float3 color;           // 繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ縲・
    float3 color2;          // 莠後▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲・
    float3 color3;          // 荳峨▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲・
    float3 directionInView; // 繧ｫ繝｡繝ｩ遨ｺ髢薙〒縺ｮ蟆・・譁ｹ蜷代・
    float3 rangePow;        // 霍晞屬縺ｫ繧医ｋ蜈峨・蠖ｱ髻ｿ邇・↓邏ｯ荵励☆繧九ヱ繝ｩ繝｡繝ｼ繧ｿ繝ｼ縲・.0縺ｧ邱壼ｽ｢縺ｮ螟牙喧繧偵☆繧九・
                            // x縺御ｸ縺､逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲【縺御ｺ後▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲】縺御ｸ峨▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲・
    float3 angle;           // 蟆・・隗貞ｺｦ(蜊倅ｽ搾ｼ壹Λ繧ｸ繧｢繝ｳ縲Ｙ縺御ｸ縺､逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲【縺御ｺ後▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲】縺御ｸ峨▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ)縲・
    float3 anglePow;        // 繧ｹ繝昴ャ繝医Λ繧､繝医→縺ｮ隗貞ｺｦ縺ｫ繧医ｋ蜈峨・蠖ｱ髻ｿ邇・↓邏ｯ荵励☆繧九ヱ繝ｩ繝｡繝ｼ繧ｿ縲・.0縺ｧ邱壼ｽ｢縺ｫ螟牙喧縺吶ｋ縲・
                            // x縺御ｸ縺､逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲【縺御ｺ後▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲】縺御ｸ峨▽逶ｮ縺ｮ繧ｫ繝ｩ繝ｼ縲・
};
#endif // _PBRLIGHTING_STRUCT_H_