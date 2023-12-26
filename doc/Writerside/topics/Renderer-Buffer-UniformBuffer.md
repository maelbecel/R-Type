# UniformBuffer

The UniformBuffer part of the Buffer. It contains the classes that will be used to create uniform buffers.
A uniform buffer is a buffer that will be used to store uniform data.

## Create

```c++
static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
```

It creates a uniform buffer.

It use the following parameters:

| Name    | Type     | Description |
|---------|----------|-------------|
| size    | uint32_t | The size    |
| binding | uint32_t | The binding |

It can be used like this:

```c++
Ref<UniformBuffer> uniformBuffer = UniformBuffer::Create(size, binding);
```

## SetData

```c++
virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) = 0;
```

It sets the data.

It takes the following parameters:

| Name   | Type     | Description |
|--------|----------|-------------|
| data   | const void* | The data    |
| size   | uint32_t | The size    |
| offset | uint32_t | The offset  |

It can be used like this:

```c++
uniformBuffer->SetData(data, 100);
```