/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Renderer2D
*/

#ifndef RENDERER2D_HPP_
    #define RENDERER2D_HPP_

    // Exodia Renderer
    #include "Renderer/Camera/OrthographicCamera.hpp"
    #include "Renderer/Camera/EditorCamera.hpp"
    #include "Renderer/Texture/SubTexture2D.hpp"
    #include "Renderer/Vertex/VertexArray.hpp"
    #include "Renderer/Shader/Shader.hpp"
    #include "Renderer/Camera/Camera.hpp"
    #include "Renderer/Buffer/UniformBuffer.hpp"

    // Exodia Scene includes
    #include "Component/Components.hpp"

    // External includes
    #include <array>

namespace Exodia {

    /**
     * @brief The Renderer2D class handles 2D rendering operations, including rendering primitives like quads and rotated quads.
     */
    class Renderer2D {

        ////////////////
        // Structures //
        ////////////////
        public:

            /**
             * @brief QuadVertex structure defines the properties of a vertex in a quad.
             */
            struct QuadVertex {
                glm::vec3 Position;     /* !< The position of the vertex. */
                glm::vec4 Color;        /* !< The color of the vertex. */
                glm::vec2 TexCoord;     /* !< The texture coordinates of the vertex. */
                float     TexIndex;     /* !< The index of the texture. */
                float     TilingFactor; /* !< The tiling factor for the texture. */

                // Editor-only
                int       EntityID;     /* !< The ID of the entity. */
            };

            /**
             * @brief CircleVertex structure defines the properties of a vertex in a circle.
             */
            struct CircleVertex {
                glm::vec3 WorldPosition; /* !< The world position of the vertex. (World position is the position of the vertex relative to the world) */
                glm::vec3 LocalPosition; /* !< The local position of the vertex. (Local position is the position of the vertex relative to the center of the circle) */
                glm::vec4 Color;         /* !< The color of the vertex. */
                float Thickness;         /* !< The thickness of the circle. */
                float Fade;              /* !< The fade of the circle. (Fade is the distance between the vertex and the center of the circle) */

                // Editor-only
                int EntityID;            /* !< The ID of the entity. */
            };

            struct LineVertex {
                glm::vec3 Position; /* !< The position of the vertex. */
                glm::vec4 Color;    /* !< The color of the vertex. */

                // Editor-only
                int EntityID;       /* !< The ID of the entity. */
            };

            /**
             * @brief Statistics structure holds rendering statistics.
             */
            struct Statistics {
                uint32_t DrawCalls = 0; /* !< The number of draw calls. */
                uint32_t QuadCount = 0; /* !< The number of quads. */

                /**
                 * @brief Get the total vertex count considering all rendered quads.
                 *
                 * @return (Type: uint32_t) Total vertex count.
                 */
                uint32_t GetTotalVertexCount() const
                {
                    return QuadCount * 4;
                }

                /**
                 * @brief Get the total index count considering all rendered quads.
                 *
                 * @return (Type: uint32_t) Total index count.
                 */
                uint32_t GetTotalIndexCount() const
                {
                    return QuadCount * 6;
                }
            };

            struct CameraData {
                glm::mat4 ViewProjection;
            };

            /**
             * @brief Renderer2DData structure holds data related to 2D rendering.
             */
            struct Renderer2DData {
                static const uint32_t MaxQuads       = 20000;          /* !< The maximum number of quads in one batch. */
                static const uint32_t MaxVertices    = MaxQuads * 4;   /* !< The maximum number of vertices in one batch. */
                static const uint32_t MaxIndices     = MaxQuads * 6;   /* !< The maximum number of indices in one batch. */
                static const uint32_t MaxTextureSlot = 32;             /* !< The maximum number of texture slots. */

                Ref<VertexArray>  QuadVertexArray;                     /* !< The vertex array for quads. */
                Ref<VertexBuffer> QuadVertexBuffer;                    /* !< The vertex buffer for quads. */
                Ref<Shader>       QuadShader;                          /* !< The shader for textures for quads. */

                Ref<VertexArray>  CircleVertexArray;                   /* !< The vertex array for circles. */
                Ref<VertexBuffer> CircleVertexBuffer;                  /* !< The vertex buffer for circles. */
                Ref<Shader>       CircleShader;                        /* !< The shader for textures for circles. */

                Ref<VertexArray>  LineVertexArray;                     /* !< The vertex array for lines. */
                Ref<VertexBuffer> LineVertexBuffer;                    /* !< The vertex buffer for lines. */
                Ref<Shader>       LineShader;                          /* !< The shader for textures for lines. */

                Ref<Texture2D>    WhiteTexture;                        /* !< The white texture. */

                uint32_t    QuadIndexCount       = 0;                  /* !< The number of indices in the current batch. (default is 0)*/
                QuadVertex *QuadVertexBufferBase = nullptr;            /* !< The base pointer to the vertex buffer. */
                QuadVertex *QuadVertexBufferPtr  = nullptr;            /* !< The current pointer to the vertex buffer. */

                uint32_t      CircleIndexCount       = 0;               /* !< The number of indices in the current batch. (default is 0)*/
                CircleVertex *CircleVertexBufferBase = nullptr;         /* !< The base pointer to the vertex buffer. */
                CircleVertex *CircleVertexBufferPtr  = nullptr;         /* !< The current pointer to the vertex buffer. */

                uint32_t     LineVertexCount = 0;                       /* !< The number of vertices in the current batch. (default is 0)*/
                LineVertex * LineVertexBufferBase = nullptr;            /* !< The base pointer to the vertex buffer. */
                LineVertex * LineVertexBufferPtr = nullptr;             /* !< The current pointer to the vertex buffer. */

                float LineWidth = 2.0f;                                 /* !< The width of the lines. */

                std::array<Ref<Texture2D>, MaxTextureSlot> TextureSlot; /* !< The texture slots. */
                uint32_t TextureSlotIndex = 1;                          /* !< The current texture slot index. (0 is for white texture, so by default is 1) */

                glm::vec4 QuadVertexPosition[4];                        /* !< The positions of the vertices in a quad. */

                Statistics Stats;                                       /* !< The statistics of the renderer. */

                CameraData         CameraBuffer;                        /* !< The camera data. */
                Ref<UniformBuffer> CameraUniformBuffer;                 /* !< The camera uniform buffer. */
            };

        /////////////
        // Methods //
        /////////////
        public:
            
            /**
             * @brief Initialize the Renderer2D class. This function sets up the necessary resources and data structures for rendering.
             */
            static void Init();

            /**
             * @brief Shutdown the Renderer2D class. This function releases any allocated resources and cleans up the rendering environment.
             */
            static void Shutdown();


            /**
             * @brief Begin a new rendering scene using the specified OrthographicCamera.
             *
             * @param camera (Type: const OrthographicCamera &) The OrthographicCamera to be used for rendering the scene.
             * 
             * @overload
             * 
             * @brief Begin a new rendering scene using the specified Camera.
             * @param camera    (Type: const Camera &)    The Camera to be used for rendering the scene.
             * @param transform (Type: const glm::mat4 &) The transform of the camera.
             * 
             * @overload
             * @param camera (Type: const EditorCamera &) The EditorCamera to be used for rendering the scene.
             */
            static void BeginScene(const OrthographicCamera &camera);
            static void BeginScene(const Camera &camera, const glm::mat4 &transform);
            static void BeginScene(const EditorCamera &camera);

            /**
             * @brief End the current rendering scene. This function finalizes the rendering process for the current scene.
             */
            static void EndScene();

            /**
             * @brief Flush the currently buffered rendering data and issue draw calls.
             */
            static void Flush();

            /**
             * @brief Reset the rendering statistics, including draw call and quad count.
             */
            static void ResetStats();

            // ------ Primitives ----- //
                // 1. Quad

            /**
             * @brief Draw a colored quad at the specified position, size, and depth.
             * Their is 6 way to draw a quad, with or without texture, and with or without rotation.
             * 
             * If the position is a glm::vec2, the depth is 0.0f.
             * Else the position is a glm::vec3, the depth is the z value of the position.
             *
             * @param position     (Type: glm::vec2 or glm::vec3) The position of the quad.
             * @param size         (Type: glm::vec2)              The size of the quad.
             * @param color        (Type: glm::vec4)              The color of the quad.
             *
             * @overload
             * @param transform (Type: glm::vec4)                 The transform of the quad.
             * @param color     (Type: glm::vec4)                 The color of the quad.
             *
             * @overload
             * @brief Draw a textured quad at the specified position, size, and depth.
             * @param position     (Type: glm::vec2 or glm::vec3) The position of the quad.
             * @param size         (Type: glm::vec2)              The size of the quad.
             * @param texture      (Type: Ref<Texture2D>)         The texture to apply to the quad.
             * @param tilingFactor (Type: float)                  The tiling factor for the texture (default is 1.0f).
             * @param tintColor    (Type: glm::vec4)              The tint color to apply to the quad (default is glm::vec4(1.0f)).
             * 
             * @overload
             * @param transform    (Type: glm::vec4)              The transform of the quad.
             * @param texture      (Type: Ref<Texture2D>)         The texture to apply to the quad.
             * @param tilingFactor (Type: float)                  The tiling factor for the texture (default is 1.0f).
             * @param tintColor    (Type: glm::vec4)              The tint color to apply to the quad (default is glm::vec4(1.0f)).
             * 
             * @overload
             * @brief Draw a sub textured quad at the specified position, size, and depth.
             * @note A sub texture is a part of a texture.
             * @param position     (Type: glm::vec2 or glm::vec3) The position of the quad.
             * @param size         (Type: glm::vec2)              The size of the quad.
             * @param subTexture   (Type: Ref<SubTexture2D>)      The sub texture to apply to the quad.
             * @param tilingFactor (Type: float)                  The tiling factor for the texture (default is 1.0f).
             * @param tintColor    (Type: glm::vec4)              The tint color to apply to the quad (default is glm::vec4(1.0f)).
             *
             * @overload
             * @note A sub texture is a part of a texture.
             * @param transform    (Type: glm::vec4)              The transform of the quad.
             * @param subTexture   (Type: Ref<SubTexture2D>)      The sub texture to apply to the quad.
             * @param tilingFactor (Type: float)                  The tiling factor for the texture (default is 1.0f).
             * @param tintColor    (Type: glm::vec4)              The tint color to apply to the quad (default is glm::vec4(1.0f)).
             */
            static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
            static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
            static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, int entityID = -1);
            static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawQuad(const glm::mat4 &transform, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f), int entityID = -1);
            static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawQuad(const glm::mat4 &transform, const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f), int entityID = -1);

                // 2. Rotated Quad (The rotation are in radians)

            /**
             * @brief Draw a colored rotate quad at the specified position, size, and depth.
             * Their is 6 way to draw a rotated quad, with or without texture, and with or without rotation.
             * 
             * If the position is a glm::vec2, the depth is 0.0f.
             * Else the position is a glm::vec3, the depth is the z value of the position.
             *
             * @param position (Type: glm::vec2 or glm::vec3) The position of the quad.
             * @param size     (Type: glm::vec2)              The size of the quad.
             * @param rotation (Type: float)                  The rotation of the quad (in radians).
             * @param color    (Type: glm::vec4)              The color of the quad.
             *
             * @overload
             * @brief Draw a textured quad at the specified position, size, and depth.
             * @param position     (Type: glm::vec2 or glm::vec3) The position of the quad.
             * @param size         (Type: glm::vec2)              The size of the quad.
             * @param rotation     (Type: float)                  The rotation of the quad (in radians).
             * @param texture      (Type: Ref<Texture2D>)         The texture to apply to the quad.
             * @param tilingFactor (Type: float)                  The tiling factor for the texture (default is 1.0f).
             * @param tintColor    (Type: glm::vec4)              The tint color to apply to the quad (default is glm::vec4(1.0f)).
             *
             * @overload
             * @brief Draw a sub textured quad at the specified position, size, and depth.
             * @note A sub texture is a part of a texture.
             * @param position     (Type: glm::vec2 or glm::vec3) The position of the quad.
             * @param size         (Type: glm::vec2)              The size of the quad.
             * @param rotation     (Type: float)                  The rotation of the quad (in radians).
             * @param subTexture   (Type: Ref<SubTexture2D>)      The sub texture to apply to the quad.
             * @param tilingFactor (Type: float)                  The tiling factor for the texture (default is 1.0f).
             * @param tintColor    (Type: glm::vec4)              The tint color to apply to the quad (default is glm::vec4(1.0f)).
             */
            static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);
            static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);
            static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
            static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

                // 3. Quad Sprite
            
            static void DrawSprite(const glm::mat4 &transform, SpriteRendererComponent &src, int entityID = 0);

                // 4. Circle

            static void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);

                // 5. Lines

            static void DrawLine(const glm::vec3 &pointA, const glm::vec3 &pointB, const glm::vec4 &color, int entityID = -1);

                // 6. Rectangle

            static void DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, int entityID = -1);
            static void DrawRect(const glm::mat4 &transform, const glm::vec4 &color, int entityID = -1);

                // 7. Sound

            static void PlaySound(AssetHandle  sound);
            static void PlaySound(Ref<Sound2D> sound);

        private:

            /**
             * @brief Flush the currently buffered rendering data, issue draw calls, and reset the rendering state.
             * This function is used internally to optimize rendering performance by periodically flushing data.
             */
            static void FlushAndReset();

            static void ResetBatch();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the rendering statistics.
             *
             * @return (Type: const Statistics &) The rendering statistics including draw call and quad count.
             */
            static const Statistics &GetStats();

            static float GetLineWidth();

            static void SetLineWidth(float width);
    };
};

#endif /* !RENDERER2D_HPP_ */
