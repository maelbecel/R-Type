# OpenGLTextureUtils

This module contains functions for loading textures into OpenGL.

## ExodiaImageFormatToGLDataFormat

```c++
static GLenum ExodiaImageFormatToGLDataFormat(Exodia::ImageFormat format);
```

It converts an Exodia::ImageFormat to a GLenum.

The method takes the following parameters:

| Name   | Type                     | Description          |
|--------|--------------------------|----------------------|
| format | Exodia::ImageFormat      | The image format     |

Here is an example of how to use it:

```c++
GLenum dataFormat = Exodia::OpenGLTextureUtils::ExodiaImageFormatToGLDataFormat(Exodia::ImageFormat::RGBA);
```

## ExodiaImageFormatToGLInternalFormat

```c++
static GLenum ExodiaImageFormatToGLInternalFormat(Exodia::ImageFormat format);
```

It converts an Exodia::ImageFormat to a GLenum.

The method takes the following parameters:

| Name   | Type                     | Description          |
|--------|--------------------------|----------------------|
| format | Exodia::ImageFormat      | The image format     |

Here is an example of how to use it:

```c++
GLenum internalFormat = Exodia::OpenGLTextureUtils::ExodiaImageFormatToGLInternalFormat(Exodia::ImageFormat::RGBA);
```
