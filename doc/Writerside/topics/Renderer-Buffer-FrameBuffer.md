# FrameBuffer

The FrameBuffer part of the Buffer. It contains the classes that will be used to create frame buffers.

## FramebufferTextureFormat

The FramebufferTextureFormat is an enum that contains the different formats of a framebuffer texture.

It contains the following values:

- **None**
- **RGBA8**
- **RED_INTEGER**
- **DEPTH24STENCIL8**
- **Depth**

## FramebufferTextureSpecification

The FramebufferTextureSpecification is a struct that contains the data of a framebuffer texture specification.

It contains the following values:

| Name | Type | Description |
|------|------|-------------|
| TextureFormat | FramebufferTextureFormat | The texture format |

## FramebufferAttachmentSpecification

The FramebufferAttachmentSpecification is a struct that contains the data of a framebuffer attachment specification.

It contains the following values:

| Name | Type | Description |
|------|------|-------------|
| Attachments | std::vector<FramebufferTextureSpecification> | The attachments |

## FramebufferSpecification

The FramebufferSpecification is a struct that contains the data of a framebuffer specification.

It contains the following values:

| Name         | Type | Description |
|--------------|------|-------------|
| Width        | uint32_t | The width |
| Height       | uint32_t | The height |
| Attachements | FramebufferAttachmentSpecification | The framebuffer attachment specification |
| Samples      | uint32_t | The samples |
| SwapChainTarget | bool | The swap chain target |

## Framebuffer

The Framebuffer is a class that represents a framebuffer.

It contains the following methods:

### Create

```c++
static Ref<Framebuffer> Create(const FramebufferSpecification &spec);
```

It creates a new Framebuffer.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| spec | const FramebufferSpecification& | The framebuffer specification |

It can be used like this:

```c++
Ref<Framebuffer> framebuffer = Framebuffer::Create(spec);
```

### Bind

```c++
void Bind();
```

It binds the framebuffer.

It can be used like this:

```c++
framebuffer->Bind();
```

### Unbind

```c++
void Unbind();
```

It unbinds the framebuffer.

It can be used like this:

```c++
framebuffer->Unbind();
```

### Resize

```c++
void Resize(uint32_t width, uint32_t height);
```

It resizes the framebuffer.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| width | uint32_t | The width |
| height | uint32_t | The height |
    
It can be used like this:

```c++
framebuffer->Resize(100, 100);
```

### ReadPixel

```c++
int ReadPixel(uint32_t attachmentIndex, int x, int y);
```

It reads a pixel.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| attachmentIndex | uint32_t | The attachment index |
| x | int | The x |
| y | int | The y |

It can be used like this:

```c++
framebuffer->ReadPixel(0, 0, 0);
```

### ClearAttachment

```c++
void ClearAttachment(uint32_t attachmentIndex, int value);
```

It clears an attachment.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| attachmentIndex | uint32_t | The attachment index |
| value | int | The value |

It can be used like this:

```c++
framebuffer->ClearAttachment(0, 0);
```

### GetSpecification

```c++
const FramebufferSpecification &GetSpecification() const;
```

It returns the framebuffer specification.

It can be used like this:

```c++
const FramebufferSpecification& spec = framebuffer->GetSpecification();
```

### GetColorAttachmentRendererID

```c++
uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const;
```

It returns the color attachment renderer id.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| index | uint32_t | The index |

It can be used like this:

```c++
uint32_t id = framebuffer->GetColorAttachmentRendererID(0);
```


