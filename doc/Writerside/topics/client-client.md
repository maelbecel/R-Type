# Client

The client is the part of the game that is used by the player.

## Project

The `Client` contain a file with a `.proj` extension. This file is used to
configure the project.

It contains the following lines:

```text
Project:
  Name: R-Type
  StartScene: 7402922757700725494
  AssetsDirectory: "../Assets"
  AssetRegistryPath: "AssetRegistry.asset"
  ScriptsDirectory: "Scripts"
```

It has the following properties:

| Name                 | Description                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| Name                 | The name of the project.                                                     |
| StartScene           | The id of the scene to start with.                                           |
| AssetsDirectory      | The path to the assets directory.                                            |
| AssetRegistryPath    | The path to the asset registry.                                              |
| ScriptsDirectory     | The path to the scripts directory.                                           |

## R-Type

The R-Type is the main part of the client.

First we create the `RTypeClient` class. It will create an application using the R-Type layer.

```c++
        RTypeClient(const ApplicationSpecification &spec) : Application(spec) { PushLayer(new RType::RTypeLayer()); }
```

We also create an entry point `CreateApplication`, that will initialize the application.

```c++
    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        RType::InitRType();

        ApplicationSpecification spec;

        spec.Name = "Application Example";
        spec.CommandLineArgs = args;

        return new RTypeClient(spec);
    }
```

## R-Type Layer

The R-Type layer is the layer that will contain the game.
We can see all details [here](client-layer.md).