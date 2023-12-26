# Math

The math part of the Game Engine. It contains the classes that will be used to do math.

The math namespace contain one method:

## DecomposeTransform

```c++
void DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
```

It decomposes the transform. By decomposing the transform, it means that it will separate the translation, rotation and scale of the transform.

It can be used like this:

```c++
glm::vec3 translation, rotation, scale;
Math::DecomposeTransform(transform, translation, rotation, scale);
```
