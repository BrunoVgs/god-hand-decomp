#!/bin/sh
# Local: route nojcc tooling to the gh-decomp container (same Nix devShell, repo at /src).
exec "$(dirname "$0")/../x" "$@"
