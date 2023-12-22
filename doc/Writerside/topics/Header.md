# Header

The header is the first thing that is generated when you run Exodia. It contains the following things:
It defines the following template:

```c++
template <typename T>
T swapEndianness(T value) {
    std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value) + sizeof(T));
    return value;
}
```

`swapEndianness` is used to swap the endianness of a value.

Here is an example of how to use it:

```c++
uint32_t value = 0x12345678;
std::cout << std::hex << value << std::endl;
value = swapEndianness(value);
std::cout << std::hex << value << std::endl;
```

## Constructor

```c++
Header(char command, unsigned long id, unsigned long size)
```

It creates a header.

The constructor takes the following parameters:

| Name    | Type          | Description        |
|---------|---------------|--------------------|
| command | char          | The command        |
| id      | unsigned long | The id             |
| size    | unsigned long | The size of packet |


Here is an example of how to use it:

```c++
Header header('c', 0, 0);
```

## fillBuffer

```c++
void fillBuffer(std::vector<char>& buffer) const
```

It fills the buffer with the header.

The method takes the following parameters:

| Name   | Type               | Description        |
|--------|--------------------|--------------------|
| buffer | std::vector<char>& | The buffer         |

Here is an example of how to use it:

```c++
std::vector<char> buffer;
header.fillBuffer(buffer);
```

## fillHeader

```c++
static Header fillHeader(const char *buffer)
```

It fills the header with the buffer.

The method takes the following parameters:

| Name   | Type     | Description        |
|--------|----------|--------------------|
| buffer | char*    | The buffer         |

Here is an example of how to use it:

```c++
Header header = Header::fillHeader(buffer);
```

## GetSize

```c++
static size_t GetSize()
```

It returns the size of the header.

Here is an example of how to use it:

```c++
std::cout << Header::GetSize() << std::endl;
```

## setSize

```c++
void setSize(unsigned long size)
```

It sets the size of the header.

The method takes the following parameters:

| Name | Type          | Description        |
|------|---------------|--------------------|
| size | unsigned long | The size of packet |

Here is an example of how to use it:

```c++
header.setSize(0);
```

## SetId

```c++
void SetId(unsigned long id)
```

It sets the id of the header.

The method takes the following parameters:

| Name | Type          | Description        |
|------|---------------|--------------------|
| id   | unsigned long | The id             |

Here is an example of how to use it:

```c++
header.SetId(0);
```

## getCommand

```c++
char getCommand() const
```

It returns the command of the header.

Here is an example of how to use it:

```c++
std::cout << header.getCommand() << std::endl;
```

## getTimestamp

```c++
float getTimestamp() const
```

It returns the timestamp of the header.

Here is an example of how to use it:

```c++
std::cout << header.getTimestamp() << std::endl;
```

## getId

```c++
unsigned long getId() const
```

It returns the id of the header.


Here is an example of how to use it:

```c++
std::cout << header.getId() << std::endl;
```

## getSize {id="getsize_1"}

```c++
unsigned long getSize() const
```

It returns the size of the header.

Here is an example of how to use it:

```c++
std::cout << header.getSize() << std::endl;
```
