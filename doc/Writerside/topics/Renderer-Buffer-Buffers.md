# Buffers

The Buffers part of the Buffer. It contains the classes that will be used to create buffers.

It defines new classes and functions:

## ShaderDataType

The ShaderDataType is an enum that contains the different types of data that can be used in a buffer.

It contains the following values:
    
- **Float** 
- **Float2**
- **Float3**
- **Float4**
- **Mat3**
- **Mat4**
- **Int**
- **Int2**
- **Int3**
- **Int4**
- **Bool**

## ShaderDataTypeSize

```c++
static uint32_t ShaderDataTypeSize(ShaderDataType type)
```

It returns the size of a ShaderDataType.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| type | ShaderDataType | The type |

It can be used like this:

```c++
uint32_t size = ShaderDataTypeSize(ShaderDataType::Float);
```

## BufferElement

The BufferElement is a struct that contains the data of a buffer element.

It contains the following values:

| Name | Type | Description |
|------|------|-------------|
| Name | std::string | The name |
| Type | ShaderDataType | The type |
| Size | uint32_t | The size |
| Offset | uint32_t | The offset |
| Normalized | bool | The normalized |

It also contains the following methods:

### GetComponentCount

```c++
uint32_t GetComponentCount() const;
```

It returns the component count.

It can be used like this:

```c++
uint32_t componentCount = bufferElement.GetComponentCount();
```

## BufferLayout

The BufferLayout is a class that contains the data of a buffer layout.

It contains the following methods:

### Constructor

```c++
BufferLayout() = default;
BufferLayout(const std::initializer_list<BufferElement> &elements);
```

It initializes a new BufferLayout.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| elements | const std::initializer_list\<BufferElement\>& | The elements |

It can be used like this:

```c++
BufferLayout bufferLayout = BufferLayout({
    { ShaderDataType::Float3, "a_Position" },
    { ShaderDataType::Float4, "a_Color" },
    { ShaderDataType::Float2, "a_TexCoord" },
});
```

### begin

```c++
std::vector<BufferElement>::iterator begin()
std::vector<BufferElement>::const_iterator begin()
```

It returns the begin iterator or the const begin iterator

It can be used like this:

```c++
std::vector<BufferElement>::iterator begin = bufferLayout.begin();
```

### end

```c++
std::vector<BufferElement>::iterator end()
std::vector<BufferElement>::const_iterator end()
```

It returns the end iterator or the const end iterator.

It can be used like this:

```c++
std::vector<BufferElement>::iterator end = bufferLayout.end();
```

### GetStride

```c++
uint32_t GetStride() const;
```

It returns the stride.

It can be used like this:

```c++
uint32_t stride = bufferLayout.GetStride();
```

### GetElements

```c++
const std::vector<BufferElement> &GetElements() const;
```

It returns the elements.

It can be used like this:

```c++
const std::vector<BufferElement> &elements = bufferLayout.GetElements();
```

## VertexBuffer

The VertexBuffer is a class that contains the data of a vertex buffer.

It contains the following methods:

### Create

```c++
static Ref<VertexBuffer> Create(uint32_t size);
static Ref<VertexBuffer> Create(float *vertices, uint32_t size);
```

It creates a new VertexBuffer.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| size | uint32_t | The size |
| vertices | float* | The vertices |

It can be used like this:

```c++
Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(100);
```

### Bind

```c++
virtual void Bind() const ;
```

It binds the VertexBuffer.

It can be used like this:

```c++
vertexBuffer->Bind();
```

### Unbind

```c++
virtual void Unbind() const;
```

It unbinds the VertexBuffer.

It can be used like this:

```c++
vertexBuffer->Unbind();
```

### SetLayout

```c++
virtual void SetLayout(const BufferLayout &layout);
```

It sets the layout.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| layout | const BufferLayout& | The layout |

It can be used like this:

```c++
vertexBuffer->SetLayout(layout);
```

### GetLayout

```c++
virtual const BufferLayout &GetLayout() const;
```

It returns the layout.

It can be used like this:

```c++
virtual const BufferLayout &layout = vertexBuffer->GetLayout();
```

### SetData

```c++
virtual void SetData(const void *data, uint32_t size);
```

It sets the data.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| data | const void* | The data |
| size | uint32_t | The size |

It can be used like this:

```c++
vertexBuffer->SetData(data, 100);
```

## IndexBuffer

The IndexBuffer is a class that contains the data of an index buffer.

It contains the following methods:

### Create {id=Create1}

```c++
static Ref<IndexBuffer> Create(uint32_t *indices, uint32_t count);
```

It creates a new IndexBuffer.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| indices | uint32_t* | The indices |
| count | uint32_t | The count |

It can be used like this:

```c++
Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 100);
```

### Bind {id=Bind1}

```c++
virtual void Bind() const;
```

It binds the IndexBuffer.

It can be used like this:

```c++
indexBuffer->Bind();
```

### Unbind {id=Unbind1}

```c++
virtual void Unbind() const;
```

It unbinds the IndexBuffer.

It can be used like this:

```c++
indexBuffer->Unbind();
```

### GetCount {id=GetCount1}

```c++
virtual uint32_t GetCount() const;
```

It returns the count.

It can be used like this:

```c++
uint32_t count = indexBuffer->GetCount();
```
