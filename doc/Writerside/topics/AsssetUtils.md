# Utils

The Utils part of the Asset is used to manage the assets.

## AssetType

```c++
    enum class AssetType : uint16_t {
        None      = 0,
        Scene     = 1,
        Texture2D = 2
        // TODO: Add more asset types
    };
```

The AssetType enum is used to define the asset type.

## AssetSpecification

```c++
    struct AssetSpecification {
        AssetType             Type = AssetType::None;
        std::filesystem::path Path;

        operator bool() const
        {
            return Type != AssetType::None;
        }
    };
```

The AssetSpecification struct is used to define the asset specification.

## AssetTypeToString

```c++
inline static std::string_view AssetTypeToString(AssetType type)
```

It converts an AssetType to a string.

The method takes the following parameters:

| Name | Type      | Description |
|------|-----------|-------------|
| type | AssetType | The asset type |

Here is an example of how to use it:

```c++
AssetType type = AssetType::Scene;
std::string_view typeString = AssetTypeToString(type);
```

## StringToAssetType

```c++
inline static AssetType StringToAssetType(const std::string_view &type)
```

It converts a string to an AssetType.

The method takes the following parameters:

| Name | Type          | Description |
|------|---------------|-------------|
| type | std::string_view | The string  |

Here is an example of how to use it:

```c++
std::string_view type = "AssetType::Scene";
AssetType assetType = StringToAssetType(type);
```


