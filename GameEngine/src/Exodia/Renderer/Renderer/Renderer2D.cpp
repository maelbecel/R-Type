/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Renderer2D
*/

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Exodia Renderer
#include "Renderer2D.hpp"
#include "Renderer/Renderer/RenderCommand.hpp"

// Exodia Core include
#include "Core/Buffer/Buffer.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

// External include
#include <cstring>

namespace Exodia {

    static Scope<Renderer2D::Renderer2DData> _Data = nullptr; /* !< Renderer2D data */

    /////////////
    // Methods //
    /////////////

    void Renderer2D::Init()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Initialize Renderer2D data and set default values
        _Data = CreateScope<Renderer2D::Renderer2DData>();
        _Data->QuadVertexArray = VertexArray::Create();
        _Data->QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(QuadVertex));
        _Data->QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position"     },
            { ShaderDataType::Float4, "a_Color"        },
            { ShaderDataType::Float2, "a_TexCoord"     },
            { ShaderDataType::Float , "a_TexIndex"     },
            { ShaderDataType::Float , "a_TilingFactor" },
            { ShaderDataType::Int   , "a_EntityID"     }
        });
        _Data->QuadVertexArray->AddVertexBuffer(_Data->QuadVertexBuffer);
        _Data->QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxVertices];

        uint32_t *quadIndices = new uint32_t[Renderer2DData::MaxIndices];
        uint32_t offset = 0;

        for (uint32_t i = 0; i < Renderer2DData::MaxIndices; i += 6) {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }
        Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, Renderer2DData::MaxIndices);

        _Data->QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

        delete[] quadIndices;

        _Data->CircleVertexArray = VertexArray::Create();
        _Data->CircleVertexBuffer = VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(CircleVertex));
        _Data->CircleVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_WorldPosition" },
            { ShaderDataType::Float3, "a_LocalPosition" },
            { ShaderDataType::Float4, "a_Color"         },
            { ShaderDataType::Float,  "a_Thickness"     },
            { ShaderDataType::Float,  "a_Fade"          },
            { ShaderDataType::Int,    "a_EntityID"      }
        });
        _Data->CircleVertexArray->AddVertexBuffer(_Data->CircleVertexBuffer);
        _Data->CircleVertexArray->SetIndexBuffer(quadIndexBuffer);
        _Data->CircleVertexBufferBase = new CircleVertex[Renderer2DData::MaxVertices];


        _Data->LineVertexArray = VertexArray::Create();
        _Data->LineVertexBuffer = VertexBuffer::Create(_Data->MaxVertices * sizeof(LineVertex));
        _Data->LineVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color"    },
            { ShaderDataType::Int,    "a_EntityID" }
        });
        _Data->LineVertexArray->AddVertexBuffer(_Data->LineVertexBuffer);
        _Data->LineVertexBufferBase = new LineVertex[_Data->MaxVertices];

        _Data->WhiteTexture = Texture2D::Create(TextureSpecification());

        uint32_t whiteTextureData = 0xffffffff;

        _Data->WhiteTexture->SetData(Buffer(&whiteTextureData, sizeof(uint32_t)));

        _Data->QuadShader = Shader::Create("./Assets/Shaders/Renderer2D_Quad.glsl");
        _Data->CircleShader = Shader::Create("./Assets/Shaders/Renderer2D_Circle.glsl");
        _Data->LineShader = Shader::Create("./Assets/Shaders/Renderer2D_Line.glsl");

        _Data->TextureSlot[0] = _Data->WhiteTexture;

        _Data->QuadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        _Data->QuadVertexPosition[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        _Data->QuadVertexPosition[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        _Data->QuadVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
        
        _Data->CameraUniformBuffer = UniformBuffer::Create(sizeof(CameraData), 0);
    }

    void Renderer2D::Shutdown()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (_Data && _Data->QuadVertexBufferBase != nullptr) {
            delete[] _Data->QuadVertexBufferBase;
            _Data->QuadVertexBufferBase = nullptr;
        }

        _Data = nullptr;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (_Data == nullptr)
            return;

        // Bind shader and set view projection matrix
        _Data->CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
        _Data->CameraUniformBuffer->SetData(&_Data->CameraBuffer, sizeof(CameraData));

        ResetBatch();
    }

    void Renderer2D::BeginScene(const Camera &camera, const glm::mat4 &transform)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (_Data == nullptr)
            return;

        _Data->CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
        _Data->CameraUniformBuffer->SetData(&_Data->CameraBuffer, sizeof(CameraData));

        ResetBatch();
    }

    void Renderer2D::BeginScene(const EditorCamera &camera)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (_Data == nullptr)
            return;

        _Data->CameraBuffer.ViewProjection = camera.GetViewProjection();
        _Data->CameraUniformBuffer->SetData(&_Data->CameraBuffer, sizeof(CameraData));

        ResetBatch();
    }

    void Renderer2D::EndScene()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (_Data == nullptr)
            return;

        Flush();
    }

    void Renderer2D::Flush()
    {
        if (_Data->QuadIndexCount) {
            // Calculate data size
            uint32_t dataSize = (uint32_t)((uint8_t *)_Data->QuadVertexBufferPtr - (uint8_t *)_Data->QuadVertexBufferBase);

            _Data->QuadVertexBuffer->SetData(_Data->QuadVertexBufferBase, dataSize);

            // Bind textures
            for (uint32_t i = 0; i < _Data->TextureSlotIndex; i++)
                _Data->TextureSlot[i]->Bind(i);
            _Data->QuadShader->Bind();

            // Draw
            RenderCommand::DrawIndexed(_Data->QuadVertexArray, _Data->QuadIndexCount);

            // Debugging stats
            _Data->Stats.DrawCalls++;
        }

        if (_Data->CircleIndexCount) {
            // Calculate data size
            uint32_t dataSize = (uint32_t)((uint8_t *)_Data->CircleVertexBufferPtr - (uint8_t *)_Data->CircleVertexBufferBase);

            _Data->CircleVertexBuffer->SetData(_Data->CircleVertexBufferBase, dataSize);

            // Bind textures
            _Data->CircleShader->Bind();

            // Draw
            RenderCommand::DrawIndexed(_Data->CircleVertexArray, _Data->CircleIndexCount);

            // Debugging stats
            _Data->Stats.DrawCalls++;
        }

        if (_Data->LineVertexCount) {
            // Calculate data size
            uint32_t dataSize = (uint32_t)((uint8_t *)_Data->LineVertexBufferPtr - (uint8_t *)_Data->LineVertexBufferBase);

            _Data->LineVertexBuffer->SetData(_Data->LineVertexBufferBase, dataSize);

            // Bind textures
            _Data->LineShader->Bind();

            // Draw
            RenderCommand::SetLineWidth(_Data->LineWidth);
            RenderCommand::DrawLines(_Data->LineVertexArray, _Data->LineVertexCount);

            // Debugging stats
            _Data->Stats.DrawCalls++;
        }
    }

    void Renderer2D::ResetStats()
    {
        std::memset(&_Data->Stats, 0, sizeof(Statistics));
    }

    void Renderer2D::FlushAndReset()
    {
        // Flush
        EndScene();

        // Reset
        ResetBatch();
    }

    void Renderer2D::ResetBatch()
    {
        // Set default values
        _Data->QuadIndexCount = 0;
        _Data->QuadVertexBufferPtr = _Data->QuadVertexBufferBase;
        _Data->CircleIndexCount = 0;
        _Data->CircleVertexBufferPtr = _Data->CircleVertexBufferBase;
        _Data->LineVertexCount = 0;
        _Data->LineVertexBufferPtr = _Data->LineVertexBufferBase;
        _Data->TextureSlotIndex = 1;
    }

    // ----- Primitives ----- //

        // 1. Quad

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, color);
    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, int entityID)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        constexpr uint32_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        // Check if we need to flush or if we can continue
        if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        const float textureIndex = 0.0f; // White texture
        const float tilingFactor = 1.0f;

        for (uint32_t i = 0; i < quadVertexCount; i++) {
            _Data->QuadVertexBufferPtr->Position = transform * _Data->QuadVertexPosition[i];
            _Data->QuadVertexBufferPtr->Color = color;
            _Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
            _Data->QuadVertexBufferPtr->TexIndex = textureIndex;
            _Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
            _Data->QuadVertexBufferPtr->EntityID = entityID;
            _Data->QuadVertexBufferPtr++;
        }
        _Data->QuadIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor, int entityID)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (texture == nullptr)
            return DrawQuad(transform, tintColor, entityID);

        constexpr uint32_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        // Check if we need to flush or if we can continue
        if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;

        // Check if the texture is already in the texture slot
        for (uint32_t i = 1; i < _Data->TextureSlotIndex; i++) {
            if (*_Data->TextureSlot[i].get() == *texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        // If the texture is not in the texture slot, add it
		if (textureIndex == 0.0f) {
            // Check if we can add a new texture
            if (_Data->TextureSlotIndex >= Renderer2DData::MaxTextureSlot)
                FlushAndReset();

            textureIndex = (float)_Data->TextureSlotIndex;
            _Data->TextureSlot[_Data->TextureSlotIndex] = texture;
            _Data->TextureSlotIndex++;
        }

        for (uint32_t i = 0; i < quadVertexCount; i++) {
            _Data->QuadVertexBufferPtr->Position = transform * _Data->QuadVertexPosition[i];
            _Data->QuadVertexBufferPtr->Color = tintColor;
            _Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
            _Data->QuadVertexBufferPtr->TexIndex = textureIndex;
            _Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
            _Data->QuadVertexBufferPtr->EntityID = entityID;
            _Data->QuadVertexBufferPtr++;
        }
        _Data->QuadIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture, float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, subTexture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture, float tilingFactor, const glm::vec4 &tintColor)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, subTexture, tilingFactor, tintColor);

    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const Ref<SubTexture2D> &subTexture, float tilingFactor, const glm::vec4 &tintColor, int entityID)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        constexpr uint32_t quadVertexCount = 4;
        const glm::vec2 *textureCoords = subTexture->GetTextureCoords();
        const Ref<Texture2D> texture = subTexture->GetTexture();

        // Check if we need to flush or if we can continue
        if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;

        // Check if the texture is already in the texture slot
        for (uint32_t i = 1; i < _Data->TextureSlotIndex; i++) {
            if (*_Data->TextureSlot[i].get() == *texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        // If the texture is not in the texture slot, add it
		if (textureIndex == 0.0f) {
            // Check if we can add a new texture
            if (_Data->TextureSlotIndex >= Renderer2DData::MaxTextureSlot)
                FlushAndReset();

            textureIndex = (float)_Data->TextureSlotIndex;
            _Data->TextureSlot[_Data->TextureSlotIndex] = texture;
            _Data->TextureSlotIndex++;
        }

        for (uint32_t i = 0; i < quadVertexCount; i++) {
            _Data->QuadVertexBufferPtr->Position = transform * _Data->QuadVertexPosition[i];
            _Data->QuadVertexBufferPtr->Color = tintColor;
            _Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
            _Data->QuadVertexBufferPtr->TexIndex = textureIndex;
            _Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
            _Data->QuadVertexBufferPtr->EntityID = entityID;
            _Data->QuadVertexBufferPtr++;
        }
        _Data->QuadIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

        // 2. Rotated Quad

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        constexpr uint32_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        // Check if we need to flush or if we can continue
        if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        const float textureIndex = 0.0f; // White texture
        const float tilingFactor = 1.0f;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (uint32_t i = 0; i < quadVertexCount; i++) {
            _Data->QuadVertexBufferPtr->Position = transform * _Data->QuadVertexPosition[i];
            _Data->QuadVertexBufferPtr->Color = color;
            _Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
            _Data->QuadVertexBufferPtr->TexIndex = textureIndex;
            _Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
            _Data->QuadVertexBufferPtr++;
        }
        _Data->QuadIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        constexpr uint32_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        // Check if we need to flush or if we can continue
        if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;

        // Check if the texture is already in the texture slot
        for (uint32_t i = 1; i < _Data->TextureSlotIndex; i++) {
            if (*_Data->TextureSlot[i].get() == *texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        // If the texture is not in the texture slot, add it
		if (textureIndex == 0.0f) {
            // Check if we can add a new texture
            if (_Data->TextureSlotIndex >= Renderer2DData::MaxTextureSlot)
                FlushAndReset();

            textureIndex = (float)_Data->TextureSlotIndex;
            _Data->TextureSlot[_Data->TextureSlotIndex] = texture;
            _Data->TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (uint32_t i = 0; i < quadVertexCount; i++) {
            _Data->QuadVertexBufferPtr->Position = transform * _Data->QuadVertexPosition[i];
            _Data->QuadVertexBufferPtr->Color = tintColor;
            _Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
            _Data->QuadVertexBufferPtr->TexIndex = textureIndex;
            _Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
            _Data->QuadVertexBufferPtr++;
        }
        _Data->QuadIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture, float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, subTexture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture, float tilingFactor, const glm::vec4 &tintColor)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        constexpr uint32_t quadVertexCount = 4;
        const glm::vec2 *textureCoords = subTexture->GetTextureCoords();
        const Ref<Texture2D> texture = subTexture->GetTexture();

        // Check if we need to flush or if we can continue
        if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;

        // Check if the texture is already in the texture slot
        for (uint32_t i = 1; i < _Data->TextureSlotIndex; i++) {
            if (*_Data->TextureSlot[i].get() == *texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        // If the texture is not in the texture slot, add it
		if (textureIndex == 0.0f) {
            // Check if we can add a new texture
            if (_Data->TextureSlotIndex >= Renderer2DData::MaxTextureSlot)
                FlushAndReset();

            textureIndex = (float)_Data->TextureSlotIndex;
            _Data->TextureSlot[_Data->TextureSlotIndex] = texture;
            _Data->TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (uint32_t i = 0; i < quadVertexCount; i++) {
            _Data->QuadVertexBufferPtr->Position = transform * _Data->QuadVertexPosition[i];
            _Data->QuadVertexBufferPtr->Color = tintColor;
            _Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
            _Data->QuadVertexBufferPtr->TexIndex = textureIndex;
            _Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
            _Data->QuadVertexBufferPtr++;
        }
        _Data->QuadIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

        // 3. Quad Sprite

    void Renderer2D::DrawSprite(const glm::mat4 &transform, SpriteRendererComponent &src, int entityID)
    {
        if (src.Texture && src.Texture->GetTexture())
            DrawQuad(transform, src.Texture, src.TilingFactor, src.Color, entityID);
        else
            DrawQuad(transform, src.Color, entityID);
    }

        // 4. Circle
    
    void Renderer2D::DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float thickness, float fade, int entityID)
    {
        EXODIA_PROFILE_FUNCTION();

		// TODO: implement for circles
		// if (_Data->QuadIndexCount >= Renderer2DData::MaxIndices)
		// 	FlushAndReset();

        for (size_t i = 0; i < 4; i++) {
            _Data->CircleVertexBufferPtr->WorldPosition = transform * _Data->QuadVertexPosition[i];
            _Data->CircleVertexBufferPtr->LocalPosition = _Data->QuadVertexPosition[i] * 2.0f;
            _Data->CircleVertexBufferPtr->Color = color;
            _Data->CircleVertexBufferPtr->Thickness = thickness;
            _Data->CircleVertexBufferPtr->Fade = fade;
            _Data->CircleVertexBufferPtr->EntityID = entityID;
            _Data->CircleVertexBufferPtr++;
        }
        _Data->CircleIndexCount += 6;
        _Data->Stats.QuadCount++;
    }

        // 5. Lines
    
    void Renderer2D::DrawLine(const glm::vec3 &pointA, const glm::vec3 &pointB, const glm::vec4 &color, int entityID)
    {
        _Data->LineVertexBufferPtr->Position = pointA;
        _Data->LineVertexBufferPtr->Color = color;
        _Data->LineVertexBufferPtr->EntityID = entityID;
        _Data->LineVertexBufferPtr++;

        _Data->LineVertexBufferPtr->Position = pointB;
        _Data->LineVertexBufferPtr->Color = color;
        _Data->LineVertexBufferPtr->EntityID = entityID;
        _Data->LineVertexBufferPtr++;

        _Data->LineVertexCount += 2;
    }

        // 6. Rectangle

    void Renderer2D::DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, int entityID)
    {
        glm::vec3 pointA = glm::vec3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
        glm::vec3 pointB = glm::vec3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
        glm::vec3 pointC = glm::vec3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
        glm::vec3 pointD = glm::vec3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);

        DrawLine(pointA, pointB, color, entityID);
        DrawLine(pointB, pointC, color, entityID);
        DrawLine(pointC, pointD, color, entityID);
        DrawLine(pointD, pointA, color, entityID);
    }

    void Renderer2D::DrawRect(const glm::mat4 &transform, const glm::vec4 &color, int entityID)
    {
        glm::vec3 lineVertices[4];

        for (size_t i = 0; i < 4; i++)
            lineVertices[i] = transform * _Data->QuadVertexPosition[i];
        
        DrawLine(lineVertices[0], lineVertices[1], color, entityID);
        DrawLine(lineVertices[1], lineVertices[2], color, entityID);
        DrawLine(lineVertices[2], lineVertices[3], color, entityID);
        DrawLine(lineVertices[3], lineVertices[0], color, entityID);
    }

        // 7. Sound
    
    void Renderer2D::PlaySound(AssetHandle sound)
    {
        Ref<Sound2D> soundRef = AssetManager::GetAsset<Sound2D>(sound);

        if (soundRef == nullptr)
            return;
        soundRef->Play();
    }

    void Renderer2D::PlaySound(Ref<Sound2D> sound)
    {
        if (sound == nullptr)
            return;
        sound->Play();
    }

    /////////////
    // Getters //
    /////////////

    const Renderer2D::Statistics &Renderer2D::GetStats()
    {
        return _Data->Stats;
    }

    float Renderer2D::GetLineWidth()
    {
        return _Data->LineWidth;
    }

    void Renderer2D::SetLineWidth(float width)
    {
        _Data->LineWidth = width;
    }
};
