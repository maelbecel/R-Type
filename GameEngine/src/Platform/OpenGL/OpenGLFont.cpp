/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OpenGLFont
*/

// Exodia Renderer includes
#include "OpenGLFont.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Exodia Assets includes
#include "Asset/Importer/TextureImporter.hpp"

#include <iostream>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLFont::OpenGLFont(const std::string &path) {
        if (Renderer::GetAPI() == RendererAPI::API::None)
            return;
        if (!GenerateGlyphs(path))
            EXODIA_CORE_ERROR("Failed to generate glyphs '{0}'", path);
    }

    /////////////
    // Methods //
    /////////////

    bool OpenGLFont::GenerateGlyphs(const std::string &path) {
        _Texture = TextureImporter::LoadTexture2D(path);

        if (!_Texture)
            return false;

        GenerateOffsets();
        GenerateCoords();
        return true;
    }

    void OpenGLFont::GenerateOffsets() {
        /*uint32_t width        = _Texture->GetWidth();
        uint32_t height       = _Texture->GetHeight();
        uint32_t widthOffset  = width  / 16;
        uint32_t heightOffset = height / 16;
        Buffer data           = _Texture->GetData();

        _Data = CreateScope<FontData>();

        if (!data || data.Size == 0)
            return;

        for (uint32_t textureX = 0; textureX < width; textureX += widthOffset) {
            for (uint32_t textureY = 0; textureY < height; textureY += heightOffset) {
                uint32_t pixelCount = 0;

                for (uint32_t x = 0; x < widthOffset; x++) {
                    bool foundPixel = false;

                    for (uint32_t y = 0; y < heightOffset; y++) {
                        if (data.Data[4 * ((textureX + x) + ((textureY + y) * width)) + 3] > 0) {
                            foundPixel = true;

                            break;
                        }
                    }

                    if (foundPixel)
                        pixelCount++;
                }

                _Data->Glyphs[(textureX / widthOffset) + ((textureY / heightOffset) * 16)].Width = pixelCount;
            }
        }*/

        // TODO: Temp code that work for all R-Type fonts
        _Data = CreateScope<FontData>();

        _Data->Glyphs[0].Width = 0;
        _Data->Glyphs[1].Width = 0;
        _Data->Glyphs[2].Width = 0;
        _Data->Glyphs[3].Width = 0;
        _Data->Glyphs[4].Width = 0;
        _Data->Glyphs[5].Width = 0;
        _Data->Glyphs[6].Width = 0;
        _Data->Glyphs[7].Width = 0;
        _Data->Glyphs[8].Width = 0;
        _Data->Glyphs[9].Width = 0;
        _Data->Glyphs[10].Width = 0;
        _Data->Glyphs[11].Width = 0;
        _Data->Glyphs[12].Width = 0;
        _Data->Glyphs[13].Width = 0;
        _Data->Glyphs[14].Width = 0;
        _Data->Glyphs[15].Width = 0;
        _Data->Glyphs[16].Width = 0;
        _Data->Glyphs[17].Width = 0;
        _Data->Glyphs[18].Width = 0;
        _Data->Glyphs[19].Width = 0;
        _Data->Glyphs[20].Width = 0;
        _Data->Glyphs[21].Width = 0;
        _Data->Glyphs[22].Width = 0;
        _Data->Glyphs[23].Width = 0;
        _Data->Glyphs[24].Width = 0;
        _Data->Glyphs[25].Width = 0;
        _Data->Glyphs[26].Width = 0;
        _Data->Glyphs[27].Width = 0;
        _Data->Glyphs[28].Width = 0;
        _Data->Glyphs[29].Width = 0;
        _Data->Glyphs[30].Width = 0;
        _Data->Glyphs[31].Width = 0;
        _Data->Glyphs[32].Width = 0;
        _Data->Glyphs[33].Width = 9;
        _Data->Glyphs[34].Width = 13;
        _Data->Glyphs[35].Width = 20;
        _Data->Glyphs[36].Width = 17;
        _Data->Glyphs[37].Width = 0;
        _Data->Glyphs[38].Width = 21;
        _Data->Glyphs[39].Width = 8;
        _Data->Glyphs[40].Width = 11;
        _Data->Glyphs[41].Width = 11;
        _Data->Glyphs[42].Width = 12;
        _Data->Glyphs[43].Width = 17;
        _Data->Glyphs[44].Width = 8;
        _Data->Glyphs[45].Width = 12;
        _Data->Glyphs[46].Width = 8;
        _Data->Glyphs[47].Width = 15;
        _Data->Glyphs[48].Width = 15;
        _Data->Glyphs[49].Width = 12;
        _Data->Glyphs[50].Width = 15;
        _Data->Glyphs[51].Width = 15;
        _Data->Glyphs[52].Width = 16;
        _Data->Glyphs[53].Width = 15;
        _Data->Glyphs[54].Width = 16;
        _Data->Glyphs[55].Width = 14;
        _Data->Glyphs[56].Width = 15;
        _Data->Glyphs[57].Width = 16;
        _Data->Glyphs[58].Width = 8;
        _Data->Glyphs[59].Width = 8;
        _Data->Glyphs[60].Width = 16;
        _Data->Glyphs[61].Width = 16;
        _Data->Glyphs[62].Width = 16;
        _Data->Glyphs[63].Width = 17;
        _Data->Glyphs[64].Width = 25;
        _Data->Glyphs[65].Width = 19;
        _Data->Glyphs[66].Width = 16;
        _Data->Glyphs[67].Width = 16;
        _Data->Glyphs[68].Width = 16;
        _Data->Glyphs[69].Width = 13;
        _Data->Glyphs[70].Width = 13;
        _Data->Glyphs[71].Width = 16;
        _Data->Glyphs[72].Width = 16;
        _Data->Glyphs[73].Width = 9;
        _Data->Glyphs[74].Width = 11;
        _Data->Glyphs[75].Width = 17;
        _Data->Glyphs[76].Width = 12;
        _Data->Glyphs[77].Width = 20;
        _Data->Glyphs[78].Width = 16;
        _Data->Glyphs[79].Width = 16;
        _Data->Glyphs[80].Width = 16;
        _Data->Glyphs[81].Width = 16;
        _Data->Glyphs[82].Width = 16;
        _Data->Glyphs[83].Width = 17;
        _Data->Glyphs[84].Width = 15;
        _Data->Glyphs[85].Width = 16;
        _Data->Glyphs[86].Width = 17;
        _Data->Glyphs[87].Width = 25;
        _Data->Glyphs[88].Width = 18;
        _Data->Glyphs[89].Width = 17;
        _Data->Glyphs[90].Width = 14;
        _Data->Glyphs[91].Width = 10;
        _Data->Glyphs[92].Width = 16;
        _Data->Glyphs[93].Width = 10;
        _Data->Glyphs[94].Width = 17;
        _Data->Glyphs[95].Width = 0;
        _Data->Glyphs[96].Width = 11;
        _Data->Glyphs[97].Width = 16;
        _Data->Glyphs[98].Width = 16;
        _Data->Glyphs[99].Width = 15;
        _Data->Glyphs[100].Width = 16;
        _Data->Glyphs[101].Width = 16;
        _Data->Glyphs[102].Width = 12;
        _Data->Glyphs[103].Width = 16;
        _Data->Glyphs[104].Width = 16;
        _Data->Glyphs[105].Width = 9;
        _Data->Glyphs[106].Width = 10;
        _Data->Glyphs[107].Width = 16;
        _Data->Glyphs[108].Width = 9;
        _Data->Glyphs[109].Width = 23;
        _Data->Glyphs[110].Width = 16;
        _Data->Glyphs[111].Width = 16;
        _Data->Glyphs[112].Width = 16;
        _Data->Glyphs[113].Width = 16;
        _Data->Glyphs[114].Width = 12;
        _Data->Glyphs[115].Width = 15;
        _Data->Glyphs[116].Width = 12;
        _Data->Glyphs[117].Width = 16;
        _Data->Glyphs[118].Width = 17;
        _Data->Glyphs[119].Width = 21;
        _Data->Glyphs[120].Width = 17;
        _Data->Glyphs[121].Width = 16;
        _Data->Glyphs[122].Width = 13;
        _Data->Glyphs[123].Width = 13;
        _Data->Glyphs[124].Width = 7;
        _Data->Glyphs[125].Width = 13;
        _Data->Glyphs[126].Width = 16;
        _Data->Glyphs[127].Width = 0;
        _Data->Glyphs[128].Width = 0;
        _Data->Glyphs[129].Width = 0;
        _Data->Glyphs[130].Width = 0;
        _Data->Glyphs[131].Width = 0;
        _Data->Glyphs[132].Width = 0;
        _Data->Glyphs[133].Width = 0;
        _Data->Glyphs[134].Width = 0;
        _Data->Glyphs[135].Width = 0;
        _Data->Glyphs[136].Width = 0;
        _Data->Glyphs[137].Width = 0;
        _Data->Glyphs[138].Width = 0;
        _Data->Glyphs[139].Width = 0;
        _Data->Glyphs[140].Width = 0;
        _Data->Glyphs[141].Width = 0;
        _Data->Glyphs[142].Width = 0;
        _Data->Glyphs[143].Width = 0;
        _Data->Glyphs[144].Width = 0;
        _Data->Glyphs[145].Width = 0;
        _Data->Glyphs[146].Width = 0;
        _Data->Glyphs[147].Width = 0;
        _Data->Glyphs[148].Width = 0;
        _Data->Glyphs[149].Width = 0;
        _Data->Glyphs[150].Width = 0;
        _Data->Glyphs[151].Width = 0;
        _Data->Glyphs[152].Width = 0;
        _Data->Glyphs[153].Width = 0;
        _Data->Glyphs[154].Width = 0;
        _Data->Glyphs[155].Width = 0;
        _Data->Glyphs[156].Width = 0;
        _Data->Glyphs[157].Width = 0;
        _Data->Glyphs[158].Width = 0;
        _Data->Glyphs[159].Width = 0;
        _Data->Glyphs[160].Width = 0;
        _Data->Glyphs[161].Width = 9;
        _Data->Glyphs[162].Width = 16;
        _Data->Glyphs[163].Width = 17;
        _Data->Glyphs[164].Width = 18;
        _Data->Glyphs[165].Width = 17;
        _Data->Glyphs[166].Width = 7;
        _Data->Glyphs[167].Width = 17;
        _Data->Glyphs[168].Width = 13;
        _Data->Glyphs[169].Width = 25;
        _Data->Glyphs[170].Width = 12;
        _Data->Glyphs[171].Width = 13;
        _Data->Glyphs[172].Width = 16;
        _Data->Glyphs[173].Width = 12;
        _Data->Glyphs[174].Width = 25;
        _Data->Glyphs[175].Width = 19;
        _Data->Glyphs[176].Width = 12;
        _Data->Glyphs[177].Width = 17;
        _Data->Glyphs[178].Width = 13;
        _Data->Glyphs[179].Width = 16;
        _Data->Glyphs[180].Width = 12;
        _Data->Glyphs[181].Width = 15;
        _Data->Glyphs[182].Width = 20;
        _Data->Glyphs[183].Width = 8;
        _Data->Glyphs[184].Width = 10;
        _Data->Glyphs[185].Width = 14;
        _Data->Glyphs[186].Width = 12;
        _Data->Glyphs[187].Width = 13;
        _Data->Glyphs[188].Width = 22;
        _Data->Glyphs[189].Width = 21;
        _Data->Glyphs[190].Width = 22;
        _Data->Glyphs[191].Width = 17;
        _Data->Glyphs[192].Width = 18;
        _Data->Glyphs[193].Width = 19;
        _Data->Glyphs[194].Width = 19;
        _Data->Glyphs[195].Width = 19;
        _Data->Glyphs[196].Width = 19;
        _Data->Glyphs[197].Width = 19;
        _Data->Glyphs[198].Width = 22;
        _Data->Glyphs[199].Width = 16;
        _Data->Glyphs[200].Width = 14;
        _Data->Glyphs[201].Width = 13;
        _Data->Glyphs[202].Width = 16;
        _Data->Glyphs[203].Width = 13;
        _Data->Glyphs[204].Width = 16;
        _Data->Glyphs[205].Width = 15;
        _Data->Glyphs[206].Width = 14;
        _Data->Glyphs[207].Width = 13;
        _Data->Glyphs[208].Width = 17;
        _Data->Glyphs[209].Width = 16;
        _Data->Glyphs[210].Width = 16;
        _Data->Glyphs[211].Width = 16;
        _Data->Glyphs[212].Width = 16;
        _Data->Glyphs[213].Width = 16;
        _Data->Glyphs[214].Width = 16;
        _Data->Glyphs[215].Width = 17;
        _Data->Glyphs[216].Width = 21;
        _Data->Glyphs[217].Width = 16;
        _Data->Glyphs[218].Width = 16;
        _Data->Glyphs[219].Width = 16;
        _Data->Glyphs[220].Width = 16;
        _Data->Glyphs[221].Width = 17;
        _Data->Glyphs[222].Width = 16;
        _Data->Glyphs[223].Width = 17;
        _Data->Glyphs[224].Width = 16;
        _Data->Glyphs[225].Width = 16;
        _Data->Glyphs[226].Width = 16;
        _Data->Glyphs[227].Width = 16;
        _Data->Glyphs[228].Width = 16;
        _Data->Glyphs[229].Width = 16;
        _Data->Glyphs[230].Width = 22;
        _Data->Glyphs[231].Width = 15;
        _Data->Glyphs[232].Width = 16;
        _Data->Glyphs[233].Width = 16;
        _Data->Glyphs[234].Width = 16;
        _Data->Glyphs[235].Width = 16;
        _Data->Glyphs[236].Width = 11;
        _Data->Glyphs[237].Width = 11;
        _Data->Glyphs[238].Width = 14;
        _Data->Glyphs[239].Width = 13;
        _Data->Glyphs[240].Width = 16;
        _Data->Glyphs[241].Width = 16;
        _Data->Glyphs[242].Width = 16;
        _Data->Glyphs[243].Width = 16;
        _Data->Glyphs[244].Width = 16;
        _Data->Glyphs[245].Width = 16;
        _Data->Glyphs[246].Width = 16;
        _Data->Glyphs[247].Width = 16;
        _Data->Glyphs[248].Width = 16;
        _Data->Glyphs[249].Width = 16;
        _Data->Glyphs[250].Width = 16;
        _Data->Glyphs[251].Width = 16;
        _Data->Glyphs[252].Width = 16;
        _Data->Glyphs[253].Width = 16;
        _Data->Glyphs[254].Width = 16;
        _Data->Glyphs[255].Width = 16;
    }

    void OpenGLFont::GenerateCoords() {
        float u = 0.0f;
        float v = 0.0f;

        for (uint32_t x = 0; x < 16; x++) {
            v = 0.0f;

            for (uint32_t y = 15; y > 0; y--) {
                _Data->Glyphs[x + (y * 16)].TextureCoord = {u, v};

                v += (1.0f / 16.0f);
            }

            u += (1.0f / 16.0f);
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const FontData &OpenGLFont::GetData() const { return *_Data; }

    Ref<Texture2D> OpenGLFont::GetTexture() const {
        if (Renderer::GetAPI() == RendererAPI::API::None)
            return nullptr;
        return _Texture;
    }
}; // namespace Exodia
