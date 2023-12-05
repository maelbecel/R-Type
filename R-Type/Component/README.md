# Components

## Description

Here is the repository where you will create all components for the R-Type project.

## Your first components

Components in ECS can be any data type, but generally they'll be a struct containing some plain old data. For now, let's define two components:
```cpp
struct Transform {
    glm::vec3 Translation;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    Transform(const Transform &) = default;
    Transform(const glm::vec3 &translation = glm::vec3(0.0f)) : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {};
};

struct Health {
    int CurrentHealth;
    int MaxHealth;

    Health(const Health &) = default;
    Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth) {};
};
```

Note that we don't have to do anything special for these structs to act as components, though there is the requirement for at least a default constructor.
