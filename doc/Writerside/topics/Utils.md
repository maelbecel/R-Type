# Utils

## [Assert](https://github.com/maelbecel/R-Type/blob/main/GameEngine/src/Utils/Assert.hpp)

### Explanation {id="explanation_assert"}

The Assert class is used to check if a condition is true. If the condition is false, it will throw an exception.

The file includes another header file, `Debug/Logs.hpp`, which is likely to contain logging utilities used in the assertion macros.

The `EXODIA_DEBUGBREAK()` macro is defined differently based on the compiler being used. If the Microsoft Visual C++ compiler (`_MSC_VER`) is being used, it uses the `__debugbreak()` function, which causes a breakpoint where the debugger stops execution of the program. If the GNU C Compiler (`__GNUC__`) or Clang (`__clang__`) is being used, it uses the `__builtin_trap()` function, which generates a trap, causing the program to exit abnormally. If none of these compilers are being used, it generates a compiler error.

The `EXODIA_ASSERT(x, ...)` and `EXODIA_CORE_ASSERT(x, ...)` macros are defined if `EXODIA_ENABLE_ASSERTS` is not defined. These macros check if the condition `x` is false. If it is, they log an error message using `EXODIA_ERROR` or `EXODIA_CORE_ERROR` (presumably defined in `Debug/Logs.hpp`), and then trigger a debug break using `EXODIA_DEBUGBREAK()`. This allows the developer to inspect the state of the program at the point of the assertion failure.

If `EXODIA_ENABLE_ASSERTS` is defined, the `EXODIA_ASSERT(x, ...)` and `EXODIA_CORE_ASSERT(x, ...)` macros are defined as empty, effectively disabling the assertion checks. This is likely intended for release builds of the software, where performance is more important and the developer doesn't want the overhead of assertion checks.

### Usage {id="usage_assert"}

You can use the `EXODIA_ASSERT(x, ...)` and `EXODIA_CORE_ASSERT(x, ...)` macros to check if a condition is true. If the condition is false, it will log an error message and trigger a debug break.

```c++
EXODIA_ASSERT(x == 5, "x must be 5!");
EXODIA_CORE_ASSERT(x == 5, "x must be 5!");
```

## [CrossPlatform](https://github.com/maelbecel/R-Type/blob/main/GameEngine/src/Utils/CrossPlatform.hpp)

### Explanation {id="explanation_crossplatform"}


The first section of the code is a preprocessor directive that checks if the code is being compiled on a Windows platform. This is done by checking if the `_WIN32` or `_WIN64` macros are defined, which are automatically defined by the compiler on Windows platforms. If the code is being compiled on a Windows platform, it includes the `windows.h` header file and defines `EXODIA_EXPORT` as `extern "C" __declspec(dllexport)`. The `extern "C"` part is used to specify C linkage, which can help avoid name-mangling issues when the code is linked with C programs. The `__declspec(dllexport)` part is specific to Windows and is used to export functions or variables from a DLL.

If the code is not being compiled on a Windows platform, it simply defines `EXODIA_EXPORT` as `extern "C"`, again specifying C linkage.

The second section of the code defines a macro `EXODIA_FUNC_SIG` that is used to get the signature of the current function. The code checks which compiler is being used and defines `EXODIA_FUNC_SIG` accordingly. For example, if the GNU C++ compiler (GCC) is being used, `EXODIA_FUNC_SIG` is defined as `__PRETTY_FUNCTION__`, which is a GCC-specific macro that returns a string representing the name and signature of the current function. If the code is being compiled with Visual Studio, `EXODIA_FUNC_SIG` is defined as `__FUNCSIG__`, which is a Visual Studio-specific macro that does the same thing. The code provides similar definitions for other compilers as well.

If the compiler being used is not recognized, `EXODIA_FUNC_SIG` is defined as a string `"EXODIA_FUNC_SIG unknown!"`.

This header file is designed to be included in other source files of the `ExodiaGameEngine` project. By using the `EXODIA_EXPORT` and `EXODIA_FUNC_SIG` macros defined in this file, the other source files can achieve cross-platform compatibility and get the current function's signature in a compiler-independent way.


### Usage {id="usage_crossplatform"}

You can use the `EXODIA_EXPORT` macro to export functions or variables from a DLL. For example:

```c++
EXODIA_EXPORT void foo();
EXODIA_EXPORT int bar = 5;
```

You can use the `EXODIA_FUNC_SIG` macro to get the signature of the current function. For example:

```c++
std::cout << EXODIA_FUNC_SIG << std::endl;
```

## [LibraryLoader](https://github.com/maelbecel/R-Type/blob/main/GameEngine/src/Utils/LibraryLoader.hpp)

### Explanation {id="explanation_libraryloader"}

This file defines a class `LibraryLoader` within the namespace `Exodia`. The `LibraryLoader` class is designed to load dynamic libraries (also known as shared libraries) at runtime. This is a common technique used in plugin architectures, where the main application doesn't need to know in advance all the code it will execute, allowing for modularity and extensibility.

The class has three static methods:

#### Load

Loads a dynamic library from the specified path and returns a handle to the library.

```c++
static void *Load(const std::string &path);
```

It takes the following parameters:

| Name   | Type                  | Description                              |
|--------|-----------------------|------------------------------------------|
| `path` | `const std::string &` | The path to the dynamic library to load. |

#### GetFunction
Gets a function pointer from the specified library handle.

```c++
static void *GetFunction(void *handle, const std::string &name);
```

It takes the following parameters:

| Name     | Type                  | Description                              |
|----------|-----------------------|------------------------------------------|
| `handle` | `void *`              | The handle to the dynamic library.       |
| `name`   | `const std::string &` | The name of the function to get.         |

#### Close
Closes the specified library handle.

```c++
static void Close(void *handle)
```

It takes the following parameters:

| Name     | Type     | Description                              |
|----------|----------|------------------------------------------|
| `handle` | `void *` | The handle to the dynamic library.       |


### Usage {id="usage_libraryloader"}

You can use the `LibraryLoader` class to load dynamic libraries at runtime. For example:

```c++
void *handle = LibraryLoader::Load("my_library.dll");
void *func = LibraryLoader::GetFunction(handle, "my_function");
LibraryLoader::Close(handle);
```

## [Memory](https://github.com/maelbecel/R-Type/blob/main/GameEngine/src/Utils/Memory.hpp)

### Explanation {id="explanation_memory"}

`Memory.hpp`, provides a set of utilities for memory management and bit manipulation.

The `BIT(x)` macro is a bitshift operator that shifts the bit to the left by `x`. This is a common operation when dealing with bitwise operations. For example, `BIT(0)` would result in `0000 0001`, `BIT(1)` would result in `0000 0010`, and so on.

The `UNUSED` macro is defined using the `__attribute__((unused))` GCC attribute. This is used to suppress compiler warnings about variables that are declared but not used in the code.

The `Ref` template is a type alias for `std::shared_ptr<T>`, where `T` is a placeholder for any type. `std::shared_ptr` is a smart pointer that retains shared ownership of an object through a pointer. Several `shared_ptr` objects may own the same object, and the object is destroyed when the last `shared_ptr` is destroyed.

The `CreateRef` function template creates a `Ref` (or `std::shared_ptr`) to an object of type `T`. It uses perfect forwarding to forward its arguments to the constructor of `T`.

Similarly, the `Scope` template is a type alias for `std::unique_ptr<T>`, a smart pointer that owns and manages another object through a pointer and disposes of that object when the `unique_ptr` goes out of scope.

The `CreateScope` function template creates a `Scope` (or `std::unique_ptr`) to an object of type `T`. It uses perfect forwarding to forward its arguments to the constructor of `T`.

Finally, the `Memcopy` function is a simple wrapper around the `memcpy` function from the C standard library. It copies `n` bytes from the object pointed to by `src` to the object pointed to by `dest`. It's declared as `inline static`, which suggests that the function has internal linkage (i.e., it's only visible within its translation unit) and is recommended to be inlined for performance reasons.

### Usage {id="usage_memory"}

You can use the `BIT(x)` macro to shift a bit to the left by `x`. For example:

```c++
int x = BIT(0); // x = 0000 0001
int y = BIT(1); // y = 0000 0010
```


You can use the `Ref` and `Scope` type aliases to create smart pointers to objects. For example:

```c++
Ref<Foo> foo = CreateRef<Foo>();
Scope<Bar> bar = CreateScope<Bar>();
```

You can use the `Memcopy` function to copy bytes from one object to another. For example:

```c++
int src = 5;
int dest = 0;
Memcopy(&src, &dest, sizeof(int));
```

## [PlatformUtils](https://github.com/maelbecel/R-Type/blob/main/GameEngine/src/Utils/PlatformUtils.hpp)

### Explanation {id="explanation_platformutils"}

`PlatformUtils.hpp` provides a set of utilities for platform-specific operations.
It defines two classes:

#### FileDialog

The `FileDialog` class is used to open a file. It has two static methods:

- *OpenFile*
  ```c++
  static std::string OpenFile(const char *filter);
  ```
  Opens a file dialog and returns the path to the selected file.

  It takes the following parameters:

  | Name     | Type         | Description                                                                 |
  |----------|--------------|-----------------------------------------------------------------------------|
  | `filter` | `const char` | A filter to apply to the file dialog. For example, `"Text Files (*.txt)\0"` |

- *SaveFile*
  ```c++
  static std::string SaveFile(const char *filter);
  ```
  Opens a save file dialog and returns the path to the selected file.

  It takes the following parameters:

  | Name     | Type         | Description                                                                 |
  |----------|--------------|-----------------------------------------------------------------------------|
  | `filter` | `const char` | A filter to apply to the file dialog. For example, `"Text Files (*.txt)\0"` |

#### Time

The `Time` class is used to get the current time. It has one static methods:

```c++
static float GetTime();
```

Returns the current time in seconds.

### Usage {id="usage_platformutils"}

You can use the `FileDialog` class to open a file dialog and get the path to the selected file. For example:

```c++
std::string path = FileDialog::OpenFile("Text Files (*.txt)\0");
```

To open a save file dialog, use the `SaveFile` method instead.

```c++
std::string path = FileDialog::SaveFile("Text Files (*.txt)\0");
```

You can use the `Time` class to get the current time. For example:

```c++
float time = Time::GetTime();
```

