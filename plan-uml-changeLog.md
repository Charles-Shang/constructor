# Changes
1. In `Builder` Class, `calculatePoints()` 从 `void` 改到 `int`
2. In `Observer` Class, `~Observer()` 的return type应该什么都不写，删除了`void`
3. In `Subject` Class, `~Subject()` 的return type应该什么都不写，删除了`void`
4. In `Subject` Class, `observers` 这个field应该是**protected**，所以改了`#`