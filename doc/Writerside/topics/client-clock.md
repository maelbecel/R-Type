# Clock

The Clock is the component that allow to manage time.

It has the following propertied:

- `float time` : The time of the clock.

## Constructor

```c++
        Clock(const Clock &) = default;
        Clock(float ElapsedTime = 0.0f) : ElapsedTime(ElapsedTime){};
```

The constructor of the Clock component initialize the properties of the component.

## Serialize

```c++
virtual void Serialize(YAML::Emitter &out) override {}
```

This function avoid the component to be serialzed on a yaml file.

## SerializeData

```c++
Exodia::Buffer SerializeData() override
```

The `SerializeData` function serialize the data of the component.

## DeserializeData

```c++
void DeserializeData(Exodia::Buffer data) override
```

The `DeserializeData` function deserialize the data of the component.

