# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.5.0] - 2026-03-08

### Changed
- **Doxygen Documentation**: Upgraded all header files to use Doxygen-style comments.
- **og3 v0.5.0 Compatibility**: Updated to use the latest `og3` API, including `setDependencies` by reference.
- **Memory Optimization**: Moved OLED display string buffer to static storage to reduce stack usage.
- **Static Code Analysis**: Integrated `cppcheck` with targeted filters to focus on library source and ignore external dependencies.
- **License Headers**: Updated copyright year to 2026.
