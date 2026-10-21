#!/usr/bin/env bash
# Inside the persistent container: nix.conf once, cached dev env, then the
# requested command. stdout/stderr of the command are not redirected.
set -euo pipefail

if [[ $# -lt 1 ]]; then
    echo "container_bootstrap: missing dev-env hash" >&2
    exit 2
fi

hash="$1"
shift

mkdir -p /etc/nix /nix/var/godhand
conf=/etc/nix/nix.conf
touch "$conf"
while IFS= read -r line; do
    grep -qxF "$line" "$conf" || printf '%s\n' "$line" >> "$conf"
done << 'EOF'
sandbox = false
filter-syscalls = false
experimental-features = nix-command flakes
EOF

cache="/nix/var/godhand/dev-env-${hash}.sh"
if [[ ! -s "$cache" ]]; then
    flake_root="/nix/var/godhand/flake-${hash}"
    rm -rf "$flake_root"
    mkdir -p "$flake_root/patches"
    cp flake.nix flake.lock "$flake_root/"
    cp -R patches/ee-as "$flake_root/patches/"
    nix print-dev-env "path:${flake_root}" > "${cache}.tmp"
    mv "${cache}.tmp" "$cache"
fi

set +u
# shellcheck disable=SC1090
source "$cache"
set -u
cd /src
exec bash scripts/container_env.sh "$@"
