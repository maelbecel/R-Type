# Packet

The Packet class is used to represent a packet.

## Constructor

```c++
Packet();
```

It creates a packet.

Here is an example of how to use it:

```c++
Packet packet;
```

## setHeader

```c++
void setHeader(Header header);
```

It sets the header.

The method takes the following parameters:

| Name   | Type   | Description        |
|--------|--------|--------------------|
| header | Header | The header         |

Here is an example of how to use it:

```c++
Header header('c', 0, 0);
packet->setHeader(header);
```

## setContent

```c++
void setContent(std::vector<char> content);
```

It sets the content.

The method takes the following parameters:

| Name    | Type                 | Description        |
|---------|----------------------|--------------------|
| content | std::vector\<char\>& | The content        |

Here is an example of how to use it:

```c++
std::vector<char> content;
packet->setContent(content);
```

## set

```c++
void set(Header header, std::vector<char> content);
```

It sets the header and the content.

The method takes the following parameters:

| Name    | Type                 | Description        |
|---------|----------------------|--------------------|
| header  | Header               | The header         |
| content | std::vector\<char\>& | The content        |

Here is an example of how to use it:

```c++
Header header('c', 0, 0);
std::vector<char> content;
packet->set(header, content);
```

## GetBuffer

```c++
std::vector<char> GetBuffer() const
```

It returns the buffer of the packet.

Here is an example of how to use it:

```c++
std::vector<char> buffer = packet->GetBuffer();
```

## GetHeader

```c++
Header GetHeader()
```

It returns the header of the packet.

Here is an example of how to use it:

```c++
Header header = packet->GetHeader();
```

## GetSize

```c++
size_t GetSize()
```

It returns the size of the packet.

Here is an example of how to use it:

```c++
size_t size = packet->GetSize();
```