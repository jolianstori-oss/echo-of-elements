#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT_FILE="$PROJECT_ROOT/EchoOfElements.uproject"

if [[ -z "${UE_ROOT:-}" ]]; then
  echo "Set UE_ROOT to the Unreal Engine 5.8 installation directory first."
  echo "Example: export UE_ROOT=/opt/UnrealEngine"
  exit 1
fi

if [[ ! -f "$PROJECT_FILE" ]]; then
  echo "Project file not found: $PROJECT_FILE" >&2
  exit 1
fi

UBT="$UE_ROOT/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh"
if [[ ! -x "$UBT" ]]; then
  echo "GenerateProjectFiles.sh was not found at: $UBT" >&2
  exit 1
fi

exec "$UBT" "$PROJECT_FILE" "$@"
