# WindowsFileDialog

The file dialog part of the Game Engine. It contains the classes that will be used to open file dialogs.

## OpenFile

```c++
static std::string FileDialog::OpenFile(const char *filter);
```

It opens a file dialog.

The function takes the following parameters:

| Name   | Type       | Description          |
|--------|------------|----------------------|
| filter | const char | The filter of the file dialog |

Here is an example of how to use it:

```c++
std::string file = Exodia::WindowsFileDialog::OpenFile("All Files (*.*)\0*.*\0");
```

## SaveFile

```c++
static std::string FileDialog::SaveFile(const char *filter);
```

It opens a file dialog.

The function takes the following parameters:

| Name   | Type       | Description          |
|--------|------------|----------------------|
| filter | const char | The filter of the file dialog |


Here is an example of how to use it:

```c++
std::string file = Exodia::WindowsFileDialog::SaveFile("All Files (*.*)\0*.*\0");
```
