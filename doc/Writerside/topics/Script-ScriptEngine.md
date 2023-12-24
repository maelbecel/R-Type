# ScriptEngine

The ScriptEngine part of the Script. It contains the classes that will be used to create the script engine.

It defines the class ScriptEngine with the following methods:

## ScriptEngineData

The ScriptEngineData part of the ScriptEngine is a struct that contains the data of the script engine.

It defines the struct ScriptEngineData with the following fields:

| Name | Type | Description |
|------|------|-------------|
| ScriptableEntities | std::vector\<std::string\> | The scriptable entities |


## Init

```c++
static void Init();
```

It initializes the script engine.

It can be used like this:

```c++
ScriptEngine::Init();
```

## Shutdown

```c++
static void Shutdown();
```

It shuts down the script engine.

It can be used like this:

```c++
ScriptEngine::Shutdown();
```

## InstantiateScript

```c++
static ScriptableEntity *InstantiateScript(const std::string &name);
```

It instantiates a script.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | const std::string& | The name    |

It returns a ScriptableEntity*.

It can be used like this:

```c++
ScriptableEntity *scriptableEntity = ScriptEngine::InstantiateScript(name);
```

## GetScriptableEntity

```c++
static std::vector<std::string> GetScriptableEntities();
```

It gets the scriptable entities.

It returns a std::vector\<std::string\>.


It can be used like this:

```c++
std::vector<std::string> scriptableEntities = ScriptEngine::GetScriptableEntities();
```
