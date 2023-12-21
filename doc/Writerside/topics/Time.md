# Time

The Time part of the Core. It contains the classes that will be used to manage time.
It contains the following parts:

- [**Timer**](#timer) : The Timer part of the Time. It contains the classes that will be used to manage timers.
- [**Timestep**](#timestep) : The Timestep part of the Time. It contains the classes that will be used to manage timesteps.

## Timer

The Timer class is used to manage timers.

### Constructor

```c++
Timer();
```

It creates a timer.

Here is an example of how to use it:

```c++
Timer timer;
```

### Reset

```c++
void Reset();
```

It resets the timer.

Here is an example of how to use it:

```c++
timer.Reset();
```

### Elapsed

```c++
float Elapsed() const;
```

It returns the elapsed time.

Here is an example of how to use it:

```c++
float elapsed = timer.Elapsed();
```

### ElapsedMillis

```c++
float ElapsedMillis() const;
```

It returns the elapsed time in milliseconds.

Here is an example of how to use it:

```c++
float elapsed = timer.ElapsedMillis();
```

## Timestep

The Timestep class is used to manage timesteps.

### Constructor {id=constructor_1}

```c++
Timestep(float time = 0.0f);
```

It creates a timestep.

The constructor takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| time | float | The time |

Here is an example of how to use it:

```c++
float time;
Timestep timestep(time);
```

### GetSeconds

```c++
float GetSeconds() const;
```

It returns the seconds.

Here is an example of how to use it:

```c++
float seconds = timestep.GetSeconds();
```

### GetMilliseconds

```c++

float GetMilliseconds() const;
```

It returns the milliseconds.

Here is an example of how to use it:

```c++
float milliseconds = timestep.GetMilliseconds();
```

