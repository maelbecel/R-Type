# Utils

The Utils part of the ECS. It contains the classes that will be used to manage utils.

It uses the following `typedef`s :

| typedef | Name      | Description |
|---------|-----------|-------------|
| std::allocator\<Exodia::Entity\> | Allocator | The entity allocator |
| std::type_index | TypeIndex | The type index |

It contains the following functions:

## GetTypeIndex

```c++
template<typename T>
inline static TypeIndex GetTypeIndex()
```

It gets the type index of a type.

The function takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| T | typename | The type |

Here is an example of how to use it:

```c++
TypeIndex typeIndex = Utils::GetTypeIndex<Component>();
```

## demangle

```c++
inline static std::string demangle(const char *name)
```

It demangles a name.

The function takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | const char * | The name |

Here is an example of how to use it:

```c++
std::string name = Utils::demangle("name");
```

## extractTypeName

```c++
inline static std::string extractTypeName(const char *name)
```

It extracts the type name from a name.

The function takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | const char * | The name |

Here is an example of how to use it:

```c++
std::string name = Utils::extractTypeName("name");
```

## GetTypeName

```c++
template<typename T>
inline static std::string GetTypeName()
```

It gets the type name of a type.

The function takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| T | typename | The type |

Here is an example of how to use it:

```c++
std::string typeName = Utils::GetTypeName<Component>();
```

