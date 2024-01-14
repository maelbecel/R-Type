# User

The `User` class is a class that represents a user.

## User

```c++
User::User(Connection &connection);
User::User(Connection &connection, Entity *pawn);
```

It constructs the user.

It takes the following parameters:

| Name       | Type         | Description |
|------------|--------------|-------------|
| connection | Connection&  | The connection |
| pawn       | Entity*      | The pawn      |

It can be used like this:

```c++
User user(connection);
```

```c++
User user(connection, pawn);
```


## GetConnection

```c++
Connection &GetConnection() const;
```

It gets the connection.

It returns a Connection&.

It can be used like this:

```c++
Connection &connection = user.GetConnection();
```

## SetConnection

```c++
void SetConnection(Connection &connection);
```

It sets the connection.

It takes the following parameters:

| Name       | Type         | Description |
|------------|--------------|-------------|
| connection | Connection&  | The connection |

It can be used like this:

```c++
user.SetConnection(connection);
```

## GetPawn

```c++
Entity *GetPawn() const;
```

It gets the pawn.

It returns an Entity*.

It can be used like this:

```c++
Entity *pawn = user.GetPawn();
```

## SetPawn


```c++
void SetPawn(Entity *pawn);
```

It sets the pawn.

It takes the following parameters:

| Name | Type     | Description |
|------|----------|-------------|
| pawn | Entity*  | The pawn    |

It can be used like this:

```c++
user.SetPawn(pawn);
```
