# IOContextManager

The IOContextManager class is used to manage the IO context.

## Constructor

```c++
IOContextManager()
```

It creates an IO context manager.

Here is an example of how to use it:

```c++
IOContextManager ioContextManager;
```

## getIOContext

```c++
asio::io_context &getIOContext()
```

It returns the IO context.

Here is an example of how to use it:

```c++
asio::io_context &ioContext = ioContextManager.getIOContext();
```

## run

```c++
void run()
```

It runs the IO context.

Here is an example of how to use it:

```c++
ioContextManager.run();
```

## stop

```c++
void stop()
```

It stops the IO context.

Here is an example of how to use it:

```c++
ioContextManager.stop();
```
