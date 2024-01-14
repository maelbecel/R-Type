# Animation

The Animation component is used to animate sprites.

It has multiple properties :

| Property            | Type                                         | Description                         |
|---------------------|----------------------------------------------|-------------------------------------|
| `Frames`            | `std::vector\<Ref\<Exodia::SubTexture2D\>\>` | The frames of the animation.        |
| `IsPlaying`         | `bool`                                       | If the animation is playing.        |
| `Repeat`            | `bool`                                       | If the animation should repeat.     |
| `FrameRate`         | `float`                                      | The frame rate of the animation.    |
| `FrameTimer`        | `float`                                      | The frame timer of the animation.   |
| `CurrentFrameIndex` | `int`                                        | The current frame of the animation. |

## Constructor

```c++
        AnimationComponent(const AnimationComponent &other)
            : Frames(other.Frames), IsPlaying(other.IsPlaying), Repeat(other.Repeat), FrameRate(other.FrameRate),
              FrameTimer(other.FrameTimer), CurrentFrameIndex(other.CurrentFrameIndex){};

        AnimationComponent(const std::vector<Ref<Exodia::SubTexture2D>> &frames = {})
            : Frames(frames), IsPlaying(false), Repeat(false), FrameRate(0.0f), FrameTimer(0.0f),
              CurrentFrameIndex(0){};
```

The constructor of the Animation component initialize the properties of the component.

## DeserializeData

```c++
void DeserializeData(Exodia::Buffer data)
```

The `DeserializeData` function deserialize the data of the component.

## SerializeData

```c++
Exodia::Buffer SerializeData()
```

The `SerializeData` function serialize the data of the component.


