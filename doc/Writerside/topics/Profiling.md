# Profiling

The Profiling part is used to manage the profiling.

It defines multiple macros to manage the profiling :

- **EXODIA_PROFILE_BEGIN_SESSION(name, filepath)** ::Exodia::Instrumentor::Get().BeginSession(name, filepath)
- **EXODIA_PROFILE_END_SESSION()**               ::Exodia::Instrumentor::Get().EndSession()
- **EXODIA_PROFILE_SCOPE(name)**                   ::Exodia::InstrumentationTimer timer##__LINE__(name)
- **EXODIA_PROFILE_FUNCTION()**                    EXODIA_PROFILE_SCOPE(EXODIA_FUNC_SIG)

It provides structs to manage the profiling :

- **ProfileResult** : The ProfileResult struct of the Profiling. It contains the classes that will be used to manage the profiling results.
- **InstrumentationSession** : The InstrumentationSession struct of the Profiling. It contains the classes that will be used to manage the instrumentation sessions.

It also defines two classes to manage the profiling :

## Instrumentor

The Instrumentor class is used to manage the instrumentation.

### Constructor

```c++
Instrumentor();
```

It creates an instrumentor.

Here is an example of how to use it:

```c++
Instrumentor instrumentor;
```

### BeginSession

```c++
void BeginSession(const std::string &name, const std::string &filepath = "results.json");
```

It begins a session.

The method takes the following parameters:

| Name     | Type          | Description |
|----------|---------------|-------------|
| name     | std::string & | The name    |
| filepath | std::string & | The filepath|

Here is an example of how to use it:

```c++
std::string name;
std::string filepath;
instrumentor.BeginSession(name, filepath);
```

### EndSession

```c++
void EndSession();
```

It ends a session.

Here is an example of how to use it:

```c++
instrumentor.EndSession();
```

### WriteProfile

```c++
void WriteProfile(const ProfileResult &result);
```

It writes a profile.

The method takes the following parameters:

| Name   | Type              | Description |
|--------|-------------------|-------------|
| result | ProfileResult & | The result  |

Here is an example of how to use it:

```c++
ProfileResult result;
instrumentor.WriteProfile(result);
```

### WriteHeader

```c++
void WriteHeader();
```

It writes a header.

Here is an example of how to use it:

```c++
instrumentor.WriteHeader();
```

### WriteFooter

```c++
void WriteFooter();
```

It writes a footer.

Here is an example of how to use it:

```c++
instrumentor.WriteFooter();
```

### Get

```c++
static Instrumentor &Get();
```

It gets the instrumentor.

Here is an example of how to use it:

```c++
Instrumentor &instrumentor = Instrumentor::Get();
```

## InstrumentationTimer

The InstrumentationTimer class is used to manage the instrumentation timers.

### Constructor

```c++
InstrumentationTimer(const char *name);
```

It creates an instrumentation timer.

The constructor takes the following parameters:

| Name | Type      | Description |
|------|-----------|-------------|
| name | const char * | The name    |

Here is an example of how to use it:

```c++
const char *name;
InstrumentationTimer timer(name);
```

### Stop

```c++
void Stop();
```

It stops the timer.

Here is an example of how to use it:

```c++
timer.Stop();
```
