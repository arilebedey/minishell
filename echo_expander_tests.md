echo $A-X-$B | cat -e # → "-X-$"          (empty vars vanish, no spaces)
echo X$AX$B | cat -e         # → "X$" (nothing between, merged)
echo $A$B$C | cat -e         # → "$" (completely empty)
echo "$A$B$C" | cat -e       # → "$" (inside quotes, still empty arg)

echo $TORTUE $TORTUE | cat -e   # → "$" (just newline, no extra space!)
echo " $TORTUE " | cat -e       # → "  $" (quotes preserve spacing)
echo ' $TORTUE ' | cat -e       # → " $TORTUE $" (single quotes: no expansion)
echo "${TORTUE}ok" | cat -e # → "ok$"
echo "[$TORTUE]" | cat -e # → "[]$" (brackets stay together)

echo start$Xend | cat -e        # → "startend$"
echo "start$Xend" | cat -e      # → "startend$"

echo "$NONE:ok" | cat -e         # → ":ok$"
echo '$NONE:ok' | cat -e         # → "$NONE:ok$" (literal)

echo "$Z"$Z | cat -e # → "$" (one quoted empty + one unquoted empty = still one empty arg, kept)
echo "$Z"abc | cat -e # → "abc$"
echo "$Z""abc" | cat -e # → "abc$"
