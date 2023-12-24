# Vertex

The Vertex part of the Renderer. It contains the classes that will be used to create vertices.

It defines the class `VertexArray` with the following methods:

## Create

```c++
static Ref<VertexArray> Create();
```

It creates a vertex array.

It can be used like this:

```c++
Ref<VertexArray> vertexArray = VertexArray::Create();
```

## Bind

```c++
void Bind() const;
```

It binds the vertex array.

It can be used like this:

```c++
vertexArray->Bind();
```

## Unbind

```c++
void Unbind() const;
```

It unbinds the vertex array.

It can be used like this:

```c++
vertexArray->Unbind();
```

## AddVertexBuffer

```c++
void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer);
```

It adds a vertex buffer.

It takes the following parameters:

| Name         | Type                          | Description   |
|--------------|-------------------------------|---------------|
| vertexBuffer | const Ref\<VertexBuffer\>& | The vertex buffer |

It can be used like this:

```c++
vertexArray->AddVertexBuffer(vertexBuffer);
```

## SetIndexBuffer

```c++
void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer);
```

It sets the index buffer.

It takes the following parameters:

| Name        | Type                       | Description   |
|-------------|----------------------------|---------------|
| indexBuffer | const Ref\<IndexBuffer\>& | The index buffer |

It can be used like this:

```c++
vertexArray->SetIndexBuffer(indexBuffer);
```

## GetVertexBuffers

```c++
const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const;
```

It returns the vertex buffers.

It returns a const std::vector\<Ref\<VertexBuffer\>\>&.
    
It can be used like this:

```c++
std::vector<Ref<VertexBuffer>> vertexBuffers = vertexArray->GetVertexBuffers();
```

## GetIndexBuffer

```c++

const Ref<IndexBuffer> &GetIndexBuffer() const;
```

It returns the index buffer.

It returns a const Ref\<IndexBuffer\>&.

It can be used like this:

```c++
Ref<IndexBuffer> indexBuffer = vertexArray->GetIndexBuffer();
```

