# OpenGLFramebufferUtils

This module contains functions for creating and managing OpenGL framebuffers.

## TextureTarget

```c++
static GLenum TextureTarget(bool multisampled)
```
Returns the texture target for the specified framebuffer.

It takes the following parameters:

| Name          | Type | Description                                                                 |
|---------------|------|-----------------------------------------------------------------------------|
| multisampled  | bool | A boolean that indicates whether the framebuffer is multisampled or not.    |

You can use it like this:
```c++
GLenum target = TextureTarget(multisampled);
```

## CreateTextures

```c++
static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
```

Creates a new OpenGL texture.

It takes the following parameters:

| Name          | Type     | Description                                                                 |
|---------------|----------|-----------------------------------------------------------------------------|
| multisampled  | bool     | A boolean that indicates whether the framebuffer is multisampled or not.    |
| outID         | uint32_t | A pointer to the texture ID.                                                |
| count         | uint32_t | The number of textures to create.                                           |

You can use it like this:
```c++
uint32_t colorAttachment[2];
CreateTextures(false, colorAttachment, 2);
```

## BindTexture

```c++
static void BindTexture(bool multisampled, uint32_t id)
```

Binds the specified texture.

It takes the following parameters:

| Name          | Type     | Description                                                                 |
|---------------|----------|-----------------------------------------------------------------------------|
| multisampled  | bool     | A boolean that indicates whether the framebuffer is multisampled or not.    |
| id            | uint32_t | The ID of the texture to bind.                                              |

You can use it like this:
```c++
BindTexture(false, colorAttachment[0]);
```

## AttachColorTexture

```c++
static void AttachColorTexture(uint32_t id, int samples, GLenum format, GLenum attachment, uint32_t width, uint32_t height, int index)
```

Attaches the specified color texture to the specified framebuffer.

It takes the following parameters:

| Name          | Type     | Description                                                                 |
|---------------|----------|-----------------------------------------------------------------------------|
| id            | uint32_t | The ID of the texture to attach.                                            |
| samples       | int      | The number of samples of the texture.                                       |
| format        | GLenum   | The format of the texture.                                                  |
| attachment    | GLenum   | The attachment of the texture.                                              |
| width         | uint32_t | The width of the texture.                                                   |
| height        | uint32_t | The height of the texture.                                                  |
| index         | int      | The index of the texture.                                                   |

You can use it like this:
```c++
AttachColorTexture(colorAttachment[0], samples, GL_RGBA8, GL_COLOR_ATTACHMENT0, width, height, 0);
```

## AttachDepthTexture

```c++
static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachment, uint32_t width, uint32_t height)
```

Attaches the specified depth texture to the specified framebuffer.

It takes the following parameters:

| Name          | Type     | Description                                                                 |
|---------------|----------|-----------------------------------------------------------------------------|
| id            | uint32_t | The ID of the texture to attach.                                            |
| samples       | int      | The number of samples of the texture.                                       |
| format        | GLenum   | The format of the texture.                                                  |
| attachment    | GLenum   | The attachment of the texture.                                              |
| width         | uint32_t | The width of the texture.                                                   |
| height        | uint32_t | The height of the texture.                                                  |

You can use it like this:
```c++
AttachDepthTexture(depthAttachment, samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, width, height);
```

## IsDepthFormat

```c++
static bool IsDepthFormat(FrameBufferTextureFormat format)
```

Returns a boolean that indicates whether the specified format is a depth format or not.

It takes the following parameters:

| Name          | Type                       | Description                                                                 |
|---------------|----------------------------|-----------------------------------------------------------------------------|
| format        | FrameBufferTextureFormat   | The format to check.                                                        |

You can use it like this:
```c++
bool isDepth = IsDepthFormat(format);
```

## ExodiaFBTextureFormatToGL

```c++
static GLenum ExodiaFBTextureFormatToGL(FrameBufferTextureFormat format)
```

Returns the OpenGL format of the specified Exodia format.

It takes the following parameters:

| Name          | Type                       | Description                                                                 |
|---------------|----------------------------|-----------------------------------------------------------------------------|
| format        | FrameBufferTextureFormat   | The format to convert.                                                      |

You can use it like this:
```c++
GLenum glFormat = ExodiaFBTextureFormatToGL(format);
```

