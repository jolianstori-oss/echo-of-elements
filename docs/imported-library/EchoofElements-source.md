# Echo of Elements

Echo of Elements is an Unreal Engine project focused on a responsive elemental world where exploration, environmental interaction, and player abilities are shaped by the relationships between fire, water, earth, and air.

> This repository is the source of truth for the project's game code, content, configuration, documentation, and build automation.

## Project status

The project is in active development. Features may change as the game design, technical architecture, and production priorities evolve.

| Area | Status |
| --- | --- |
| Engine | Unreal Engine 5.x |
| Target platforms | Windows first; additional platforms to be evaluated |
| Build automation | GitHub Actions skeleton for Windows |
| Contribution model | Issues, pull requests, and design discussions |

## Repository layout

```text
EchoOfElements/
├── Config/                  # Project and editor configuration
├── Content/                 # Unreal assets, maps, materials, blueprints, and data
├── Plugins/                 # Optional project plugins
├── Source/                  # C++ game and editor modules
├── .github/
│   ├── ISSUE_TEMPLATE/      # Standardized issue forms/templates
│   └── workflows/           # Continuous integration workflows
├── CODE_OF_CONDUCT.md
├── CONTRIBUTING.md
├── README.md
└── EchoOfElements.uproject
```

The exact Unreal Engine folders may appear progressively as project content is added. Generated directories such as `Binaries/`, `DerivedDataCache/`, `Intermediate/`, and `Saved/` should not be committed.

## Prerequisites

Development requires a supported Windows installation, the project’s selected Unreal Engine version, Visual Studio with the Desktop development with C++ workload, and the Windows SDK required by that engine version. Contributors should use the same engine version recorded by the project team to avoid incompatible generated files and build results.

## Getting started

Clone the repository, open `EchoOfElements.uproject` with the approved Unreal Engine version, allow the engine to generate project files, and build the editor target from Visual Studio. Before opening a pull request, verify that the relevant map or feature works in a clean editor session and that no generated files or local-only settings have been added.

## Development principles

Echo of Elements prioritizes readable and maintainable systems, data-driven gameplay, deterministic behavior where practical, intentional performance budgets, accessible player feedback, and small reviewable changes. New systems should include the documentation, tests, debug tooling, or reproduction steps needed for another contributor to understand and validate them.

## Issues and pull requests

Use the issue templates for bug reports, feature proposals, and engineering or production tasks. Pull requests should explain the problem, summarize the change, identify validation performed, and call out any content, configuration, performance, save compatibility, or platform implications.

Please read [CONTRIBUTING.md](CONTRIBUTING.md) before submitting work and follow the expectations in [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) when participating in project spaces.

## License

No license has been selected for this repository yet. Until a license is added by the project owner, all rights are reserved and the contents should not be redistributed or reused outside the project.
