# og3x-oled Development Mandates

This is an extension library for the `og3` framework. It must adhere to the core standards defined in the main `og3` repository.

## Coding Standards
- **Naming**: Follow `og3` conventions: `camelCase` methods, `snake_case` locals, `m_` prefix for private members.
- **Documentation**: All public/protected members in headers MUST use Doxygen-style comments.
- **Namespaces**: Use the `og3::` namespace.

## Architecture & Integration
- **Dependency Management**: Use `HADependencies` or `HADependenciesArray` when integrating with WiFi/MQTT features of `og3`.
- **Module System**: All features must be implemented as `og3::Module` subclasses.
- **Memory Management**:
  - Minimize stack usage for ESP8266 compatibility.
  - Prefer `static` buffers for fixed-size display strings over local arrays.

## Quality
- **CHANGELOG**: Maintain a `CHANGELOG.md` following the [Keep a Changelog](https://keepachangelog.com/) format.
- **Compatibility**: Ensure the library remains compatible with both ESP32 and ESP8266 platforms.
