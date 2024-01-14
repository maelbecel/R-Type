# Health

The component that allow to manage health.

It has the following properties:

| Property        | Type  | Description               |
|-----------------|-------|---------------------------|
| `CurrentHealth` | `int` | The health of the entity. |
| `MaxHealth`     | `int` | The max health of entity. |

## Constructor

```c++
        Health(const Health &) = default;
        Health(int MaxHealth = 100) : CurrentHealth(CurrentHealth), MaxHealth(MaxHealth){};
```

It set the properties of the component

## SerializeData

```c++
Exodia::Buffer SerializeData() override
```

It serializes the data of the component.

## DeserializeData

```c++
void DeserializeData(Exodia::Buffer data) override
```

It deserializes the data of the component.

