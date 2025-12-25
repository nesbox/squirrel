## Changelog

- Fixed `clock` squirrel function incosistent behaviour across different platforms
- Fixed possible crashes in `dump` function due to lack of ref increment while traversing through the printed object
- Fixed skipping `instance members` while iterating over `class instance`.