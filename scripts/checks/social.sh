#!/usr/bin/env bash
# Advisory checks.  ALWAYS exit 0 or 78 — never fails the session.
#
# Check:
#   - No untracked files under asm/ (those should come from splat,
#     not from hand-edits).
#
# Exit codes:
#   0   no warnings
#   78  pass-with-warnings (dispatcher renders them inline)
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

warns=()

# --- no untracked files under asm/ -----------------------------------
if [[ "${GODHAND_ALLOW_GIT:-}" == 1 || "${GITHUB_ACTIONS:-}" == true ]] && [[ -d "$ROOT/.git" ]] && command -v git >/dev/null 2>&1; then
    untracked=$(git -C "$ROOT" ls-files --others --exclude-standard -- 'asm/' 2>/dev/null || true)
    if [[ -n "$untracked" ]]; then
        warns+=("untracked files under asm/ (asm/ should come from splat only):")
        while IFS= read -r f; do
            warns+=("    $f")
        done <<<"$untracked"
    fi
fi

if (( ${#warns[@]} > 0 )); then
    for w in "${warns[@]}"; do
        echo "WARN: $w"
    done
    exit 78
fi
exit 0
