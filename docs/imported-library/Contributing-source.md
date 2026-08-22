# Contributing to Echo of Elements

Thank you for helping build Echo of Elements. Contributions should improve the player experience while keeping the project understandable, stable, and practical to maintain.

## Before you start

Check existing issues and pull requests before beginning substantial work. For a new feature, system, refactor, or production task, open or update an issue first so the intended outcome and scope are visible to the team. Small documentation fixes and clearly scoped maintenance changes may proceed directly to a pull request.

Use the project’s approved Unreal Engine version and the documented toolchain. Do not commit generated output, local editor preferences, credentials, packaged builds, derived data, or assets that cannot be legally redistributed.

## Branches and commits

Create a focused branch from the repository’s default branch. Prefer names that communicate intent, such as `feature/elemental-reaction-system`, `fix/water-volume-crash`, or `docs/contributing-guide`.

Keep commits small and coherent. Use an imperative subject line and include the relevant issue reference when one exists. Avoid mixing unrelated formatting, asset, and gameplay changes in the same commit because it makes review and rollback more difficult.

## Pull requests

A pull request should include a concise summary of the problem and solution, the issue it addresses, the areas of the project it touches, and the validation performed. Include screenshots or short recordings when the change affects visuals, animation, UI, level flow, or player feedback.

Reviewers should be able to build or inspect the change without relying on unrecorded local setup. If a change requires a new plugin, engine setting, migration step, data asset, or manual editor action, document it in the pull request and in the appropriate project documentation.

## Unreal Engine guidelines

Use clear names for actors, components, assets, gameplay tags, data assets, and modules. Prefer data-driven configuration over duplicated Blueprint graphs or hard-coded values. Keep Blueprint logic readable, expose only intentional configuration points, and place reusable C++ behavior in the appropriate module rather than in level-specific code.

Do not modify engine source or project-wide settings without explaining the reason and the expected impact. Changes to input, rendering, physics, packaging, save data, or networking require extra validation because they can affect multiple systems and target platforms.

## Validation checklist

Before requesting review, confirm that the project opens with the approved engine version, the affected map or feature runs from a clean editor session, relevant automated or manual tests pass, and logs do not contain new errors or warnings that are attributable to the change. For performance-sensitive work, record the test context and the relevant measurement.

## Reporting bugs and proposing work

Use the bug template for reproducible defects and include the engine version, platform, reproduction steps, expected behavior, actual behavior, logs, and supporting media where available. Use the feature template for player-facing capabilities and explain the intended player value, acceptance criteria, and design or technical considerations. Use the task template for bounded engineering, content, documentation, or production work.

## Code of conduct

By participating in this project, you agree to follow [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). Questions about process should be raised in an issue or discussion using a respectful, specific description of the problem and the desired outcome.
