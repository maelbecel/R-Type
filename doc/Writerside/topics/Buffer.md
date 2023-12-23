# Buffer

The Buffer class is used to manage buffers.

It contains the following parts:
- [**Buffer**](#buffer) : The Buffer part of the Buffer. It contains the classes that will be used to manage buffers.
- [**ScopedBuffer**](#scopedbuffer) : The ScopedBuffer part of the Buffer. It contains the classes that will be used to manage scoped buffers.


## Buffer

The Buffer struct is used to manage buffers.

### Constructor

```c++
Buffer();
Buffer(uint64_t size);
Buffer(const void *data, uint64_t size);
Buffer(const Buffer &other);
```

It creates a buffer.

The constructor takes the following parameters:

| Name   | Type         | Description      |
|--------|--------------|------------------|
| size   | uint64_t     | The buffer size  |
| data   | const void * | The buffer data  |
| other  | Buffer &     | The other buffer |

Here is an example of how to use it:

```c++
Buffer buffer;
Buffer buffer(10);
Buffer buffer(data, 10);
Buffer buffer(other);
```

### Copy

```c++
static Buffer Copy(const Buffer &other);
```

It copies a buffer.

The method takes the following parameters:

| Name   | Type         | Description      |
|--------|--------------|------------------|
| other  | Buffer &     | The other buffer |

Here is an example of how to use it:

```c++
Buffer other;
Buffer buffer = Buffer::Copy(other);
```

### Allocate

```c++
void Allocate(uint64_t size);
```

It allocates a buffer.

The method takes the following parameters:

| Name   | Type         | Description      |
|--------|--------------|------------------|
| size   | uint64_t     | The buffer size  |

Here is an example of how to use it:

```c++
Buffer buffer;
buffer.Allocate(10);
```

### Release

```c++
void Release();
```

It releases a buffer.

Here is an example of how to use it:

```c++
Buffer buffer;
buffer.Release();
```

### As

```c++
template <typename T>
T *As();
```

It casts the buffer to a type.

The method takes the following parameters:

| Name   | Type         | Description      |
|--------|--------------|------------------|
| T      | typename     | The type         |

Here is an example of how to use it:

```c++
Buffer buffer;
float *data = buffer.As<float>();
```

## ScopedBuffer

The ScopedBuffer struct is used to manage scoped buffers.

### Constructor {id=constructor_1}

```c++
ScopedBuffer(Buffer buffer);
ScopedBuffer(uint64_t size);
```

It creates a scoped buffer.

The constructor takes the following parameters:

| Name   | Type         | Description      |
|--------|--------------|------------------|
| buffer | Buffer       | The buffer       |
| size   | uint64_t     | The buffer size  |

Here is an example of how to use it:

```c++
Buffer buffer;
ScopedBuffer scopedBuffer(buffer);
ScopedBuffer scopedBuffer(10);
```

### Data

```c++
uint8_t *Data();
```

It gets the buffer data.

Here is an example of how to use it:

```c++
ScopedBuffer scopedBuffer;
uint8_t *data = scopedBuffer.Data();
```

### Size

```c++
uint64_t Size();
```

It gets the buffer size.

Here is an example of how to use it:

```c++
ScopedBuffer scopedBuffer;
uint64_t size = scopedBuffer.Size();
```

### As {id=as_1}

```c++
template <typename T>
T *As();
```

It casts the buffer to a type.

The method takes the following parameters:

| Name   | Type         | Description      |
|--------|--------------|------------------|
| T      | typename     | The type         |

Here is an example of how to use it:

```c++
ScopedBuffer scopedBuffer;
float *data = scopedBuffer.As<float>();
```

