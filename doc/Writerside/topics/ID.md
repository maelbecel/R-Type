# ID

The UUID class is used to manage IDs.

## Constructor

```c++
UUID(uint64_t uuid = 0);
UUID(const UUID &other);
```

It creates an ID.

The constructor takes the following parameters:

| Name  | Type     | Description |
|-------|----------|-------------|
| uuid  | uint64_t | The UUID    |
| other | UUID &   | The other ID|

Here is an example of how to use it:

```c++
UUID uuid;
UUID uuid(other);
```
