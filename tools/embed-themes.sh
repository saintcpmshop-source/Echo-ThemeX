#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."

OUT="src/embedded_themes.c"
rm -f "$OUT"

{
  echo '#include <stddef.h>'
  echo 'typedef struct { const char *name; const unsigned char *data; unsigned int len; } EmbeddedTheme;'
  echo ''

  idx=0
  for f in themes/*.p3t; do
    [ -f "$f" ] || continue
    xxd -i -n "theme_${idx}_data" "$f" >> "$OUT"
    idx=$((idx + 1))
  done

  echo ''
  echo 'EmbeddedTheme g_themes[] = {'
  idx=0
  for f in themes/*.p3t; do
    [ -f "$f" ] || continue
    name=$(basename "$f" .p3t)
    sz=$(stat -c%s "$f" 2>/dev/null || stat -f%z "$f")
    echo "  { \"${name}\", theme_${idx}_data, ${sz} },"
    idx=$((idx + 1))
  done
  echo '};'
  echo "int g_theme_count = ${idx};"
} > "$OUT"

echo "Generated $OUT with ${idx} themes"
