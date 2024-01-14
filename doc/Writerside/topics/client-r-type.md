# R-Type

The R-Type file contain the function to initialize the R-Type.

```c++
inline static void InitRType()
```

We start by loading the project

```c++
        Ref<Exodia::Project> project = Exodia::Project::Load("./Client/R-Type.proj");
```

Then we register all the components.

```c++
        project->RegisterComponent("Health", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Health>(data);
        });

        project->RegisterComponent("Animation", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<RType::AnimationComponent>(data);
        });

        project->RegisterComponent("Clock", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Clock>(data);
        });
```

And finally, we register every script.

```c++
        project->RegisterScript("Star", []() -> Exodia::ScriptableEntity * { return new RType::Star(); });

        project->RegisterScript("PataPata", []() -> Exodia::ScriptableEntity * { return new PataPata(); });

        project->RegisterScript("BulletPlayer",
                                []() -> Exodia::ScriptableEntity * { return new RType::BulletPlayer(); });

        project->RegisterScript("BulletEnnemy",
                                []() -> Exodia::ScriptableEntity * { return new RType::BulletEnnemy(); });

        project->RegisterScript("Player", []() -> Exodia::ScriptableEntity * { return new RType::Player(); });
```


