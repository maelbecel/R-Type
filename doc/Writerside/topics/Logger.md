# Logger

The Logger part is used to manage the logger.

It defines multiple log macros:
- **EXODIA_CORE_TRACE(...)**  ::Exodia::Log::GetCoreLogger()->trace(__VA_ARGS__)
- **EXODIA_CORE_INFO(...)**  ::Exodia::Log::GetCoreLogger()->info(__VA_ARGS__)
- **EXODIA_CORE_WARN(...)**  ::Exodia::Log::GetCoreLogger()->warn(__VA_ARGS__)
- **EXODIA_CORE_ERROR(...)** ::Exodia::Log::GetCoreLogger()->error(__VA_ARGS__)
- **EXODIA_CORE_FATAL(...)** ::Exodia::Log::GetCoreLogger()->fatal(__VA_ARGS__)


It also defines the `Log` class.

## Init

```c++
    static void Init(const std::string &name = "Exodia");
```

It initializes the logger.

The method takes the following parameters:

| Name  | Type          | Description |
|-------|---------------|-------------|
| name  | std::string & | The name    |

Here is an example of how to use it:

```c++
std::string name;
Log::Init(name);
```

## GetCoreLogger

```c++
    static Ref<spdlog::logger> &GetCoreLogger();
```

It gets the core logger.

Here is an example of how to use it:

```c++
Ref<spdlog::logger> &logger = Log::GetCoreLogger();
```

## GetClientLogger

```c++
    static Ref<spdlog::logger> &GetClientLogger();
```

It gets the client logger.

Here is an example of how to use it:

```c++
Ref<spdlog::logger> &logger = Log::GetClientLogger();
```

